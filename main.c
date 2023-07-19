//
//  main.c
//  ND_DISPLAY
//
//  Created by  on 1/31/23.
//



#include <gtk/gtk.h>
#include <cairo.h>
#include <glib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>








static void
rounded_rectangle_wstroke(cairo_t *cr, double x, double y, double width, double height, double radius,
                          double red, double green, double blue, double sred, double sgreen, double sblue, double strokewidth)
{
    double degrees = M_PI / 180;
    cairo_new_sub_path(cr);
    cairo_arc(cr, x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
    cairo_arc(cr, x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
    cairo_arc(cr, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
    cairo_arc(cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
    cairo_close_path(cr);
    cairo_set_source_rgb(cr, red, green, blue);
    cairo_fill_preserve(cr);
    cairo_set_source_rgb(cr, sred, sgreen, sblue);
    cairo_set_line_width(cr, strokewidth);
    cairo_stroke(cr);
}

static void
rounded_rectangle_wstroke_nocolor(cairo_t *cr, double x, double y, double width, double height, double radius, double strokewidth)
{
    double degrees = M_PI / 180;
    cairo_new_sub_path (cr);
    cairo_arc (cr, x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
    cairo_arc (cr, x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
    cairo_arc (cr, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
    cairo_arc (cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
    cairo_close_path (cr);
    
    cairo_fill_preserve (cr);
    
    cairo_set_line_width (cr, strokewidth);
    cairo_stroke (cr);
}


static void
better_rectangle(cairo_t *cr, double x, double y, double width, double height, double r, double g, double b)
{
    cairo_set_source_rgb (cr, r, g, b);
    cairo_rectangle (cr, x, y, width, height);
    cairo_fill(cr);
}

static void
better_rectangle_no_rgb(cairo_t *cr, double x, double y, double width, double height)
{
    cairo_rectangle (cr, x, y, width, height);
    cairo_fill(cr);
}

static void
MFD_low_txtbox(cairo_t *cr, double x, double y)
{
    rounded_rectangle_wstroke(cr, x, y, 230, 70, 5, 0.33, 0.29, 0.34, 1, 1, 1, 2.5);
}

static void
draw_text(cairo_t *cr, const char *text, double x, double y, int align)
{
    cairo_text_extents_t extents;
    cairo_text_extents(cr, text, &extents);
    
    
    
    switch (align) {
        case 0:
            cairo_move_to(cr, x, y);
            //1: Left
            break;
        case 1:
            cairo_move_to(cr, x - extents.width / 2, y);
            
            //Center
            break;
        case 2:
            cairo_move_to(cr, x - extents.width, y);
            //Right
            break;
            
        default:
            break;
    }
    
    cairo_show_text(cr, text);
}

long double
toRadians(const long double degree)
{
    // cmath library in C++
    // defines the constant
    // M_PI as the value of
    // pi accurate to 1e-30
    long double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}

long double
distance(long double lat1, long double long1,
         long double lat2, long double long2)
{
    // Convert the latitudes
    // and longitudes
    // from degree to radians.
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);
    
    // Haversine Formula
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;
    
    long double ans = pow(sin(dlat / 2), 2) +
    cos(lat1) * cos(lat2) *
    pow(sin(dlong / 2), 2);
    
    ans = 2 * asin(sqrt(ans));
    
    // Radius of Earth in
    // Kilometers, R = 6371
    // Use R = 3956 for miles
    long double R = (3956/1.151);
    
    // Calculate the result
    ans = ans * R;
    
    return ans;
}

int
count_newlines(char *buffer, int size)
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (buffer[i] == '\n')
        {
            count++;
        }
    }
    return count;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------UTIL FUNCTIONS END!!--------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static void
MFD_low_freqswitchbox(cairo_t *cr, double x, double y)
{
    better_rectangle(cr, x, y, 60, 40, 1,1, 1);
    better_rectangle(cr, x + 2.5, y + 2.5, 60-5, 40-5, 0.33, 0.29, 0.34);
    
    cairo_select_font_face(cr, "URWGordonW01-Medium", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 32.0);
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_move_to(cr, x + 37, y + 31);
    cairo_show_text(cr, ">");
    cairo_move_to(cr, x + 5 , y + 31);
    cairo_show_text(cr, "<");
}

static void
MFD_low_VHFpanel(cairo_t *cr, double x, double y)
{
    rounded_rectangle_wstroke(cr, 473 + x, 985 + y, 596, 393, 5, 0, 0.49, 0.69, 1, 1, 1, 2.5);
    rounded_rectangle_wstroke(cr, 263 + x, 985 + y, 237, 100, 5, 0, 0.49, 0.69, 1, 1, 1, 2.5);
    better_rectangle(cr, 467 + x, 986 + x, 130, 98, 0, 0.49, 0.69);
    better_rectangle(cr, 474 + x, 989 + x, 130, 98, 0, 0.49, 0.69);
    MFD_low_txtbox(cr, 485 + x, 1075 + y);
    MFD_low_txtbox(cr, 825 + x, 1075 + y);
    MFD_low_freqswitchbox(cr, 740, 1090);
    
    cairo_set_font_size(cr, 40.0);
    cairo_move_to(cr, 308 + x, 1050 + y);
    cairo_show_text(cr, "VHF 1");
    
    
    
    cairo_set_font_size(cr, 30.0);
    cairo_move_to(cr, 500 + x, 1070 + x);
    cairo_show_text(cr, "ACTIVE");
}


static void
CircleND(cairo_t *cr, double x, double y) {
    /*
    * Unused function
    */
  
    const char* degreesList []  = {"N", "3", "6", "E", "12", "15", "S", "21", "24", "W", "30", "33"};
    
    double r = 375;
    double spike_len = 10;
    int spike_count = 72;
    double angle_increment = 2 * M_PI / spike_count;
    
    cairo_save(cr);
    cairo_translate(cr, x, y);
    cairo_rotate(cr, -M_PI / 2);
    cairo_translate(cr, -x, -y);
    
    cairo_select_font_face(cr, "URWGordonW01-Medium", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    for (int i = 0; i < spike_count; ++i) {
        cairo_set_source_rgb(cr, 1, 1, 1);
        double angle = i * angle_increment;
        cairo_move_to(cr, x + r * cos(angle), y + r * sin(angle));
        if (i % 2 != 0)
        {
            cairo_set_source_rgb(cr, 1, 1, 1);
            cairo_line_to(cr, x + (r + spike_len) * cos(angle), y + (r + spike_len) * sin(angle));
            cairo_stroke(cr);
            
        }
        else
        {
            cairo_set_source_rgb(cr, 1, 1, 1);
            cairo_line_to(cr, x + (r + (spike_len*2)) * cos(angle), y + (r + (spike_len*2)) * sin(angle));
            cairo_stroke(cr);
        }
        
        if (i % 6 == 0)
        {
            /*
             cairo_set_font_size(cr, 35);
             
             draw_text(cr, degreesList[i/6],x + (r + (spike_len*2)) * cos(angle), y + (r + (spike_len*2)) * sin(angle), 1);
             */
            
            
            cairo_set_font_size(cr, 35);
            cairo_save(cr);
            double text_angle = angle + M_PI_2;
            cairo_text_extents_t extents;
            cairo_text_extents(cr, degreesList[i/6], &extents);
            
            cairo_translate(cr, x + (r + (spike_len*2)) * cos(angle), y + (r + (spike_len*2)) * sin(angle));
            
            cairo_rotate(cr, text_angle);
            cairo_set_source_rgba(cr, 0, 0, 0, 0);
            cairo_rectangle(cr, -extents.width/2, -extents.height/2, extents.width, extents.height);
            cairo_stroke(cr);
            
            cairo_set_source_rgb(cr, 1, 1, 1);
            
            
            cairo_translate(cr, -extents.width/2, extents.height/20);
            
            
            
            cairo_show_text(cr, degreesList[i/6]);
            cairo_restore(cr);
            cairo_set_source_rgb(cr, 1, 1, 1);
            
        }
        
        
        
    }
    
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_arc(cr, x, y, r, 0, 2*M_PI);
    cairo_stroke(cr);
    
    static const double dashed3[] = {{9.5, 51.0, 9.5}};
    
    cairo_set_dash(cr, dashed3, 1, 0);
    cairo_arc(cr, x, y, r/2, 0, 2*M_PI);
    cairo_stroke(cr);
    
    cairo_restore(cr);
    
    static const double undash[] = {{1.0}};
    
    cairo_set_dash(cr, undash, 0, 0);
    
    
    
    
    //DRAW PLANE -------------------------------------------->
    cairo_save(cr);
    cairo_set_source_rgb(cr, 1, 1, 0);
    cairo_set_line_width(cr, 4.0);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_move_to(cr, x, y-15);
    cairo_line_to(cr, x, y+40);
    
    cairo_move_to(cr, x-35, y);
    cairo_line_to(cr, x+35, y);
    
    cairo_move_to(cr, x-10, y+35);
    cairo_line_to(cr, x+10, y+35);
    
    cairo_stroke(cr);
    cairo_restore(cr);
    //DRAW PLANE -------------------------------------------->
    
    //ROSE MODE -------------------------------------------->
    
    int mode = 0;
    //-1: IRS not aligned
    //0: Rose Mode
    
    
    if (mode == -1)
    {
        cairo_set_source_rgb(cr, 1, 1, 0);
        cairo_set_font_size(cr, 31);
        draw_text(cr, "FPLN NOT AVAILABLE", x, y-100, 1);
    }
    else if (mode == 0)
    {
        //VOR 1 DRAW -------------------------------------------->
        
        
        
        //VOR 1 DRAW -------------------------------------------->
        
        //VOR 2 DRAW -------------------------------------------->
        
        /*
         cairo_save(cr);
         cairo_translate(cr, x, y);
         cairo_rotate(cr, -M_PI / 4);
         cairo_translate(cr, -x, -y);
         */
        
        cairo_set_source_rgb(cr, 1, 1, 1);
        cairo_move_to(cr, x, y - 375);
        cairo_line_to(cr, x, y - 305);
        
        cairo_move_to(cr, x, y - 305);
        cairo_line_to(cr, x - 35.5, y - 275);
        
        cairo_move_to(cr, x - 35.5, y - 275);
        cairo_line_to(cr, x - 35.5, y - 205);
        
        cairo_move_to(cr, x, y - 305);
        cairo_line_to(cr, x + 35.5, y - 275);
        
        cairo_move_to(cr, x + 35.5, y - 275);
        cairo_line_to(cr, x + 35.5, 270);
        
        cairo_move_to(cr, x + 35.5, y - 275);
        cairo_line_to(cr, x, y-255);
        
        cairo_move_to(cr, x - 35.5, y - 275);
        cairo_line_to(cr, x, y-255);
        
        
        
        
        
        
        cairo_move_to(cr, x, y + 375);
        cairo_line_to(cr, x, y + 280 - 40);
        
        cairo_move_to(cr, x, y + 280 - 40);
        cairo_line_to(cr, x + 35.5, y + 280 + 20- 40);
        cairo_move_to(cr, x + 35.5, y + 280 + 20 - 40);
        cairo_line_to(cr, x + 35.5, y + 200 - 40 + 40);
        
        
        cairo_move_to(cr, x, y + 280 - 40);
        cairo_line_to(cr, x - 35.5, y + 280 + 20 - 40);
        cairo_move_to(cr, x - 35.5, y + 280 + 20 - 40);
        cairo_line_to(cr, x - 35.5, y + 200 - 40 + 40);
        
        
        cairo_stroke(cr);
        
        cairo_restore(cr);
        //VOR2 DRAW -------------------------------------------->
        
        
    }
    
    
    
    
}


int line_number = 1;
char line[256];
char line2[256];
char aptRaw[256];
// char rwyList[40][256];
char rwyList[32][128];
int rwyCount = 0;
char iata_code[256];
char datum_lat[256];
char datum_lon[256];

char rwyNumsList[32][2][48];
int runwayCount = 0;

char rwyCoordsListChar[10][4][48];


static void
parseAptdat(char* apt)
{
    /* EXAMPLE FORMAT
     1    392 0 0 LFPG Paris - Charles De Gaulle
     1302 city Paris
     1302 country France
     1302 datum_lat 49.009747222
     1302 datum_lon 2.547819444a
     1302 gui_label 3D
     1302 iata_code CDG
     1302 icao_code LFPG
     1302 region_code LF
     1302 state Île-de-France
     1302 transition_alt 5000
     1302 transition_level 70
     100 60.00 1 0 0.00 1 3 0 09L 49.0247190 2.5248920 0 0 3 2 1 0 27R 49.0266940 2.5616890 0 66 3 2 1 0
     100 45.11 1 0 0.00 1 3 0 09R 49.0206170 2.5130580 0 0 3 2 1 0 27L 49.0236851 2.5703075 599 0 3 2 1 0
     100 45.11 1 0 0.00 1 3 0 08L 48.9956874 2.5527569 0 151 3 2 1 0 26R 48.9986995 2.6091707 528 135 3 2 1 0
     100 60.05 1 0 0.00 1 3 0 08R 48.9929139 2.5656774 0 150 3 2 1 0 26L 48.9948780 2.6024330 0 149 3 2 1 0
     */
    
    
    
    
    const char* filename = "/Users/apt.dat";
    
    const int chunk_size = 1024*4;
    char buffer[chunk_size];
    FILE *file = fopen(filename, "r");
    
    char* eel[40];
    
    if (file == NULL)
    {
       
        perror("fopen");
        
    }
    


    while (fread(buffer, chunk_size, 1, file) == 1)
    {
        char *occurrence = strstr(buffer, apt);
        if (occurrence != NULL)
        {
            char *line_start = occurrence;
            char *line_end = occurrence;
            while (line_start > buffer && *(line_start - 1) != '\n')
            {
                line_start--;
            }
            while (*line_end != '\n' && *line_end != '\0')
            {
                line_end++;
            }
            int line_length = line_end - line_start;
            strncpy(line, line_start, line_length);
            line[line_length] = '\0';
            
            if (strncmp(line, "1    ", 5) == 0)
            {
            
                
                strncpy(aptRaw, line_start, line_length);
                aptRaw[line_length] = '\0';
                
           
      
                
                // Parse file for iata_code
                char *iata_start = strstr(line_end, "1302 iata_code");
                if (iata_start != NULL)
                {
                    iata_start += 5;
                    char *iata_end = iata_start;
                    while (*iata_end != '\n' && *iata_end != '\0')
                    {
                        iata_end++;
                    }
                    int iata_length = iata_end - iata_start;
                    strncpy(iata_code, iata_start, iata_length);
                    iata_code[iata_length] = '\0';
                    
                 
                   //cairo_show_text(cr, iata_code);
                }
                
                // Parse file for datum_lat
                char *datum_lat_start = strstr(line_end, "1302 datum_lat");
                if (datum_lat_start != NULL)
                {
                    datum_lat_start += 5;
                    char *datum_lat_end = datum_lat_start;
                    while (*datum_lat_end != '\n' && *datum_lat_end != '\0')
                    {
                        datum_lat_end++;
                    }
                    int datum_lat_length = datum_lat_end - datum_lat_start;
                    strncpy(datum_lat, datum_lat_start, datum_lat_length);
                    datum_lat[datum_lat_length] = '\0';
                    
                
                    //cairo_show_text(cr, datum_lat);
                }
                
                // Parse file for datum_lon
                char *datum_lon_start = strstr(line_end, "1302 datum_lon");
                if (datum_lon_start != NULL)
                {
                    datum_lon_start += 5;
                    char *datum_lon_end = datum_lon_start;
                    while (*datum_lon_end != '\n' && *datum_lon_end != '\0')
                    {
                        datum_lon_end++;
                    }
                    int datum_lon_length = datum_lon_end - datum_lon_start;
                    strncpy(datum_lon, datum_lon_start, datum_lon_length);
                    datum_lon[datum_lon_length] = '\0';
                    
           
                    //cairo_show_text(cr, datum_lon);
                }
                
                char *occurrence2 = strstr(buffer, "100 ");
                if (occurrence2 != NULL) {
                    char *line_start2 = occurrence2;
                    char *line_end2 = occurrence2;
                    
                    while (line_start2 > buffer && *(line_start2 - 1) != '\n') {
                        line_start2--;
                    }
                    while (*line_end2 != '\n' && *line_end2 != '\0') {
                        line_end2++;
                    }
                    int line_length2 = line_end2 - line_start2;
                    
                    strncpy(rwyList[rwyCount], line_start2, line_length2);
                    rwyList[rwyCount][line_length2] = '\0';
                    rwyCount++;
                    
                    while (rwyCount < 32) {
                        char *occurrence3 = strstr(line_end2, "100 ");
                        if (occurrence3 == NULL) {
                            break;
                        }
                        
                        line_start2 = occurrence3;
                        line_end2 = occurrence3;
                        while (*line_end2 != '\n' && *line_end2 != '\0') {
                            line_end2++;
                        }
                        line_length2 = line_end2 - line_start2;
                        
                        strncpy(rwyList[rwyCount], line_start2, line_length2);
                        rwyList[rwyCount][line_length2] = '\0';
                        rwyCount++;
                    }
                }
            }
        }
        
        line_number += count_newlines(buffer, chunk_size);
    }
    
    

    
    
    
    for (int i = 0; i < rwyCount; i++) {
        char line[128];
        strcpy(line, rwyList[i]);
        
        char *token = strtok(line, " ");
        int field = 0;
        
        while (token != NULL) {
            if (field == 8)
            {
                strncpy(rwyNumsList[runwayCount][0], token, 3);
                rwyNumsList[runwayCount][0][3] = '\0';
            }
            else if (field == 17)
            {
                strncpy(rwyNumsList[runwayCount][1], token, 3);
                rwyNumsList[runwayCount][1][3] = '\0';
            }
            else if (field == 9)
            {
                printf(token);
                strncpy(rwyCoordsListChar[runwayCount][0], token, 11);
                rwyCoordsListChar[runwayCount][0][11] = '\0';
            }
            else if (field == 10)
            {
                strncpy(rwyCoordsListChar[runwayCount][1], token, 11);
                rwyCoordsListChar[runwayCount][1][11] = '\0';
                
            }
            else if (field == 18)
            {
                strncpy(rwyCoordsListChar[runwayCount][2], token, 11);
                rwyCoordsListChar[runwayCount][2][11] = '\0';
            }
            else if (field == 19)
            {
                strncpy(rwyCoordsListChar[runwayCount][3], token, 11);
                rwyCoordsListChar[runwayCount][3][11] = '\0';
                runwayCount++;
            }
            
            token = strtok(NULL, " ");
            field++;
            
            
        }
        
        
        
    }
    fclose(file);
    
}



int timesparsed = 0;

static void
drawMapRWY(cairo_t *cr, double x, double y, char* apt)
{
    //0.5 nm to edge
    //780px to edge
    

    int ppn = 1560/6; //150 pixels per nautical mile. This is a 5nm scale right now.
    int rwyAngle = 310;
  
    if (!timesparsed > 0)
    {
        parseAptdat(apt);
        timesparsed++;
    }
    
    
    cairo_set_source_rgb(cr, 1, 1, 1);
    
    char aptFull[256];
    memcpy(aptFull, &aptRaw[18], 255);
    aptFull[255] = '\0';
    cairo_set_font_size(cr, 35);
    draw_text(cr, aptFull, 1000-5, 35, 2);
    
    
    char aptICAO[5];
    memcpy(aptICAO, &aptRaw[13], 4);
    aptICAO[5] = "\0";
    //printf(aptICAO);
    cairo_set_font_size(cr, 35);
    draw_text(cr, aptICAO, 900, 70, 2);
    
    char aptIATA[4];
    memcpy(aptIATA, &iata_code[10], 3);
    aptIATA[4] = "\0";
    
    cairo_set_font_size(cr, 35);
    draw_text(cr, aptIATA, 1000-5, 70, 2);
    
    
    char datum_lat_raw[256];
    memcpy(datum_lat_raw, datum_lat + 10, sizeof(datum_lat) - 14);
    datum_lat_raw[sizeof(datum_lat) - 14] = '\0';
    double datum_lat_value = atof(datum_lat_raw);

    char datum_lon_raw[256];
    memcpy(datum_lon_raw, datum_lon + 10, sizeof(datum_lon) - 14);
    datum_lon_raw[sizeof(datum_lon) - 14] = '\0';
    double datum_lon_value = atof(datum_lon_raw);

    
    

    
    
    
    double rwyCoordsList[10][4];
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 4; j++) {
            char *ptr;
            rwyCoordsList[i][j] = strtod(rwyCoordsListChar[i][j], &ptr);
            
            
        }
    }
    
    
    char test[256];
    sprintf(test, "%d", rwyCoordsList[0][0]);
    
    
    double CURR_POS[] = {datum_lat_value, datum_lon_value};
    
    
    
    double nmDiffStart_x ;
    double nmDiffStart_y ;
    
    double nmDiffEnd_x ;
    double nmDiffEnd_y ;
    
    double pxStart_x;
    double pxStart_y;
    
    double pxEnd_x;
    double pxEnd_y;
    
    double angle;
    double center_y;
    double center_x;
    
    cairo_save(cr);
    cairo_translate(cr, x, y);
    cairo_rotate(cr, -M_PI / 2);
    cairo_translate(cr, -x, -y);
    
    const double a = 6378137.0; // Semi-major axis
    const double b = 6356752.314245; // Semi-minor axis
    
    for (int f = 0; f <= 10; f++)
    {
        
        
        double rwy_start_lat = rwyCoordsList[f][0];
        double rwy_start_lon = rwyCoordsList[f][1];
        double rwy_end_lat = rwyCoordsList[f][2];
        double rwy_end_lon = rwyCoordsList[f][3];

        // Convert runway start and end coordinates to Cartesian coordinates
        double rwy_start_x = rwy_start_lon * a;
        double rwy_start_y = log(tan(M_PI / 4.0 + rwy_start_lat * M_PI / 180.0 / 2.0)) * b;
        double rwy_end_x = rwy_end_lon * a;
        double rwy_end_y = log(tan(M_PI / 4.0 + rwy_end_lat * M_PI / 180.0 / 2.0)) * b;

        // Calculate the distance between the current position and runway start/end
        double nmDiffStart_x = distance(CURR_POS[0], CURR_POS[1], rwy_start_lat, CURR_POS[1]);
        double nmDiffStart_y = distance(CURR_POS[0], CURR_POS[1], CURR_POS[0], rwy_start_lon);
        double nmDiffEnd_x = distance(CURR_POS[0], CURR_POS[1], rwy_end_lat, CURR_POS[1]);
        double nmDiffEnd_y = distance(CURR_POS[0], CURR_POS[1], CURR_POS[0], rwy_end_lon);

        // Calculate the projected pxStart_x and pxEnd_x
        

        if (CURR_POS[0] > rwy_start_lat) {
            pxStart_x = x - (nmDiffStart_x * ppn);
        } else {
            pxStart_x = x + (nmDiffStart_x * ppn);
        }

        if (CURR_POS[0] > rwy_end_lat) {
            pxEnd_x = x - (nmDiffEnd_x * ppn);
        } else {
            pxEnd_x = x + (nmDiffEnd_x * ppn);
        }

        // Calculate the projected pxStart_y and pxEnd_y
        if (CURR_POS[1] > rwy_start_lon) {
            pxStart_y = y - (nmDiffStart_y * ppn);
        } else {
            pxStart_y = y + (nmDiffStart_y * ppn);
        }

        if (CURR_POS[1] > rwy_end_lon) {
            pxEnd_y = y - (nmDiffEnd_y * ppn);
        } else {
            pxEnd_y = y + (nmDiffEnd_y * ppn);
        }
        
        
        
        cairo_set_source_rgb(cr, 1, 1, 1);
        //cairo_arc(cr, pxStart_x, pxStart_y, 5, 0, 2*M_PI);
        cairo_save(cr);
        
        
        
        cairo_set_line_width(cr, 10.0);
        cairo_set_line_cap(cr, CAIRO_LINE_CAP_SQUARE);
        cairo_move_to(cr,  pxStart_x, pxStart_y);
        
        
        // cairo_arc(cr, pxEnd_x, pxEnd_y, 5, 0, 2*M_PI);
        cairo_line_to(cr,  pxEnd_x, pxEnd_y);
        cairo_stroke(cr);
        
        cairo_restore(cr);
        
        cairo_set_font_size(cr, 30);
        
        angle = atan2(pxEnd_y - pxStart_y, pxEnd_x - pxStart_x);
        cairo_text_extents_t extents;
        cairo_text_extents(cr, rwyNumsList[f][1], &extents);

        cairo_save(cr);
        cairo_translate(cr, 30 * cos(angle), 30 * sin(angle));

        // Transformations for the first side of the runway text
        cairo_translate(cr, pxEnd_x - (extents.width/2 + extents.x_bearing) * cos(angle + M_PI/2) - (extents.height/2 + extents.y_bearing) * sin(angle + M_PI/2), pxEnd_y - (extents.width/2 + extents.x_bearing) * sin(angle + M_PI/2) + (extents.height/2 + extents.y_bearing) * cos(angle + M_PI/2));
        cairo_rotate(cr, angle + M_PI/2);
        center_x = extents.x_bearing + extents.width / 2;
        center_y = extents.y_bearing + extents.height / 2;
        cairo_translate(cr, center_x, center_y);
        cairo_rotate(cr, M_PI);
        cairo_translate(cr, -center_x, -center_y);
        
        
        
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_move_to(cr, extents.x_bearing, extents.y_bearing+extents.height);
        cairo_line_to(cr, extents.x_bearing, extents.y_bearing);
        cairo_line_to(cr, extents.x_bearing + extents.width/2, extents.y_bearing - extents.height/2);
        cairo_line_to(cr, extents.x_bearing + extents.width, extents.y_bearing);
        cairo_line_to(cr, extents.x_bearing + extents.width, extents.y_bearing + extents.height);
        cairo_close_path(cr);
        cairo_fill(cr);
        
        cairo_set_source_rgb(cr, 1, 1, 1);
        
        
        
        cairo_show_text(cr, rwyNumsList[f][1]);

        cairo_set_line_width(cr, 2.5);
        cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND);
        cairo_move_to(cr, extents.x_bearing, extents.y_bearing+extents.height);
        cairo_line_to(cr, extents.x_bearing, extents.y_bearing);
        cairo_line_to(cr, extents.x_bearing + extents.width/2, extents.y_bearing - extents.height/2);
        cairo_line_to(cr, extents.x_bearing + extents.width, extents.y_bearing);
        cairo_line_to(cr, extents.x_bearing + extents.width, extents.y_bearing + extents.height);
        cairo_stroke(cr);
        
        cairo_set_font_size(cr, 35);
        //second side

        cairo_restore(cr);

        cairo_save(cr);
        cairo_translate(cr, 30 * cos(angle + M_PI), 30 * sin(angle + M_PI));
        
        cairo_text_extents(cr, rwyNumsList[f][0], &extents);

        // Transformations for the second side of the runway text
        cairo_translate(cr, pxStart_x - (extents.width/2 + extents.x_bearing) * cos(angle + M_PI/2) - (extents.height/2 + extents.y_bearing) * sin(angle + M_PI/2), pxStart_y - (extents.width/2 + extents.x_bearing) * sin(angle + M_PI/2) + (extents.height/2 + extents.y_bearing) * cos(angle + M_PI/2));
        cairo_rotate(cr, angle + M_PI + M_PI/2); // Rotate by 180 degrees
        center_x = extents.x_bearing + extents.width / 2;
        center_y = extents.y_bearing + extents.height / 2;
        cairo_translate(cr, 0, -extents.height * 2);
        cairo_rotate(cr, M_PI);
        
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_move_to(cr, extents.x_bearing, extents.y_bearing+extents.height);
        cairo_line_to(cr, extents.x_bearing, extents.y_bearing);
        cairo_line_to(cr, extents.x_bearing + extents.width/2, extents.y_bearing - extents.height/2);
        cairo_line_to(cr, extents.x_bearing + extents.width, extents.y_bearing);
        cairo_line_to(cr, extents.x_bearing + extents.width, extents.y_bearing + extents.height);
        cairo_close_path(cr);
        cairo_fill(cr);
        
        cairo_set_source_rgb(cr, 1, 1, 1);
        
        cairo_show_text(cr, rwyNumsList[f][0]);

        cairo_set_line_width(cr, 2.5);
        cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND);
        
        

        
        
        cairo_move_to(cr, extents.x_bearing, extents.y_bearing+extents.height);
        cairo_line_to(cr, extents.x_bearing, extents.y_bearing);
        cairo_line_to(cr, extents.x_bearing + extents.width/2, extents.y_bearing - extents.height/2);
        cairo_line_to(cr, extents.x_bearing + extents.width, extents.y_bearing);
        cairo_line_to(cr, extents.x_bearing + extents.width, extents.y_bearing + extents.height);
        cairo_stroke(cr);
        
        


        cairo_restore(cr);
        
        
        

        
        //Draw the rwy numbers in the center:
        
        char combinedNums[256];
        
        strcpy(combinedNums, rwyNumsList[f][0]);
        strcat(combinedNums, "-");
        strcat(combinedNums, rwyNumsList[f][1]);
        
        // Calculate the center of the runway
        double centerX = (pxStart_x + pxEnd_x) / 2.0;
        double centerY = (pxStart_y + pxEnd_y) / 2.0;

        // Define the width and height of the rectangle
        double rectWidth = 100.0;
        double rectHeight = 20.0;

        // Calculate the coordinates of the rectangle
        double rectX = centerX - rectWidth / 2.0;
        double rectY = centerY - rectHeight / 2.0;

        // Set the font size for the runway text
        cairo_set_font_size(cr, 20);

        // Calculate the text extents
        cairo_text_extents_t textExtents;
        cairo_text_extents(cr, combinedNums, &textExtents);

        // Apply transformations for the rectangle and runway text
        cairo_save(cr);
        cairo_translate(cr, centerX, centerY);
        cairo_rotate(cr, angle);

        // Draw the rectangle
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_rectangle(cr, -textExtents.width/2-3, -textExtents.height/2, textExtents.width+7, textExtents.height);
        cairo_fill(cr);

        // Draw the runway text in the middle of the rectangle
        cairo_set_source_rgb(cr, 1, 1, 1);
        cairo_move_to(cr, -textExtents.width / 2.0, textExtents.height/2);
        cairo_show_text(cr, combinedNums);

        cairo_restore(cr);

        
  
        
        
        
        

        
        
        
    }
    
    cairo_restore(cr);
    
    cairo_set_font_size(cr, 20);
   // draw_text(cr, test, 1000, 140, 2);
    
    
    
    
    
    
    
    
    
    
    
    
    
}








static void
mapND (cairo_t *cr, double x, double y)
{
    
    
    
    
    const char* degreesList []  = {"N", "3", "6", "E", "12", "15", "S", "21", "24", "W", "30", "33"};
    
    double r = 375;
    double spike_len = 10;
    int spike_count = 72;
    double angle_increment = 2 * M_PI / spike_count;
    
    
    
    cairo_save(cr);
    cairo_translate(cr, x, y);
    cairo_rotate(cr, -M_PI / 2);
    cairo_translate(cr, -x, -y);
    
    
    
    for (int i = 0; i < spike_count; ++i) {
        cairo_set_source_rgb(cr, 1, 1, 1);
        double angle = i * angle_increment;
        cairo_move_to(cr, x + r * cos(angle), y + r * sin(angle));
        if (i % 2 != 0)
        {
            cairo_set_source_rgb(cr, 1, 1, 1);
            cairo_line_to(cr, x + (r + spike_len) * cos(angle), y + (r + spike_len) * sin(angle));
            cairo_stroke(cr);
            
        }
        else
        {
            cairo_set_source_rgb(cr, 1, 1, 1);
            cairo_line_to(cr, x + (r + (spike_len*2)) * cos(angle), y + (r + (spike_len*2)) * sin(angle));
            cairo_stroke(cr);
        }
        
        if (i % 6 == 0)
        {
            /*
             cairo_set_font_size(cr, 35);
             
             draw_text(cr, degreesList[i/6],x + (r + (spike_len*2)) * cos(angle), y + (r + (spike_len*2)) * sin(angle), 1);
             */
            
            
            cairo_set_font_size(cr, 35);
            cairo_save(cr);
            double text_angle = angle + M_PI_2;
            cairo_text_extents_t extents;
            cairo_text_extents(cr, degreesList[i/6], &extents);
            
            cairo_translate(cr, x + (r + (spike_len*2)) * cos(angle), y + (r + (spike_len*2)) * sin(angle));
            
            cairo_rotate(cr, text_angle);
            cairo_set_source_rgba(cr, 0, 0, 0, 0);
            cairo_rectangle(cr, -extents.width/2, -extents.height/2, extents.width, extents.height);
            cairo_stroke(cr);
            
            cairo_set_source_rgb(cr, 1, 1, 1);
            
            
            cairo_translate(cr, -extents.width/2, extents.height/20);
            
            
            
            cairo_show_text(cr, degreesList[i/6]);
            cairo_restore(cr);
            cairo_set_source_rgb(cr, 1, 1, 1);
            
        }
        
        
        
        
        
    }
    
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_arc(cr, x, y, r, 0, 2*M_PI);
    cairo_stroke(cr);
    
    static const double dashed3[] = {{9.5, 51.0, 9.5}};
    
    cairo_set_dash(cr, dashed3, 1, 0);
    cairo_arc(cr, x, y, r/2, 0, 2*M_PI);
    cairo_stroke(cr);
    
    cairo_restore(cr);
    
    static const double undash[] = {{1.0}};
    
    cairo_set_dash(cr, undash, 0, 0);
    
    
    
    
    //DRAW PLANE -------------------------------------------->
    cairo_save(cr);
    cairo_set_source_rgb(cr, 1, 0, 1);
    cairo_set_line_width(cr, 4.0);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_move_to(cr, x, y-15);
    cairo_line_to(cr, x, y+40);
    
    cairo_move_to(cr, x-35, y);
    cairo_line_to(cr, x+35, y);
    
    cairo_move_to(cr, x-10, y+35);
    cairo_line_to(cr, x+10, y+35);
    
    //375
    
    cairo_stroke(cr);
    cairo_restore(cr);
    //DRAW PLANE -------------------------------------------->
    
    
    
    
    
    
    
}














// Global position variables
double rwy_x = 500;
double rwy_y = 500;

static gboolean on_button_press_event(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
    if (event->button == GDK_BUTTON_PRIMARY) // left mouse button
    {
        rwy_x = event->x;
        rwy_y = event->y;

        gtk_widget_queue_draw(widget);
    }

    return TRUE;
}

static gboolean on_motion_notify_event(GtkWidget *widget, GdkEventMotion *event, gpointer data)
{
    if (event->state & GDK_BUTTON1_MASK) // left mouse button is pressed
    {
        rwy_x = event->x;
        rwy_y = event->y;

        gtk_widget_queue_draw(widget);
    }

    return TRUE;
}



static void do_drawing(cairo_t *cr, GtkWidget *widget)
{
    GtkWidget *win = gtk_widget_get_toplevel(widget);
    
    int width, height;
    gtk_window_get_size(GTK_WINDOW(win), &width, &height);
    
    cairo_select_font_face(cr, "BoeingEICAS", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_rectangle(cr, 0, 0, 10000, 10000);
    cairo_fill(cr);
    
    drawMapRWY(cr, rwy_x, rwy_y, "KORD");
}

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr,
                              gpointer user_data)
{
    do_drawing(cr, widget);
    
    return FALSE;
}




int main (int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *darea;
    
    gtk_init(&argc, &argv);
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    
    
    darea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), darea);
    
    g_signal_connect(G_OBJECT(darea), "draw",
                     G_CALLBACK(on_draw_event), NULL);
    
    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(darea), "button-press-event",
                     G_CALLBACK(on_button_press_event), NULL);
    g_signal_connect(G_OBJECT(darea), "motion-notify-event",
                     G_CALLBACK(on_motion_notify_event), NULL);

    // You must set the widget to receive these events.
    gtk_widget_set_events(darea, gtk_widget_get_events(darea) |
                                  GDK_BUTTON_PRESS_MASK |
                                  GDK_POINTER_MOTION_MASK);
    
    //gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
    
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 1000);
    
    
    
    
    
    gtk_window_set_title(GTK_WINDOW(window), "APTVISUALS");
    
    gtk_widget_show_all(window);
    
    gtk_main();
    
    return 0;
}
