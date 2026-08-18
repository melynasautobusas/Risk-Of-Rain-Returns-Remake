#pragma once
#include "Texture.h"
#include "utils.h"
#include <vector>
#include <fstream>
#include <iostream>
#include "GameInfo.h"
class DataManager final
{
public:
	explicit DataManager(const Rectf& viewport);
	~DataManager();

	void Draw() const;
	void Update(float elapsedSec);
	void KeyInput(const SDL_KeyboardEvent& e);
	void MouseInput(const SDL_MouseButtonEvent& e);

	void SetCommandoData(std::map<CommandoSprites, std::vector<EntityData>>* pData);

private:
	EntityData m_EntityData{};
	std::vector<EntityData> m_arrEntityFrames;
	const Rectf m_Viewport;

	float m_Scale{ 10.f };
	Vector2f m_Offset{ 0.f, -2400.f * m_Scale };
	Vector2f m_BottomLeft{};
	Vector2f m_TopRight{};
	Rectf m_SavedFrame{};
	Rectf m_SavedHitbox{};

	Texture* m_Texture{};
	nlohmann::json m_Data{ nlohmann::json::object() };

	bool m_PlayAnimation{ false };
	bool m_Edit{ false };
	bool m_ReadFromJson{ false };
	float m_ElapsedTime{};
	int m_FrameIdx{ 0 };

	void CreateJsonFile(const std::string& fileName, const nlohmann::json& j = nlohmann::json::object());
	bool JsonFileExists(const std::string& fileName);
	void ReadJsonFile(nlohmann::json& j, const std::string fileName);
	void DumpToJson(const std::string& fileName);
	void RecalcFrame();
	void DrawEntityFrameData(const EntityData& data) const;
	void SaveFrameDataToKey(const std::string& key);
	void DrawCurrentStateFrames() const;
	void GetFrameDataVec(const std::string& key);
	void ClearVector();
	void UpdateAnimation(float elapsedSec);
	void DrawAnimation() const;
};

void to_json(nlohmann::json& j, const EntityData& data);
void from_json(const nlohmann::json& j, EntityData& data);
