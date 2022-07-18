/*                                                                                                          */
/*                                                                                                          */
/*                                                                                                          */
/*                                                                                                          */
/*                                     Time class and utility functions                                     */
/*                              Created by Alireza reisi & Amirhossein bahrami                              */
/*                                                June 2022                                                 */
/*                                                                                                          */
/*                                                                                                          */
/*                                                                                                          */
/*                                                                                                          */
#include <ctime>
//------------------------------------------------------------------------------------
// gettersetter macro
//------------------------------------------------------------------------------------
#ifndef gettersetter_declare
#define gettersetter_declare(type, name) \
    type get_##name();                   \
    void set_##name(type input);
#endif
#ifndef gettersetter_define
#define gettersetter_define(class, type, name) \
    type class ::get_##name() { return name; } \
    void class ::set_##name(type input) { name = input; }
#endif
//------------------------------------------------------------------------------------
class Time
{
private:
    int hour, minute, second;

public:
    Time();                                // default constructor
    Time(int h, int mi, int s);            // constructor with input
    void current_time();                   // changes time to current time
    void change_Time(int y, int m, int d); // changes time
    //------------------------------------------------------------------------------------
    // declaration of getters and setters
    //------------------------------------------------------------------------------------
    gettersetter_declare(int, hour);
    gettersetter_declare(int, minute);
    gettersetter_declare(int, second);
    //------------------------------------------------------------------------------------
};
Time::Time()
{
    hour = 1;
    minute = 1;
    second = 1;
}
Time::Time(int h, int mi, int s)
{
    if (h >= 0 && h <= 24 && mi >= 0 && mi <= 60 && s >= 0 && s <= 60)
    {
        hour = h;
        minute = mi;
        second = s;
    }
    else
    {
        throw "error:in making date -invalid date";
    }
}

void Time::current_time()
{
    time_t current = time(0);
    tm *date = localtime(&current);
    hour = date->tm_hour;
    minute = date->tm_min;
    second = date->tm_sec;
}
