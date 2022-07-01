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
using namespace std;
#include "Account.h"
#include <string>
#include <vector>
class Customer
{
public:
    Customer();                          // default constructor
    Customer(long long int input);       // constructor that gets id
    void push_back(Account input);       // adds given account to customer
    Account &operator[](int input);      //[]operator that returns address to account with index of input
    int size();                          // returns number of accounts of customer
    bool has_account(Account input);     // checks if customer has given account
    int index_of_account(Account input); // returns index of given account
    void erase(Account input);           // erase account
    string data();                       // returns a string containing data of customer
    string data_full();                  // returns a string containing data of customer with explanation
    void read(string input);             // reads data of a customer
    string showaccounts();               // returns a string containing all account numbers of customer
    string showaccountsfull();           // returns a string containing all accounts of customer
    string showaccountsbalance();        // returns a string containing all account numbers of customer with balance
    //------------------------------------------------------------------------------------
    // declaration of getters and setters
    //------------------------------------------------------------------------------------
    gettersetter_declare(string, name);
    gettersetter_declare(string, lastname);
    gettersetter_declare(long long int, id);
    gettersetter_declare(Date, birthday);
    gettersetter_declare(string, username);
    gettersetter_declare(string, password);
    gettersetter_declare(vector<Account>, accounts);
    //------------------------------------------------------------------------------------

private:
    string name;
    string lastname;
    long long int id;
    Date birthday;
    string username;
    string password;
    vector<Account> accounts;
};
Customer::Customer()
{
    name = "";
    lastname = "";
    id = 0;
    birthday.change_date(1, 1, 1);
    username = "";
    password = "";
}
Customer::Customer(long long int input)
{
    name = "";
    lastname = "";
    id = input;
    birthday.change_date(1, 1, 1);
    username = "";
    password = "";
}
void Customer::push_back(Account input)
{
    input.set_id_owner(id);
    if (!has_account(input))
    {
        accounts.push_back(input);
    }
    else
    {
        throw "error:in customer accounts -duplicate account";
    }
}
Account &Customer::operator[](int input)
{
    return accounts[input];
}
int Customer::size()
{
    return accounts.size();
}
bool Customer::has_account(Account input)
{
    bool result = false;
    for (size_t i = 0; i < accounts.size(); i++)
    {
        if (input.get_account_number() == accounts[i].get_account_number())
        {
            result = true;
        }
    }
    return result;
}
int Customer::index_of_account(Account input)
{
    int result = -1;
    if (Customer::has_account(input))
    {
        for (size_t i = 0; i < accounts.size(); i++)
        {
            if (input.get_account_number() == accounts[i].get_account_number())
            {
                result = i;
            }
        }
    }
    return result;
}
void Customer::erase(Account input)
{
    if (Customer::has_account(input))
    {
        accounts.erase(accounts.begin() + (Customer::index_of_account(input)) + 1);
    }
    else
    {
        throw "error:in customer erase account -no mathing account";
    }
}
string Customer::data()
{
    string result;
    result += name;
    result += ";";
    result += lastname;
    result += ";";
    result += username;
    result += ";";
    result += password;
    result += ";";
    result += to_string(id);
    result += ";";
    result += to_string(birthday.get_year());
    result += "/";
    result += to_string(birthday.get_month());
    result += "/";
    result += to_string(birthday.get_day());
    result += ";";
    result += to_string(accounts.size());
    result += ";";
    for (size_t i = 0; i < accounts.size(); i++)
    {
        result += to_string(accounts[i].get_account_number());
        result += ";";
        result += to_string(accounts[i].get_balance());
        result += ";";
        result += to_string(accounts[i].get_opening_date().get_year());
        result += "/";
        result += to_string(accounts[i].get_opening_date().get_month());
        result += "/";
        result += to_string(accounts[i].get_opening_date().get_day());
        result += ";";
        result += to_string(accounts[i].get_active());
        result += ";";
    }
    return result;
}
string Customer::data_full()
{
    string result = "name:";
    result += name;
    result += ";lastname:";
    result += lastname;
    result += ";username:";
    result += username;
    result += ";password:";
    result += password;
    result += ";id:";
    result += to_string(id);
    result += ";birthday:";
    result += to_string(birthday.get_year());
    result += "/";
    result += to_string(birthday.get_month());
    result += "/";
    result += to_string(birthday.get_day());
    return result;
}
void Customer::read(string input)
{
    int i = 0;
    string temp = "";
    while (input[i] != ';')
    {
        temp += input[i];
        i++;
    }
    i++;
    name = temp;
    temp = "";
    while (input[i] != ';')
    {
        temp += input[i];
        i++;
    }
    i++;
    lastname = temp;
    temp = "";
    while (input[i] != ';')
    {
        temp += input[i];
        i++;
    }
    i++;
    username = temp;
    temp = "";
    while (input[i] != ';')
    {
        temp += input[i];
        i++;
    }
    i++;
    password = temp;
    temp = "";
    while (input[i] != ';')
    {
        temp += input[i];
        i++;
    }
    i++;
    id = stoull(temp);
    temp = "";
    while (input[i] != '/')
    {
        temp += input[i];
        i++;
    }
    i++;
    birthday.set_year(stoi(temp));
    temp = "";
    while (input[i] != '/')
    {
        temp += input[i];
        i++;
    }
    i++;
    birthday.set_month(stoi(temp));
    temp = "";
    while (input[i] != ';')
    {
        temp += input[i];
        i++;
    }
    i++;
    birthday.set_day(stoi(temp));
    temp = "";
    int j = 0;
    while (input[i] != ';')
    {
        temp += input[i];
        i++;
    }
    i++;
    j = stoi(temp);
    temp = "";
    for (int k = 0; k < j; k++)
    {
        Account a;
        temp = "";
        while (input[i] != ';')
        {
            temp += input[i];
            i++;
        }
        i++;
        a.set_account_number(stoll(temp));
        temp = "";
        while (input[i] != ';')
        {
            temp += input[i];
            i++;
        }
        i++;
        a.set_balance(stoull(temp));
        temp = "";
        while (input[i] != '/')
        {
            temp += input[i];
            i++;
        }
        i++;
        int y = stoi(temp);
        temp = "";
        while (input[i] != '/')
        {
            temp += input[i];
            i++;
        }
        i++;
        int m = stoi(temp);
        temp = "";
        while (input[i] != ';')
        {
            temp += input[i];
            i++;
        }
        i++;
        int d = stoi(temp);
        a.set_opening_date(Date{y, m, d});
        temp = "";
        while (input[i] != ';')
        {
            temp += input[i];
            i++;
        }
        i++;
        a.set_active(stoi(temp));
        accounts.push_back(a);
    }
}
string Customer::showaccounts()
{
    string result;
    for (size_t i = 0; i < accounts.size(); i++)
    {
        result += to_string(accounts[i].get_account_number());
        if (i != accounts.size() - 1)
        {
            result += ";";
        }
    }
    return result;
}
string Customer::showaccountsfull()
{
    string result;
    for (size_t i = 0; i < accounts.size(); i++)
    {
        result += to_string(accounts[i].get_account_number());
        result += ";";
        result += to_string(accounts[i].get_balance());
        result += ";";
        result += to_string(accounts[i].get_opening_date().get_year());
        result += "/";
        result += to_string(accounts[i].get_opening_date().get_month());
        result += "/";
        result += to_string(accounts[i].get_opening_date().get_day());
        result += ";";
        result += to_string(accounts[i].get_active());
        if (i != accounts.size() - 1)
        {
            result += ";";
        }
    }
    return result;
}
string Customer::showaccountsbalance()
{
    string result;
    for (size_t i = 0; i < accounts.size(); i++)
    {
        result += "account number:";
        result += to_string(accounts[i].get_account_number());
        result += ", balance:";
        result += to_string(accounts[i].get_balance());
        result += "$";
        if (i != accounts.size() - 1)
        {
            result += ";";
        }
    }
    return result;
}