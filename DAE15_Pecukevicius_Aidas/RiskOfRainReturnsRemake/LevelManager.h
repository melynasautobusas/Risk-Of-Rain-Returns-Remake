#pragma once
#include <map>
#include "Texture.h"
#include "GameInfo.h"

class LevelManager final
{
public:
	explicit LevelManager();
	~LevelManager();

	void Draw() const;
	void Update(float elapsedSec);

	const std::vector<MapData>* GetMapData();

	Vector2f GetLevelSize() const;
private:
	enum class MapObjectName {
		grassTile
	};
	const Vector2f m_LevelSize{}; // Desolate forest is this huge

	MapData m_Object{};
	std::vector<MapData>* m_pArrMapData{};

	void DrawStaticTextures() const;
	void DrawDynamicTextures() const;
	void UpdateDynamicTextures();
	void DumpObjects();
	void ReadObjects();
};

void to_json(nlohmann::json& j, const MapData& data);
void from_json(const nlohmann::json& j, MapData& data);


