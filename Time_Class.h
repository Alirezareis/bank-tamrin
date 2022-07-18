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
#ifndef Time_guard
#define Time_guard
#include "Time_Class.cpp"
//------------------------------------------------------------------------------------
// definition of getters and setters of time class
//------------------------------------------------------------------------------------
gettersetter_define(Time, int, hour);
gettersetter_define(Time, int, minute);
gettersetter_define(Time, int, second);
//------------------------------------------------------------------------------------
#endif