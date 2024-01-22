#include <errno.h>
#include <string.h>
#include <stdio.h>

#include "interface_comm.h"

FILE *init_serial_interface(char *portname) 
{
	FILE *fd = fopen(portname, "rb");
	if (fd < 0) {
	        printf("error %d opening %s: %s", errno, portname, strerror(errno));
	}
	
        return fd;
}

