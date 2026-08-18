#pragma once
#include "GameInfo.h"
class Collider final
{
public:
	//use for attacks and object interactions
	bool IsColliding(const Rectf& hitbox1, const Rectf& hitbox2);
	void SetMapHitboxes(const std::vector<MapData>* pArrMapHitboxes);
	Vector2f PlaceInBounds(const Rectf& hitbox, const Vector2f& velocity);

private:

	const std::vector<MapData>* m_pArrMapHitboxes{};
};

