#pragma once
#include "Texture.h"
#include <vector>
#include <map>
#include <fstream>
class FrameDataManager final
{
public:
	explicit FrameDataManager();
	~FrameDataManager() = default;

	void Draw() const;
	void SelectFrame();
	void MoveFrame();

private:
	Rectf m_SavedFrame{};
	std::string m_Directory{"/Resources/"};
};

