#pragma once
#include "Texture.h"
#include "GameInfo.h"
#include <map>
class Player final
{
public:
	void Initialize(const Texture* pSpriteSheet);
	void Draw() const;
	void Update(float elapsedSec);

	void Input(float elapsedSec);
	void SetFrameData(std::map<CommandoState, std::vector<Rectf>>* data);
	Vector2f GetPlayerCenter() const;

private:
	float m_CurrentFrameTime{ 0.f };
	int m_FrameIndex{ 0 };
	float m_Direction{ 1.f };

	CommandoState m_State{ CommandoState::idle };
	Rectf m_Hitbox{};
	Rectf m_CurrentFrameInfo{};
	const Texture* m_pTextureMap{};
	std::map<CommandoState, std::vector<Rectf>>* m_FrameData{ nullptr };

	void UpdateFrameInfo(float elapsedSec);
	void Move(float elapsedSec, const Uint8 * pKeyState);
};