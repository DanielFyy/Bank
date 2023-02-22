#include "Account.h"

Account::Account(const std::string& surname, const std::string& name, const std::string& iban, const account_type& type)
: surname(surname), name(name), iban(iban), balance(0), type(type)
{
    std::cout << "Created Account " << surname + name << std::endl;
}

Account::~Account()
{
    std::cout << "Destroyed Account " << surname + name << std::endl;
}

void Account::set_surname(const std::string& surname)
{
    this->surname = surname;
}

void Account::set_name(const std::string& name)
{
    this->name = name;
}

void Account::set_balance(const int& balance)
{
    this->balance = balance;
}

void Account::set_type(const account_type& type)
{
    this->type = type;
}

const std::string Account::get_surname() const
{
    return surname;
}

const std::string Account::get_name() const
{
    return name;
}

const std::string Account::get_iban() const
{
    return iban;
}

const int Account::get_balance() const
{
    return balance;
}

const account_type Account::get_type() const
{
    return type;
}

const std::string Account::get_type_name() const
{
    if (type == lei)
        return "Lei";
    else if (type == currency)
        return "Currency";
    else
        return "Unspecified";
}
