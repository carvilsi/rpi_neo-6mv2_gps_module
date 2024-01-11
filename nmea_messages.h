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
}NMEA_GGA;

void get_nmea_gga_message(char *dt_itm, int itm, NMEA_GGA *gga);
void print_nmea_gga_message(NMEA_GGA gga);
