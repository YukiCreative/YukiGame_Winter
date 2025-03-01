#pragma once
#include <memory>
#include "Vector2.h"
#include <string>
#include <vector>

class Image;

// アニメーション
class Animation
{
private:
	// 元画像
	// ※元画像は一枚で一つのアニメーションを持っていて、左向きに一列に並んでいる想定
	int m_sourceHandle;
	// 分割したやつ
	std::vector<int> m_frameHandle;
	// アニメーションの総数
	int m_allAnimNum;
	// アニメーション終了までの総フレーム
	int m_allFrame;
	// 今の画像が何番目か
	int m_nowAnimNum;
	// アニメーションの再生速度(何フレームでアニメーションが切り替わるか)
	int m_oneAnimTime;
	int m_frameCount;
	std::shared_ptr<Image> m_image;
	int m_loopCount;
public:
	Animation();

	/// <summary>
	/// アニメーションを設定する際に、コンストラクタではなくこちらで初期化する
	/// </summary>
	/// <param name="path">アニメーション画像のパス</param>
	/// <param name="oneFrameSize">画像を切るサイズ</param>
	/// <param name="playSpeed">再生速度(画像が切り替わるまで何フレームかけるか)</param>
	void Init(const std::string& fileName, const Vector2Int& oneImageSize, const int& playSpeed);

	void Update();
	void Draw(const Vector2& pos) const;

	// Imageの仲介
	void SetExRate(const float& rate);
	void SetBlendMode(const int& mode, const int& param);
	void ReverceX(const bool& value);
	void SetRotate(const float& deg);

	// アニメーションが何回ループしたかを返す
	int LoopCount() const { return m_loopCount; };
	void ResetLoopCount() { m_loopCount = 0; }
};