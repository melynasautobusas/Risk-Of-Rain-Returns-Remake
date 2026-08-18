#include "pch.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include "utils.h"



Player::Player()
{
	m_pFrameData = new std::map<CommandoSprites, std::vector<EntityData>>;
}

Player::~Player()
{
	delete m_pFrameData;
	m_pFrameData = nullptr;
}

void Player::SetSpriteSheet(const Texture* pSpriteSheet)
{
	m_pSpriteSheet = pSpriteSheet;
}

void Player::Draw() const
{
	if (m_MovementData.sourceRect.width == 0.f)
	{
		return;
	}

	glPushMatrix();

	Vector2f correctionMovement = m_BottomMiddle - m_MovementData.pivotPoint;
	Vector2f correctionAbility = m_BottomMiddle - m_AbilityData.pivotPoint;

	if (m_Direction == -1.f)
	{
		glTranslatef(m_BottomMiddle.x, m_BottomMiddle.y, 0.f);
		glScalef(m_Direction, 1.f, 1.f);
		glTranslatef(-m_BottomMiddle.x, -m_BottomMiddle.y, 0.f);
	}

	if (m_AbilityState == CommandoSprites::doubleTapA || m_AbilityState == CommandoSprites::doubleTapB)
	{
		Vector2f pivot{ m_BottomMiddle.x - m_AbilityData.pivotPoint.x,
			m_BottomMiddle.y - m_AbilityData.pivotPoint.y + m_MovementData.hitbox.height };
		m_pSpriteSheet->Draw(correctionMovement, m_MovementData.sourceRect);
		m_pSpriteSheet->Draw(pivot, m_AbilityData.sourceRect);
	}
	else if (m_AbilityState == CommandoSprites::fullMetalJacket
		|| m_AbilityState == CommandoSprites::singleSuppressive ||
		m_AbilityState == CommandoSprites::doubleSuppressive || m_AbilityState == CommandoSprites::tacticalDive)
	{
		m_pSpriteSheet->Draw(correctionAbility, m_AbilityData.sourceRect);
	}
	else
	{
		m_pSpriteSheet->Draw(correctionMovement, m_MovementData.sourceRect);
	}
	glPopMatrix();
	utils::DrawRect(m_Hitbox);
	utils::FillEllipse(m_BottomMiddle, 2.f, 2.f);
}

void Player::Update(float elapsedSec, const Uint8* pKeyStates)
{
	static size_t frameIndex{ 0 };
	static float frameTime{ 0.f };

	UpdatePosition(pKeyStates);
	Input(pKeyStates, elapsedSec, frameIndex, frameTime);
	UpdateMovementAnimations(elapsedSec, pKeyStates);
	UpdateAbilityAnimations(elapsedSec, frameIndex, frameTime);
	CalculateHitbox();
}

void Player::Input(const Uint8* pKeyStates, float elapsedSec, const size_t& frameIndex, float frameTime)
{
	Abilities(pKeyStates, elapsedSec, frameIndex, frameTime);
	//Attack(pKeyStates);
	Move(pKeyStates);
}

Vector2f Player::GetBottomMiddle() const
{
	return Vector2f{ 0.f, 0.f };
}

Rectf Player::GetHitbox() const
{
	return m_Hitbox;
}

Vector2f Player::GetPlayerVelocity() const
{
	return m_Velocity;
}

void Player::CalculateHitbox()
{
	Rectf hitbox{};
	if (m_AbilityState == CommandoSprites::doubleTapA || m_AbilityState == CommandoSprites::doubleTapB
		|| m_AbilityState == CommandoSprites::fullMetalJacket
		|| m_AbilityState == CommandoSprites::singleSuppressive
		|| m_AbilityState == CommandoSprites::tacticalDive)
	{
		hitbox = m_AbilityData.hitbox;
		if (m_Direction == -1.f)
		{
			hitbox.left -= abs(m_AbilityData.pivotPoint.x - hitbox.width);
		}
		else
		{
			hitbox.left -= m_AbilityData.pivotPoint.x;
		}
		hitbox.bottom -= m_AbilityData.pivotPoint.y;
	}
	else
	{
		hitbox = m_MovementData.hitbox;
		if (m_Direction == -1.f)
		{
			hitbox.left -= abs(m_MovementData.pivotPoint.x - hitbox.width);
		}
		else
		{
			hitbox.left -= m_MovementData.pivotPoint.x;
		}
		hitbox.bottom -= m_MovementData.pivotPoint.y;
	}

	hitbox.left += m_BottomMiddle.x;
	hitbox.bottom += m_BottomMiddle.y;

	m_Hitbox = hitbox;
}

