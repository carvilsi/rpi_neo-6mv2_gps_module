#include <stdio.h>

#define BAUD_RATE B9600
#define PARITY 0

FILE *init_serial_interface(char *portname);
void close_serial_interface(FILE *fd);

