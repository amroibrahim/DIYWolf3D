#include "Angle.h"

#include <math.h>

# define M_PIl 3.141592653589793238462643383279502884L /* pi */

Angle::Angle()
{
	m_fAngle = 0;
}

Angle::Angle(float fAngle)
{
	m_fAngle = fAngle;
}

Angle::~Angle()
{
}

void Angle::Set(float fAngle)
{
	m_fAngle = 0;
	Add(fAngle);
}

void Angle::Add(float fAngle)
{
	m_fAngle += fAngle;

	if (m_fAngle < 0)
	{
		m_fAngle += 360;
	}
	else if (m_fAngle >= 360)
	{
		m_fAngle -= 360;
	}
}

float Angle::Get()
{
	return m_fAngle;
}

bool Angle::IsPointingUp()
{
	return !IsPointingDown();
}

bool Angle::IsPointingDown()
{
	if (180 <= m_fAngle && m_fAngle < 360)
	{
		return true;
	}
	return false;
}

bool Angle::IsPointingLeft()
{
	if (90 <= m_fAngle && m_fAngle < 270)
	{
		return true;
	}
	return false;
}

bool Angle::IsPointingRight()
{
	return !IsPointingLeft();
}

float Angle::DegreesToRadians(float fAngle)
{
	return fAngle * M_PIl / 180.0f;
}

float Angle::GetSin()
{
	return sin(DegreesToRadians(m_fAngle));
}

float Angle::GetCos()
{
	return cos(DegreesToRadians(m_fAngle));
}

float Angle::GetTan()
{
	return tan(DegreesToRadians(m_fAngle));
}