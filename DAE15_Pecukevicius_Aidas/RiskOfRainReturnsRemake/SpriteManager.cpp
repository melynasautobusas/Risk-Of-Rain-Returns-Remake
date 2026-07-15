#include "pch.h"
#include "SpriteManager.h"
#include <iostream>

SpriteManager::~SpriteManager()
{
	delete m_PlayerSprites;
	m_PlayerSprites = nullptr;
}

void SpriteManager::LoadSprites()
{
	if (!Texture{ "CommandoSpriteSheetA0.png" }.IsCreationOk())
	{
		std::cout << "Player sprite not found!\n";
	}
	else
	{
		m_PlayerSprites = new Texture{ "CommandoSpriteSheetA0.png" };
	}
}

Texture* SpriteManager::GetPlayerSprites()
{
	return m_PlayerSprites;
}