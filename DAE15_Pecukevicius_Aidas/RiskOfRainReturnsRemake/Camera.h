#pragma once
class Camera final
{
public:
	explicit Camera(const Vector2f& levelSize, const Vector2f& m_ScreenSize, float scale = 1.f);
	~Camera() = default;

	void Update(float elapsedSec);
	void Center(const Vector2f & bottomCenter) const;
	void Reset() const;
private:
	const Vector2f m_LevelSize{};
	const Vector2f m_ScreenSize{};
	const float m_Scale{3.f};
};