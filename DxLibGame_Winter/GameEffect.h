#pragma once
#include "GameObject.h"
#include <memory>
#include <string>

class Animation;

// 実はアニメーションだけを持ったただのゲームオブジェクト
class GameEffect : public GameObject
{
private:
	std::shared_ptr<Animation> m_animation;
	std::weak_ptr<GameObject>  m_followGameObject;
	bool    m_isLoop;
	Vector2 m_offset;
public:
	GameEffect(const std::shared_ptr<Animation>& animInstance, const Vector2& initPos, const Vector2& offset = Vector2::Zero());
	GameEffect(const std::string& filename, const Vector2Int& oneImageSize, const int& playSpeed, const Vector2& initPos, const Vector2& offset = Vector2::Zero());

	void Update() override;
	void Draw() const override;

	void Loop(const bool& loopOrNot) { m_isLoop = loopOrNot; }
	// ここは コンスト参照はしない
	void SetFollowGameObject(std::shared_ptr<GameObject> object) { m_followGameObject = object; }
	void ResetFollowObject() { m_followGameObject.reset(); }
};

