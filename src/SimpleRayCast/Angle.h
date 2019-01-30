#pragma once
class Angle
{
public:
    Angle();
    Angle(float fAngle);
    ~Angle();

    void Set(float fAngle);
    void Add(float fAngle);

    float Get();
    float GetSin();
    float GetCos();
    float GetTan();

    bool IsPointingUp();
    bool IsPointingDown();
    bool IsPointingLeft();
    bool IsPointingRight();

    static float DegreesToRadians(float fAngle);

protected:

    float m_fAngle;
};

