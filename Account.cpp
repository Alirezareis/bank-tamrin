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
#include <vector>
using namespace std;
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
class Account
{
public:
    Account();                          // default constructor
    Account(long long int input);       // constructor that gets account number
    void deposit(long long int input);  // deposit func
    bool withdraw(long long int input); // withdraw func
    //------------------------------------------------------------------------------------
    // declaration of getters of setters
    //------------------------------------------------------------------------------------
    gettersetter_declare(long long int, account_number);
    gettersetter_declare(long long int, id_owner);
    gettersetter_declare(Date, opening_date);
    gettersetter_declare(long long int, balance);
    gettersetter_declare(bool, active);
    //------------------------------------------------------------------------------------
private:
    long long int account_number;
    long long int id_owner;
    Date opening_date;
    long long int balance;
    bool active = false;
};
Account::Account()
{
    account_number = 0;
    id_owner = 0;
    opening_date.change_date(1, 1, 1);
    balance = 0;
    active = false;
}
Account::Account(long long int input)
{
    account_number = input;
    id_owner = 0;
    opening_date.change_date(1, 1, 1);
    balance = 0;
    active = false;
}
void Account::deposit(long long int input)
{
    balance += input;
}
bool Account::withdraw(long long int input)
{
    bool result = false;

    if (balance >= input)
    {
        balance -= input;
        result = true;
    }
    else
    {
        throw "error:in withdrawing -insufficent balance";
    }
    return result;
}