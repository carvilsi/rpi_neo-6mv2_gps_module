#include <stdbool.h>

//#define GGA "gga"
//#define GSV "gsv"
//#define GSA "gsa"
//#define GLL "gll"
//#define RMC "rmc"
//#define VTG "vtg"

#define PGGGA "$GPGGA"
#define PGGSV "$GPGSV"
#define PGGSA "$GPGSA"
#define PGGLL "$GPGLL"
#define PGRMC "$GPRMC"
#define PGVTG "$GPVTG"

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
        }msg_type;
        union {
                nmea_gga *gga;
                nmea_gll *gll;
        };
}nmea_mssg;

void get_nmea_gga_message(char *dt_itm, int itm, nmea_mssg *mssg, int chck_sum);
void print_nmea_gga_message(nmea_gga *gga);
char *get_nmea_message_string(nmea_mssg *mssg);
