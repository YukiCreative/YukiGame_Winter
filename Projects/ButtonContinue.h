#pragma once
#include "Button.h"

class Image;

// ゲームオーバー画面に設置する
class ButtonContinue : public Button
{
private:
	std::shared_ptr<Image> m_image;

	void FocusedUpdate() override;
	void NormalUpdate() override;
public:
	ButtonContinue(const Vector2& initPos);

	void Draw() const override;

	void OnFocused() override;
	void OnDisfocused() override;

	void OnPressed() override;

	// Imageの引継ぎの引継ぎ
	void SetBlendingMode(const int& mode, const int& param);
};

