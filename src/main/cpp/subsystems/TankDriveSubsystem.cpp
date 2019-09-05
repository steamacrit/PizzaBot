/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/TankDriveSubsystem.h"
#include "RobotMap.h"

std::unique_ptr<TankDriveSubsystem> g_tank_drive_subsystem{ nullptr };

TankDriveSubsystem * TankDriveSubsystem::GetInstance()
{
    if (g_tank_drive_subsystem == nullptr)
        g_tank_drive_subsystem.reset(new TankDriveSubsystem());

    return g_tank_drive_subsystem.get();
}

TankDriveSubsystem::TankDriveSubsystem() 
{
    m_left_front_motor.reset(new TalonSRX(RobotMap::LEFT_FRONT_MOTOR_ID));
    m_left_rear_motor.reset(new TalonSRX(RobotMap::LEFT_REAR_MOTOR_ID));
    m_right_front_motor.reset(new TalonSRX(RobotMap::RIGHT_FRONT_MOTOR_ID));
    m_right_rear_motor.reset(new TalonSRX(RobotMap::RIGHT_REAR_MOTOR_ID));
}

void TankDriveSubsystem::SetMotorOutputByPercentage(double left, double right)
{
    m_left_front_motor->Set(ControlMode::PercentOutput, left);
    m_left_rear_motor->Set(ControlMode::PercentOutput, left);
    m_right_front_motor->Set(ControlMode::PercentOutput, -right);
    m_right_rear_motor->Set(ControlMode::PercentOutput, -right);
}