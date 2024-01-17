#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/data_process.h"
#include "lib/interface_comm.h"

//TODO: add a getopts or maybe not (p.-)
//TODO: create a struct for the program options or maybe not (p.-)
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
	
        // trying to read a GGA NMEA message from GPS module
        nmea_gga pggga;
        nmea_mssg mssg;
        mssg.type = GGA;
        mssg.gga = &pggga;

        read_gps_data(portname, &mssg);
        /*print_nmea_gga_message(mssg.gga);*/
        print_nmea_message(mssg);

        // trying to read a GLL NMEA message from GPS module
        nmea_gll pggll;
        nmea_mssg ms;
        ms.type = GLL;
        ms.gll = &pggll;

        read_gps_data(portname, &ms);
        /*print_nmea_gll_message(ms.gll);*/
        print_nmea_message(ms);
		
	return 0;
}

