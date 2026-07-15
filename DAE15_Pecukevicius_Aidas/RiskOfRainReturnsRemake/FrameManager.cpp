#include "pch.h"
#include "FrameManager.h"
#include <iostream>
#include <map>
/*
void FrameManager::WriteDataToPath(const std::string& fileName) const
{
	const std::string path{ "../../RiskOfRainReturnsRemake/Resources/" + fileName + ".json" };
	nlohmann::json j;
	std::ifstream inFile(path);

	if (!inFile.is_open())
	{
		std::cout << "creating file " << fileName << "\n";
		std::ofstream{ path };
		inFile.open(path);
	}

	std::string stateName;
	std::cout << "state name: ";
	std::cin >> stateName;

	if (inFile.peek() != std::ifstream::traits_type::eof())
	{
		j = nlohmann::json::parse(inFile);

		if (j.contains(stateName) && j[stateName].is_array())
		{
			std::cout << "do you want to change existing data? y/n: ";
			char answer;
			std::cin >> answer;
			if (answer != 'y')
			{
				return;
			}
		}
	}
	else
	{
		std::cout << "creating state " << stateName << "\n";
		j[stateName] = nlohmann::json::array();
	}
	inFile.close();

	FrameInfo newFrame{};
	int index{};
	{
		std::cout << "Frame Info:\n";
		std::cout << "index: ";
		std::cin >> index;
		std::cout << "left: ";
		std::cin >> newFrame.left;
		std::cout << "top: ";
		std::cin >> newFrame.top;
		std::cout << "width: ";
		std::cin >> newFrame.width;
		std::cout << "height: ";
		std::cin >> newFrame.height;
	}

	index = std::min(static_cast<int>(j[stateName].size()),
		std::max(0, index));

	if (j[stateName].empty() || index >= j[stateName].size())
	{
		j[stateName].emplace_back(newFrame);
	}
	else
	{
		j[stateName].at(index) = newFrame;
	}
	std::ofstream outFile(path);
	outFile << j.dump(4);
	outFile.close();
}
*/

void FrameManager::Initialize()
{
	{
		m_PlayerData.insert({ CommandoState::idle, std::vector<Rectf>{1} });
		m_PlayerData.insert({ CommandoState::walk, std::vector<Rectf>{8} });
		m_PlayerData.insert({ CommandoState::back, std::vector<Rectf>{8} });
		m_PlayerData.insert({ CommandoState::jump, std::vector<Rectf>{3} });
		m_PlayerData.insert({ CommandoState::climb, std::vector<Rectf>{6} });
		m_PlayerData.insert({ CommandoState::death, std::vector<Rectf>{8} });
	}
	{
		m_PlayerData.at(CommandoState::idle).at(0) = Rectf{ 6, 25, 17, 22 };
		for (size_t index{}; index < m_PlayerData.at(CommandoState::walk).size(); ++index)
		{
			m_PlayerData.at(CommandoState::walk).at(index) 
				= Rectf{ 6 + static_cast<float>(index) * 34, 58, 33, 30 };
		}
		for (size_t index{}; index < m_PlayerData.at(CommandoState::back).size(); ++index)
		{
			m_PlayerData.at(CommandoState::back).at(index)
				= Rectf{ 6 + static_cast<float>(index) * 16, 99, 15, 21 };
		}
		for (size_t index{}; index < m_PlayerData.at(CommandoState::climb).size(); ++index)
		{
			m_PlayerData.at(CommandoState::climb).at(index)
				= Rectf{ 5 + static_cast<float>(index) * 22, 235, 21, 29 };
		}
		for (size_t index{}; index < m_PlayerData.at(CommandoState::death).size(); ++index)
		{
			m_PlayerData.at(CommandoState::death).at(index)
				= Rectf{ 5 + static_cast<float>(index) * 41, 275, 40, 22 };
		}
	}
}

std::map<CommandoState, std::vector<Rectf>>* FrameManager::GetPlayerData()
{
	return &m_PlayerData;
}

//const std::map<PlayerState, std::vector<Rectf>>* FrameManager::GetPlayerFrameData() const
//{
//	return nullptr;
//}

//void from_json(const nlohmann::json& j, FrameManager::FrameInfo& frameInfo)
//{
//	j.at("left").get_to(frameInfo.left);
//	j.at("top").get_to(frameInfo.top);
//	j.at("width").get_to(frameInfo.width);
//	j.at("height").get_to(frameInfo.height);
//}
//
//void to_json(nlohmann::json& j, const FrameManager::FrameInfo frameInfo)
//{
//	j = nlohmann::json{ {"left", frameInfo.left }, {"top", frameInfo.top},
//		{"width", frameInfo.width}, {"height", frameInfo.height} };
//}

std::ostream& operator<<(std::ostream& out, const Rectf& frameInfo)
{
	out << "left: " << frameInfo.left << "\n";
	out << "top: " << frameInfo.bottom << "\n";
	out << "width: " << frameInfo.width << "\n";
	out << "height: " << frameInfo.height << "\n";
	return out;
}
