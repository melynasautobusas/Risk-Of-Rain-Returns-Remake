#pragma once
#include "Texture.h"
#include <vector>
#include <map>

class SpriteManager
{
public:
	explicit SpriteManager();
	~SpriteManager();

	Texture* GetPlayerSprites();

private:
	Texture* m_PlayerSpriteSheet{};
	Texture* m_GolemSpriteSheet{};
	Texture* m_LemurianSpriteSheet{};
	Texture* m_ColossusSpriteSheet{};
	Texture* m_LevelSpriteSheet{};

	void LoadSprites();
};