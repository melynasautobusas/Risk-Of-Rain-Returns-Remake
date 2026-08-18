#include "pch.h"
#include "DataManager.h"

static float textureHeight;

using json = nlohmann::json;

DataManager::DataManager(const Rectf& viewport)
	: m_Viewport{ viewport }
{
	ReadJsonFile(m_Data, "CommandoFrameData");
	//std::cout << ", - Enter Debug Mode\n";
	m_Texture = new Texture{ resourceDirectory + "CommandoSpriteSheet.png" };
	textureHeight = m_Texture->GetHeight();
}

DataManager::~DataManager()
{
	delete m_Texture;
	m_Texture = nullptr;
}

void DataManager::Draw() const
{
	if (m_PlayAnimation)
	{
		DrawAnimation();
	}
	else
	{
		glPushMatrix();
		// Apply translation first, then scale so: screen = m_Scale * world + m_Offset
		glTranslatef(m_Offset.x, m_Offset.y, 0.f);
		glScalef(m_Scale, m_Scale, 1.f);

		if (m_Texture != nullptr)
		{
			m_Texture->Draw();
		}
		DrawEntityFrameData(m_EntityData);
		DrawCurrentStateFrames();
		utils::SetColor(Color4f{ 1.f, 1.f, 1.f, 1.f });
		utils::DrawRect(m_SavedFrame);
		glPopMatrix();
	}
}

void DataManager::Update(float elapsedSec)
{
	if (m_PlayAnimation)
	{
		UpdateAnimation(elapsedSec);
	}
}

void DataManager::KeyInput(const SDL_KeyboardEvent& e)
{
	if (e.keysym.sym == SDLK_COMMA)
	{
		std::cout << "exit - Exit\n";
		std::cout << "read - Read Json\n";
		std::cout << "add - Add frame data to vector\n";
		std::cout << "save - Save vector to Json\n";
		std::cout << "dump - Dump to Json File\n";
		std::cout << "gfd - Get key frame data from json\n";
		std::cout << "clear - Clear vector\n";
		std::cout << "get - Get Keys\n";
		std::cout << "edit - Edit Mode\n";
		std::string action{};
		do
		{
			std::cin >> action;
			if (action == "read")
			{
				std::string file;
				std::cout << "File name: ";
				std::cin >> file;
				ReadJsonFile(m_Data, file);
			}
			else if (action == "add")
			{
				size_t index{};
				std::cout << "Index: ";
				std::cin >> index;
				m_arrEntityFrames.resize(index + 1);
				m_arrEntityFrames.at(index) = m_EntityData;
			}
			else if (action == "save")
			{
				std::string key;
				std::cout << "Key name: ";
				std::cin >> key;
				SaveFrameDataToKey(key);
			}
			else if (action == "dump")
			{
				std::string file{ "CommandoFrameData" };
				//std::cout << "File name: ";
				//std::cin >> file;
				DumpToJson(file);
			}
			else if (action == "gfd")
			{
				std::string key;
				std::cout << "Key name: ";
				std::cin >> key;
				GetFrameDataVec(key);
			}
			else if (action == "clear")
			{
				ClearVector();
				m_ReadFromJson = false;
			}
			else if (action == "get")
			{
				for (const auto& key : m_Data.items())
				{
					std::cout << key.key() << '\n';
				}
			}
			else if (action == "edit")
			{
				if (!m_Edit)
				{
					std::cout << "Entering Edit\n";
				}
				else
				{
					std::cout << "Exiting Edit\n";
				}
				m_Edit = !m_Edit;
			}
		} while (action != "exit");

		std::cout << "--Exiting Json Debug mode--\n";
	}

	switch (e.keysym.sym)
	{
	case SDLK_z:
	{
		m_Scale += 0.2f;
		break;
	}
	case SDLK_x:
	{
		m_Scale -= 0.2f;
		break;
	}
	case SDLK_UP:
	{
		m_Offset.y -= 5.f * m_Scale;
		break;
	}
	case SDLK_DOWN:
	{
		m_Offset.y += 5.f * m_Scale;
		break;
	}
	case SDLK_LEFT:
	{
		m_Offset.x -= 5.f * m_Scale;
		break;
	}
	case SDLK_RIGHT:
	{
		m_Offset.x += 5.f * m_Scale;
		break;
	}
	case SDLK_r:
	{
		RecalcFrame();
		break;
	}
	case SDLK_1:
	{
		m_EntityData.sourceRect = m_SavedFrame;
		break;
	}
	case SDLK_2:
	{
		m_EntityData.hitbox.left = abs(m_SavedFrame.left - m_EntityData.sourceRect.left);
		m_EntityData.hitbox.bottom = abs(m_SavedFrame.bottom - m_EntityData.sourceRect.bottom);
		m_EntityData.hitbox.width = m_SavedFrame.width;
		m_EntityData.hitbox.height = m_SavedFrame.height;
		break;
	}
	case SDLK_3:
	{
		m_EntityData.pivotPoint = Vector2f{ m_EntityData.hitbox.width * 0.5f, 0.f };
		break;
	}
	case SDLK_w:
	{
		m_EntityData.pivotPoint.y += 0.5f;
		break;
	}
	case SDLK_s:
	{
		m_EntityData.pivotPoint.y -= 0.5f;
		break;
	}
	case SDLK_a:
	{
		m_EntityData.pivotPoint.x -= 0.5f;
		break;
	}
	case SDLK_d:
	{
		m_EntityData.pivotPoint.x += 0.5f;
		break;
	}
	case SDLK_SPACE:
	{
		if (!m_arrEntityFrames.empty())
		{
			m_PlayAnimation = !m_PlayAnimation;
			m_FrameIdx = 0;
		}
		break;
	}
	case SDLK_TAB:
	{
		if (!m_PlayAnimation && m_EntityData.sourceRect.width != 0)
		{
			if (m_Edit)
			{
				m_arrEntityFrames.at(m_FrameIdx) = m_EntityData;
			}
			else
			{
				m_arrEntityFrames.push_back(m_EntityData);
			}
		}
		break;
	}
	case SDLK_KP_4:
	{
		--m_FrameIdx;
		if (m_FrameIdx < 0)
		{
			m_FrameIdx = static_cast<int>(m_arrEntityFrames.size()) - 1;
		}
		m_EntityData = m_arrEntityFrames.at(m_FrameIdx);
		break;
	}
	case SDLK_KP_6:
	{
		++m_FrameIdx;
		if (m_FrameIdx > m_arrEntityFrames.size() - 1)
		{
			m_FrameIdx = 0;
		}
		m_EntityData = m_arrEntityFrames.at(m_FrameIdx);
		break;
	}
	}
}

