#include <stdbool.h>

#define PGGGA "$GPGGA"
#define PGGSV "$GPGSV"
#define PGGSA "$GPGSA"
#define PGGLL "$GPGLL"
#define PGRMC "$GPRMC"
#define PGVTG "$GPVTG"

#define PGGGA_CNTR 13
#define PGGLL_CNTR 7

//TODO: improve memory for structs

#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

// $GPGGA
// check: https://aprs.gids.nl/nmea/#gga
typedef struct {
        char *id;
        float utc_pstfx;
        float latitude;
        char *dir_lat;
        float longitude;
        char *dir_long;
        int qlty;
        int sat_num;
        float hdop;
        float alt;
        char *alt_units;
        float geoid_sep;
        char *geoid_sep_units;
        //char *diff_gps; // not used in module
        //int id_station; // not used in module
        char *chck_sum;
        bool data_valid; // if the checksum is valid
}nmea_gga;

typedef struct {
        char *id;
        float latitude;
        char *dir_lat;
        float longitude;
        char *dir_long;
        float utc_pstfx;
        char *status; // A: valid data; V: invalid data;
        char *chck_sum;
        bool data_valid;
}nmea_gll; 

typedef struct {
        enum {
                GGA,
                GLL
        }type;
        union {
                nmea_gga *gga;
                nmea_gll *gll;
        };
}nmea_mssg;

#endif /* STRUCT_H_INCLUDED */

void get_nmea_gga_message(char *dt_itm, int itm, nmea_mssg *mssg, int chck_sum);
void print_nmea_gga_message(nmea_gga *gga);
void get_nmea_gll_message(char *dt_itm, int itm, nmea_mssg *mssg, int chck_sum);
void print_nmea_gll_message(nmea_gll *gll);
void get_nmea_message_values(nmea_mssg *mssg, char **nmea_mssg_str, int *nmea_mssg_cntr);
