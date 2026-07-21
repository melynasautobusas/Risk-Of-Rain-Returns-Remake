#include "pch.h"
#include "LevelManager.h"

LevelManager::LevelManager()
	: m_LevelSize{ 11580.f, 3584.f }
{
}

Vector2f LevelManager::GetLevelSize() const
{
	return m_LevelSize;
}

void LevelManager::DrawStaticTextures() const
{
}

void LevelManager::DrawDynamicTextures() const
{
}

void LevelManager::UpdateDynamicTextures()
{
}
