#pragma once

#include "Map.h"
#include "Angle.h"

class Player
{
public:
    Player(int iFieldOfView);
    ~Player();

    void SetPositionX(int iPositionX);
    void SetPositionY(int iPositionY);
    void SetAngle(float fAngle);

    void MoveForward();
    void MoveBackward();
    void RotateLeft();
    void RotateRight();

    int GetFieldOfView();
    float GetPositionX();
    float GetPositionY();
    float GetAngle();

    bool IsFacingUp();
    bool IsFacingDown();
    bool IsFacingLeft();
    bool IsFacingRight();

    //protected:
    int m_iFieldOfView;
    int m_iRotationSpeedMultiplier;
    int m_iMoveSpeedMultiplier;
    float m_iPositionX;
    float m_iPositionY;
    Angle m_Angle;
};

