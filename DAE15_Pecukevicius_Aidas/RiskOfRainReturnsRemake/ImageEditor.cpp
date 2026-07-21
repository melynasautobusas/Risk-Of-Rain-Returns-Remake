#include "pch.h"
#include "ImageEditor.h"
#include <iostream>

ImageEditor::ImageEditor()
{
	std::cout << "Controls:\n";
	std::cout << "Z - Zoom in\n";
	std::cout << "X - Zoom out\n";

	m_pTexture = new Texture{ "CommandoSpriteSheetA0.png" };
}

ImageEditor::~ImageEditor()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void ImageEditor::Draw() const
{
	glPushMatrix();
	glScalef(m_Scale, m_Scale, 1.f);
	if (m_pTexture != nullptr)
	{
		m_pTexture->Draw(m_Offset);
	}
	glPopMatrix();
}

void ImageEditor::Zoom(float scale)
{
	m_Scale += scale;
}

void ImageEditor::Move(const Vector2f& offset)
{
	m_Offset += offset;
}

void ImageEditor::Reset()
{
	m_Offset = Vector2f{};
	m_Scale = 1.f;
}

void ImageEditor::AddPath(const std::string path)
{
	std::cout << "Adding path: " << path << "\n";

	m_PathFiles.emplace_back(path);
}

void ImageEditor::SelectFrame()
{
}

void ImageEditor::SelectTexture()
{
	if (m_PathFiles.size() == 0)
	{
		std::cout << "No path specified\n";
	}
	else
	{
		for (int index{ 0 }; index < m_PathFiles.size(); ++index)
		{
			std::cout << index << ' ' << m_PathFiles.at(index) << "\n";
		}
	}

	int index{ 0 };

	do
	{
		std::cout << "Select index : ";
		std::cin >> index;
	} while (index > m_PathFiles.size());

	std::cout << "Selected " << m_PathFiles.at(index) << "\n";

	if (Texture{ m_PathFiles.at(index) }.IsCreationOk())
	{
		std::cout << "Success!\n";
		if (m_pTexture != nullptr)
		{
			delete m_pTexture;
			m_pTexture = nullptr;
		}

		m_pTexture = new Texture{ m_PathFiles.at(index) };
	}
}

void ImageEditor::Test()
{
	SDL_Event e{};

	while (SDL_PollEvent(&e) != 0)
	{
		std::cout << "runin\n";
	}
}
