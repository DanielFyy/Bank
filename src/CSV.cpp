#include "CSV.h"

CSV::CSV()
{

}

CSV::~CSV()
{

}

void CSV::save_database(const std::vector <std::shared_ptr<Account>>& database)
{   
    std::fstream file;
    file.open("accounts.csv", std::ios::out);

    for (const std::shared_ptr<Account>& account : database) 
    {
        file << account->get_surname() + "," 
        + account->get_name() + "," + account->get_iban() + ","
        +  std::to_string(account->get_balance()) + ","
        + account->get_type() + "\n";
    }   
    file.close();
}

void CSV::load_database(std::vector <std::shared_ptr<Account>>& database)
{
    std::fstream file;

    file.open("accounts.csv", std::ios::in);
    
    std::vector <std::string> data;
    std::string row, row_element;
    while (std::getline(file, row)) 
    {
        std::stringstream stream(row);
        while(std::getline(stream, row_element, ',')) 
        {
            data.push_back(row_element); 
        }
    }

    std::string surname, name, iban, balance, type;
    int x = 0;
    for (int i = 0; i < data.size() / 5; i++) 
    {   
        database.push_back(std::make_unique<Account>(data[0 + x], data[1 + x], data[2 + x], stoi(data[3 + x]), data[4 + x]));
        x += 5;
    }

    file.close();
}

void CSV::save_ibans(const std::vector <std::string>& unique_ibans)
{
    std::fstream file;
    file.open("ibans.csv", std::ios::out);

    for (const std::string& iban : unique_ibans) 
    {
        file << iban + "\n";
    }   

    file.close();
}

void CSV::load_ibans(std::vector <std::string>& unique_ibans)
{
    std::fstream file;

    file.open("ibans.csv", std::ios::in);
    
    std::vector <std::string> data;
    std::string iban;
    while (std::getline(file, iban)) 
        data.push_back(iban); 

    for (int i = 0; i < data.size(); i++) 
        unique_ibans.push_back(data[i]);

    file.close();
}
