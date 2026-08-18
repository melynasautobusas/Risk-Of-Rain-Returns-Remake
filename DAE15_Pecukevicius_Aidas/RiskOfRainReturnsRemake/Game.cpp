#include "pch.h"
#include "Game.h"
#include <iostream>

Game::Game(const Window& window)
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	m_StageManager.Initialize();
}

void Game::Cleanup()
{
}

void Game::Update(float elapsedSec)
{
	static float elapsedTime{ 0.f };

	elapsedTime += elapsedSec;

	while (elapsedTime >= 1.f / frameCap) // while to account for lag
	{
		m_StageManager.Update();
		elapsedTime -= 1.f / frameCap;
	}
}

void Game::Draw() const
{
	ClearBackground();
	m_StageManager.Draw();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	m_StageManager.KeyInput(e);
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	m_StageManager.MouseInput(e);
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
}

void Game::ClearBackground() const
{
	glClearColor(0.0f, 0.80f, 0.80f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}