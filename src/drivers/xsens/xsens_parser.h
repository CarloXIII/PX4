/****************************************************************************
 *
 *   Copyright (C) 2008-2013 PX4 Development Team. All rights reserved.
 *   Author: Carlo Zgraggen <carlo.zgraggen@hslu.ch>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/* @file xsens_parser.h */

#ifndef XSENS_PARSER_H_
#define XSENS_PARSER_H_

#include "xsens_helper.h"


#define XSENS_PRE 0xFA
#define XSENS_BID 0xFF
#define XSENS_MID 0x32

#define XSENS_BAUDRATE 115200

#define HORIZONTAL_ACCURACY_FOR_FIX 8.0f	// This are the sigma values. Use it to define the fix_type
#define VERTICAL_ACCURACY_FOR_FIX 12.0f	// of the xsens_vehicle_gps_position message [m]
#define SPEED_ACCURACY_FOR_FIX 2.0f	// [m/s]

typedef enum {
	XSENS_DECODE_UNINIT = 0,
	XSENS_DECODE_GOT_SYNC1,
	XSENS_DECODE_GOT_SYNC2,
	XSENS_DECODE_GOT_SYNC3,
	XSENS_DECODE_GOT_HEADER_LGTH,
	XSENS_DECODE_GOT_MESSAGE_LGTH,
	XSENS_DECODE_GOT_CHECKSUM
} xsens_decode_state_t;

/** the structures of the binary packets */
#pragma pack(push, 1)

typedef struct { // reverse order because of swapping the bytes (little/big endian)
	uint8_t bgps; /**< GPS status byte or GPS data age. */
	uint32_t sacc; /**< Speed Accuracy Estimate. Expected error standard deviation, cm/s */
	uint32_t vacc; /**< Vertical Accuracy Estimate. Expected error standard deviation, mm */
	uint32_t hacc; /**< Horizontal Accuracy Estimate. Expected error standard deviation, mm */
	int32_t vel_d; /**< NED down velocity, cm/s */
	int32_t vel_e; /**< NED east velocity, cm/s */
	int32_t vel_n; /**< NED north velocity, cm/s */
	int32_t alt; /**< Altitude/Height above Ellipsoid, mm */
	int32_t lon; /**< Longitude, 1e7*deg */
	int32_t lat; /**< Latitude, 1e7*deg */
	uint32_t itow; /**< GPS Millisecond Time of Week, ms */
	uint8_t bprs; /**< Pressure sensor status. When the value decreases, new pressure data is available */
	uint16_t press; /**< Pressure, Pa*2 */
}xsens_gps_pvt_t;

typedef struct {
	float_t temp; /**< Internal temperatur of the sensor, �C */
}xsens_temp_t;

typedef struct { // reverse order because of swapping the bytes (little/big endian)
	float_t magz; /**< Magnetic field z-axis [arbitrary Unit normalized to earth field strength] */
	float_t magy; /**< Magnetic field y-axis [arbitrary Unit normalized to earth field strength] */
	float_t magx; /**< Magnetic field x-axis [arbitrary Unit normalized to earth field strength] */
	float_t gyrz; /**< Angular rate z-axis [rad/s] */
	float_t gyry; /**< Angular rate y-axis [rad/s] */
	float_t gyrx; /**< Angular rate x-axis [rad/s] */
	float_t accz; /**< Acceleration z-axis [m/s^2] */
	float_t accy; /**< Acceleration y-axis [m/s^2] */
	float_t accx; /**< Acceleration x-axis [m/s^2] */
}xsens_calibrated_data_t;

typedef struct { // reverse order because of swapping the bytes (little/big endian)
	float_t q3; /**< Orientation quaternion format */
	float_t q2; /**< Orientation quaternion format */
	float_t q1; /**< Orientation quaternion format */
	float_t q0; /**< Orientation quaternion format */
}xsens_orientation_quaternion_t;

typedef struct { // reverse order because of swapping the bytes (little/big endian)
	float_t yaw;	/**< yaw angle (rotation around Z) Orientation Euler angles format [deg], defined form (-180�...180�) */
	float_t pitch;	/**< pitch angle (rotation around Y) Orientation Euler angles format [deg], defined form (-90�...90�) */
	float_t roll;	/**< roll angle (rotation around X) Orientation Euler angles format [deg], defined form (-180�...180�) */
}xsens_orientation_euler_t;