void Player::SetPlayerCenter(const Vector2f& bottomLeft)
{
	m_Hitbox.left = bottomLeft.x;
	m_Hitbox.bottom = bottomLeft.y;

	if (m_AbilityState == CommandoSprites::doubleTapA || m_AbilityState == CommandoSprites::doubleTapB
		|| m_AbilityState == CommandoSprites::fullMetalJacket
		|| m_AbilityState == CommandoSprites::singleSuppressive
		|| m_AbilityState == CommandoSprites::tacticalDive)
	{
		if (m_Direction == -1.f)
		{
			m_BottomMiddle.x = m_Hitbox.left + abs(m_AbilityData.pivotPoint.x - m_Hitbox.width);
		}
		else
		{
			m_BottomMiddle.x = m_Hitbox.left + m_AbilityData.pivotPoint.x;
		}
	}
	else
	{
		if (m_Direction == -1.f)
		{
			m_BottomMiddle.x = m_Hitbox.left + abs(m_MovementData.pivotPoint.x - m_Hitbox.width);
		}
		else
		{
			m_BottomMiddle.x = m_Hitbox.left + m_MovementData.pivotPoint.x;
		}
	}
	m_BottomMiddle.y = bottomLeft.y;
}

std::map<CommandoSprites, std::vector<EntityData>>* Player::GetDataPointer()
{
	return m_pFrameData;
}

void Player::Move(const Uint8* pKeyState)
{
	if (m_MovementState != CommandoSprites::climbDown && m_MovementState != CommandoSprites::climbUp)
	{
		m_MovementState = CommandoSprites::idle;
	}

	if (pKeyState[SDL_SCANCODE_S])
	{
		m_Direction = -1.f;
	}
	else if (pKeyState[SDL_SCANCODE_D])
	{
		m_Direction = 1.f;
	}

	if (m_AbilityState == CommandoSprites::none)
	{
		if (pKeyState[SDL_SCANCODE_SPACE])
		{
			//m_MovementState = CommandoSprites::jump;
			m_MovementState = CommandoSprites::idle; // replace when added collisions
		}
		if (pKeyState[SDL_SCANCODE_UP])
		{
			m_MovementState = CommandoSprites::climbUp;
		}
		else if (pKeyState[SDL_SCANCODE_DOWN])
		{
			m_MovementState = CommandoSprites::climbDown;
		}
		if (m_MovementState == CommandoSprites::climbDown || m_MovementState == CommandoSprites::climbUp)
		{
			return;
		}

		if (pKeyState[SDL_SCANCODE_LEFT])
		{
			if (pKeyState[SDL_SCANCODE_D])
			{
				m_MovementState = CommandoSprites::back;
				return;
			}
			m_MovementState = CommandoSprites::walk;
			m_Direction = -1.f;
		}
		else if (pKeyState[SDL_SCANCODE_RIGHT])
		{
			if (pKeyState[SDL_SCANCODE_S])
			{
				m_MovementState = CommandoSprites::back;
				return;
			}
			m_MovementState = CommandoSprites::walk;
			m_Direction = 1.f;
		}
	}
	else
	{
		if (pKeyState[SDL_SCANCODE_LEFT])
		{
			if (m_Direction == 1.f)
			{
				m_MovementState = CommandoSprites::back;
				return;
			}
			m_MovementState = CommandoSprites::walk;
		}
		else if (pKeyState[SDL_SCANCODE_RIGHT])
		{
			if (m_Direction == -1.f)
			{
				m_MovementState = CommandoSprites::back;
				return;
			}
			m_MovementState = CommandoSprites::walk;
		}
	}
}

