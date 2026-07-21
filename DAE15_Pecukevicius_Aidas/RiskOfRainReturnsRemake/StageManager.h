#pragma once
#include "Player.h"
#include "SpriteManager.h"
#include "FrameManager.h"
#include "nlohmann/json.hpp"
#include "Camera.h"
#include "LevelManager.h"

class StageManager
{
public:
	explicit StageManager(const Rectf& viewport); // give constructors to each manager class
	~StageManager() = default;

	void Initialize();
	void Draw() const;
	void Update(float elapsedSec);

private:
	Rectf m_Viewport{};
	const std::string m_ResourceDirectory{ "../../RiskOfRainReturnsRemake/Resources/" };

	SpriteManager m_SpriteManager;
	FrameManager m_FrameManager;
	LevelManager m_LevelManager;
	Player m_Player;
	Camera m_Camera;
};