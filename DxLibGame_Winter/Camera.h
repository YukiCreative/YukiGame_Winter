#pragma once
#include "Vector2.h"
#include "game.h"

/// <summary>
/// �I�u�W�F�N�g�̃��[���h���W��`��̃X�N���[�����W�ɕϊ�
/// </summary>
class Camera
{
private:
	/// <summary>
	/// �J�����̍��W(���[���h)
	/// </summary>
	Vector2 m_pos;
	/// <summary>
	/// Update�ňꊇ�ňړ����邽�߂Ɉꎞ�I�ɋL�����Ă���
	/// </summary>
	Vector2 m_velocity;
public:
	/// <summary>
	/// �J�����̍X�V
	/// </summary>
	void Update() 
	{
		m_pos += m_velocity;
		// �ړ��ʃ��Z
		m_velocity = Vector2();
	}
	/// <summary>
	/// �����ɓ����ꂽ���[���h���W���A���݂̃J�����̃��[���h���W�ɂ���ăX�N���[�����W�ɕϊ�
	/// </summary>
	/// <param name="pos">���[���h���W</param>
	/// <returns>�X�N���[�����W</returns>
	Vector2 Capture(const Vector2& objPos) const
	{
		Vector2 screenPos = objPos - m_pos;
		// �X�N���[���̒����ɂȂ�悤�ɕ␳
		screenPos.x += Game::kScreenWidth * 0.5f;
		screenPos.y += Game::kScreenHeight * 0.5f;
		return screenPos;
	}
	/// <summary>
	/// �J�����̈ړ�
	/// </summary>
	void Move(Vector2 moveValue) { m_pos += moveValue; }

	Vector2 GetPos() const { return m_pos; };
};
