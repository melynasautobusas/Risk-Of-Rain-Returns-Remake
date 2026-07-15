#include "pch.h"
#include "ImageEditor.h"
#include <iostream>

ImageEditor::ImageEditor()
{
	std::cout << "Controls:\n";
	std::cout << "Z - Zoom in\n";
	std::cout << "X - Zoom out\n";
}

ImageEditor::~ImageEditor()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void ImageEditor::Draw() const
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Draw();
	}
}

void ImageEditor::Zoom()
{
	//Matrix2x3 scale{};
	//scale.SetAsScale();

	std::cout << "on\n";
}

void ImageEditor::Move()
{
}

void ImageEditor::Reset()
{
	m_Transformation = Matrix2x3{};
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
