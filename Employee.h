/*                                                                                                          */
/*                                                                                                          */
/*                                                                                                          */
/*                                                                                                          */
/*                                   Employee class and utility functions                                   */
/*                              Created by Alireza reisi & Amirhossein bahrami                              */
/*                                                June 2022                                                 */
/*                                                                                                          */
/*                                                                                                          */
/*                                                                                                          */
/*                                                                                                          */
#ifndef Employee_gaurd
#define Employee_gaurd
#include "Employee.cpp"
//------------------------------------------------------------------------------------
// definition of getters and setters of employee class
//------------------------------------------------------------------------------------
gettersetter_define(Employee, string, name);
gettersetter_define(Employee, string, lastname);
gettersetter_define(Employee, long long int, personnel_id);
gettersetter_define(Employee, Date, birthday);
gettersetter_define(Employee, string, username);
gettersetter_define(Employee, string, password);
gettersetter_define(Employee, float, income);
gettersetter_define(Employee, float, over_time);
gettersetter_define(Employee, float, last_leave_time);
gettersetter_define(Employee, bool, is_boss);
//------------------------------------------------------------------------------------
// definition of getters and setters of employee class
//------------------------------------------------------------------------------------
#endif