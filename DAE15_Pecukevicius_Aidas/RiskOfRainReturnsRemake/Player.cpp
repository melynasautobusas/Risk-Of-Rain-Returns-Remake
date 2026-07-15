#include "pch.h"
#include "Player.h"
#include <iostream>
#include <fstream>

void Player::Initialize(const Texture* pSpriteSheet)
{
	m_pTexture = pSpriteSheet;
}

void Player::Draw() const
{
	glPushMatrix();

	m_pTexture->Draw(Vector2f{ m_Hitbox.left, m_Hitbox.bottom }, m_FrameData->at(m_State).at(m_FrameIndex));
}

void Player::Update(float elapsedSec)
{
	Input();
	UpdateFrameInfo(elapsedSec);
}

void Player::Input()
{
	const Uint8* pKeyBoardStates{ SDL_GetKeyboardState(nullptr) };
}

void Player::SetFrameData(std::map<CommandoState, std::vector<Rectf>>* data)
{
	m_FrameData = data;
}

void Player::UpdateFrameInfo(float elapsedSec)
{
	if (m_State != CommandoState::idle)
	{
		m_CurrentFrameTime += elapsedSec * 60.f;
		if (m_CurrentFrameTime >= 3.f)
		{
			m_CurrentFrameTime = 0.f;
			++m_FrameIndex;
		}
		if (m_FrameIndex > m_FrameData->at(m_State).size() - 1)
		{
			m_FrameIndex = 0;
		}
	}
	else
	{
		m_FrameIndex = 0;
		m_CurrentFrameTime = 0.f;
	}
}
