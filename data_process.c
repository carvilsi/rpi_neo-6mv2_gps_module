#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "data_process.h"
/*#include "nmea_messages.h"*/

bool RAW = false;

static void parse_data(char *dt_ln, int chck_sum, nmea_mssg *mssg)
{
        int cntr = 0;
        char *gga = get_nmea_message_string(mssg);
        char *nmea_mssg_typ;
        char *dt_itm = strtok(dt_ln, DATA_DELIMITER);
        while (dt_itm != NULL) {
                if (cntr == 0) {
                        if (strcmp(dt_itm, gga) == 0) {
                                nmea_mssg_typ = gga;
                        } else {
                                nmea_mssg_typ = NULL;
                        }
                }
                
               /*NMEA_GGA gpgga; */
               if (nmea_mssg_typ != NULL && strcmp(nmea_mssg_typ, gga) == 0) {
                        get_nmea_gga_message(dt_itm, cntr, mssg, chck_sum);
                        if (cntr == 13)
                                print_nmea_gga_message(mssg->gga);
                }
                
                cntr++;
                dt_itm = strtok(NULL, DATA_DELIMITER);
        }
}

// XXX: Not super proud about check sum approach
void process_buffer(uint8_t *buff, nmea_mssg *mssg)
{
        int cntr = 0;
	int i = 0;
        char dt_ln[100];
        bool nw = false;
        int chck_sum;
        bool dt_chck_sum = true;

	for (; i < BUFF_SIZE; i++) {
                uint8_t data = buff[i];
                if (RAW)
                        printf("%c", data);
		
                if (data == '$') {
                        nw = true;
                        cntr = 0;
                        memset(dt_ln, 0, sizeof(dt_ln));
                        chck_sum = 0;
                        dt_chck_sum = true;
                }
		if (data == '\n') { 
                        nw = false;
                        parse_data(dt_ln, chck_sum, mssg);
                }
                if (nw) {
                        if (data == '*')
                                dt_chck_sum = false;
                         if (data != '*'  && 
                            data != '$' && data != ' ' &&
                            data != '\n') {
                                 if (dt_chck_sum) 
                                         chck_sum = chck_sum ^ data;
                        }

                        if (data != '*' ) {
                                dt_ln[cntr] = data;
                                cntr++;
                        }
                } 
	}
}

void read_gps_data(int fd, nmea_mssg *mssg)
{
	uint8_t buff[BUFF_SIZE];
	for (;;) {
		read(fd, buff, sizeof buff);
		process_buffer(buff, mssg);
	}
}

