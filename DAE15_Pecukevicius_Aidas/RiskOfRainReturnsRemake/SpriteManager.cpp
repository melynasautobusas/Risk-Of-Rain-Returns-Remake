#include "pch.h"
#include "SpriteManager.h"
#include <iostream>

SpriteManager::SpriteManager()
{
	LoadSprites();
}

SpriteManager::~SpriteManager()
{
	delete m_PlayerSpriteSheet;
	m_PlayerSpriteSheet = nullptr;
	//delete m_GolemSpriteSheet;
	//m_GolemSpriteSheet = nullptr;
	//delete m_LemurianSpriteSheet;
	//m_LemurianSpriteSheet = nullptr;
	//delete m_ColossusSpriteSheet;
	//m_ColossusSpriteSheet = nullptr;
	//delete m_LevelSpriteSheet;
	//m_LevelSpriteSheet = nullptr;
}

void SpriteManager::LoadSprites()
{
	m_PlayerSpriteSheet = new Texture{ "CommandoSpriteSheet.png" };
	//m_GolemSpriteSheet = new Texture{ "GolemSpriteSheet.png" };
	//m_LemurianSpriteSheet = new Texture{ "LemurianSpriteSheet.png" };
	//m_ColossusSpriteSheet = new Texture{ "ColossusSpriteSheet.png" };
}

Texture* SpriteManager::GetPlayerSprites()
{
	return m_PlayerSpriteSheet;
}