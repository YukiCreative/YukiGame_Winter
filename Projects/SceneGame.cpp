#include "Camera.h"
#include "ColliderTestScene.h"
#include "game.h"
#include "HPUI.h"
#include "ImageObject.h"
#include "Input.h"
#include "MapSystem.h"
#include "Music.h"
#include "ObjectKind.h"
#include "ObjectsController.h"
#include "Player.h"
#include "SceneController.h"
#include "SceneGame.h"
#include "SceneGameover.h"
#include "ScenePause.h"
#include "ScreenFade.h"
#include "SoundManager.h"
#include "Statistics.h"
#include "TileImage.h"
#include "Time.h"
#include <cassert>
#include <DxLib.h>
#include "CoinUI.h"
#include "TimeUI.h"
#include "Image.h"

namespace
{
	const Vector2 kScreenMiddlePos(Game::kScreenHalfWidth, Game::kScreenHalfHeight);
	//                                          ↓PlatinumのX  ↓〃Y
	const Vector2 Stage1PlayerInitPos = { 80 * (3 - 8), 80 * (35 - 5) };
	const Vector2 Stage2PlayerInitPos = { 80 * (3 - 8), 80 * (8 - 5) };
	const Vector2 Stage3PlayerInitPos = { 80 * (6 - 8), 80 * (125 - 5) };
	const Vector2 kInitHpUIPos   = { kScreenMiddlePos.x - 256, kScreenMiddlePos.y + 300 };
	const Vector2 kCoinUIInitPos = { 50, 50 };
	const Vector2 kTimeUIInitPos = { 275, 50 };
	const Vector2 kHowToPlayPos = { Game::kScreenWidth - 100, 100 };
	constexpr float kHowToPlayExRate = 0.5f;
	const std::string kStage1Pass = "Data/MapData/Stage1.fmf";
	const std::string kStage2Pass = "Data/MapData/Stage2.fmf";
	const std::string kStage3Pass = "Data/MapData/Stage3.fmf";
	const std::string kBackGroundPass  = "Marine.jpg";
	const std::string kBackGroundTile  = "WaterBackWallTile.png";
	const std::string kHowToPlayFile = "HowToPlay.png";

	const std::string kPausesound = "Pause.mp3";
	const std::string kNormalStageBGM = "Data/Music/NormalStage.wav";
	const std::string kStage3BGM = "Data/Music/Stage3.mp3";
}

Stages SceneGame::s_nowStage = Stages::kStage1;

void SceneGame::MapChangeUpdate()
{
	m_fade.Update();
	// プレイヤーのアニメションだけ実行したい
	m_player->AnimationUpdate();

	if (m_fade.IsFading()) return;

	m_objectCont->ClearObjects();
	ChangeMap(m_nextMapPath, m_playerTransportPos);
	m_fade.Fade(60, 0);
	// 枠に収める
	m_camera->FitMap();
	m_isMapChanging = false;
}

void SceneGame::HitStopUpdate()
{
	// ゲームの更新は行わないが、カメラと、マップチップの更新はしたい
	m_camera->Update();
	m_map->Update();
}

SceneGame::SceneGame() :
	m_frameCount(0),
	m_nextMapPath(),
	m_playerTransportPos(),
	m_isMapChanging(false),
	m_stopFrame(0)
{
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	m_hpUI = std::make_shared<HitPoints>(kInitHpUIPos);
	m_coinUI = std::make_shared<CoinUI>(kCoinUIInitPos);
	m_timeUI = std::make_shared<TimeUI>(kTimeUIInitPos);
	m_player = std::make_shared<Player>(*m_camera, Vector2::Zero(), *m_hpUI);
	m_objectCont = std::make_shared<ObjectsController>(*m_camera, *m_player);
	m_map = std::make_shared<MapSystem>();
	m_imageHowToPlay = std::make_shared<Image>(kHowToPlayFile);
	m_imageHowToPlay->SetExRate(kHowToPlayExRate);

	// 今の進行度に応じて読み込むマップを変える
	// switch
	switch (s_nowStage)
	{
	case Stages::kStage1:
		m_map->InitMap(*m_camera, kStage1Pass, *m_objectCont);
		m_player->Teleportation(Stage1PlayerInitPos);
		m_camera->Move(Stage1PlayerInitPos);
		break;
	case Stages::kStage2:
		m_map->InitMap(*m_camera, kStage2Pass, *m_objectCont);
		m_player->Teleportation(Stage2PlayerInitPos);
		m_camera->Move(Stage2PlayerInitPos);
		break;
	case Stages::kStage3:
		m_map->InitMap(*m_camera, kStage3Pass, *m_objectCont);
		m_player->Teleportation(Stage3PlayerInitPos);
		m_camera->Move(Stage3PlayerInitPos);
		break;
	default:
		assert(false && "よくわからんステージが読み込まれた");
		break;
	}

	// そもそも参照で取らなきゃよかった
	m_player->Init(m_map, m_objectCont);
	m_camera->SetFollowObject(m_player);
	m_camera->SetMapSize(m_map->GetMapSize());
	m_objectCont->ResetObjectSpawnStatus(*m_map);
	m_camera->FitMap();
}

