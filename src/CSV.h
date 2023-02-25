#ifndef CSV_H
#define CSV_H

#pragma once
#include "Account.h"

class CSV
{
public:
    CSV();
    ~CSV();
    
    //save account data into a csv file account.csv
    void save_file(const std::vector <std::shared_ptr<Account>>& database);

    //get data from the account.csv file
    void load_file(std::vector <std::shared_ptr<Account>>& database);
private:
};

#endif