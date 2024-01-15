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
	if (argc < 2) {
		printf(
                        "You need to provide the port where the GPS is connected\n" 
		       "e.g: %s /dev/ttyAMA0 \n", argv[0]);
		exit(1);
	}

	char *portname = argv[1];
	
	int fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
	if (fd < 0) {
	        printf("error %d opening %s: %s", errno, portname, strerror(errno));
	}
	
	set_interface_attribs(fd, BAUD_RATE, NO_PARITY);
	set_blocking(fd, 0);

        // trying to read a GGA NMEA message from module

        nmea_gga pggga;
        nmea_mssg mssg;
        mssg.type = GGA;
        mssg.gga = &pggga;

	read_gps_data(fd, &mssg);
        
        //TODO: we need to have this!
        /*print_nmea_gga_message(mssg.gga);*/
		
	return 0;
}

