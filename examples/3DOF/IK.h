
#pragma once

#define PI          3.141592653589793238462
#define half_pi     (PI / 2.0)
#define degtorad    (PI / 180.0)
#define radtodeg    (180.0 / PI)

class IK
{
public:
    struct Vector {
        Vector() : x(0), y(0), z(0) {}

        double x, y, z;
    };

    IK(double link1, double link2, double link3);

    void inverseKinematics(double x, double y, double z, double angles[3]);

    static IK::Vector rotate(IK::Vector pos, IK::Vector rot);

    static double toRad(double a);
    static double toDeg(double a);

public:
    double m_L1, m_L2, m_L3;
};
