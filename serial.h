
#ifndef _SERIAL_H_
#define _SERIAL_H_

#include <stdio.h>
#include <string.h>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include <time.h>


int serial_open(char *port_name);
int serial_close(int serial_port);


#endif // _SERIAL_H_
