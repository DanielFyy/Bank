#ifndef ACCOUNT_H
#define ACCOUNT_H

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <conio.h>


class Account
{
public:
    Account(const std::string& surname, const std::string& name, const std::string& iban, const int& balance, const std::string& type);
    ~Account();

    void set_surname(const std::string& surname);
    void set_name(const std::string& name);
    void set_balance(const int& balance);
    void set_type(const std::string& type);

    const std::string get_surname() const;
    const std::string get_name() const;
    const std::string get_iban() const;
    const int get_balance() const;
    const std::string get_type() const;
    
private:
    std::string surname;
    std::string name;
    const std::string iban;
    int balance;
    std::string type;
};

#endif