typedef struct { // reverse order because of swapping the bytes (little/big endian)
	float_t i; /**< Rotation matrix (DCM) */
	float_t h; /**< Rotation matrix (DCM) */
	float_t g; /**< Rotation matrix (DCM) */
	float_t f; /**< Rotation matrix (DCM) */
	float_t e; /**< Rotation matrix (DCM) */
	float_t d; /**< Rotation matrix (DCM) */
	float_t c; /**< Rotation matrix (DCM) */
	float_t b; /**< Rotation matrix (DCM) */
	float_t a; /**< Rotation matrix (DCM) */
}xsens_orientation_matrix_t;

typedef struct { // reverse order because of swapping the bytes (little/big endian)
	uint16_t ain2; /**< XXX */
	uint16_t ain1; /**< XXX */
}xsens_auxiliary_data_t;

typedef struct { // reverse order because of swapping the bytes (little/big endian)
	float_t alt; /**< Height above earth [m] */
	float_t lon; /**< Longitude according to WGS 84 [deg] */
	float_t lat; /**< Latitude according to WGS 84 [deg] */
}xsens_position_data_t;

typedef struct { // reverse order because of swapping the bytes (little/big endian)
	float_t velz; /**< Velocity Up/Down (depends on setting) [m/s] */
	float_t vely; /**< Velocity West/East (depends on setting) [m/s] */
	float_t velx; /**< Velocity North (depends on setting) [m/s] */
}xsens_velocity_data_t;

typedef struct {
	uint8_t status; /**< Bit0:Self Test ; Bit1:XKF Valid ; Bit2:GPS Fix ; Bit3/4:No Rotation Status ; Bit5-7:reserved */
}xsens_status_t;

typedef struct {
	uint16_t sample_counter; /** wraps around after 65536 */
}xsens_sample_counter_t;

typedef struct { // reverse order because of swapping the bytes (little/big endian)
	uint8_t status;		/**< 0x01 = Valid Time of Week; 0x02 = Valid Week Number; 0x04 = Valid UTC (Leap Seconds already known?) */
	uint8_t seconds;	/**< Seconds of minute, range 0 .. 59 */
	uint8_t minute;		/**< Minute of hour, range 0 .. 59 */
	uint8_t hour;		/**< Hour of day, range 0 .. 23 */
	uint8_t day;		/**< Day of month, range 1 .. 31 */
	uint8_t month;		/**< Month, range 1 .. 12 */
	uint16_t year;		/**< Year, range 1999 .. 2099 */
	uint32_t nsec;		/**< Nanoseconds of second, range 0 .. 1.000.000.000 */
}xsens_utc_time_t;

#pragma pack(pop)

#define XSENS_RECV_BUFFER_SIZE 150

class XSENS_PARSER : public XSENS_Helper
{
public:
	XSENS_PARSER(const int &fd, struct xsens_vehicle_gps_position_s *gps_position, struct xsens_sensor_combined_s  *xsens_sensor_combined,
			struct xsens_vehicle_attitude_s * _xsens_vehicle_attitude, struct xsens_vehicle_global_position_s * _global_position);
	~XSENS_PARSER();
	int				receive(unsigned timeout);
	int				configure(unsigned &baudrate);
private:
	/**
	 * Parse the XSENS packet
	 */
	int				parse_char(uint8_t b);

	/**
	 * Handle the package once it has arrived
	 */
	int				handle_message(void);

	/**
	 * Reset the parse state machine for a fresh start
	 */
	void				decode_init(void);

	/**
	 * Calculate the checksum of a block of data
	 */
	unsigned long		calculate_checksum(unsigned long message_lgth, unsigned char *data);

	void				swapBytes(char* message, unsigned size);

	int					_fd;
	struct xsens_vehicle_gps_position_s *_gps_position;
	struct xsens_sensor_combined_s *_xsens_sensor_combined;
	struct xsens_vehicle_attitude_s * _xsens_vehicle_attitude;
	struct xsens_vehicle_global_position_s * _global_position;
	xsens_decode_state_t	_decode_state;
	uint8_t				_xsens_revision;
	uint8_t				_rx_header_lgth;
	unsigned			_rx_message_lgth;
	uint8_t				_rx_buffer[XSENS_RECV_BUFFER_SIZE];
	char				_messageSwapped[50];
	unsigned			_rx_count;
	unsigned long		_calculated_checksum;
	uint8_t 			xsens_last_bgps;
};

#endif /* XSENS_PARSER_H_ */
