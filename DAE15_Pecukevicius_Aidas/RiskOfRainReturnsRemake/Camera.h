#pragma once
class Camera final
{
public:
	explicit Camera(const Vector2f& levelSize, const Vector2f& m_ScreenSize, float scale = 1.f);

	void Update(float elapsedSec);
	void Center() const;
	void Reset() const;
	void SetPlayerCenter(const Vector2f& playerCenter);

private:
	const Vector2f m_LevelSize{};
	const Vector2f m_ScreenSize{};
	const float m_Scale{};
	Vector2f m_PlayerCenter{};
};

