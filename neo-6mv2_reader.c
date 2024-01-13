#include <errno.h>
#include <fcntl.h> 
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "data_process.h"
#include "interface_comm.h"

#define BAUD_RATE B9600
#define NO_PARITY 0

//TODO: add a getopts
//TODO: create a struct for the program options
int main(int argc, char **argv)
{
	if (argc < 3) {
		printf(
                        "You need to provide the port where the GPS is connected\n" 
                        "and provide the type of NMEA that you want to get\n"
		       "e.g: %s /dev/ttyAMA0 gga\n", argv[0]);
		exit(1);
	}

	char *portname = argv[1];
        char *nmea_mssg = argv[2];
	
	int fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
	if (fd < 0) {
	        printf("error %d opening %s: %s", errno, portname, strerror(errno));
	}
	
	set_interface_attribs(fd, BAUD_RATE, NO_PARITY);
	set_blocking(fd, 0);

	read_gps_data(fd, nmea_mssg);
		
	return 0;
}

