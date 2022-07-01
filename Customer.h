/*                                                                                                          */
/*                                                                                                          */
/*                                                                                                          */
/*                                                                                                          */
/*                                   Customer class and utility functions                                   */
/*                              Created by Alireza reisi & Amirhossein bahrami                              */
/*                                                June 2022                                                 */
/*                                                                                                          */
/*                                                                                                          */
/*                                                                                                          */
/*                                                                                                          */
#ifndef Customer_gaurd
#define Customer_gaurd
#include "Customer.cpp"
//------------------------------------------------------------------------------------
// definition of getters and setters of customer class
//------------------------------------------------------------------------------------
gettersetter_define(Customer, string, name);
gettersetter_define(Customer, string, lastname);
gettersetter_define(Customer, long long int, id);
gettersetter_define(Customer, Date, birthday);
gettersetter_define(Customer, string, username);
gettersetter_define(Customer, string, password);
gettersetter_define(Customer, vector<Account>, accounts);
//------------------------------------------------------------------------------------
#endif