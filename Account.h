/*                                                                                                          */
/*                                                                                                          */
/*                                                                                                          */
/*                                                                                                          */
/*                                   Account class and utility functions                                    */
/*                              Created by Alireza reisi & Amirhossein bahrami                              */
/*                                                June 2022                                                 */
/*                                                                                                          */
/*                                                                                                          */
/*                                                                                                          */
/*                                                                                                          */
#include "Date.h"
#ifndef Account_gaurd
#define Account_gaurd
#include "Account.cpp"
#ifndef gettersetter_declare
#define gettersetter_declare(type, name) \
    type get_##name();                   \
    void set_##name(type input);
#endif
//------------------------------------------------------------------------------------
// definition of getters and setters of account class
//------------------------------------------------------------------------------------
#ifndef gettersetter_define
#define gettersetter_define(class, type, name) \
    type class ::get_##name() { return name; } \
    void class ::set_##name(type input) { name = input; }
#endif
gettersetter_define(Account, long long int, account_number);
gettersetter_define(Account, long long int, id_owner);
gettersetter_define(Account, Date, opening_date);
gettersetter_define(Account, long long int, balance);
gettersetter_define(Account, bool, active);
#endif
//------------------------------------------------------------------------------------