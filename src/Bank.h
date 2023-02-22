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

    void create_new_account(); //adds a new account object into database
    void modify_account(); //modifies variables of an existing account in database
    void delete_account(const std::unique_ptr<Account>& account_adress);
    const std::string generate_iban(); //generates a unique iban code
    void clear_screen();
    //save to CSV
private:
    std::vector <std::unique_ptr<Account>> database;
};

#endif