void DataManager::MouseInput(const SDL_MouseButtonEvent& e)
{
	const float x = static_cast<float>(e.x);
	const float y = static_cast<float>(e.y);
	const Vector2f point{ (x - m_Offset.x) / m_Scale, (y - m_Offset.y) / m_Scale };

	if (e.button == SDL_BUTTON_LEFT)
	{
		m_BottomLeft = point;
	}
	else if (e.button == SDL_BUTTON_RIGHT)
	{
		m_TopRight = point;
	}
}

void DataManager::SetCommandoData(std::map<CommandoSprites, std::vector<EntityData>>* pData)
{
	std::ifstream fin(resourceDirectory + "CommandoFrameData.json");

	nlohmann::json jcommando{ nlohmann::json::parse(fin) };

	pData->insert({ CommandoSprites::idle, jcommando.at("idle").get<std::vector<EntityData>>() });
	pData->insert({ CommandoSprites::walk, jcommando.at("walk").get<std::vector<EntityData>>() });
	pData->insert({ CommandoSprites::walkhalf, jcommando.at("walkhalf").get<std::vector<EntityData>>() });
	pData->insert({ CommandoSprites::jump, jcommando.at("jump").get<std::vector<EntityData>>() });
	pData->insert({ CommandoSprites::peak, jcommando.at("peak").get<std::vector<EntityData>>() });
	pData->insert({ CommandoSprites::fall, jcommando.at("fall").get<std::vector<EntityData>>() });
	pData->insert({ CommandoSprites::climbUp, jcommando.at("climbup").get<std::vector<EntityData>>() });
	pData->insert({ CommandoSprites::climbDown, jcommando.at("climbdown").get<std::vector<EntityData>>() });
	pData->insert({ CommandoSprites::death, jcommando.at("death").get<std::vector<EntityData>>() });
	pData->insert({ CommandoSprites::back, jcommando.at("back").get<std::vector<EntityData>>() });
	pData->insert({ CommandoSprites::backhalf, jcommando.at("backhalf").get<std::vector<EntityData>>() });
	pData->insert({ CommandoSprites::doubleTapA,
		jcommando.at("doubletapa").get<std::vector<EntityData>>() });
	pData->insert({ CommandoSprites::doubleTapB,
		jcommando.at("doubletapb").get<std::vector<EntityData>>() });
	pData->insert({ CommandoSprites::fullMetalJacket,
		jcommando.at("fmt").get<std::vector<EntityData>>() });
	pData->insert({ CommandoSprites::singleSuppressive,
		jcommando.at("sfsingle").get<std::vector<EntityData>>() });
	pData->insert({ CommandoSprites::doubleSuppressive,
		jcommando.at("sfdouble").get<std::vector<EntityData>>() });
	pData->insert({ CommandoSprites::tracer,
		jcommando.at("tracer").get<std::vector<EntityData>>() });
	pData->insert({ CommandoSprites::tacticalDive,
		jcommando.at("dive").get<std::vector<EntityData>>() });
}

