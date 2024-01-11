#include <errno.h>
#include <fcntl.h> 
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "data_process.h"
#include "interface_comm.h"

int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("You need to provide the port where the GPS is connected\n"
		       "e.g: %s /dev/ttyAMA0\n", argv[0]);
		exit(1);
	}

	char *portname = argv[1];
	
	int fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
	if (fd < 0) {
	        printf("error %d opening %s: %s", errno, portname, strerror(errno));
	}
	
	set_interface_attribs(fd, B9600, 0);
	set_blocking(fd, 0);

	read_gps_data(fd);
		
	return 0;
}

