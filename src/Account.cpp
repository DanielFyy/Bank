#include "Account.h"

Account::Account(const std::string& surname, const std::string& name, const std::string& iban, const int& balance, const std::string& type)
: surname(surname), name(name), iban(iban), balance(balance), type(type)
{
}

Account::~Account()
{
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

void Account::set_type(const std::string& type)
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

const std::string Account::get_type() const
{
    return type;
}
