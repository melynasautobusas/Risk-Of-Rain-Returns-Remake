#include "pch.h"
#include "StageManager.h"
#include <iostream>
#include <fstream>

StageManager::StageManager(const Rectf& viewport)
	: m_Viewport{ viewport }
	, m_SpriteManager{}
	, m_FrameManager{}
	, m_LevelManager{}
	, m_Camera{ m_LevelManager.GetLevelSize(), Vector2f{m_Viewport.width, m_Viewport.height}, 3.f }
{
}

void StageManager::Initialize()
{
	m_Player.Initialize(m_SpriteManager.GetPlayerSprites());
	m_Player.SetFrameData(m_FrameManager.GetPlayerData());
	//m_FrameManager.Initialize();
}

void StageManager::Draw() const
{
	m_Camera.Center(m_Player.GetPlayerCenter());
	m_Player.Draw();
	m_Camera.Reset();
}

void StageManager::Update(float elapsedSec)
{
	m_Player.Update(elapsedSec);
}