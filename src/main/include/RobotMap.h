#pragma once

class RobotMap
{
public: // PUBLIC DATA
    // Motor Controle ID Constants
    static constexpr int32_t LEFT_FRONT_MOTOR_ID{ 1 };
    static constexpr int32_t LEFT_REAR_MOTOR_ID{ 2 };
    static constexpr int32_t RIGHT_FRONT_MOTOR_ID{ 3 };
    static constexpr int32_t RIGHT_REAR_MOTOR_ID{ 4 };
    
    // Joystick ID Constants
    static constexpr int32_t DRIVER1_JOYSTICK_PORT{ 0 };
    static constexpr int32_t DRIVER2_JOYSTICK_PORT{ 1 };
    
};