#include "pch.h"
#include "Player.h"
#include <iostream>
#include <fstream>

void Player::Initialize(const Texture* pSpriteSheet)
{
	m_pTextureMap = pSpriteSheet;
}

void Player::Draw() const
{
	glPushMatrix();
	glScalef(m_Direction, 1.f, 1.f);
	m_pTextureMap->Draw(Vector2f{ m_Hitbox.left - m_CurrentFrameInfo.width * 0.5f,
		m_Hitbox.bottom - m_CurrentFrameInfo.height * 0.5f }, m_CurrentFrameInfo);
	glPopMatrix();
}

void Player::Update(float elapsedSec)
{
	Input(elapsedSec);
	UpdateFrameInfo(elapsedSec);
}

void Player::Input(float elapsedSec)
{
	const Uint8* pKeyBoardStates{ SDL_GetKeyboardState(nullptr) };
	Move(elapsedSec, pKeyBoardStates);
}

void Player::SetFrameData(std::map<CommandoState, std::vector<Rectf>>* data)
{
	m_FrameData = data;
}

Vector2f Player::GetPlayerCenter() const
{
	return Vector2f{ m_CurrentFrameInfo.width * 0.5f, m_CurrentFrameInfo.height * 0.5f };
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
	m_CurrentFrameInfo = m_FrameData->at(m_State).at(m_FrameIndex);
	m_Hitbox.width = m_CurrentFrameInfo.width;
	m_Hitbox.height = m_CurrentFrameInfo.height;
}

void Player::Move(float elapsedSec, const Uint8* pKeyState)
{
	if (pKeyState[SDL_SCANCODE_LEFT])
	{
		if (m_Direction == 1.f)
		{
			m_Direction = -m_Direction;
		}
		m_State = CommandoState::walk;
	}
	else if (pKeyState[SDL_SCANCODE_RIGHT])
	{
		if (m_Direction == -1.f)
		{
			m_Direction = -m_Direction;
		}
		m_State = CommandoState::walk;
	}
	else
	{
		m_State = CommandoState::idle;
	}
}
