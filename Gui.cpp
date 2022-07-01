#include <iostream>
#include <string.h>
#include <vector>
#include "include/raylib-cpp.hpp"
#define RAYGUI_IMPLEMENTATION
#define SUPPORT_FILEFORMAT_MP3
#include "../src/extras/raygui.h"
#include "Customer.h"
#include "Employee.h"
#include "Bank.h"
using namespace std;

int main()
{
    // screen window initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 150;                                    // screen size x
    int screenHeight = 130;                                   // screen size y
    raylib::Color TextColor = raylib::Color::LightGray();     // default text color
    raylib::Window window(screenWidth, screenHeight, "bank"); // window
    int screen = 1;                                           // level of menu
    //--------------------------------------------------------------------------------------
    // bank initialization
    //--------------------------------------------------------------------------------------
    Bank bank(1, "markazi");
    bank.load();//load from file
    //--------------------------------------------------------------------------------------
    // login checkbox booleans
    //--------------------------------------------------------------------------------------
    int last_checkbox = 1;
    bool customer = true, employee = false;
    //--------------------------------------------------------------------------------------
    // Other variables
    //--------------------------------------------------------------------------------------
    bool editmode_user = false;
    bool editmode_pass = false;
    bool editmode_deposit = false;
    int scroll = 0;
    string name;
    char *input_n = new char[100]; // char for getting the username from user
    strcpy(input_n, "");
    char *input_p = new char[100]; // char for getting the password from user
    strcpy(input_p, "");
    long long deposit = 0;
    int employee_selection = -1;
    int boss_selection = -1;
    int customer_selection = -1;
    string gui_error = "";
    bool show_acc = false;
    //-------------------------------------------------------------------------------------------------------------
    while (!window.ShouldClose()) // renders window until ECS key pressed or exit button clicked
    {
        //-------------------------------------------------------------------------------------------------------------
        // updating screen size
        //-------------------------------------------------------------------------------------------------------------
        if (screen == 2)
        {
            int formersizex = screenWidth;
            int formersizey = screenHeight;
            screenWidth = 200;  // screen size x
            screenHeight = 187; // screen size y
            int formerx = window.GetPosition().x;
            int formery = window.GetPosition().y;
            window.SetSize(screenWidth, screenHeight);
            window.SetPosition(formerx - (screenWidth - formersizex) / 2, formery - (screenHeight - formersizey) / 2);
        }
        if (employee && screen == 3)
        {
            int formersizex = screenWidth;
            int formersizey = screenHeight;
            int formerx = window.GetPosition().x;
            int formery = window.GetPosition().y;
            if (!bank.get_is_boss())
            {
                screenWidth = 230;  // screen size x
                screenHeight = 220; // screen size y
            }
            else
            {
                screenWidth = 230;  // screen size x
                screenHeight = 300; // screen size y
            }
            window.SetSize(screenWidth, screenHeight);
            window.SetPosition(formerx - (screenWidth - formersizex) / 2, formery - (screenHeight - formersizey) / 2);
        }
        if (customer && screen == 3)
        {
            int formersizex = screenWidth;
            int formersizey = screenHeight;
            screenWidth = 230;  // screen size x
            screenHeight = 136; // screen size y
            int formerx = window.GetPosition().x;
            int formery = window.GetPosition().y;
            window.SetSize(screenWidth, screenHeight);
            window.SetPosition(formerx - (screenWidth - formersizex) / 2, formery - (screenHeight - formersizey) / 2);
        }
        if (screen == 4)
        {
            int formersizex = screenWidth;
            int formersizey = screenHeight;
            if (boss_selection != 2 && employee_selection != 2 && boss_selection != 8 && (customer_selection == -1 || show_acc) && boss_selection != 4 && employee_selection != 4 && boss_selection != 7 && !(boss_selection == 1 || employee_selection == 1) && !(boss_selection == 0 || employee_selection == 0))
            {
                screenWidth = 440;  // screen size x
                screenHeight = 260; // screen size y
            }
            else
            {
                screenWidth = 230;  // screen size x
                screenHeight = 260; // screen size y
            }
            int formerx = window.GetPosition().x;
            int formery = window.GetPosition().y;
            window.SetSize(screenWidth, screenHeight);
            window.SetPosition(formerx - (screenWidth - formersizex) / 2, formery - (screenHeight - formersizey) / 2);
        }
        //-------------------------------------------------------------------------------------------------------------
        // rendering screen
        //-------------------------------------------------------------------------------------------------------------
        BeginDrawing();
        {
            window.ClearBackground(RAYWHITE); // background color
            //-------------------------------------------------------------------------------------------------------------
            // rendering login screen
            //-------------------------------------------------------------------------------------------------------------
            if (screen == 1)
            {
                GuiUnlock();
                if (GuiButton(Rectangle{float(screenWidth / 2) - 50, float(screenHeight / 2) - 25, 100, 50}, "login")) // login button
                {
                    screen++; // to next screen
                }
                GuiLock();
            }
            else if (screen == 2)
            {
                GuiUnlock();
                //-------------------------------------------------------------------------------------------------------------
                // username textbox
                //-------------------------------------------------------------------------------------------------------------
                raylib::Color TextColor = raylib::Color::Gray();
                TextColor.DrawText("Username", float(screenWidth / 2) - 75, float(screenHeight / 2) - 69.0f, 14);
                if (GuiTextBox(Rectangle{float(screenWidth / 2) - 75, float(screenHeight / 2) - 55.0f, 150, 25}, input_n, 256, editmode_user)) // the entry username for log in
                {
                    editmode_user = !editmode_user;
                }
                //-------------------------------------------------------------------------------------------------------------
                // password textbox
                //-------------------------------------------------------------------------------------------------------------
                TextColor.DrawText("Password", float(screenWidth / 2) - 75, float(screenHeight / 2) - 24.0f, 14);
                if (GuiTextBox(Rectangle{float(screenWidth / 2) - 75, float(screenHeight / 2) - 10.0f, 150, 25}, input_p, 256, editmode_pass)) // the entry password for log in
                {
                    editmode_pass = !editmode_pass;
                }
                //-------------------------------------------------------------------------------------------------------------
                // checkboxes
                //-------------------------------------------------------------------------------------------------------------
                customer = GuiCheckBox(Rectangle{float(screenWidth / 2) - 75, float(screenHeight / 2) + 50.0f, 18, 18}, "customer", customer);
                if (customer)
                {
                    if (last_checkbox != 1) // for only one checkbox to be true
                    {

                        employee = false;
                        last_checkbox = 1;
                    }
                }
                else if (!employee && last_checkbox == 1) // customer check box
                {
                    customer = true;
                }
                employee = GuiCheckBox(Rectangle{float(screenWidth / 2) + 8, float(screenHeight / 2) + 50.0f, 18, 18}, "employee", employee);
                if (employee)
                {
                    if (last_checkbox != 2) // for only one checkbox to be true
                    {
                        customer = false;
                        last_checkbox = 2;
                    }
                }
                else if (!customer && last_checkbox == 2) // employee check box
                {
                    employee = true;
                }
                //-------------------------------------------------------------------------------------------------------------
                // next button and login func
                //-------------------------------------------------------------------------------------------------------------
                if (GuiButton(Rectangle{float(screenWidth / 2) - 56.25f, float(screenHeight / 2) + 20.0f, 112.5, 25}, "next")) // next button
                {
                    bool login;
                    if (customer)
                    {
                        try
                        {
                            login = bank.login(input_n, input_p, true);
                            if (login)
                            {
                                screen++; // to next screen
                                gui_error = "";
                                bank.report("Customer", bank.customers[bank.get_index()].get_id(), "login", 999999999999); // for reporting
                            }
                        }
                        catch (const char *error) // for catching error
                        {
                            bank.log(error);
                            gui_error = error;
                        }
                    }
                    else
                    {
                        try
                        {
                            login = bank.login(input_n, input_p, false);
                            if (login)
                            {
                                screen++; // to next screen
                                gui_error = "";
                                bank.report("Employee", bank.employees[bank.get_index()].get_personnel_id(), "login", 999999999999); // for reporting
                            }
                        }
                        catch (const char *error)
                        {
                            bank.log(error);
                            gui_error = error;
                        }
                    }
                }
                GuiLock();
                //-------------------------------------------------------------------------------------------------------------
            }
            //-------------------------------------------------------------------------------------------------------------
            // normal employee button list
            //-------------------------------------------------------------------------------------------------------------
            else if (employee && screen == 3 && !bank.get_is_boss())
            {
                GuiUnlock();
                employee_selection = GuiToggleGroup(Rectangle{float(screenWidth / 2) - 100, float(screenHeight / 2) - 95, 200, 25}, "leave time request\nover time request\nshow personal information\nview customer information\nopen an account\ndelete an account\nback", employee_selection); // employee selection
                GuiLock();
                if (employee_selection != -1 && employee_selection != 6)
                {
                    screen++; // to next screen
                }
            }
            //-------------------------------------------------------------------------------------------------------------
            // boss button list
            //-------------------------------------------------------------------------------------------------------------
            else if (employee && screen == 3 && bank.get_is_boss())
            {
                GuiUnlock();
                boss_selection = GuiToggleGroup(Rectangle{float(screenWidth / 2) - 100, float(screenHeight / 2) - 135, 200, 25}, "leave time request\nover time request\nshow personal information\nview customer information\nopen an account\ndelete an account\nshow employee information\nadd employee\nfire an employee\nback", boss_selection); // boss selection
                GuiLock();
                if (boss_selection != -1 && boss_selection != 9)
                {
                    screen++; // to next screen
                }
            }
            //-------------------------------------------------------------------------------------------------------------
            // customer button list
            //-------------------------------------------------------------------------------------------------------------
            else if (customer && screen == 3)
            {
                GuiUnlock();
                customer_selection = GuiToggleGroup(Rectangle{float(screenWidth / 2) - 100, float(screenHeight / 2) - 53, 200, 25}, "increase account balance\nwithdraw from account\nview personal information\nback", customer_selection);
                if (customer_selection != -1 && customer_selection != 3)
                {
                    screen++; // to next screen
                }
                GuiLock();
            }
            //-------------------------------------------------------------------------------------------------------------
            // rendering fourth screen based on selection
            //-------------------------------------------------------------------------------------------------------------
            else if (screen == 4)
            {
                //-------------------------------------------------------------------------------------------------------------
                // employee and boss selection
                //-------------------------------------------------------------------------------------------------------------
                if (employee)
                {
                    //-------------------------------------------------------------------------------------------------------------
                    // leave time request
                    //-------------------------------------------------------------------------------------------------------------
                    if (boss_selection == 0 || employee_selection == 0)
                    {
                        GuiUnlock();
                        static bool editmode_hour = false;
                        static bool editmode_min = false;
                        static bool show = false;
                        static int hour = 0, minute = 0; // for input
                        static float value;              // requesed leave time
                        long long salary = bank.employees[bank.get_index()].get_income();
                        float remaining = (15 - value - bank.employees[bank.get_index()].get_last_leave_time()); // remaining hours for leave without reducing income
                        value = hour + float(minute / 60.0f);
                        int maxh, maxm; // maxh= maximum hour that employee can take & maxm= maximum minute that employee can take
                        maxh = int((bank.employees[bank.get_index()].get_income() / 100000));
                        maxh += 15 - bank.employees[bank.get_index()].get_last_leave_time();
                        if (maxh > hour)
                        {
                            maxm = 60;
                        }
                        else
                        {
                            maxm = 0;
                        }
                        //-------------------------------------------------------------------------------------------------------------
                        // rendering buttons and input boxes
                        //-------------------------------------------------------------------------------------------------------------
                        if (GuiSpinner(Rectangle{float(screenWidth / 2) + MeasureText("hour", 10) - 95, float(screenHeight / 2) + 7.5f, float(200 - MeasureText("hour", 10)), 25}, "hour", &hour, 0, maxh, editmode_hour))
                        {
                            editmode_hour = !editmode_hour;
                        }
                        if (GuiSpinner(Rectangle{float(screenWidth / 2) + MeasureText("minute", 10) - 95, float(screenHeight / 2) + 37.5f, float(200 - MeasureText("minute", 10)), 25}, "minute", &minute, 0, maxm, editmode_min))
                        {
                            editmode_min = !editmode_min;
                        }
                        if (GuiButton(Rectangle{float(screenWidth / 2) - 100, float(screenHeight / 2) + 90, 99, 25}, "confirm"))
                        {
                            bank.employees[bank.get_index()].req_leave_time(value);
                            hour = 0;
                            minute = 0;
                            bank.report("Employee", bank.employees[bank.get_index()].get_personnel_id(), "rest", value);
                        }
                        if (GuiButton(Rectangle{float(screenWidth / 2) + 1, float(screenHeight / 2) + 90, 99, 25}, "back"))
                        {
                            boss_selection = -1;
                            employee_selection = -1;
                            screen--; // to previous screen
                            show = false;
                            value = 0;
                        }
                        GuiDisable();
                        if (15 - bank.employees[bank.get_index()].get_last_leave_time() < value) // updating salary
                        {
                            salary -= 100000 * (value - 15 + bank.employees[bank.get_index()].get_last_leave_time());
                        }
                        if (remaining < 0) // remaining time for leave without  reducing income cant be less than 0
                        {
                            remaining = 0;
                        }
                        GuiValueBox(Rectangle{float(screenWidth / 2) - 95 + MeasureText("income", 10), float(screenHeight / 2) - 57.5f, float(200 - MeasureText("income", 10)), 25}, "income", &salary, 0, 9999999999999, false);
                        GuiValueBox(Rectangle{float(screenWidth / 2) - 95 + MeasureText("remaining hours", 10), float(screenHeight / 2) - 22.5f, float(200 - MeasureText("remaining hours", 10)), 25}, "remaining hours", &remaining, 0, 9999999999999, false);
                        GuiEnable();
                        GuiLock();
                        //-------------------------------------------------------------------------------------------------------------
                    }
                    //-------------------------------------------------------------------------------------------------------------
                    // overtime request
                    //-------------------------------------------------------------------------------------------------------------
                    else if (boss_selection == 1 || employee_selection == 1)
                    {
                        GuiUnlock();
                        static bool editmode_hour = false;
                        static bool editmode_min = false;
                        static bool show = false;
                        static int hour = 0, minute = 0;
                        static float value; // requested time
                        long long salary = bank.employees[bank.get_index()].get_income();
                        float remaining = (12 - value - bank.employees[bank.get_index()].get_over_time());
                        value = hour + float(minute / 60.0f);
                        int maxh, maxm; // maxh= maximum hour that employee can take & maxm= maximum minute that employee can take
                        maxh = 12 - bank.employees[bank.get_index()].get_over_time();
                        if (maxh > hour)
                        {
                            maxm = 60;
                        }
                        else
                        {
                            maxm = 0;
                        }
                        //-------------------------------------------------------------------------------------------------------------
                        // rendering buttons and input boxes
                        //-------------------------------------------------------------------------------------------------------------
                        if (GuiSpinner(Rectangle{float(screenWidth / 2) + MeasureText("hour", 10) - 95, float(screenHeight / 2) + 7.5f, float(200 - MeasureText("hour", 10)), 25}, "hour", &hour, 0, maxh, editmode_hour))
                        {
                            editmode_hour = !editmode_hour;
                        }
                        if (GuiSpinner(Rectangle{float(screenWidth / 2) + MeasureText("minute", 10) - 95, float(screenHeight / 2) + 37.5f, float(200 - MeasureText("minute", 10)), 25}, "minute", &minute, 0, maxm, editmode_min))
                        {
                            editmode_min = !editmode_min;
                        }

                        if (GuiButton(Rectangle{float(screenWidth / 2) - 100, float(screenHeight / 2) + 90, 99, 25}, "confirm"))
                        {
                            bank.employees[bank.get_index()].req_over_time(value);
                            hour = 0;
                            minute = 0;
                            bank.report("Employee", bank.employees[bank.get_index()].get_personnel_id(), "overtime", value);
                        }
                        if (GuiButton(Rectangle{float(screenWidth / 2) + 1, float(screenHeight / 2) + 90, 99, 25}, "back"))
                        {
                            boss_selection = -1;
                            employee_selection = -1;
                            screen--; // to previus screen
                            show = false;
                            value = 0;
                        }
                        GuiDisable();

                        salary += value * 120000; // updating salary
                        if (remaining < 0)        // remaining time cant be less than 0
                        {
                            remaining = 0;
                        }
                        GuiValueBox(Rectangle{float(screenWidth / 2) - 95 + MeasureText("income", 10), float(screenHeight / 2) - 57.5f, float(200 - MeasureText("income", 10)), 25}, "income", &salary, 0, 9999999999999, false);
                        GuiValueBox(Rectangle{float(screenWidth / 2) - 95 + MeasureText("remaining hours", 10), float(screenHeight / 2) - 22.5f, float(200 - MeasureText("remaining hours", 10)), 25}, "remaining hours", &remaining, 0, 9999999999999, false);
                        GuiEnable();
                        GuiLock();
                        //-------------------------------------------------------------------------------------------------------------
                    }
                    //-------------------------------------------------------------------------------------------------------------
                    // show personal information
                    //-------------------------------------------------------------------------------------------------------------
                    else if (boss_selection == 2 || employee_selection == 2)
                    {
                        GuiUnlock();
                        static int active = -1;
                        static int scroll = 0;
                        if (GuiButton(Rectangle{float(screenWidth / 2) - 25, float(screenHeight / 2) + 90, 50, 25}, "back"))
                        {
                            boss_selection = -1;
                            employee_selection = -1;
                            screen--;
                            active = -1;
                            scroll = 0;
                        }
                        active = GuiListView(Rectangle{float(screenWidth / 2) - 100, float(screenHeight / 2) - 115, 200, 200}, bank.employees[bank.get_index()].data_full().c_str(), &scroll, active);
                        GuiLock();
                    }
                    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                    // view customer information
                    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                    else if (boss_selection == 3 || employee_selection == 3)
                    {
                        GuiUnlock();
                        gui_error = "";
                        static int active = -1;
                        static int scroll = 0;
                        static int active_acc = -1;
                        static int scroll_acc = 0;

                        if (GuiButton(Rectangle{float(screenWidth / 2) - 25, float(screenHeight / 2) + 90, 50, 25}, "back"))
                        {
                            boss_selection = -1;
                            employee_selection = -1;
                            screen--;
                            active = -1;
                            scroll = 0;
                            active_acc = -1;
                            scroll_acc = 0;
                        }
                        active = GuiListView(Rectangle{float(screenWidth / 2) - 205, float(screenHeight / 2) - 115, 200, 200}, bank.customer_names().c_str(), &scroll, active);
                        if (active == -1)
                        {
                            active_acc = GuiListView(Rectangle{float(screenWidth / 2) + 5, float(screenHeight / 2) - 115, 200, 200}, "", &scroll_acc, active_acc);
                        }
                        else
                        {
                            active_acc = GuiListView(Rectangle{float(screenWidth / 2) + 5, float(screenHeight / 2) - 115, 200, 200}, bank.customers[active].data_full().c_str(), &scroll_acc, active_acc);
                        }
                        GuiLock();
                    }
                    //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                    // open an account
                    //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                    else if (boss_selection == 4 || employee_selection == 4)
                    {
                        GuiUnlock();
                        static bool editmode_id = false;
                        static bool show = false;
                        static long long int value = 0; // input for id
                        //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                        // rendering back & confirm button & id inputbox
                        //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                        if (GuiValueBox(Rectangle{float(screenWidth / 2) - 95 + MeasureText("id", 10), float(screenHeight / 2) + 90, float(104 - MeasureText("id", 10)), 25}, "id", &value, 0, 9999999999999, editmode_id))
                        {
                            editmode_id = !editmode_id;
                        }
                        if (GuiButton(Rectangle{float(screenWidth / 2) + 11, float(screenHeight / 2) + 90, 44, 25}, "confirm"))
                        {
                            show = true;
                        }
                        if (GuiButton(Rectangle{float(screenWidth / 2) + 57, float(screenHeight / 2) + 90, 44, 25}, "back"))
                        {
                            boss_selection = -1;
                            employee_selection = -1;
                            screen--; // to previous screen
                            editmode_id = false;
                            show = false;
                            value = 0;
                        }
                        //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                        // rendering buttons and text boxes based on id
                        //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                        if (show)
                        {
                            Customer temp(value);
                            if (bank.index_customer(temp) > -1) // checks if id exist
                            {
                                //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                // rendering existing customer data
                                //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                string s = bank.customers[bank.index_customer(temp)].data();
                                temp.read(s);
                                char *str = new char[256];
                                char *str1 = new char[256];
                                char *str2 = new char[256];
                                char *str3 = new char[256];
                                strcpy(str, temp.get_name().c_str());
                                strcpy(str1, temp.get_lastname().c_str());
                                strcpy(str2, temp.get_username().c_str());
                                strcpy(str3, temp.get_password().c_str());
                                static char *name = str;
                                static char *lastname = str1;
                                static char *username = str2;
                                static char *password = str3;
                                static Date birth;
                                static bool editmode_name = false;
                                static bool editmode_lastname = false;
                                static bool editmode_username = false;
                                static bool editmode_password = false;
                                static bool editmode_day = false;
                                static bool editmode_month = false;
                                static bool editmode_year = false;
                                static bool customer_confirmed = false;
                                birth.current_date();
                                static int y = birth.get_year();
                                static int m = birth.get_month();
                                static int d = birth.get_day();
                                GuiDisable();
                                if (GuiTextBox(Rectangle{float(screenWidth / 2) - 100, float(screenHeight / 2) - 115, 99, 25}, name, 256, editmode_name))
                                {
                                    editmode_name = !editmode_name;
                                }
                                if (GuiTextBox(Rectangle{float(screenWidth / 2) + 1, float(screenHeight / 2) - 115, 99, 25}, lastname, 256, editmode_lastname))
                                {
                                    editmode_lastname = !editmode_lastname;
                                }
                                if (GuiTextBox(Rectangle{float(screenWidth / 2) - 100, float(screenHeight / 2) - 70, 99, 25}, username, 256, editmode_username))
                                {
                                    editmode_username = !editmode_username;
                                }
                                if (GuiTextBox(Rectangle{float(screenWidth / 2) + 1, float(screenHeight / 2) - 70, 99, 25}, password, 256, editmode_password))
                                {
                                    editmode_password = !editmode_password;
                                }
                                if (GuiSpinner(Rectangle{float(screenWidth / 2) - 23, float(screenHeight / 2) - 25, 75, 15}, "birthday", &d, 1, 31, editmode_day))
                                {
                                    editmode_day = !editmode_day;
                                }
                                if (GuiSpinner(Rectangle{float(screenWidth / 2) - 23, float(screenHeight / 2) - 5, 75, 15}, "birthmonth", &m, 1, 12, editmode_month))
                                {
                                    editmode_month = !editmode_month;
                                }
                                if (GuiSpinner(Rectangle{float(screenWidth / 2) - 23, float(screenHeight / 2) + 15, 75, 15}, "birthyear", &y, 1, 99999, editmode_year))
                                {
                                    editmode_year = !editmode_year;
                                }
                                if (GuiButton(Rectangle{float(screenWidth / 2) + 57, float(screenHeight / 2) - 10, 25, 25}, "#1#"))
                                {
                                    customer_confirmed = true;
                                }
                                GuiEnable();
                                //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                // getting account data
                                //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                Account acc;
                                Date opening;
                                static long long balance = 50000;
                                static bool editmode_balance = false;
                                static bool account_confirmed = false;
                                opening.current_date();
                                acc.set_opening_date(opening);
                                acc.set_id_owner(temp.get_id());
                                acc.set_account_number(bank.number_of_accounts() + 1);
                                if (GuiValueBox(Rectangle{float(screenWidth / 2) - 95 + MeasureText("balance", 10), float(screenHeight / 2) + 50, float(200 - (35 + MeasureText("balance", 10))), 25}, "balance", &balance, 50000, 9999999999999, editmode_balance))
                                {
                                    editmode_balance = !editmode_balance;
                                }
                                if (GuiButton(Rectangle{float(screenWidth / 2) + 75, float(screenHeight / 2) + 50, 25, 25}, "#1#"))
                                {
                                    account_confirmed = true;
                                }
                                if (account_confirmed)
                                {
                                    acc.set_balance(balance);
                                    acc.set_active(true);
                                    bank.customers[bank.index_customer(temp)].push_back(acc);
                                    bank.report("Account", acc.get_account_number(), "open", 99999999999);
                                    screen--;
                                    if (bank.get_is_boss())
                                    {
                                        boss_selection = -1;
                                    }
                                    else
                                    {
                                        employee_selection = -1;
                                    }
                                }
                                //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                            }
                            else
                            {
                                //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                // getting customer data
                                //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                char *str = new char[256];
                                char *str1 = new char[256];
                                char *str2 = new char[256];
                                char *str3 = new char[256];
                                strcpy(str, "customer name");
                                strcpy(str1, "lastname");
                                strcpy(str2, "username");
                                strcpy(str3, "password");
                                static char *name = str;
                                static char *lastname = str1;
                                static char *username = str2;
                                static char *password = str3;
                                static Date birth;
                                static bool editmode_name = false;
                                static bool editmode_lastname = false;
                                static bool editmode_username = false;
                                static bool editmode_password = false;
                                static bool editmode_day = false;
                                static bool editmode_month = false;
                                static bool editmode_year = false;
                                static bool customer_confirmed = false;
                                birth.current_date();
                                static int y = birth.get_year();
                                static int m = birth.get_month();
                                static int d = birth.get_day();
                                if (customer_confirmed)
                                {
                                    GuiDisable();
                                }
                                if (GuiTextBox(Rectangle{float(screenWidth / 2) - 100, float(screenHeight / 2) - 115, 99, 25}, name, 256, editmode_name))
                                {
                                    editmode_name = !editmode_name;
                                }
                                if (GuiTextBox(Rectangle{float(screenWidth / 2) + 1, float(screenHeight / 2) - 115, 99, 25}, lastname, 256, editmode_lastname))
                                {
                                    editmode_lastname = !editmode_lastname;
                                }
                                if (GuiTextBox(Rectangle{float(screenWidth / 2) - 100, float(screenHeight / 2) - 70, 99, 25}, username, 256, editmode_username))
                                {
                                    editmode_username = !editmode_username;
                                }
                                if (GuiTextBox(Rectangle{float(screenWidth / 2) + 1, float(screenHeight / 2) - 70, 99, 25}, password, 256, editmode_password))
                                {
                                    editmode_password = !editmode_password;
                                }
                                if (GuiSpinner(Rectangle{float(screenWidth / 2) - 23, float(screenHeight / 2) - 25, 75, 15}, "birthday", &d, 1, 31, editmode_day))
                                {
                                    editmode_day = !editmode_day;
                                }
                                if (GuiSpinner(Rectangle{float(screenWidth / 2) - 23, float(screenHeight / 2) - 5, 75, 15}, "birthmonth", &m, 1, 12, editmode_month))
                                {
                                    editmode_month = !editmode_month;
                                }
                                if (GuiSpinner(Rectangle{float(screenWidth / 2) - 23, float(screenHeight / 2) + 15, 75, 15}, "birthyear", &y, 1, 99999, editmode_year))
                                {
                                    editmode_year = !editmode_year;
                                }
                                if (GuiButton(Rectangle{float(screenWidth / 2) + 57, float(screenHeight / 2) - 10, 25, 25}, "#1#"))
                                {
                                    customer_confirmed = true;
                                }
                                if (customer_confirmed)
                                {
                                    GuiEnable();
                                }
                                //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                if (customer_confirmed)
                                {
                                    if (!bank.username_is_unique(username)) // checks if entered username is unique
                                    {
                                        gui_error = "-duplicate username";
                                        customer_confirmed = false;
                                    }
                                    else
                                    {
                                        //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                        // getting account data
                                        //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                        gui_error = "";
                                        temp.set_name(name);
                                        temp.set_lastname(lastname);
                                        temp.set_username(username);
                                        temp.set_password(password);
                                        temp.set_birthday(birth);
                                        Account acc;
                                        Date opening;
                                        static long long balance = 50000;
                                        static bool editmode_balance = false;
                                        static bool account_confirmed = false;
                                        opening.current_date();
                                        acc.set_opening_date(opening);
                                        acc.set_id_owner(temp.get_id());
                                        acc.set_account_number(bank.number_of_accounts() + 1);
                                        if (GuiValueBox(Rectangle{float(screenWidth / 2) - 95 + MeasureText("balance", 10), float(screenHeight / 2) + 50, float(200 - (35 + MeasureText("balance", 10))), 25}, "balance", &balance, 50000, 9999999999999, editmode_balance))
                                        {
                                            editmode_balance = !editmode_balance;
                                        }
                                        if (GuiButton(Rectangle{float(screenWidth / 2) + 75, float(screenHeight / 2) + 50, 25, 25}, "#1#"))
                                        {
                                            account_confirmed = true;
                                        }
                                        if (account_confirmed)
                                        {
                                            acc.set_balance(balance);
                                            acc.set_active(true);
                                            temp.push_back(acc);
                                            bank.add_customer(temp);
                                            bank.report("Customer", acc.get_id_owner(), "add", 99999999999);
                                            bank.report("Account", acc.get_account_number(), "open", 99999999999);
                                            screen--;
                                            if (bank.get_is_boss())
                                            {
                                                boss_selection = -1;
                                            }
                                            else
                                            {
                                                employee_selection = -1;
                                            }
                                        }
                                        //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                    }
                                }
                            }
                        }

                        GuiLock();
                    }
                    //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                    // deleting account
                    //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                    else if (boss_selection == 5 || employee_selection == 5)
                    {
                        //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                        // rendering buttons , customers and accounts lists
                        //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                        GuiUnlock();
                        gui_error = "";
                        static int active = -1;
                        static int scroll = 0;
                        static int active_acc = -1;
                        static int scroll_acc = 0;
                        static bool keep_money = false;
                        if (GuiButton(Rectangle{float(screenWidth / 2) - 100, float(screenHeight / 2) + 90, 50, 25}, "back"))
                        {
                            boss_selection = -1;
                            employee_selection = -1;
                            screen--;
                            active = -1;
                            scroll = 0;
                            active_acc = -1;
                            scroll_acc = 0;
                            keep_money = false;
                        }
                        active = GuiListView(Rectangle{float(screenWidth / 2) - 205, float(screenHeight / 2) - 115, 200, 200}, bank.customer_names().c_str(), &scroll, active);
                        if (active == -1)
                        {
                            active_acc = GuiListView(Rectangle{float(screenWidth / 2) + 5, float(screenHeight / 2) - 115, 200, 200}, "", &scroll_acc, active_acc);
                        }
                        else
                        {
                            active_acc = GuiListView(Rectangle{float(screenWidth / 2) + 5, float(screenHeight / 2) - 115, 200, 200}, bank.customers[active].showaccountsbalance().c_str(), &scroll_acc, active_acc);
                        }
                        keep_money = GuiCheckBox(Rectangle{float(screenWidth / 2) + 4, float(screenHeight / 2) + 93.5f, 18, 18}, "keep money", keep_money);
                        if (GuiButton(Rectangle{float(screenWidth / 2) - 48, float(screenHeight / 2) + 90, 50, 25}, "Delete"))
                        {
                            //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                            // deleting account and customer if there is no remaining account
                            //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                            if (active != -1 && active_acc != -1)
                            {
                                long long temp = bank.customers[active][active_acc].get_balance();
                                bank.customers[active].erase(bank.customers[active][active_acc]);
                                bank.report("Account", bank.customers[active][active_acc].get_account_number(), "delete", 9999999999);
                                if (keep_money && bank.customers[active].size() > 0)
                                {
                                    bank.customers[active][0].deposit(temp);
                                    bank.report("Account", bank.customers[active][0].get_account_number(), "deposit", temp);
                                }
                                if (bank.customers[active].size() == 0)
                                {
                                    bank.delete_customer(active);
                                    bank.report("Customer", bank.customers[active][0].get_id_owner(), "delete", 9999999999);
                                }
                            }
                            //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                        }
                        GuiLock();
                        //------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                    }
                    //--------------------------------------------------------------------------------------------------------------------------------
                    // show employee information
                    //--------------------------------------------------------------------------------------------------------------------------------
                    else if (boss_selection == 6 && bank.get_is_boss())
                    {
                        //--------------------------------------------------------------------------------------------------------------------------------
                        // rendering employee list and data
                        //--------------------------------------------------------------------------------------------------------------------------------
                        GuiUnlock();
                        gui_error = "";
                        static int active = -1;
                        static int scroll = 0;
                        static int active_acc = -1;
                        static int scroll_acc = 0;
                        static bool keep_money = false;
                        if (GuiButton(Rectangle{float(screenWidth / 2) - 25, float(screenHeight / 2) + 90, 50, 25}, "back"))
                        {
                            boss_selection = -1;
                            employee_selection = -1;
                            screen--;
                            active = -1;
                            scroll = 0;
                            active_acc = -1;
                            scroll_acc = 0;
                            keep_money = false;
                        }
                        active = GuiListView(Rectangle{float(screenWidth / 2) - 205, float(screenHeight / 2) - 115, 200, 200}, bank.employee_names().c_str(), &scroll, active);
                        if (active == -1)
                        {
                            active_acc = GuiListView(Rectangle{float(screenWidth / 2) + 5, float(screenHeight / 2) - 115, 200, 200}, "", &scroll_acc, active_acc);
                        }
                        else
                        {
                            active_acc = GuiListView(Rectangle{float(screenWidth / 2) + 5, float(screenHeight / 2) - 115, 200, 200}, bank.employees[active + 1].data_full().c_str(), &scroll_acc, active_acc);
                        }
                        GuiLock();
                        //--------------------------------------------------------------------------------------------------------------------------------
                    }
                    //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                    // add employee
                    //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                    else if (boss_selection == 7 && bank.get_is_boss())
                    {
                        //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                        // rendering back & confirm buttn & id input box
                        //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                        GuiUnlock();
                        static bool editmode_id = false;
                        static bool show = false;
                        static long long int value = 0;
                        if (GuiValueBox(Rectangle{float(screenWidth / 2) - 95 + MeasureText("personnel id", 10), float(screenHeight / 2) + 90, float(104 - MeasureText("personnel id", 10)), 25}, "personnel id", &value, 100, 999, editmode_id))
                        {
                            editmode_id = !editmode_id;
                        }
                        if (GuiButton(Rectangle{float(screenWidth / 2) + 11, float(screenHeight / 2) + 90, 44, 25}, "confirm"))
                        {
                            show = true;
                        }
                        if (GuiButton(Rectangle{float(screenWidth / 2) + 57, float(screenHeight / 2) + 90, 44, 25}, "back"))
                        {
                            boss_selection = -1;
                            employee_selection = -1;
                            screen--;
                            editmode_id = false;
                            show = false;
                            value = 0;
                        }
                        if (show)
                        {
                            Employee temp(value);
                            if (bank.index_employee(temp) > -1)
                            {
                                gui_error = "-duplicate personnel id";
                                show = false;
                            }
                            else
                            {
                                //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                // rendering input boxes for getting employee data
                                //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                gui_error = "";
                                char *str = new char[256];
                                char *str1 = new char[256];
                                char *str2 = new char[256];
                                char *str3 = new char[256];
                                strcpy(str, "employee name");
                                strcpy(str1, "lastname");
                                strcpy(str2, "username");
                                strcpy(str3, "password");
                                static char *name = str;
                                static char *lastname = str1;
                                static char *username = str2;
                                static char *password = str3;
                                static Date birth;
                                static long long income = 5600000;
                                static bool editmode_name = false;
                                static bool editmode_lastname = false;
                                static bool editmode_username = false;
                                static bool editmode_password = false;
                                static bool editmode_day = false;
                                static bool editmode_month = false;
                                static bool editmode_year = false;
                                static bool editmode_income = false;
                                static bool employee_confirmed = false;
                                birth.current_date();
                                static int y = birth.get_year();
                                static int m = birth.get_month();
                                static int d = birth.get_day();
                                if (employee_confirmed)
                                {
                                    GuiDisable();
                                }
                                if (GuiTextBox(Rectangle{float(screenWidth / 2) - 100, float(screenHeight / 2) - 115, 99, 25}, name, 256, editmode_name))
                                {
                                    editmode_name = !editmode_name;
                                }
                                if (GuiTextBox(Rectangle{float(screenWidth / 2) + 1, float(screenHeight / 2) - 115, 99, 25}, lastname, 256, editmode_lastname))
                                {
                                    editmode_lastname = !editmode_lastname;
                                }
                                if (GuiTextBox(Rectangle{float(screenWidth / 2) - 100, float(screenHeight / 2) - 70, 99, 25}, username, 256, editmode_username))
                                {
                                    editmode_username = !editmode_username;
                                }
                                if (GuiTextBox(Rectangle{float(screenWidth / 2) + 1, float(screenHeight / 2) - 70, 99, 25}, password, 256, editmode_password))
                                {
                                    editmode_password = !editmode_password;
                                }
                                if (GuiSpinner(Rectangle{float(screenWidth / 2) - 23, float(screenHeight / 2) - 25, 75, 15}, "birthday", &d, 1, 31, editmode_day))
                                {
                                    editmode_day = !editmode_day;
                                }
                                if (GuiSpinner(Rectangle{float(screenWidth / 2) - 23, float(screenHeight / 2) - 5, 75, 15}, "birthmonth", &m, 1, 12, editmode_month))
                                {
                                    editmode_month = !editmode_month;
                                }
                                if (GuiSpinner(Rectangle{float(screenWidth / 2) - 23, float(screenHeight / 2) + 15, 75, 15}, "birthyear", &y, 1, 99999, editmode_year))
                                {
                                    editmode_year = !editmode_year;
                                }
                                if (GuiValueBox(Rectangle{float(screenWidth / 2) - 95 + MeasureText("income", 10), float(screenHeight / 2) + 50, float(200 - (35 + MeasureText("income", 10))), 25}, "income", &income, 50000, 9999999999999, editmode_income))
                                {
                                    editmode_income = !editmode_income;
                                }
                                if (GuiButton(Rectangle{float(screenWidth / 2) + 75, float(screenHeight / 2) + 50, 25, 25}, "#1#"))
                                {
                                    employee_confirmed = true;
                                }
                                if (employee_confirmed)
                                {
                                    GuiEnable();
                                }
                                if (employee_confirmed)
                                {
                                    if (!bank.username_is_unique(username)) // checks if username is unique
                                    {
                                        gui_error = "-duplicate username";
                                        employee_confirmed = false;
                                    }
                                    else
                                    {
                                        gui_error = "";
                                        temp.set_name(name);
                                        temp.set_lastname(lastname);
                                        temp.set_username(username);
                                        temp.set_password(password);
                                        temp.set_birthday(birth);
                                        temp.set_personnel_id(value);
                                        temp.set_income(income);
                                        bank.employees.push_back(temp);
                                        bank.report("Employee", value, "add", 9999999999999);
                                        boss_selection = -1;
                                        screen--;
                                    }
                                }
                                //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                            }
                        }
                        GuiLock();
                        //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                    }
                    //------------------------------------------------------------------------------------------------------------------------------
                    // fire an employee
                    //------------------------------------------------------------------------------------------------------------------------------
                    else if (boss_selection == 8 && bank.get_is_boss())
                    {
                        //------------------------------------------------------------------------------------------------------------------------------
                        // rendering buttons and employee list
                        //------------------------------------------------------------------------------------------------------------------------------
                        GuiUnlock();
                        if (GuiButton(Rectangle{float(screenWidth / 2) + 2.5f, float(screenHeight / 2) + 90, 50, 25}, "back"))
                        {
                            boss_selection = -1;
                            employee_selection = -1;
                            screen--;
                        }
                        static int active = -1;
                        static int scroll = 0;
                        active = GuiListView(Rectangle{float(screenWidth / 2) - 100, float(screenHeight / 2) - 115, 200, 200}, bank.employee_names().c_str(), &scroll, active);
                        if (GuiButton(Rectangle{float(screenWidth / 2) - 52.5f, float(screenHeight / 2) + 90, 50, 25}, "Fire!"))
                        {
                            bank.report("Employee", bank.employees[active].get_personnel_id(), "fire", 9999999999999);
                            bank.fire_employee(active);
                        }
                        GuiLock();
                        //------------------------------------------------------------------------------------------------------------------------------
                    }
                    //------------------------------------------------------------------------------------------------------------------------------
                }
                //-------------------------------------------------------------------------------------------------------------
                // customer selection
                //-------------------------------------------------------------------------------------------------------------
                else
                {
                    //---------------------------------------------------------------------------------------------------------------------------------------
                    // increase account balance
                    //---------------------------------------------------------------------------------------------------------------------------------------
                    if (customer_selection == 0)
                    {
                        //---------------------------------------------------------------------------------------------------------------------------------------
                        // render buttons and accounts list
                        //---------------------------------------------------------------------------------------------------------------------------------------
                        GuiUnlock();
                        static int scroll_acc = 0;
                        static int active_acc = -1;
                        static bool confirmed = false;
                        if (GuiValueBox(Rectangle{float(screenWidth / 2) - 100, float(screenHeight / 2) + 90, 99, 25}, NULL, &deposit, 0, 9999999999999, editmode_deposit)) // the entry password for log in
                        {
                            editmode_deposit = !editmode_deposit;
                        }
                        if (GuiButton(Rectangle{float(screenWidth / 2) + 1, float(screenHeight / 2) + 90, 49, 25}, "confirm"))
                        {
                            confirmed = true;
                        }
                        if (GuiButton(Rectangle{float(screenWidth / 2) + 51, float(screenHeight / 2) + 90, 49, 25}, "back"))
                        {
                            customer_selection = -1;
                            screen--;
                            scroll_acc = 0;
                            active_acc = -1;
                            confirmed = false;
                            deposit = 0;
                        }
                        active_acc = GuiListView(Rectangle{float(screenWidth / 2) - 100, float(screenHeight / 2) - 115, 200, 200}, bank.customers[bank.get_index()].showaccountsbalance().c_str(), &scroll_acc, active_acc);
                        if (confirmed && active_acc != -1)//depositing to account
                        {
                            bank.customers[bank.get_index()][active_acc].deposit(deposit);
                            bank.report("Account", bank.customers[bank.get_index()][active_acc].get_account_number(), "deposit", deposit);
                            confirmed = false;
                        }
                        GuiLock();
                        //------------------------------------------------------------------------------------------------------------------------------
                    }
                    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                    //withdraw from account
                    //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                    else if (customer_selection == 1)
                    {
                        //---------------------------------------------------------------------------------------------------------------------------------------
                        // render buttons and accounts list
                        //---------------------------------------------------------------------------------------------------------------------------------------
                        GuiUnlock();
                        static int scroll_acc = 0;
                        static int active_acc = -1;
                        static bool confirmed = false;
                        static long long withdraw = 0;
                        static bool editmode_withdraw = false;
                        if (GuiValueBox(Rectangle{float(screenWidth / 2) - 100, float(screenHeight / 2) + 90, 99, 25}, NULL, &withdraw, 0, 9999999999999, editmode_withdraw)) // the entry password for log in
                        {
                            editmode_withdraw = !editmode_withdraw;
                        }
                        if (GuiButton(Rectangle{float(screenWidth / 2) + 1, float(screenHeight / 2) + 90, 49, 25}, "confirm"))
                        {
                            confirmed = true;
                        }
                        if (GuiButton(Rectangle{float(screenWidth / 2) + 51, float(screenHeight / 2) + 90, 49, 25}, "back"))
                        {
                            customer_selection = -1;
                            screen--;
                            withdraw = 0;
                            editmode_withdraw = false;
                            active_acc = -1;
                            scroll_acc = 0;
                            gui_error = "";
                        }
                        active_acc = GuiListView(Rectangle{float(screenWidth / 2) - 100, float(screenHeight / 2) - 115, 200, 200}, bank.customers[bank.get_index()].showaccountsbalance().c_str(), &scroll_acc, active_acc);
                        if (confirmed && active_acc != -1)
                        {
                            try
                            {
                                if (bank.customers[bank.get_index()][active_acc].withdraw(withdraw))
                                {
                                    gui_error = "";
                                    bank.report("Account", bank.customers[bank.get_index()][active_acc].get_account_number(), "withdraw", withdraw);
                                }
                            }
                            catch (const char *error)
                            {
                                bank.log(error);
                                gui_error = error;
                            }
                            confirmed = false;
                        }
                        GuiLock();
                        //---------------------------------------------------------------------------------------------------------------------------------------
                    }
                    //-------------------------------------------------------------------------------------------------------------------------------------------------
                    //view personal information
                    //-------------------------------------------------------------------------------------------------------------------------------------------------
                    else if (customer_selection == 2)
                    {
                        //---------------------------------------------------------------------------------------------------------------------------------------
                        // render buttons and data
                        //---------------------------------------------------------------------------------------------------------------------------------------
                        GuiUnlock();
                        gui_error = "";
                        static int active = -1;
                        static int scroll = 0;
                        static int active_acc = -1;
                        static int scroll_acc = 0;
                        static bool info_selected = true;
                        static bool acc_selected = false;

                        if (GuiButton(Rectangle{float(screenWidth / 2) - 51, float(screenHeight / 2) + 90, 50, 25}, "back"))
                        {
                            customer_selection = -1;
                            screen--;
                            show_acc = false;
                        }
                        show_acc = GuiCheckBox(Rectangle{float(screenWidth / 2) + 1, float(screenHeight / 2) + 93.5f, 18, 18}, "show accounts", show_acc);
                        if (!show_acc)
                        {

                            active = GuiListView(Rectangle{float(screenWidth / 2) - 100, float(screenHeight / 2) - 115, 200, 200}, bank.customers[bank.get_index()].data_full().c_str(), &scroll, active);
                        }
                        else
                        {
                            active = GuiListView(Rectangle{float(screenWidth / 2) - 205, float(screenHeight / 2) - 115, 200, 200}, bank.customers[bank.get_index()].data_full().c_str(), &scroll, active);
                            if (active != -1)
                            {
                                info_selected = true;
                                if (info_selected && acc_selected)
                                {
                                    acc_selected = false;
                                    active_acc = -1;
                                }
                            }
                            else
                            {
                                info_selected = false;
                            }
                            active_acc = GuiListView(Rectangle{float(screenWidth / 2) + 5, float(screenHeight / 2) - 115, 200, 200}, bank.customers[bank.get_index()].showaccountsbalance().c_str(), &scroll_acc, active_acc);
                            if (active_acc != -1)
                            {
                                acc_selected = true;
                                if (info_selected && acc_selected)
                                {
                                    info_selected = false;
                                    active = -1;
                                }
                            }
                            else
                            {
                                acc_selected = false;
                            }
                        }
                        //---------------------------------------------------------------------------------------------------------------------------------------
                    }
                    //---------------------------------------------------------------------------------------------------------------------------------------
                }
            }
            //---------------------------------------------------------------------------------------------------------------------------------------
            // checks if back button of button list clicked
            //---------------------------------------------------------------------------------------------------------------------------------------
            if ((customer && customer_selection == 3) || (employee && employee_selection == 6) || (employee && bank.get_is_boss() && boss_selection == 9))
            {
                screen--;
                customer_selection = -1;
                employee_selection = -1;
                boss_selection = -1;
                gui_error = "";
            }
            //---------------------------------------------------------------------------------------------------------------------------------------
            // rendering error
            //---------------------------------------------------------------------------------------------------------------------------------------
            DrawError(gui_error);
            //---------------------------------------------------------------------------------------------------------------------------------------
        }
        EndDrawing();
        //-------------------------------------------------------------------------------------------------------------
    }
    bank.save();//saving to file
}
