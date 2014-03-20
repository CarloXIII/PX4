/****************************************************************************
 *
 *   Author: @author Lukas Koepfli <lukas.koepfli@stud.hslu.ch>
 *
 ****************************************************************************/

/* @file Twist Angle Control */

#ifndef TWIST_ANGLE_CONTROL_H_
#define TWIST_ANGLE_CONTROL_H_

#include <uORB/topics/manual_control_setpoint.h> /* use this, to get the yaw input from the radio control */
#include <uORB/topics/vehicle_paraglider_angle.h> /* use this, to get the actual value from the potentiometers */
#include <uORB/topics/actuator_controls.h> /* use this, to set the control variable */
#include <uORB/topics/debug_key_value.h> /* use this for debuging */

int twist_angle_control(const struct vehicle_paraglider_angle_s *angle_measurement, const struct manual_control_setpoint_s *manual_sp,
				struct actuator_controls_s *actuators, struct debug_key_value_s *dbg);

#endif /* TWIST_ANGLE_CONTROL_H_ */
