#ifndef CSV_H
#define CSV_H

#pragma once
#include "Account.h"

class CSV
{
public:
    CSV();
    ~CSV();
    
    
    void save_database(const std::vector <std::shared_ptr<Account>>& database); //save account data into a csv file account.csv
    void load_database(std::vector <std::shared_ptr<Account>>& database); //get data from the account.csv file

    void save_ibans(const std::vector <std::string>& unique_ibans);
    void load_ibans(std::vector <std::string>& unique_ibans);

private:
};

#endif