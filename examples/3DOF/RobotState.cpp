#include <math.h>
#include <string.h>

#include "Utils.h"
#include "RobotState.h"
#include "GCodeController.h"

RobotState::RobotState(GCodeController& gcodeCtrl) :
    m_gcodeCtrl(gcodeCtrl), m_moveTime(0), m_baseLength(0),m_baseWidth(0)
{
    Init();
}

bool RobotState::Init()
{
    for (int i = 0; i < 4; ++i) m_legToAdjust[i] = true;

    if (!GetCurrentPos()) return false;
    return true;
}

int RobotState::GetMoveTimeInMS(IK::Vector v, double speed)
{
    double dist = sqrt(v.x*v.x + v.y*v.y + v.z*v.z); // in meters
    m_moveTime = (dist / speed) * 1000;

    return m_moveTime;
}

IK::Vector RobotState::GetMoveVector(int legId, IK::Vector pos)
{
    IK::Vector v;

    v.x = m_legAdjusted[legId-1].pos.x - pos.x;
    v.y = m_legAdjusted[legId-1].pos.y - pos.y;
    v.z = m_legAdjusted[legId-1].pos.z - pos.z;

    return v;
}

IK::Vector RobotState::GetPosByVector(int legId, IK::Vector v)
{
    IK::Vector pos;

    pos.x = m_leg[legId-1].pos.x + v.x;
    pos.y = m_leg[legId-1].pos.y + v.y;
    pos.z = m_leg[legId-1].pos.z + v.z;

    return pos;
}

bool RobotState::MoveLeg(int legId, IK::Vector pos, double speed)
{
    IK::Vector p = GetAdjustedLegPosition(legId, pos);
    IK::Vector v = GetMoveVector(legId, p);
    m_moveTime = GetMoveTimeInMS(v, speed);

    m_leg        [legId-1].pos = pos;
    m_legAdjusted[legId-1].pos = p;

    return m_gcodeCtrl.add_point(legId, p, m_moveTime);
}

bool RobotState::MoveBase(IK::Vector v, double speed)
{
    for (int legId = 1; legId <= 4; ++legId) {
        IK::Vector pos = GetPosByVector(legId, v);

        if (!MoveLeg(legId, pos, speed)) return false;
    }
    return true;
}

bool RobotState::SetBase(IK::Vector pos, double speed)
{
    for (int legId = 1; legId <= 4; legId++) {
        if (!MoveLeg(legId, pos, speed)) return false;
    }
    return true;
}

IK::Vector RobotState::GetLegPositionInBaseFrame(int legId, IK::Vector pos)
{
    // Base axis: X along base legth (from robot center to forward), Y along base width (from robot center to left), Z is height (up)

    IK::Vector ret;

    ret.z = pos.y;

    switch (legId)
    {
    case 1:
        ret.x = pos.z + m_baseLength/2;
        ret.y = pos.x - m_baseWidth /2;
        break;
    case 2:
        ret.x = pos.z + m_baseLength/2;
        ret.y = pos.x + m_baseWidth /2;
        break;
    case 3:
        ret.x = pos.z - m_baseLength/2;
        ret.y = pos.x - m_baseWidth /2;
        break;
    case 4:
        ret.x = pos.z - m_baseLength/2;
        ret.y = pos.x + m_baseWidth /2;
        break;
    }

    return ret;
}

IK::Vector RobotState::GetLegPositionInLegFrame(int legId, IK::Vector pos)
{
    // Leg axis: X from leg's center to robot's left, Y from legs' center to down, Z from leg's center to robot forward

    IK::Vector ret;

    ret.y = pos.z;

    switch (legId)
    {
    case 1:
        ret.x = pos.y + m_baseWidth /2;
        ret.z = pos.x - m_baseLength/2;
        break;
    case 2:
        ret.x = pos.y - m_baseWidth /2;
        ret.z = pos.x - m_baseLength/2;
        break;
    case 3:
        ret.x = pos.y + m_baseWidth /2;
        ret.z = pos.x + m_baseLength/2;
        break;
    case 4:
        ret.x = pos.y - m_baseWidth /2;
        ret.z = pos.x + m_baseLength/2;
        break;
    }

    return ret;
}

// Adjust by base rotation (m_rot) and offset (m_baseOffset)
IK::Vector RobotState::GetAdjustedLegPosition(int legId, IK::Vector pos)
{
    IK::Vector legRoot; // = { 0, 0, 0 }
    IK::Vector legInBaseFrame = GetLegPositionInBaseFrame(legId, legRoot);

    IK::Vector legPos = m_legToAdjust[legId] ? IK::rotate(legInBaseFrame, m_rot) : legInBaseFrame;

    legPos.x -= m_baseOffset.x;
    legPos.y -= m_baseOffset.y;
    legPos.z += m_baseOffset.z;

    IK::Vector offset = GetLegPositionInLegFrame(legId, legPos);

    pos.x += offset.x;
    pos.y += offset.y;
    pos.z += offset.z;

    return pos;
}

void RobotState::WaitForMove()
{
    utils::delay_ms(m_moveTime);
}

bool RobotState::GetCurrentPos()
{
    // ToDo: get from servo pos + forward kinematics
    return true;
}
