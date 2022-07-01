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
#ifndef Date_guard
#define Date_guard
#include "Date.cpp"
//------------------------------------------------------------------------------------
// definition of getters and setters of date class
//------------------------------------------------------------------------------------
gettersetter_define(Date, int, year);
gettersetter_define(Date, int, month);
gettersetter_define(Date, int, day);
//------------------------------------------------------------------------------------
#endif