#include "pch.h"
#include "LevelManager.h"
#include <fstream>
#include "utils.h"

LevelManager::LevelManager()
	: m_LevelSize{ 11580.f, 3584.f }
{
	m_pArrMapData = new std::vector<MapData>{};
    ReadObjects();
    m_Object.hitbox = Rectf{
        0.f,
        -1.f,
        100.f, 1.f
    };
    //m_pArrMapData->push_back(m_Object);
    //DumpObjects();
}

LevelManager::~LevelManager()
{
	delete m_pArrMapData;
	m_pArrMapData = nullptr;
}

void LevelManager::Draw() const
{
    for (const MapData& hitbox : *m_pArrMapData)
    {
        utils::SetColor(Color4f{ 1.f, 1.f, 1.f, 1.f });
        utils::DrawRect(hitbox.hitbox);
    }
}

void LevelManager::Update(float elapsedSec)
{

}

const std::vector<MapData>* LevelManager::GetMapData()
{
	return m_pArrMapData;
}

Vector2f LevelManager::GetLevelSize() const
{
	return m_LevelSize;
}

void LevelManager::DrawStaticTextures() const
{
}

void LevelManager::DrawDynamicTextures() const
{
}

void LevelManager::UpdateDynamicTextures()
{
}

void LevelManager::DumpObjects()
{
    std::ofstream fout(resourceDirectory + "MapData.json");

    nlohmann::json j{};

    j["objectData"] = *m_pArrMapData;

    fout << j.dump(4);

    fout.close();
}

void LevelManager::ReadObjects()
{
    std::ifstream fin(resourceDirectory + "MapData.json");

    nlohmann::json j{ nlohmann::json::parse(fin) };

    *m_pArrMapData = j.at("objectData").get<std::vector<MapData>>();
}

void to_json(nlohmann::json& j, const MapData& data)
{
    j = {
        { "hitbox", {
            { "left", data.hitbox.left },
            { "bottom", data.hitbox.bottom },
            { "width", data.hitbox.width },
            { "height", data.hitbox.height }
        }},
        { "interactable", data.interactable }
    };
}

void from_json(const nlohmann::json& j, MapData& data)
{
    j.at("hitbox").at("left").get_to(data.hitbox.left);
    j.at("hitbox").at("bottom").get_to(data.hitbox.bottom);
    j.at("hitbox").at("width").get_to(data.hitbox.width);
    j.at("hitbox").at("height").get_to(data.hitbox.height);
    j.at("interactable").get_to(data.interactable);
}
