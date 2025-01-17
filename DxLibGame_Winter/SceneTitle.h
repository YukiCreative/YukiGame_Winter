#pragma once
#include "Scene.h"
#include <memory>

class ImageObject;
class Camera;
class ScreenFade;
class ButtonSystem;

// 一番最初に表示されるシーン
class SceneTitle : public Scene
{
private:
	std::shared_ptr<ImageObject>  m_backGround;
	std::shared_ptr<ButtonSystem> m_buttonSystem;
	std::shared_ptr<ImageObject>  m_titleLogo;

	void ButtonInit();
public:
	SceneTitle();

	void Entry() override;
	void NormalUpdate() override;
	void Draw() const override;

	void GameStart();
};

