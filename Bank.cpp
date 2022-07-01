/*                                                                                                          */
/*                                                                                                          */
/*                                                                                                          */
/*                                                                                                          */
/*                                     Bank class and utility functions                                     */
/*                              Created by Alireza reisi & Amirhossein bahrami                              */
/*                                                June 2022                                                 */
/*                                                                                                          */
/*                                                                                                          */
/*                                                                                                          */
/*                                                                                                          */
#ifndef Customer_gaurd
#define Customer_gaurd
#include "Customer.h"
#endif
#ifndef Employee_gaurd
#define Employee_gaurd
#include "Employee.h"
#endif
#include <vector>
#include <fstream>
#include <string>
#ifndef Time_gaurd
#define Time_gaurd
#include "Time_Class.h"
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

class Bank
{
public:
    Bank();                                                                // default constructor
    Bank(int input, string name);                                          // constructor with branch code and name as input
    void log(string log_text);                                             // func for logging errors
    void report(string kind, long long id, string action, long long prop); // report to file
    void report(string kind, long long id, string action, float prop);     // report to file
    void save();                                                           // save data to file
    void load();                                                           // load data from file
    bool login(string user, string pass, bool is_customer);                // login func returns true if login is successful
    void add_customer(Customer input);                                     // adds a customer to database
    void add_employee(Employee input);                                     // adds a employee to database
    int index_customer(Customer input);                                    // returns index of given customer (-1 if its not in the database)
    int index_employee(Employee input);                                    // returns index of given employee (-1 if its not in the database)
    static vector<Customer> customers;                                     // customers data
    static vector<Employee> employees;                                     // employees data
    bool username_is_unique(string username);                              // check if given username is unique
    int number_of_accounts();                                              // returns the account number of last added account (number of accounts if no account got deleted)
    string customer_names();                                               // returns a string containing name of customers
    string employee_names();                                               // returns a string containing name of employees except the boss
    void fire_employee(int index);                                         // fire an employee with given index
    void delete_customer(int index);                                       // delete a customer with given index
    //--------------------------------------------
    // declaration of getters and setters
    //--------------------------------------------
    gettersetter_declare(string, branch_name);
    gettersetter_declare(int, branch_code);
    gettersetter_declare(bool, is_employee);
    gettersetter_declare(bool, is_boss);
    gettersetter_declare(int, index);
    //--------------------------------------------

private:
    string branch_name;   // branch name
    int branch_code;      // branch code
    bool is_employee;     // the person who logged in is an employee or not
    bool is_boss = false; // the person who logged in is the boss or not
    int index = -1;       // index of the person who logged in in database
};
vector<Customer> Bank::customers;
vector<Employee> Bank::employees;
Bank::Bank()
{
    branch_code = 0;
    branch_name = "";
}
Bank::Bank(int input, string name)
{
    branch_code = input;
    branch_name = name;
}
void Bank::log(string log_text)
{
    static bool first_time = true;
    string temp = "", result = "";
    if (first_time) // makes log.txt for the first time
    {
        ofstream log("log.txt");
        log << log_text;
        log.close();
        first_time = false;
    }
    else // reads log.txt if its not first time that log is running and saves it in result string
    {
        ifstream log("log.txt");
        if (log) // checks if log.txt exists
        {
            while (log)
            {
                getline(log, temp); // reads a line from log.txt
                if (result.size() > 0)
                {
                    result += "\n";
                }
                result += temp; // adds the line to result
            }
            for (size_t i = 0; i < temp.size() + 1; i++) // deletes the duplicate line at the end
            {
                result.pop_back();
            }
        }
        else
        {
            result = "error: in log -log file went missing -creating new log file";
        }
    }
    if (result.size() > 0) // checks if result contains anything
    {
        result += "\n";
        result += log_text;
        log_text = result;
    }
    ofstream log("log.txt");
    log << log_text;
}
void Bank::report(string kind, long long id, string action, long long prop)
{
    Date date_current; // date object
    Time time_current; // time object
    date_current.current_date();
    time_current.current_time();
    string result = "", temp = "";
    ifstream report("report.txt"); // opens report.txt
    if (report)                    // checks if report.txt exists
    {
        while (report)
        {
            getline(report, temp); // reads a line from report.txt
            if (result.size() > 0)
            {
                result += "\n";
            }
            result += temp; // adds the line to result
        }
        for (size_t i = 0; i < temp.size() + 1; i++) // deletes the duplicate line at the end
        {
            result.pop_back();
        }
    }
    else
    {
        ofstream report("report.txt"); // makes report.txt
    }
    {
        ofstream report("report.txt"); // makes report.txt
        report << result << endl;      // write result to report
        //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        // reporting conditions
        //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        if (kind == "Employee")
        {
            if (action == "login")
            {
                report << kind << " with personnel id: " << id << " " << action << " in Date: " << date_current.get_day() << "/" << date_current.get_month() << "/" << date_current.get_year() << " Time: " << time_current.get_hour() << ":" << time_current.get_minute() << ":" << time_current.get_second();
            }
            else if (action == "add")
            {
                report << kind << " with personnel id: " << id << " " << action << "ed in Date: " << date_current.get_day() << "/" << date_current.get_month() << "/" << date_current.get_year() << " Time: " << time_current.get_hour() << ":" << time_current.get_minute() << ":" << time_current.get_second();
            }
            else if (action == "fire")
            {
                report << kind << " with personnel id: " << id << " " << action << "ed in Date: " << date_current.get_day() << "/" << date_current.get_month() << "/" << date_current.get_year() << " Time: " << time_current.get_hour() << ":" << time_current.get_minute() << ":" << time_current.get_second();
            }
        }
        else if (kind == "Customer")
        {
            if (action == "login")
            {
                report << kind << " with id: " << id << " " << action << " in Date: " << date_current.get_day() << "/" << date_current.get_month() << "/" << date_current.get_year() << " Time: " << time_current.get_hour() << ":" << time_current.get_minute() << ":" << time_current.get_second();
            }
            if (action == "add")
            {
                report << kind << " with id: " << id << " " << action << "ed in Date: " << date_current.get_day() << "/" << date_current.get_month() << "/" << date_current.get_year() << " Time: " << time_current.get_hour() << ":" << time_current.get_minute() << ":" << time_current.get_second();
            }
            if (action == "delete")
            {
                report << kind << " with id: " << id << " " << action << "ed in Date: " << date_current.get_day() << "/" << date_current.get_month() << "/" << date_current.get_year() << " Time: " << time_current.get_hour() << ":" << time_current.get_minute() << ":" << time_current.get_second();
            }
        }
        else if (kind == "Account")
        {
            if (action == "open")
            {
                report << kind << " with account number: " << id << " " << action << "ed in Date: " << date_current.get_day() << "/" << date_current.get_month() << "/" << date_current.get_year() << " Time: " << time_current.get_hour() << ":" << time_current.get_minute() << ":" << time_current.get_second();
            }
            else if (action == "delete")
            {
                report << kind << " with account number: " << id << " " << action << "ed in Date: " << date_current.get_day() << "/" << date_current.get_month() << "/" << date_current.get_year() << " Time: " << time_current.get_hour() << ":" << time_current.get_minute() << ":" << time_current.get_second();
            }
            else if (action == "deposit")
            {
                report << kind << " with account number: " << id << " " << action << "ed amount " << prop << " in Date: " << date_current.get_day() << "/" << date_current.get_month() << "/" << date_current.get_year() << " Time: " << time_current.get_hour() << ":" << time_current.get_minute() << ":" << time_current.get_second();
            }
            else if (action == "withdraw")
            {
                report << kind << " with account number: " << id << " " << action << "ed amount " << prop << " in Date: " << date_current.get_day() << "/" << date_current.get_month() << "/" << date_current.get_year() << " Time: " << time_current.get_hour() << ":" << time_current.get_minute() << ":" << time_current.get_second();
            }
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    }
}
void Bank::report(string kind, long long id, string action, float prop)
{
    Date date_current; // date object
    Time time_current; // time object
    date_current.current_date();
    time_current.current_time();
    string result = "", temp = "";
    ifstream report("report.txt"); // opens report.txt
    if (report)                    // checks if report.txt exists
    {
        while (report)
        {
            getline(report, temp); // reads a line from report.txt
            if (result.size() > 0)
            {
                result += "\n";
            }
            result += temp; // adds the line to result
        }
        for (size_t i = 0; i < temp.size() + 1; i++) // deletes the duplicate line at the end
        {
            result.pop_back();
        }
    }
    else
    {
        ofstream report("report.txt"); // makes report.txt
    }
    {
        ofstream report("report.txt"); // makes report.txt
        report << result << endl;      // write result to report
        //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

        //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        if (kind == "Employee")
        {
            if (action == "rest")
            {
                report << kind << " with personnel id: " << id << " requested " << prop << " hour of " << action << " in Date: " << date_current.get_day() << "/" << date_current.get_month() << "/" << date_current.get_year() << " Time: " << time_current.get_hour() << ":" << time_current.get_minute() << ":" << time_current.get_second();
            }
            else if (action == "overtime")
            {
                report << kind << " with personnel id: " << id << " requested " << prop << " hour of " << action << " in Date: " << date_current.get_day() << "/" << date_current.get_month() << "/" << date_current.get_year() << " Time: " << time_current.get_hour() << ":" << time_current.get_minute() << ":" << time_current.get_second();
            }
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    }
}
void Bank::save()
{
    ofstream Bank_data("Bank_data.txt"); // makes Bank_data.txt
    Bank_data << "Employees" << endl
              << "//name;lastname;username;password;personnel id;birthday;income;leave_hour;over_time;is_boss;" << endl; // saving format of employees
    Bank_data << employees.size() << endl;
    for (size_t i = 0; i < employees.size(); i++)
    {
        Bank_data << employees[i].data() << endl;
    }
    Bank_data << "Customer" << endl
              << "//name;lastname;username;password;id;birthday;number_of_accounts;account_number[1];blance;opening_date;is_active;account_number[2];..." << endl; // saving format of customers
    Bank_data << customers.size() << endl;
    for (size_t i = 0; i < customers.size(); i++)
    {
        Bank_data << customers[i].data() << endl;
    }
    Bank_data.close();
}
void Bank::load()
{
    string temp;
    ifstream Bank_data("Bank_data.txt"); // opens Bank_data.txt
    if (!Bank_data)                      // checks if Bank_data.txt does not exist
    {
        ofstream Bank_data("Bank_data.txt"); // makes Bank_data.txt
    }
    else
    {
        int employee_count = 0, customer_count = 0;
        for (size_t i = 0; i < 3; i++) // will to go third line and reads employee count
        {
            getline(Bank_data, temp);
            if (i == 2)
            {
                employee_count = stoi(temp);
            }
        }
        for (int i = 0; i < employee_count; i++) // reads employees
        {
            getline(Bank_data, temp);
            Employee employee;
            employee.read(temp);
            employees.push_back(employee);
        }
        for (size_t i = 0; i < 3; i++) // will to go third line after last employee and reads customer count
        {
            getline(Bank_data, temp);
            if (i == 2)
            {
                customer_count = stoi(temp);
            }
        }
        for (int i = 0; i < customer_count; i++) // reads customers
        {
            getline(Bank_data, temp);
            Customer customer;
            customer.read(temp);
            customers.push_back(customer);
        }
    }
}
bool Bank::login(string user, string pass, bool is_customer)
{

    bool result = false;
    if (user.size() == 0)
    {
        throw "error: in login -empty username";
    }
    else
    {
        if (pass.size() == 0)
        {
            throw "error: in login -empty password";
        }
    }
    if (is_customer)
    {
        if (customers.size() == 0)
        {
            throw "error: in login -no customer in database";
        }
        for (size_t i = 0; i < customers.size() && !result; i++)
        {
            if (user == customers[i].get_username())
            {
                if (pass == customers[i].get_password())
                {
                    result = true;
                    is_employee = false;
                    index = i;
                }
                else
                {
                    throw "error: in login -wrong password";
                }
            }
            else if (i == customers.size() - 1)
            {
                throw "error: in login -no matching username";
            }
        }
    }
    else
    {
        if (employees.size() == 0)
        {
            throw "error: in login -no employee in database";
        }
        for (size_t i = 0; i < employees.size() && !result; i++)
        {

            if (user == employees[i].get_username())
            {
                if (pass == employees[i].get_password())
                {
                    result = true;
                    is_employee = true;
                    index = i;
                    if (employees[i].get_is_boss())
                    {
                        is_boss = true;
                    }
                    else
                    {
                        is_boss = false;
                    }
                }
                else
                {
                    throw "error: in login -wrong password";
                }
            }
            else if (i == employees.size() - 1)
            {
                throw "error: in login -no matching username";
            }
        }
    }

    return result;
}

void Bank::add_customer(Customer input)
{
    if (Bank::index_customer(input) == -1)
    {
        customers.push_back(input);
    }
}
void Bank::add_employee(Employee input)
{
    if (Bank::index_employee(input) == -1)
    {
        employees.push_back(input);
    }
}
int Bank::index_customer(Customer input)
{

    int result = -1;
    for (size_t i = 0; i < customers.size(); i++)
    {
        if (customers[i].get_id() == input.get_id())
        {
            result = i;
        }
    }
    return result;
}
int Bank::index_employee(Employee input)
{

    int result = -1;
    for (size_t i = 0; i < employees.size(); i++)
    {
        if (employees[i].get_personnel_id() == input.get_personnel_id())
        {
            result = i;
        }
    }
    return result;
}
bool Bank::username_is_unique(string username)
{
    bool result = true;
    for (size_t i = 0; i < customers.size(); i++)
    {
        if (username == customers[i].get_username())
        {
            result = false;
        }
    }
    for (size_t i = 0; i < employees.size(); i++)
    {
        if (username == employees[i].get_username())
        {
            result = false;
        }
    }
    return result;
}
int Bank::number_of_accounts()
{
    int result = 0;
    for (size_t i = 0; i < customers.size(); i++)
    {
        for (size_t j = 0; j < customers[i].size(); j++)
        {
            if (customers[i][j].get_account_number() >= result)
            {
                result = customers[i][j].get_account_number();
            }
        }
    }
    return result;
}
string Bank::customer_names()
{
    string result = "";
    for (size_t i = 0; i < customers.size(); i++)
    {

        result += customers[i].get_name();
        result += " ";
        result += customers[i].get_lastname();
        result += ";";
    }
    result.pop_back();
    return result;
}
string Bank::employee_names()
{
    string result = "";
    for (size_t i = 0; i < employees.size(); i++)
    {
        if (!employees[i].get_is_boss())
        {
            result += employees[i].get_name();
            result += " ";
            result += employees[i].get_lastname();
            result += ";";
        }
    }
    result.pop_back();
    return result;
}
void Bank::fire_employee(int index)
{
    employees.erase(employees.begin() + index + 1);
}
void Bank::delete_customer(int index)
{
    customers.erase(customers.begin() + index + 1);
}
void DrawError(string error) // draws the gui error
{
    if (int(error.size()) > 0)
    {
        string temp;
        int index = 0;
        while (error[index] != '-')
        {
            index++;
        }
        index++;
        while (index < int(error.size()))
        {
            temp += error[index];
            index++;
        }
        raylib::Color TextColor = RED;
        TextColor.DrawText(temp, GetScreenWidth() / 2 - MeasureText(temp.c_str(), 8) / 2, GetScreenHeight() - 13, 8);
    }
}
bool GuiValueBox(Rectangle bounds, const char *text, long long int *value, int minValue, long long int maxValue, bool editMode) // gui value box that gets long long
{
#if !defined(VALUEBOX_MAX_CHARS)
#define VALUEBOX_MAX_CHARS 32
#endif

    GuiControlState state = guiState;
    bool pressed = false;

    char textValue[VALUEBOX_MAX_CHARS + 1] = "\0";
    sprintf(textValue, "%lld", *value);

    Rectangle textBounds = {0};
    if (text != NULL)
    {
        textBounds.width = (float)GetTextWidth(text);
        textBounds.height = (float)GuiGetStyle(DEFAULT, TEXT_SIZE);
        textBounds.x = bounds.x + bounds.width + GuiGetStyle(VALUEBOX, TEXT_PADDING);
        textBounds.y = bounds.y + bounds.height / 2 - GuiGetStyle(DEFAULT, TEXT_SIZE) / 2;
        if (GuiGetStyle(VALUEBOX, TEXT_ALIGNMENT) == GUI_TEXT_ALIGN_LEFT)
            textBounds.x = bounds.x - textBounds.width - GuiGetStyle(VALUEBOX, TEXT_PADDING);
    }

    // Update control
    //--------------------------------------------------------------------
    if ((state != GUI_STATE_DISABLED) && !guiLocked)
    {
        Vector2 mousePoint = GetMousePosition();

        bool valueHasChanged = false;

        if (editMode)
        {
            state = GUI_STATE_PRESSED;

            int keyCount = (int)strlen(textValue);

            // Only allow keys in range [48..57]
            if (keyCount < VALUEBOX_MAX_CHARS)
            {
                if (GetTextWidth(textValue) < bounds.width)
                {
                    int key = GetCharPressed();
                    if ((key >= 48) && (key <= 57))
                    {
                        textValue[keyCount] = (char)key;
                        keyCount++;
                        valueHasChanged = true;
                    }
                }
            }

            // Delete text
            if (keyCount > 0)
            {
                if (IsKeyPressed(KEY_BACKSPACE))
                {
                    keyCount--;
                    textValue[keyCount] = '\0';
                    if (keyCount < 0)
                        keyCount = 0;
                    valueHasChanged = true;
                }
            }

            if (valueHasChanged)
                *value = atoll(textValue);

            if (IsKeyPressed(KEY_ENTER) || (!CheckCollisionPointRec(mousePoint, bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)))
                pressed = true;
        }
        else
        {
            if (*value > maxValue)
                *value = maxValue;
            else if (*value < minValue)
                *value = minValue;

            if (CheckCollisionPointRec(mousePoint, bounds))
            {
                state = GUI_STATE_FOCUSED;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    pressed = true;
            }
        }
    }
    //--------------------------------------------------------------------

    // Draw control
    //--------------------------------------------------------------------
    Color baseColor = BLANK;
    if (state == GUI_STATE_PRESSED)
        baseColor = GetColor(GuiGetStyle(VALUEBOX, BASE_COLOR_PRESSED));
    else if (state == GUI_STATE_DISABLED)
        baseColor = GetColor(GuiGetStyle(VALUEBOX, BASE_COLOR_DISABLED));

    // WARNING: BLANK color does not work properly with Fade()
    GuiDrawRectangle(bounds, GuiGetStyle(VALUEBOX, BORDER_WIDTH), Fade(GetColor(GuiGetStyle(VALUEBOX, BORDER + (state * 3))), guiAlpha), baseColor);
    GuiDrawText(textValue, GetTextBounds(VALUEBOX, bounds), GUI_TEXT_ALIGN_CENTER, Fade(GetColor(GuiGetStyle(VALUEBOX, TEXT + (state * 3))), guiAlpha));

    // Draw cursor
    if (editMode)
    {
        // NOTE: ValueBox internal text is always centered
        Rectangle cursor = {bounds.x + GetTextWidth(textValue) / 2 + bounds.width / 2 + 2, bounds.y + 2 * GuiGetStyle(VALUEBOX, BORDER_WIDTH), 4, bounds.height - 4 * GuiGetStyle(VALUEBOX, BORDER_WIDTH)};
        GuiDrawRectangle(cursor, 0, BLANK, Fade(GetColor(GuiGetStyle(VALUEBOX, BORDER_COLOR_PRESSED)), guiAlpha));
    }

    // Draw text label if provided
    GuiDrawText(text, textBounds, (GuiGetStyle(VALUEBOX, TEXT_ALIGNMENT) == GUI_TEXT_ALIGN_RIGHT) ? GUI_TEXT_ALIGN_LEFT : GUI_TEXT_ALIGN_RIGHT, Fade(GetColor(GuiGetStyle(LABEL, TEXT + (state * 3))), guiAlpha));
    //--------------------------------------------------------------------

    return pressed;
}
bool GuiValueBox(Rectangle bounds, const char *text, float *value, float minValue, float maxValue, bool editMode) // gui value box that gets float
{
#if !defined(VALUEBOX_MAX_CHARS)
#define VALUEBOX_MAX_CHARS 32
#endif

    GuiControlState state = guiState;
    bool pressed = false;

    char textValue[VALUEBOX_MAX_CHARS + 1] = "\0";
    sprintf(textValue, "%f", *value);

    Rectangle textBounds = {0};
    if (text != NULL)
    {
        textBounds.width = (float)GetTextWidth(text);
        textBounds.height = (float)GuiGetStyle(DEFAULT, TEXT_SIZE);
        textBounds.x = bounds.x + bounds.width + GuiGetStyle(VALUEBOX, TEXT_PADDING);
        textBounds.y = bounds.y + bounds.height / 2 - GuiGetStyle(DEFAULT, TEXT_SIZE) / 2;
        if (GuiGetStyle(VALUEBOX, TEXT_ALIGNMENT) == GUI_TEXT_ALIGN_LEFT)
            textBounds.x = bounds.x - textBounds.width - GuiGetStyle(VALUEBOX, TEXT_PADDING);
    }

    // Update control
    //--------------------------------------------------------------------
    if ((state != GUI_STATE_DISABLED) && !guiLocked)
    {
        Vector2 mousePoint = GetMousePosition();

        bool valueHasChanged = false;

        if (editMode)
        {
            state = GUI_STATE_PRESSED;

            int keyCount = (int)strlen(textValue);

            // Only allow keys in range [48..57]
            if (keyCount < VALUEBOX_MAX_CHARS)
            {
                if (GetTextWidth(textValue) < bounds.width)
                {
                    int key = GetCharPressed();
                    if ((key >= 48) && (key <= 57))
                    {
                        textValue[keyCount] = (char)key;
                        keyCount++;
                        valueHasChanged = true;
                    }
                }
            }

            // Delete text
            if (keyCount > 0)
            {
                if (IsKeyPressed(KEY_BACKSPACE))
                {
                    keyCount--;
                    textValue[keyCount] = '\0';
                    if (keyCount < 0)
                        keyCount = 0;
                    valueHasChanged = true;
                }
            }

            if (valueHasChanged)
                *value = atoll(textValue);

            if (IsKeyPressed(KEY_ENTER) || (!CheckCollisionPointRec(mousePoint, bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)))
                pressed = true;
        }
        else
        {
            if (*value > maxValue)
                *value = maxValue;
            else if (*value < minValue)
                *value = minValue;

            if (CheckCollisionPointRec(mousePoint, bounds))
            {
                state = GUI_STATE_FOCUSED;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    pressed = true;
            }
        }
    }
    //--------------------------------------------------------------------

    // Draw control
    //--------------------------------------------------------------------
    Color baseColor = BLANK;
    if (state == GUI_STATE_PRESSED)
        baseColor = GetColor(GuiGetStyle(VALUEBOX, BASE_COLOR_PRESSED));
    else if (state == GUI_STATE_DISABLED)
        baseColor = GetColor(GuiGetStyle(VALUEBOX, BASE_COLOR_DISABLED));

    // WARNING: BLANK color does not work properly with Fade()
    GuiDrawRectangle(bounds, GuiGetStyle(VALUEBOX, BORDER_WIDTH), Fade(GetColor(GuiGetStyle(VALUEBOX, BORDER + (state * 3))), guiAlpha), baseColor);
    GuiDrawText(textValue, GetTextBounds(VALUEBOX, bounds), GUI_TEXT_ALIGN_CENTER, Fade(GetColor(GuiGetStyle(VALUEBOX, TEXT + (state * 3))), guiAlpha));

    // Draw cursor
    if (editMode)
    {
        // NOTE: ValueBox internal text is always centered
        Rectangle cursor = {bounds.x + GetTextWidth(textValue) / 2 + bounds.width / 2 + 2, bounds.y + 2 * GuiGetStyle(VALUEBOX, BORDER_WIDTH), 4, bounds.height - 4 * GuiGetStyle(VALUEBOX, BORDER_WIDTH)};
        GuiDrawRectangle(cursor, 0, BLANK, Fade(GetColor(GuiGetStyle(VALUEBOX, BORDER_COLOR_PRESSED)), guiAlpha));
    }

    // Draw text label if provided
    GuiDrawText(text, textBounds, (GuiGetStyle(VALUEBOX, TEXT_ALIGNMENT) == GUI_TEXT_ALIGN_RIGHT) ? GUI_TEXT_ALIGN_LEFT : GUI_TEXT_ALIGN_RIGHT, Fade(GetColor(GuiGetStyle(LABEL, TEXT + (state * 3))), guiAlpha));
    //--------------------------------------------------------------------

    return pressed;
}