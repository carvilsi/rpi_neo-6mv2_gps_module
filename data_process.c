#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "data_process.h"
#include "nmea_messages.h"

bool RAW = false;

static void parse_data(char *dt_ln)
{
        int cntr = 0;
        char *gga = "$GPGGA";
        char *nmea_mssg;
        printf(">> %s\n", dt_ln);
        char *dt_itm = strtok(dt_ln, DATA_DELIMITER);
        while (dt_itm != NULL) {
                if (cntr == 0) {
                        if (strcmp(dt_itm, gga) == 0) {
                                nmea_mssg = gga;
                        } else {
                                nmea_mssg = NULL;
                        }
                }
                
                NMEA_GGA gpgga; 
                if (nmea_mssg != NULL && strcmp(nmea_mssg, gga) == 0) {
                        get_nmea_gga_message(dt_itm, cntr, &gpgga);
                        if (cntr == 13)
                                print_nmea_gga_message(gpgga);
                }
                
                cntr++;
                dt_itm = strtok(NULL, DATA_DELIMITER);
        }
}

void process_buffer(uint8_t *buff)
{
        int cntr = 0;
	int i = 0;
        char dt_ln[100];
        bool nw = false;
	for (i; i < BUFF_SIZE; i++) {
                char data = buff[i];
                if (RAW)
                        printf("%c", data);
		
                if (data == '$') {
                        nw = true;
                        cntr = 0;
                        memset(dt_ln, 0, sizeof(dt_ln));
                }
		if (data == '\n') { 
                        nw = false;
                        parse_data(dt_ln);
                }
                if (nw) {
                        dt_ln[cntr] = data;
                        cntr++;
                } 
	}
}

void read_gps_data(int fd)
{
	uint8_t buff[BUFF_SIZE];
	int cntr = 0;
	for (;;) {
		int n = read(fd, buff, sizeof buff);
		process_buffer(buff);
	}
}

