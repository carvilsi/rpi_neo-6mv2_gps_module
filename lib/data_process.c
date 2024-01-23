#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "interface_comm.h"
#include "data_process.h"

bool RAW = false;
int done = 0;

static void parse_data(char *dt_ln, int chck_sum, nmea_mssg *mssg)
{
        done = 0;
        int cntr = 0;
        char *nmea_mssg_str = NULL;
        int nmea_mssg_cntr;
        get_nmea_message_values(mssg, &nmea_mssg_str, &nmea_mssg_cntr);
        char *nmea_mssg_typ;
        char *dt_itm = strtok(dt_ln, DATA_DELIMITER);
        while (dt_itm != NULL) {
                if (cntr == 0) {
                        if (strcmp(dt_itm, nmea_mssg_str) == 0) {
                                nmea_mssg_typ = nmea_mssg_str;
                        } else {
                                nmea_mssg_typ = NULL;
                        }
                }
                
               if (nmea_mssg_typ != NULL && strcmp(nmea_mssg_typ, nmea_mssg_str) == 0) {
                       switch (mssg->type) {
                               case GGA:
                                        get_nmea_gga_message(dt_itm, cntr, mssg, chck_sum);
                                        if (cntr == nmea_mssg_cntr)
                                                done = 1;
                                        break;
                                case GLL:
                                        get_nmea_gll_message(dt_itm, cntr, mssg, chck_sum);
                                        if (cntr == nmea_mssg_cntr)
                                                done = 1;
                                        break;
                                //TODO: the gsv message requires more work in order to
                                //parse all the data related with second, third and fourth SVs
                                case GSV:
                                        get_nmea_gsv_message(dt_itm, cntr, mssg, chck_sum);
                                        if (cntr == nmea_mssg_cntr)
                                                done = 1;
                                        break;
                                default:
                                        fprintf(stderr, "Unknown nmea message type\n");
                       }
                }
                
                cntr++;
                dt_itm = strtok(NULL, DATA_DELIMITER);
        }
}

static void process_buffer(uint8_t *buff, nmea_mssg *mssg)
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
                if (done)
                        break;
	}
}

void read_gps_data(char *portname, nmea_mssg *mssg)
{
        done = 0;
        FILE *fd = init_serial_interface(portname);
	uint8_t buff[BUFF_SIZE];
        while (done == 0) {
		fread(buff, sizeof(uint8_t), sizeof(buff), fd);
		process_buffer(buff, mssg);
        }
}

