#include "ButtonReturnToTitleFromGameover.h"
#include "SceneController.h"
#include "SceneGameover.h"
#include "Image.h"

namespace
{
	const std::string kImagePath = "ButtonReturnToTitle_Gameover.png";
	const std::string kNoFImagePath = "ButtonReturnToTitle_Gameover_NoF.png";

	constexpr float kBaseExRate    = 1.0f;
	constexpr float kFocusedExRate = 1.5f;
}

void ButtonReturnToTitleFromGameover::FocusedUpdate()
{
	// lerp�ŃV���b���Ƒ傫������
	float exRate = std::lerp(m_image->ExRate(), kFocusedExRate, 0.2f);
	m_image->SetExRate(exRate);
}

void ButtonReturnToTitleFromGameover::NormalUpdate()
{
	float exRate = std::lerp(m_image->ExRate(), kBaseExRate, 0.2f);
	m_image->SetExRate(exRate);
}

ButtonReturnToTitleFromGameover::ButtonReturnToTitleFromGameover(const Vector2& initPos) :
	Button(initPos)
{
	m_image = std::make_shared<Image>(kImagePath);
	m_image->SetExRate(kBaseExRate);
}

void ButtonReturnToTitleFromGameover::Draw() const
{
	m_image->Draw(m_pos);
}

void ButtonReturnToTitleFromGameover::OnFocused()
{
	InvertState();
	m_image->SetGraph(kImagePath);
}

void ButtonReturnToTitleFromGameover::OnDisfocused()
{
	InvertState();
	m_image->SetGraph(kNoFImagePath);
}

void ButtonReturnToTitleFromGameover::OnPressed()
{
	// �^�C�g���ɖ߂�
	// �� �� ��
	std::static_pointer_cast<SceneGameover>(SceneController::GetInstance().CurrentScene())->ReturnToTitle();
}