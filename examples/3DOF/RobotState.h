#pragma once

class GCodeController;

#include "IK.h"

const double kMaxSpeed = 0.12; // m/s

class RobotState
{
public:
    struct Leg {
        Leg() {} //: onGround(true) {}

        IK::Vector pos;
        //bool   onGround;
    };

    RobotState(GCodeController& gcodeCtrl);

    bool Init();

    IK::Vector GetMoveVector (int legId, IK::Vector pos);
    IK::Vector GetPosByVector(int legId, IK::Vector v);

    int GetMoveTimeInMS(IK::Vector v, double speed);

    bool MoveLeg(int legId, IK::Vector pos, double speed);

    bool MoveBase(IK::Vector   v, double speed); // Relative move
    bool SetBase (IK::Vector pos, double speed); // Absolute move

    IK::Vector GetLegPositionInBaseFrame(int legId, IK::Vector pos);
    IK::Vector GetLegPositionInLegFrame (int legId, IK::Vector pos);

    IK::Vector GetAdjustedLegPosition(int legId, IK::Vector pos);

    void WaitForMove();

    bool GetCurrentPos();

public:
    IK::Vector m_speed; // m/s
    Leg m_leg[4];           // Position in leg frame
    Leg m_legAdjusted[4];   // Position after adjusting to base rotation and offset
    bool m_legToAdjust[4];

    double m_baseLength, m_baseWidth;

    IK::Vector m_rot; // Base rotation in rad
    IK::Vector m_baseOffset;

    int m_moveTime; // in ms

    GCodeController& m_gcodeCtrl;
};
