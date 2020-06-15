# Inverse Kinematics (IK) demystify

The IK is a set of a mathematical formulas that allows to calculate the joint positions (the angels for servos that move joints) for the end-effector in the 2D or 3D space (depends on application).

NB! Depends of joints count and types (revolute or prismatic) the formula will be different. So, you can't just take the IK formula and attach it to another robot with different configuration (count of joints, length and types). You have to modify the IK formula and tune it using special methods, for example, like this one:</br>
https://en.wikipedia.org/wiki/Denavit%E2%80%93Hartenberg_parameters

Here the example of the IK formula for my 3DOF quadruped robot leg:</br>
https://github.com/RoboLabHub/InverseKinematics/tree/master/examples/3DOF

Here the example for 6DOF robot arm:</br>
https://github.com/thomashiemstra/robot_arm_with_vision/blob/master/src/IK.cpp

To get understand how these formulas are created please check this set of videos:</br>
https://www.youtube.com/watch?v=rJx_XZ8xz6w</br>
https://www.youtube.com/watch?v=3RHg6OJLYhM</br>
https://www.youtube.com/watch?v=VjsuBT4Npvk</br>

Manipulator types:</br>
https://www.youtube.com/watch?v=lySKu7qtfCs

The examples of videos where IK is used:</br>
https://youtu.be/N-FH-j3-j_k</br>
https://youtu.be/P7M-U_FudNk</br>
