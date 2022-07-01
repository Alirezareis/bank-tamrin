/*                                                                                                          */
/*                                                                                                          */
/*                                                                                                          */
/*                                                                                                          */
/*                                     Date class and utility functions                                     */
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
class Date
{
private:
    int year, month, day;

public:
    Date();                                // default constructor
    Date(int y, int m, int d);             // constructor with input
    void current_date();                   // changes date to current date
    void change_date(int y, int m, int d); // changes date
    //------------------------------------------------------------------------------------
    // declaration of getters and setters
    //------------------------------------------------------------------------------------
    gettersetter_declare(int, year);
    gettersetter_declare(int, month);
    gettersetter_declare(int, day);
    //------------------------------------------------------------------------------------
};
Date::Date()
{
    year = 1;
    month = 1;
    day = 1;
}
Date::Date(int y, int m, int d)
{
    if ((y > 0 && m > 0 && m < 7 && d > 0 && d < 32) || (y > 0 && m > 7 && m < 12 && d > 0 && d < 31) || (y > 0 && m == 12 && d > 0 && d < 30))
    {
        year = y;
        month = m;
        day = d;
    }
    else
    {
        throw "error:in making date -invalid date";
    }
}
void Date::current_date()
{
    time_t current = time(0);
    tm *date = localtime(&current);
    year = 1900 + date->tm_year;
    month = 1 + date->tm_mon;
    day = date->tm_mday;
}
void Date::change_date(int y, int m, int d)
{
    if ((y > 0 && m > 0 && m < 7 && d > 0 && d < 32) || (y > 0 && m > 7 && m < 12 && d > 0 && d < 31) || (y > 0 && m == 12 && d > 0 && d < 30))
    {
        year = y;
        month = m;
        day = d;
    }
    else
    {
        throw "error:in changing date -invalid date";
    }
}