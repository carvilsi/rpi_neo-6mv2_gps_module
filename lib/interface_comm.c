#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "interface_comm.h"

FILE *init_serial_interface(char *portname) 
{
	FILE *fd = fopen(portname, "rb");
	if (fd < 0) {
	        printf("error %d opening %s: %s", errno, portname, strerror(errno));
                if (fd != NULL)
                        fclose(fd);
                exit(EXIT_FAILURE);
	}
	
        return fd;
}

void close_serial_interface(FILE *fd)
{
        fclose(fd);
}
