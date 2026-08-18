#include "pch.h"
#include "StageManager.h"
#include <iostream>
#include <fstream>

StageManager::StageManager(const Rectf& viewport)
	: m_Viewport{ viewport }
	, m_SpriteManager{}
	, m_LevelManager{}
	, m_Camera{ m_LevelManager.GetLevelSize(), Vector2f{m_Viewport.width, m_Viewport.height}, m_Scale }
{
}

void StageManager::Initialize()
{
	if (m_ManageSprites)
	{
		return;
	}
	m_Player.SetSpriteSheet(m_SpriteManager.GetPlayerSprites());
	//m_Player.SetFrameData(m_FrameManager.GetPlayerData());
	m_DataManager.SetCommandoData(m_Player.GetDataPointer());
	m_Collider.SetMapHitboxes(m_LevelManager.GetMapData());
}

void StageManager::Draw() const
{
	if (m_ManageSprites)
	{
		m_DataManager.Draw();
		return;
	}
	glPushMatrix();
	//glScalef(m_Scale, m_Scale, 1.f);
	m_LevelManager.Draw();
	m_Camera.Center(m_Player.GetBottomMiddle());
	m_Player.Draw();
	m_Camera.Reset();
	glPopMatrix();
}

void StageManager::Update()
{
	const Uint8* pKeyStates{ SDL_GetKeyboardState(nullptr) };

	static float elapsedSec{ 1.f / frameCap };

	if (m_ManageSprites)
	{
		m_DataManager.Update(elapsedSec);
		return;
	}

	m_Player.Update(elapsedSec, pKeyStates);
	m_Player.SetPlayerCenter(m_Collider.PlaceInBounds(m_Player.GetHitbox(), m_Player.GetPlayerVelocity()));
}

void StageManager::KeyInput(const SDL_KeyboardEvent& e)
{
	if (m_ManageSprites)
	{
		m_DataManager.KeyInput(e);
		return;
	}
}

void StageManager::MouseInput(const SDL_MouseButtonEvent& e)
{
	if (m_ManageSprites)
	{
		m_DataManager.MouseInput(e);
		return;
	}
}
