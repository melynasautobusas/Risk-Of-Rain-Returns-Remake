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

	void Zoom();
	void Move();
	void Reset();
	void AddPath(const std::string path);
	void SelectFrame();
	void SelectTexture();
	void Test();
private:
	std::vector<std::string> m_PathFiles;
	const Texture* m_pTexture{nullptr};
	Matrix2x3 m_Transformation{};
};

