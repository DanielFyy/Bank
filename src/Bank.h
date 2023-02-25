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
    
    void get_database(); //displays the number of accounts in database aswell as details about all existing accounts

    void create_new_account(); //adds a new account object into database

    void login(); //login into an existing account

    void account_balance(const std::shared_ptr<Account> account); //modifies the balance of an account

    void modify_account(const std::shared_ptr<Account> account); //menu for modifying existing account

    void change_surname(const std::shared_ptr<Account> account); //changes the surname of an account

    void change_name(const std::shared_ptr<Account> account); //changes the name of an account

    void change_type(const std::shared_ptr<Account> account); //changes the type of an account

    void delete_account(const std::shared_ptr<Account> account); //deletes acccount of matching adress

    const std::string generate_iban(); //generates a unique iban code

    void clear_screen(); //clears the console
private:
    std::vector <std::shared_ptr<Account>> database;
    std::vector <std::string> unique_iban;
    CSV csv;
};
/*
    To Do:
    - Unique Iban CSV file
    - Rewrite without unique pointers
    - Rewrite menu navigation to be cleaner
    - Implement all missing features

*/

#endif