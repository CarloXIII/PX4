
#include <termios.h>
#include <errno.h>
#include <systemlib/err.h>
#include <drivers/drv_hrt.h>
#include "rpm_arduino_helper.h"

/**
 * @file rpm_arduino_helper.cpp
 */

int
RPM_ARDUINO_Helper::set_baudrate(const int &fd, unsigned baud)
{
	/* process baud rate */
	int speed;

	switch (baud) {
	case 9600:   speed = B9600;   break;

	case 19200:  speed = B19200;  break;

	case 38400:  speed = B38400;  break;

	case 57600:  speed = B57600;  break;

	case 115200: speed = B115200; break;

	warnx("try baudrate: %d\n", speed);

	default:
		warnx("ERROR: Unsupported baudrate: %d\n", baud);
		return -EINVAL;
	}
	struct termios uart_config;
	int termios_state;

	/* fill the struct for the new configuration */
	tcgetattr(fd, &uart_config);

	/* clear ONLCR flag (which appends a CR for every LF) */
	uart_config.c_oflag &= ~ONLCR;
	/* no parity, one stop bit */
	uart_config.c_cflag &= ~(CSTOPB | PARENB);

	/* set baud rate */
	if ((termios_state = cfsetispeed(&uart_config, speed)) < 0) {
		warnx("ERROR setting config: %d (cfsetispeed)\n", termios_state);
		return -1;
	}
	if ((termios_state = cfsetospeed(&uart_config, speed)) < 0) {
		warnx("ERROR setting config: %d (cfsetospeed)\n", termios_state);
		return -1;
	}
	if ((termios_state = tcsetattr(fd, TCSANOW, &uart_config)) < 0) {
		warnx("ERROR setting baudrate (tcsetattr)\n");
		return -1;
	}
	/* XXX if resetting the parser here, ensure it does exist (check for null pointer) */
	return 0;
}
