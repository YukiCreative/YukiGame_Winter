#pragma once
#include "Button.h"
#include "Vector2.h"
#include <memory>

class Image;
class ScenePause;

// ポーズ画面の「タイトルに戻る」ボタン
class ButtonReturnToTitle : public Button
{ 
private:
	int m_frameCount;

	std::shared_ptr<Image> m_image;

	void FocusedUpdate() override;
	void NormalUpdate() override;
public:
	ButtonReturnToTitle(Vector2 initPos);
	~ButtonReturnToTitle();

	void OnFocused() override;
	void OnDisfocused() override;

	void OnPressed() override;

	void Draw() const override;
};

