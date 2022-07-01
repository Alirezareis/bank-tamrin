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
#include <string>
#ifndef Customer_gaurd
#define Customer_gaurd
#include "Customer.h"
#endif
#ifndef Date_gaurd
#define Date_gaurd
#include "Date.h"
#endif
#include <vector>
#ifndef Account_gaurd
#define Account_gaurd
#include "Account.h"
#endif
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
class Employee
{
public:
    Employee();                       // default constructor
    Employee(long long int input);    // constructor that gets personnel id
    string data();                    // returns a string containing data of employee
    string data_full();               // returns a string containing data of employee with explanation
    void read(string input);          // reads employee data from a string
    void req_leave_time(float value); // request leave time func
    void req_over_time(float value);  // request over time func
    //------------------------------------------------------------------------------------
    // gettersetter macro
    //------------------------------------------------------------------------------------
    gettersetter_declare(string, name);
    gettersetter_declare(string, lastname);
    gettersetter_declare(long long int, personnel_id);
    gettersetter_declare(Date, birthday);
    gettersetter_declare(string, username);
    gettersetter_declare(string, password);
    gettersetter_declare(float, income);
    gettersetter_declare(float, over_time);
    gettersetter_declare(float, last_leave_time);
    gettersetter_declare(bool, is_boss);
    //------------------------------------------------------------------------------------

private:
    string name;
    string lastname;
    long long int personnel_id;
    Date birthday;
    float income;
    string username;
    string password;
    float over_time;
    float last_leave_time;
    bool is_boss = false;
};
Employee::Employee()
{
    name = "";
    lastname = "";
    personnel_id = 0;
    income = 0;
    birthday.change_date(1, 1, 1);
    username = "";
    password = "";
}
Employee::Employee(long long int input)
{
    name = "";
    lastname = "";
    personnel_id = input;
    income = 0;
    birthday.change_date(1, 1, 1);
    username = "";
    password = "";
}

string Employee::data()
{
    string result = "";
    result += name;
    result += ";";
    result += lastname;
    result += ";";
    result += username;
    result += ";";
    result += password;
    result += ";";
    result += to_string(personnel_id);
    result += ";";
    result += to_string(birthday.get_year());
    result += "/";
    result += to_string(birthday.get_month());
    result += "/";
    result += to_string(birthday.get_day());
    result += ";";
    result += to_string(income);
    result += ";";
    result += to_string(last_leave_time);
    result += ";";
    result += to_string(over_time);
    result += ";";
    result += to_string(is_boss);
    result += ";";
    return result;
}
string Employee::data_full()
{
    string result = "name:";
    result += name;
    result += ";lastname:";
    result += lastname;
    result += ";username:";
    result += username;
    result += ";password:";
    result += password;
    result += ";personnel id:";
    result += to_string(personnel_id);
    result += ";birthday:";
    result += to_string(birthday.get_year());
    result += "/";
    result += to_string(birthday.get_month());
    result += "/";
    result += to_string(birthday.get_day());
    result += ";income:";
    result += to_string(income);
    result += ";leave hour:";
    result += to_string(last_leave_time);
    result += ";over time:";
    result += to_string(over_time);
    return result;
}
void Employee::read(string input)
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
    personnel_id = stoul(temp);
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
    while (input[i] != ';')
    {
        temp += input[i];
        i++;
    }
    i++;
    income = stof(temp);
    temp = "";
    while (input[i] != ';')
    {
        temp += input[i];
        i++;
    }
    i++;
    last_leave_time = stof(temp);
    temp = "";
    while (input[i] != ';')
    {
        temp += input[i];
        i++;
    }
    i++;
    over_time = stof(temp);
    temp = "";
    while (input[i] != ';')
    {
        temp += input[i];
        i++;
    }
    i++;
    is_boss = stoi(temp);
}
void Employee::req_leave_time(float value)
{
    last_leave_time += value;
    income -= 100000 * value;
}
void Employee::req_over_time(float value)
{
    over_time += value;
    if (over_time >= 12)
    {
        over_time = 12;
    }
    income += over_time * 120000;
}