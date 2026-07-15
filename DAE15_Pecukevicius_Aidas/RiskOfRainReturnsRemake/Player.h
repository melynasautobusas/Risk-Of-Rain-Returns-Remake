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

	void Input();
	void SetFrameData(std::map<CommandoState, std::vector<Rectf>>* data);
private:

	float m_CurrentFrameTime{ 0.f };
	int m_FrameIndex{ 0 };
	float m_xDirection{ -1 };

	CommandoState m_State{ CommandoState::idle };
	Rectf m_Hitbox{};
	const Texture* m_pTexture{};
	std::map<CommandoState, std::vector<Rectf>>* m_FrameData{ nullptr };

	void UpdateFrameInfo(float elapsedSec);
};