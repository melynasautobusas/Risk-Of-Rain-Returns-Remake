#pragma once
#include <map>
#include "Texture.h";

class LevelManager
{
public:

	void Draw() const;
	void Update(float elapsedSec);

	Vector2f GetLevelSize() const;
private:
	const Vector2f m_LevelSize{ 11580.f, 3584.f }; // Desolate forest is this huge

	void DrawStaticTextures() const;
	void DrawDynamicTextures() const;
	void UpdateDynamicTextures();
};