void DataManager::RecalcFrame()
{
	const float left = std::min(m_BottomLeft.x, m_TopRight.x);
	const float top = std::min(m_BottomLeft.y, m_TopRight.y);
	const float width = std::abs(m_TopRight.x - m_BottomLeft.x);
	const float height = std::abs(m_TopRight.y - m_BottomLeft.y);

	m_SavedFrame.left = std::trunc(left);
	m_SavedFrame.bottom = std::trunc(top);
	m_SavedFrame.width = std::trunc(width) + 1.f;
	m_SavedFrame.height = std::trunc(height) + 1.f;
}

void DataManager::DrawEntityFrameData(const EntityData& data) const
{
	utils::SetColor(Color4f{ 0.f, 1.f, 0.f, 1.f });
	Rectf sourceRect{
		data.sourceRect.left,
		data.sourceRect.bottom,
		data.sourceRect.width,
		data.sourceRect.height
	};
	utils::DrawRect(sourceRect);

	utils::SetColor(Color4f{ 1.f, 0.f, 0.f, 1.f });
	Rectf localHitbox{
		sourceRect.left + data.hitbox.left,
		sourceRect.bottom + data.hitbox.bottom,
		data.hitbox.width,
		data.hitbox.height
	};
	utils::DrawRect(localHitbox);

	utils::SetColor(Color4f{ 0.f, 0.f, 1.f, 1.f });
	Vector2f localPivot{
		data.pivotPoint.x + sourceRect.left,
		data.pivotPoint.y + sourceRect.bottom
	};
	utils::FillEllipse(localPivot, 2.f, 2.f);
}

void DataManager::SaveFrameDataToKey(const std::string& key)
{
	m_Data[key] = m_arrEntityFrames;
}

void DataManager::DrawCurrentStateFrames() const
{
	for (const EntityData& entityData : m_arrEntityFrames)
	{
		DrawEntityFrameData(entityData);
	}
}

void DataManager::GetFrameDataVec(const std::string& key)
{
	if (!m_Data.contains(key))
	{
		std::cout << "key doesn't exist\n";
		return;
	}
	m_arrEntityFrames = m_Data.at(key).get<std::vector<EntityData>>();
	m_ReadFromJson = true;

	for (EntityData& data : m_arrEntityFrames)
	{
		data.sourceRect.bottom = abs(data.sourceRect.bottom - textureHeight + data.sourceRect.height);
	}
}

void DataManager::ClearVector()
{
	m_arrEntityFrames.clear();
}

void DataManager::UpdateAnimation(float elapsedSec)
{
	m_ElapsedTime += elapsedSec / frameCap;
	if (m_ElapsedTime >= 1.f / frameCap / 10.f)
	{
		m_ElapsedTime = 0.f;
		++m_FrameIdx;
	}
	if (m_FrameIdx >= m_arrEntityFrames.size())
	{
		m_FrameIdx = 0;
	}
}

