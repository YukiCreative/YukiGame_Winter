#include "ScreenFade.h"
#include <DxLib.h>
#include "game.h"
#include <cassert>

namespace
{
	constexpr float kAlphaMax = 255.0f;
	constexpr float kPercentToBlendParam = 255.0f / 100.0f;
}

ScreenFade::ScreenFade() :
	m_fadeFrame(0),
	m_transParFrame(0),
	m_color(0x000000),
	m_updateState(&ScreenFade::NormalUpdate),
	m_alpha(100)
{
}

ScreenFade& ScreenFade::Getinstance()
{
	static ScreenFade instance;
	return instance;
}

void ScreenFade::Update()
{
	// FadeIn��Out���͂��܂��c
	(this->*m_updateState)();
}

void ScreenFade::FadeInUpdate()
{
	// �����x��������
	// �I�������� ���ݓ����x < �ŏI�����x
	m_alpha += m_transParFrame;
	if (m_alpha <= m_targetAlpha)
	{
		m_alpha = m_targetAlpha;
		m_updateState = &ScreenFade::NormalUpdate;
		return;
	}
}

void ScreenFade::FadeOutUpdate()
{
	// �����x���グ��
	// �I�������� ���ݓ����x > �ŏI�����x
	m_alpha += m_transParFrame;
	if (m_alpha >= m_targetAlpha)
	{
		m_alpha = m_targetAlpha;
		m_updateState = &ScreenFade::NormalUpdate;
		return;
	}
}

void ScreenFade::NormalUpdate()
{
	// �������Ȃ��H
}

void ScreenFade::Draw() const
{
	// Image���g�����l����
	SetDrawBlendMode(DX_BLENDMODE_MULA, static_cast<int>(m_alpha.value * kPercentToBlendParam));
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_color, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ScreenFade::Fade(const int& totalFrame, const float& percent)
{
	// 0�t���[���Ȃ�{��
	assert(totalFrame && "0�t���[���̃t�F�[�h�@�Ӗ��Ȃ���@�����Ƀt�F�[�h�������Ȃ�1�t���[���ł��");
	m_targetAlpha = percent;
	// m_transPerFrame������o��
	m_transParFrame = (m_targetAlpha - m_alpha) / totalFrame;
	// ���݂̏�Ԃ��t�F�[�h�C�����A�E�g������
	// ����֐��������ق�����������
	if (m_transParFrame > 0)
	{
		m_updateState = &ScreenFade::FadeOutUpdate;
	}
	else
	{
		m_updateState = &ScreenFade::FadeInUpdate;
	}
}