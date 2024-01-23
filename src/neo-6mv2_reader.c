#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "interface_comm.h"
#include "../lib/data_process.h"

int main(int argc, char **argv)
{
	if (argc < 2) {
		printf(
                        "You need to provide the port where the GPS is connected\n" 
		        "e.g: %s /dev/ttyAMA0 \n", argv[0]);
		exit(EXIT_FAILURE);
	}

        if (strlen(argv[1]) > 50) {
                fprintf(stderr, "%s seems to be a non valid port\n", argv[1]);
                exit(EXIT_FAILURE);
        }

	char *portname = argv[1];

        // open the serial to read
        FILE *fd = init_serial_interface(portname);
	
        // lib usage
        // trying to read a GGA NMEA message from GPS module
        // create an instance of nmea_gga struct
        nmea_gga gpgga;
        // create an instance of nmea struct 
        nmea_mssg mssg;
        // specify the type
        mssg.type = GGA;
        // append the gga type message
        mssg.gga = &gpgga;

        // read one gga message
        read_gps_data(fd, &mssg);
        // print, in this case the whole gga message
        print_nmea_message(mssg);

        // or if just want to print something more specific
        // e.g. the current altitude:
        printf("Current altitude: %.2f\n", gpgga.alt);

        // trying to read a GLL NMEA message from GPS module
        nmea_gll gpgll;
        nmea_mssg ms;
        ms.type = GLL;
        ms.gll = &gpgll;

        read_gps_data(fd, &ms);
        print_nmea_message(ms);

        // trying to read a GSV NMEA message from GPS module
        nmea_gsv gpgsv;
        nmea_mssg nmeagsv;
        nmeagsv.type = GSV;
        nmeagsv.gsv = &gpgsv;

        read_gps_data(fd, &nmeagsv);
        print_nmea_message(nmeagsv);

        // close the serial
        close_serial_interface(fd);
		
	return 0;
}