void Player::UpdateMovementAnimations(float elapsedSec, const Uint8* pKeyStates)
{
	static size_t frameIndex{ 0 };
	static float frameTime{ 0.f };
	const float timePerFrame{ 3.f / frameCap / (m_Stats.speed / Stats{}.speed) };
	bool stopAnim{ false };
	float speed{ m_Stats.speed };

	switch (m_MovementState)
	{
	case CommandoSprites::idle:
	case CommandoSprites::jump:
	case CommandoSprites::peak:
	case CommandoSprites::fall:
	{
		if (m_AbilityState == CommandoSprites::doubleTapA || m_AbilityState == CommandoSprites::doubleTapB)
		{
			frameIndex = 1;
		}
		else
		{
			frameIndex = 0;
		}
		frameTime = 0.f;
		break;
	}
	case CommandoSprites::walk:
	{
		if (m_AbilityState == CommandoSprites::doubleTapA || m_AbilityState == CommandoSprites::doubleTapB)
		{
			m_MovementState = CommandoSprites::walkhalf;
		}
		if (frameTime >= timePerFrame)
		{
			++frameIndex;
			frameTime -= timePerFrame;
		}
		break;
	}
	case CommandoSprites::back:
	{
		if (m_AbilityState == CommandoSprites::doubleTapA || m_AbilityState == CommandoSprites::doubleTapB)
		{
			m_MovementState = CommandoSprites::backhalf;
		}
		if (frameTime >= timePerFrame)
		{
			++frameIndex;
			frameTime -= timePerFrame;
		}
		break;
	}
	case CommandoSprites::climbUp:
	case CommandoSprites::climbDown:
	{
		if (!pKeyStates[SDL_SCANCODE_UP] && !pKeyStates[SDL_SCANCODE_DOWN])
		{
			stopAnim = true;
		}
		if (frameTime >= 5.f / frameCap)
		{
			++frameIndex;
			frameTime -= 5.f / frameCap;
		}
		break;
	}
	default:
		break;
	}

	if (frameIndex > m_pFrameData->at(m_MovementState).size() - 1)
	{
		frameIndex = 0;
	}
	m_MovementData = m_pFrameData->at(m_MovementState).at(frameIndex);
	if (m_AbilityState == CommandoSprites::fullMetalJacket || m_AbilityState == CommandoSprites::singleSuppressive
		|| m_AbilityState == CommandoSprites::tacticalDive)
	{
		frameTime = 0.f;
	}
	else if (!stopAnim)
	{
		frameTime += elapsedSec;
	}
}

void Player::UpdateAbilityAnimations(float elapsedSec, size_t& frameIndex, float& frameTime)
{
	static int suppressiveFireShots{ 0 };

	if (m_AbilityState == CommandoSprites::none || m_MovementState == CommandoSprites::climbUp
		|| m_MovementState == CommandoSprites::climbDown)
	{
		return;
	}

	switch (m_AbilityState)
	{
	case CommandoSprites::doubleTapA:
	case CommandoSprites::doubleTapB:
	{
		if (frameTime >= 6.f / frameCap / (m_Stats.ATKSpeed / Stats{}.ATKSpeed))
		{
			++frameIndex;
			frameTime -= 6.f / frameCap / (m_Stats.ATKSpeed / Stats{}.ATKSpeed);
		}
		break;
	}
	case CommandoSprites::fullMetalJacket:
	{
		if (frameTime >= 5.f / frameCap)
		{
			++frameIndex;
			frameTime -= 5.f / frameCap;
		}
		break;
	}
	case CommandoSprites::tacticalDive:
	{
		if (frameTime >= 3.f / frameCap)
		{
			++frameIndex;
			frameTime -= 3.f / frameCap;
		}
		break;
	}
	case CommandoSprites::singleSuppressive:
	case CommandoSprites::doubleSuppressive:
	{
		int shotAmount{ static_cast<int>(floor(6.f * (m_Stats.ATKSpeed / Stats{}.ATKSpeed))) };

		if (frameTime >= 3.f / frameCap)
		{
			++frameIndex;
			frameTime -= 3.f / frameCap;
			if (frameIndex == 3)
			{
				frameIndex = 1;
				++suppressiveFireShots;
			}
			if (suppressiveFireShots >= shotAmount)
			{
				suppressiveFireShots = 0;
				frameIndex = 3;
			}
		}
		break;
	}
	default:
		break;
	}


	if (frameIndex > m_pFrameData->at(m_AbilityState).size() - 1)
	{
		frameIndex = 0;
		frameTime = 0.f;
		m_AbilityState = CommandoSprites::none;
	}

	if (m_AbilityState != CommandoSprites::none)
	{
		m_AbilityData = m_pFrameData->at(m_AbilityState).at(frameIndex);
		frameTime += elapsedSec;
	}

}

