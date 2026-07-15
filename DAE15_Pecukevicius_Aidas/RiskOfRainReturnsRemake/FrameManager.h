#pragma once
#include <map>
#include "GameInfo.h"
class FrameManager
{
public:
	friend std::ostream& operator<<(std::ostream& out, const Rectf& frameInfo);

	void Initialize();

	std::map<CommandoState, std::vector<Rectf>>* GetPlayerData();

private:
	std::map<CommandoState, std::vector<Rectf>> m_PlayerData;

};

//void from_json(const nlohmann::json& j, FrameManager::FrameInfo& frameInfo);
//void to_json(nlohmann::json& j, const FrameManager::FrameInfo frameInfo);