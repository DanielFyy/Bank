#include "CSV.h"

CSV::CSV()
{

}

CSV::~CSV()
{

}

void CSV::save_file(const std::vector <std::shared_ptr<Account>>& database)
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

void CSV::load_file(std::vector <std::shared_ptr<Account>>& database)
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
