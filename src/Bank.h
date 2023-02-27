#ifndef BANK_H
#define BANK_H

#pragma once
#include "CSV.h"

class Bank
{
public:
    Bank();
    ~Bank();

    void main_terminal(); //main screen of the application used to navigate the system
    void get_database(); //displays the number of accounts in database as well as details about all existing accounts
    void create_new_account(); //adds a new account object into database
    void login(); //find  existing account
    void account_balance(Account* const account); //modifies the balance of an account
    void modify_account(Account* const account); //menu for modifying existing account
    void change_surname(Account* const account); //changes the surname of an account
    void change_name(Account* const account); //changes the name of an account
    void change_type(Account* const account); //changes the type of an account
    void delete_account(Account* const account); //deletes acccount of matching adress
    const std::string generate_iban(); //generates a unique iban code
    void clear_screen(); //clears the console

private:
    std::vector <Account*> database;
    std::vector <std::string> unique_ibans;
    CSV csv;
};

#endif