void Player::Abilities(const Uint8* pKeyState, float elapsedSec, const size_t& frameIndex, float frameTime)
{
	if (m_MovementState == CommandoSprites::climbUp || m_MovementState == CommandoSprites::climbDown)
	{
		return;
	}

	static float FMJCD{ 0.f };
	static float DiveCD{ 0.f };
	static float SFCD{ 0.f };

	if (frameIndex == 0 && frameTime <= 0.f)
	{
		if (pKeyState[SDL_SCANCODE_V] && SFCD <= 0.f)
		{
			m_AbilityState = CommandoSprites::singleSuppressive;
			SFCD = 5.f;
		}
		else if (pKeyState[SDL_SCANCODE_C] && DiveCD <= 0.f)
		{
			m_AbilityState = CommandoSprites::tacticalDive;
			m_Velocity.x = m_Direction * m_Stats.speed * 2.f;
			DiveCD = 4.f;
		}
		else if (pKeyState[SDL_SCANCODE_X] && FMJCD <= 0.f)
		{
			m_AbilityState = CommandoSprites::fullMetalJacket;
			FMJCD = 3.f;
		}
		else if (pKeyState[SDL_SCANCODE_Z])
		{
			bool leftHand{ static_cast<bool>(rand() % 2) };
			if (leftHand)
			{
				m_AbilityState = CommandoSprites::doubleTapA;
			}
			else
			{
				m_AbilityState = CommandoSprites::doubleTapB;
			}
		}
	}

	if (FMJCD > 0.f)
	{
		FMJCD -= elapsedSec;
	}
	if (DiveCD > 0.f)
	{
		DiveCD -= elapsedSec;
	}
	if (SFCD > 0.f)
	{
		SFCD -= elapsedSec;
	}
}

void Player::UpdatePosition(const Uint8* pKeyStates)
{
	if (m_AbilityState != CommandoSprites::fullMetalJacket
		&& m_AbilityState != CommandoSprites::singleSuppressive
		&& m_AbilityState != CommandoSprites::tacticalDive)
	{
		if (pKeyStates[SDL_SCANCODE_LEFT])
		{
			m_Velocity.x = -m_Stats.speed / 10.f;
		}
		else if (pKeyStates[SDL_SCANCODE_RIGHT])
		{
			m_Velocity.x = m_Stats.speed / 10.f;
		}
	}

	if (m_AbilityState != CommandoSprites::tacticalDive)
	{
		if (abs(m_Velocity.x) > 0.f)
		{
			m_Velocity.x *= 0.7f;
		}
		else
		{
			m_Velocity.x = 0;
		}
	}

	if (m_AbilityState == CommandoSprites::doubleTapA || m_AbilityState == CommandoSprites::doubleTapB)
	{
		m_Velocity.x *= 0.5f;
	}
	if (m_MovementState == CommandoSprites::back || m_MovementState == CommandoSprites::backhalf)
	{
		m_Velocity.x *= 0.5f;
	}

	if (m_MovementState != CommandoSprites::climbUp && m_MovementState != CommandoSprites::climbDown)
	{
		m_BottomMiddle.x += m_Velocity.x;
	}
	if (m_MovementState != CommandoSprites::tacticalDive)
	{
		m_BottomMiddle.y += m_Velocity.y;
	}
	//m_BottomMiddle.y += 1.f;

}
