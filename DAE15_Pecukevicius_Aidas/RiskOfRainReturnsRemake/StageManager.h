#pragma once
#include "Player.h"
#include "SpriteManager.h"
#include "LevelManager.h"
#include "Camera.h"
#include "DataManager.h"
#include "Collider.h"

class StageManager
{
public:
	explicit StageManager(const Rectf& viewport); 
	~StageManager() = default;

	void Initialize();
	void Draw() const;
	void Update();
	void KeyInput(const SDL_KeyboardEvent& e);
	void MouseInput(const SDL_MouseButtonEvent& e);

private:
	const Rectf m_Viewport;
	bool m_ManageSprites{ false };
	float m_Scale{ 5.f };

	SpriteManager m_SpriteManager;
	LevelManager m_LevelManager;
	Player m_Player;
	Camera m_Camera;
	DataManager m_DataManager{ m_Viewport };
	Collider m_Collider{};
};