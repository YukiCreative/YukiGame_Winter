#pragma once
#include <string>
#include "Vector2.h"
#include "Calculation.h"

// �摜��\������R���|�[�l���g���ۂ����
class Image
{
private:
	int m_sourceHandle;
	float m_expandRate;
	float m_angle;
	int m_blendMode;
	uint8_t m_blendPal;
public:
	Image(const int& handle);
	Image(const std::string& path);

	void Draw(const Vector2& pos) const;

	void SetGraph(const int& handle) { m_sourceHandle = handle; }
	void SetGraph(const std::string& path);

	// ���݂̉��{�̑傫���ɂ��邩
	void ExpandGraph(const float& exRate) { m_expandRate *= exRate; }
	// ���
	void SetExRate(const float& value) { m_expandRate = value; }
	// ���󂩂牽�x��]�����邩
	void RotateGraph(const float& deg) { m_angle += deg * Calculation::kDegToRad; }
	// ���
	void SetAngle(const float& angleDeg) { m_angle = angleDeg * Calculation::kDegToRad; }
	// SetDrawBlendMode�����̂܂ܕ\�Ɍ����Ă���
	void SetImageBlendMode(const int& blendmode, const int& pal)
	{
		m_blendMode = blendmode;
		m_blendPal = pal;
	}
	void SetImageBlendMode(const int& blendMode) { m_blendMode = blendMode; }
	void SetImageBlendPal(const int& pal) { m_blendPal = pal; }
	int GraphHandle() const { return m_sourceHandle; }
};
