#pragma once
#include "Texture.h"
#include "FrameManager.h"
#include <vector>
#include <map>

class SpriteManager
{
public:
	explicit SpriteManager();
	~SpriteManager();

	Texture* GetPlayerSprites();

private:
	Texture* m_PlayerSprites{};
	Texture* m_LevelSprites{};
	void LoadSprites();
};