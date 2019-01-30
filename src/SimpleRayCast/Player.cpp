#include "Player.h"

Player::Player(int iFieldOfView)
{
    m_iFieldOfView = iFieldOfView;
    m_iRotationSpeedMultiplier = 4;
    m_iMoveSpeedMultiplier = 2;
}

Player::~Player()
{
}

void Player::SetPositionX(int iPositionX)
{
    m_iPositionX = iPositionX;
}

void Player::SetPositionY(int iPositionY)
{
    m_iPositionY = iPositionY;
}

void Player::SetAngle(float fAngle)
{
    m_Angle.Set(fAngle);
}

float Player::GetPositionX()
{
    return m_iPositionX;
}

float Player::GetPositionY()
{
    return m_iPositionY;
}

float Player::GetAngle()
{
    return m_Angle.Get();
}

int Player::GetFieldOfView()
{
    return m_iFieldOfView;
}

void Player::MoveForward()
{
    m_iPositionX += m_Angle.GetCos() * m_iMoveSpeedMultiplier;
    m_iPositionY += -m_Angle.GetSin() * m_iMoveSpeedMultiplier;
}

void Player::MoveBackward()
{
    m_iPositionX -= m_Angle.GetCos() * m_iMoveSpeedMultiplier;
    m_iPositionY -= -m_Angle.GetSin()* m_iMoveSpeedMultiplier;
}

void Player::RotateLeft()
{
    m_Angle.Add(0.1875 * m_iRotationSpeedMultiplier);
}

void Player::RotateRight()
{
    m_Angle.Add(-0.1875 * m_iRotationSpeedMultiplier);
}

bool Player::IsFacingUp()
{
    return m_Angle.IsPointingUp();
}

bool Player::IsFacingDown()
{
    return m_Angle.IsPointingDown();
}

bool Player::IsFacingLeft()
{
    return m_Angle.IsPointingLeft();
}

bool Player::IsFacingRight()
{
    return m_Angle.IsPointingRight();
}