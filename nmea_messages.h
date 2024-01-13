#include <stdbool.h>

#define GGA "gga"
#define GSV "gsv"
#define GSA "gsa"
#define GLL "gll"
#define RMC "rmc"
#define VTG "vtg"

#define PGGGA "$PGGGA"
#define PGGSV "$PGGSV"
#define PGGSA "$PGGSA"
#define PGGLL "$PGGLL"
#define PGRMC "$PGRMC"
#define PGVTG "$PGVTG"

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
        //char *diff_gps;
        //int id_station;
        char *chck_sum;
        bool data_valid; // if the checksum is valid
}NMEA_GGA;

void get_nmea_gga_message(char *dt_itm, int itm, NMEA_GGA *gga, int chck_sum);
void print_nmea_gga_message(NMEA_GGA gga);
char *get_nmea_message_string(char *typ_nmea_mssg);
