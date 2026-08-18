#include "pch.h"
#include "Collider.h"
#include "utils.h"

bool Collider::IsColliding(const Rectf& hitbox1, const Rectf& hitbox2)
{
	return utils::IsOverlapping(hitbox1, hitbox2);
}

void Collider::SetMapHitboxes(const std::vector<MapData>* pArrMapHitboxes)
{
	m_pArrMapHitboxes = pArrMapHitboxes;
}

Vector2f Collider::PlaceInBounds(const Rectf& hitbox, const Vector2f& velocity)
{
	Rectf newHitbox{hitbox};
	for (const MapData& mapHitbox : *m_pArrMapHitboxes) 
	{
		if (utils::IsOverlapping(newHitbox, mapHitbox.hitbox))
		{
			const float xDstLeft{ newHitbox.left + newHitbox.width - mapHitbox.hitbox.left };
			const float xDstRight{ mapHitbox.hitbox.left + mapHitbox.hitbox.width - newHitbox.left };
			if (xDstLeft < xDstRight)
			{
				newHitbox.left = mapHitbox.hitbox.left - newHitbox.width;
			}
			else
			{
				newHitbox.left = mapHitbox.hitbox.left + mapHitbox.hitbox.width;
			}
		}
	}
	for (const MapData& mapHitbox : *m_pArrMapHitboxes) 
	{
		if (utils::IsOverlapping(newHitbox, mapHitbox.hitbox))
		{
			const float xDstBottom{ newHitbox.bottom + newHitbox.height - mapHitbox.hitbox.bottom };
			const float xDstTop{ mapHitbox.hitbox.bottom + mapHitbox.hitbox.height - newHitbox.bottom };
			if (xDstBottom < xDstTop)
			{
				newHitbox.bottom = mapHitbox.hitbox.bottom - newHitbox.height;
			}
			else
			{
				newHitbox.bottom = mapHitbox.hitbox.bottom + mapHitbox.hitbox.height;
			}
		}

	}
	return Vector2f{ newHitbox.left, newHitbox.bottom };
}
