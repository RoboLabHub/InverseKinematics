# Inverse Kinematics (IK) demystify

The IK is a set of a mathematical formulas that allows to calculate the joint positions (the angels for servos that move joints) for the end-effector in the 3D or 3D space (depends on application).

NB! Depends of joints count and types (revolute or prismatic) the formula will be different. So, you can't just take the IK formula and attach it to another robot with different configuration (count of joints, length, types). You have to modify the IK formula and tune it.

Here the example of IK formula for my 3DOF quadruped robot leg:


Here the example for 6DOF robot arm:
https://github.com/thomashiemstra/robot_arm_with_vision/blob/master/src/IK.cpp

To get understand how these formulas are created please check this set of videos:
https://www.youtube.com/watch?v=rJx_XZ8xz6w

Manipulator types:
https://www.youtube.com/watch?v=lySKu7qtfCs
