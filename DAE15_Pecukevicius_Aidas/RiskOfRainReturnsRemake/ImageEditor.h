#pragma once
#include "Matrix2x3.h"
#include "Texture.h"
#include "SDL.h"
#include <vector>
class ImageEditor final
{
public:
	ImageEditor();
	~ImageEditor();

	void Draw() const;

	void Zoom(float scale);
	void Move(const Vector2f& offset);
	void Reset();
	void AddPath(const std::string path);
	void SelectFrame();
	void SelectTexture();
	void Test();
private:
	Vector2f m_Offset{};
	float m_Scale{ 1.f };
	std::vector<std::string> m_PathFiles;
	const Texture* m_pTexture{nullptr};
	const std::string m_ResourceDirectory{ "../../RiskOfRainReturnsRemake/Resources/" };
};