void SceneGame::GameClear()
{
	SceneChangeWithFadeOut("Clear");
}

void SceneGame::GameOver()
{
	// 今ステージのスコアは無効
	Statistics::GetInstance().ResetNowStageScore();
	// ここでポーズを開いた(フェードの色が変わっている)想定をしないといけないのが不服
	m_fade.SetColor(0x000000);
	SceneChangeWithFadeOut("Gameover", 120);
}

void SceneGame::ChangeMapWithFadeOut(const Stages stage, const std::string& path, const Vector2& playerTransferPos)
{
	Statistics::GetInstance().SaveScore();
	// 与えられた情報を覚えておく
	s_nowStage = stage;
	m_nextMapPath = path;
	m_playerTransportPos = playerTransferPos;

	m_fade.Fade(60, 100);
	m_player->Stop();

	// 自分はフェード待ち状態へ移行
	// フラグ管理はほんとはしたくなかった
	m_isMapChanging = true;
}

void SceneGame::ChangeMap(const std::string& path)
{
	m_map->ChangeMapData(path, *m_objectCont);
	m_camera->SetMapSize(m_map->GetMapSize());
}

void SceneGame::ChangeMap(const std::string& path, const Vector2& playerTransferPos)
{
	// BGMを変える
	// 場所がよくないのは分かっている
	if (path == kStage3Pass)
	{
		Music::GetInstance().Play(kStage3BGM);
	}

	// プレイヤーとカメラの位置を変更
	m_player->Teleportation(playerTransferPos);
	m_camera->Teleport(playerTransferPos);
	// 別のfmfファイルを読み込む
	m_map->ChangeMapData(path, *m_objectCont);
	// 新しいマップのカメラの制限を把握
	m_camera->SetMapSize(m_map->GetMapSize());
	m_camera->FitMap();
}

void SceneGame::Entry()
{
	// 主にフェード
	m_fade.Fade(60, 0);

	Music::GetInstance().Play(kNormalStageBGM);
	Music::GetInstance().SetVolume(255);
}

void SceneGame::NormalUpdate()
{
	Statistics::GetInstance().IncreaseTimer();

	// フラグで申し訳ない
	if (m_stopFrame > 0)
	{
		HitStopUpdate();
		--m_stopFrame;
		return;
	}
	// マップ遷移中ならそっちの処理をする
	if (m_isMapChanging)
	{
		MapChangeUpdate();
		return;
	}

	Input& input = Input::GetInstance();

	++m_frameCount;
	m_camera->Update();
	m_fade.Update();
	m_hpUI->Update();
	m_coinUI->Update();
	m_map->Update();
	m_player->Update();
	m_objectCont->Update();

	if (input.IsTrigger("Pause"))
	{
		// ここでフェードパネルの色変える
		m_fade.SetColor(0xffffff);
		SoundManager::GetInstance().Play(kPausesound);
		SceneStackWithFadeOut("Pause", 30);
		return;
	}
#if _DEBUG
	if (input.IsTrigger("ChangeScene_Debug"))
	{
		GameClear();
		//SceneChangeWithFadeOut("Gameover");
		//ChangeMapWithFadeOut("Data/MapData/TestMapGroundStage.fmf", Vector2(-100, 0));
		return;
	}
#endif
}

void SceneGame::Draw() const
{
	m_map->DrawBackGround();
	m_objectCont->DrawBehindMapObject();
	m_map->Draw();
	m_objectCont->DrawFrontMapObject();
	m_player->Draw();
	m_hpUI->Draw();
	m_coinUI->Draw();
	m_timeUI->Draw();
	m_imageHowToPlay->Draw(kHowToPlayPos);
	m_fade.Draw();

#if _DEBUG
	DrawFormatString(0, 0, 0x999999, "SceneGame 現在%dフレーム経過中", m_frameCount);
	DrawFormatString(0, 60, 0x999999, "%fFPS", Time::FPS());
	DrawFormatString(0, 75, 0x999999, "deltaTime:%f", Time::DeltaTime());
	DrawFormatString(0, 90, 0x999999, "Cameraのワールド座標:x,%f y,%f", m_camera->GetPos().x, m_camera->GetPos().y);

	DrawFormatString(0, 105, 0xffffff, "コインの数%d", Statistics::GetInstance().GetCoinNum());
#endif
}

void SceneGame::HitStop(const int frame)
{
	m_stopFrame = frame;
}

void SceneGame::ResetStageProgress()
{
	s_nowStage = Stages::kStage1;
}
