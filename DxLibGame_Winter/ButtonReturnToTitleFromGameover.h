#pragma once
#include "Button.h"
#include <memory>

class Image;

// クラス名が長い
class ButtonReturnToTitleFromGameover : public Button
{
private:
	void FocusedUpdate() override;
	void NormalUpdate() override;

	std::shared_ptr<Image> m_image;
public:
	ButtonReturnToTitleFromGameover(const Vector2& initPos);

	void Draw() const override;

	void OnFocused()    override;
	void OnDisfocused() override;
	void OnPressed()    override;

	// Imageの引継ぎの引継ぎ
	void SetBlendingMode(const int& mode, const int& param);
};