void DataManager::DrawAnimation() const
{
	Vector2f bottomMiddle{20.f, 10.f};
	Rectf sourceRect{ m_arrEntityFrames.at(m_FrameIdx).sourceRect };
	sourceRect.bottom = abs(sourceRect.bottom - textureHeight + sourceRect.height);

	Rectf hitbox{ m_arrEntityFrames.at(m_FrameIdx).hitbox };
	Vector2f pivot{ m_arrEntityFrames.at(m_FrameIdx).pivotPoint };

	hitbox.left = hitbox.left + bottomMiddle.x - pivot.x;
	hitbox.bottom = hitbox.bottom + bottomMiddle.y - pivot.y;

	glPushMatrix();
	glScalef(m_Scale, m_Scale, 1.f);
	m_Texture->Draw(bottomMiddle - pivot, sourceRect);
	utils::SetColor(Color4f{ 1.f, 0.f, 0.f, 1.f });
	utils::DrawRect(hitbox);
	utils::SetColor(Color4f{ 1.f, 1.f, 1.f, 1.f });
	utils::FillEllipse(bottomMiddle, 2.f, 2.f);
	glPopMatrix();
}

void DataManager::CreateJsonFile(const std::string& fileName, const nlohmann::json& j)
{
	if (JsonFileExists(fileName))
	{
		std::cout << "Json already exists!\n";
		return;
	}
	std::ofstream fout(resourceDirectory + fileName + ".json");

	fout << j.dump(4);

	fout.close();
}

bool DataManager::JsonFileExists(const std::string& fileName)
{
	std::ifstream fin(resourceDirectory + fileName + ".json");
	return fin.is_open();
}

void DataManager::ReadJsonFile(nlohmann::json& j, const std::string fileName)
{
	if (JsonFileExists(fileName))
	{
		std::cout << "Reading from " << fileName << ".json\n";
	}
	else
	{
		std::cout << "Json not found!\n";
		return;
	}

	std::ifstream fin(resourceDirectory + fileName + ".json");

	j = json::parse(fin);

	fin.close();

	//for (const auto& item : j.items())
	//{
	//	std::cout << item.key() << "\n";
	//}
}

void DataManager::DumpToJson(const std::string& fileName)
{
	if (!JsonFileExists(fileName))
	{
		std::cout << "File doesn't exist\n";
		return;
	}
	std::ofstream fout(resourceDirectory + fileName + ".json");

	fout << m_Data.dump(4);

	fout.close();
}

void to_json(nlohmann::json& j, const EntityData& data)
{
	j = {
		{"pivotPoint", {
			{"x", data.pivotPoint.x},
			{"y", data.pivotPoint.y}
		}},
		{"sourceRect", {
			{"left", data.sourceRect.left},
			{"bottom", abs(data.sourceRect.bottom - textureHeight + data.sourceRect.height)},
			{"width", data.sourceRect.width},
			{"height", data.sourceRect.height}
		}},
		{"hitbox", {
			{"left", data.hitbox.left},
			{"bottom", data.hitbox.bottom},
			{"width", data.hitbox.width},
			{"height", data.hitbox.height}
		}}
	};
}

void from_json(const nlohmann::json& j, EntityData& data)
{
	j.at("pivotPoint").at("x").get_to(data.pivotPoint.x);
	j.at("pivotPoint").at("y").get_to(data.pivotPoint.y);

	j.at("sourceRect").at("left").get_to(data.sourceRect.left);
	j.at("sourceRect").at("bottom").get_to(data.sourceRect.bottom);
	j.at("sourceRect").at("width").get_to(data.sourceRect.width);
	j.at("sourceRect").at("height").get_to(data.sourceRect.height);

	j.at("hitbox").at("left").get_to(data.hitbox.left);
	j.at("hitbox").at("bottom").get_to(data.hitbox.bottom);
	j.at("hitbox").at("width").get_to(data.hitbox.width);
	j.at("hitbox").at("height").get_to(data.hitbox.height);
}