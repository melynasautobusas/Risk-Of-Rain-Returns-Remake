#pragma once
#include <map>
#include "GameInfo.h"
class FrameManager
{
public:
	explicit FrameManager();
	~FrameManager() = default;
	friend std::ostream& operator<<(std::ostream& out, const Rectf& frameInfo);


	std::map<CommandoState, std::vector<Rectf>>* GetPlayerData();

private:
	std::map<CommandoState, std::vector<Rectf>> m_PlayerData;
	void Initialize();
};

//void from_json(const nlohmann::json& j, FrameManager::FrameInfo& frameInfo);
//void to_json(nlohmann::json& j, const FrameManager::FrameInfo frameInfo);