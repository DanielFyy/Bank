#ifndef BANK_H
#define BANK_H

#pragma once
#include "Account.h"

class Bank
{
public:
    Bank();
    ~Bank();
    void main_terminal();

    //adds a new account object into database
    void create_new_account(); 
    //menu for modifying existing account
    void modify_account();
    //deletes acccount of matching adress
    void delete_account(const std::unique_ptr<Account>& account);
    //generates a unique iban code
    const std::string generate_iban(); 
    //clears the console
    void clear_screen();
    //save to CSV
private:
    std::vector <std::unique_ptr<Account>> database;
};

#endif