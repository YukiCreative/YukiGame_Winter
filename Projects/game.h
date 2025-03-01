#pragma once

namespace Game
{
	//constexpr int kScreenWidth = 1920;
	//constexpr int kScreenHeight = 1080;
	//constexpr int kScreenWidth = 640;
	//constexpr int kScreenHeight = 480; // 昔のブラウン管の比率らしい DXLibのデフォルト
	constexpr int kScreenWidth = 1280;
	constexpr int kScreenHeight = 720; // 先生個人的に推奨
	constexpr int kColorBitNum = 32;

	// 次があったら可変フレームレートに挑戦したい
	constexpr int kFrameRate = 60;
	constexpr int kMillisecondsPerFrame = 1000000 / kFrameRate;

	constexpr int kScreenHalfWidth = Game::kScreenWidth >> 1;
	constexpr int kScreenHalfHeight = Game::kScreenHeight >> 1;

	constexpr bool kDefaultWindowMode = true;
}