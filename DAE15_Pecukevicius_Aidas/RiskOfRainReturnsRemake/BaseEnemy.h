#pragma once
class BaseEnemy
{
public:

	enum class Type
	{
		Lemurian,
		RockGolem,
		Wisp,
		GreaterWisp,
		Jellyfish,
		Trokk
	};

	BaseEnemy();

	void Draw() const;
	virtual void Update(float elapsedSec) = 0;
};

