#pragma once
#include <algorithm>

// 体力がintなのがみじめなので
struct HitPoint
{
private:
	const int kMinHitPoint = 0;
	const int kMaxHitPoint = 99;

	int m_value;
public:
	HitPoint(int value)
	{
		// 値を正しい範囲に収める
		m_value = std::clamp(value, kMinHitPoint, kMaxHitPoint);
	}

	void operator=(HitPoint right)
	{
		m_value = right.m_value;
	}

	int Value() const
	{
		return m_value;
	}

	HitPoint operator+(HitPoint right)
	{
		return HitPoint(m_value + right.m_value);
	}

	HitPoint operator-(HitPoint right)
	{
		return HitPoint(m_value - right.m_value);
	}

	void operator+=(const HitPoint& value)
	{
		// この書き方怖いんだけど
		*this = *this + value;
	}

	void operator-=(const HitPoint& value)
	{
		*this = *this - value;
	}

	bool IsDead() const
	{
		return m_value <= 0;
	}
};