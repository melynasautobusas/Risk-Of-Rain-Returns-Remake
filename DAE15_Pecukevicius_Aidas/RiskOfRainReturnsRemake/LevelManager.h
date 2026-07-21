#pragma once
#include <map>
#include "Texture.h"

class LevelManager final
{
public:
	explicit LevelManager();
	~LevelManager() = default;

	void Draw() const;
	void Update(float elapsedSec);

	Vector2f GetLevelSize() const;
private:
	const Vector2f m_LevelSize{}; // Desolate forest is this huge

	void DrawStaticTextures() const;
	void DrawDynamicTextures() const;
	void UpdateDynamicTextures();
};

