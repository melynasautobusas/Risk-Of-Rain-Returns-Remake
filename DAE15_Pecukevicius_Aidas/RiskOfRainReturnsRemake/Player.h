#pragma once
#include "Texture.h"
#include "GameInfo.h"
#include <map>
class Player final
{
public:

	explicit Player();
	~Player();

	void SetSpriteSheet(const Texture* pSpriteSheet);
	void Draw() const;
	void Update(float elapsedSec, const Uint8* pKeyStates);

	void Input(const Uint8* pKeyStates, float elapsedSec, const size_t& frameIndex, float frameTime);
	Vector2f GetBottomMiddle() const;
	Rectf GetHitbox() const;
	Vector2f GetPlayerVelocity() const;
	void CalculateHitbox();
	void SetPlayerCenter(const Vector2f & bottomLeft);
	
	std::map<CommandoSprites, std::vector<EntityData>>* GetDataPointer();

private:

	struct Stats {
		int experience{0};
		int hp{ 110 };
		float regen{ 0.6f };
		float damage{ 12.f };
		int armor{ 0 };
		float speed{ 20.f }; // / 10 for rough speed in pixels
		float ATKSpeed{ 1.f };
	};
	
	size_t m_FrameIndex{ 0 };
	int m_FrameCount{ 0 };

	float m_Direction{ 1.f };
	Vector2f m_BottomMiddle{ 0.f, 0.f};
	Vector2f m_Velocity{};
	Rectf m_Hitbox{};

	CommandoSprites m_MovementState{ CommandoSprites::walk };
	EntityData m_MovementData{};
	CommandoSprites m_AbilityState{ CommandoSprites::none };
	EntityData m_AbilityData{};
	const Texture* m_pSpriteSheet{};
	std::map<CommandoSprites, std::vector<EntityData>>* m_pFrameData{ nullptr };

	Stats m_Stats{};
	const Stats m_LevelUp{
		0,
		32,
		0.6f,
		12.f,
		2,
		20.f,
		0.f
	};

	const int m_XPreq{ 20 };

	void UpdateMovementAnimations(float elapsedSec, const Uint8* pKeyStates);
	void UpdateAbilityAnimations(float elapsedSec, size_t& frameIndex, float& frameTime);
	void Move(const Uint8* pKeyState);
	void Abilities(const Uint8* pKeyState, float elapsedSec, const size_t& frameIndex, float frameTime);
	void UpdatePosition(const Uint8* pKeyStates);
};