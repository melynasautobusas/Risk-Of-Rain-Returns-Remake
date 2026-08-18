#include "pch.h"
#include "Camera.h"

Camera::Camera(const Vector2f& levelSize, const Vector2f& screenSize, float scale)
	: m_LevelSize{levelSize}
	, m_ScreenSize{screenSize}
	, m_Scale{scale}
{
}

void Camera::Center(const Vector2f& bottomCenter) const
{
	glPushMatrix();
	glTranslatef(m_ScreenSize.x * 0.5f, m_ScreenSize.y * 0.5f, 0.f);
}

void Camera::Reset() const
{
	glPopMatrix();
}