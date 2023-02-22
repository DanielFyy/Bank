#ifndef ACCOUNT_H
#define ACCOUNT_H

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <memory>
#include <windows.h>
#include <conio.h>

enum account_type {lei, currency};

class Account
{
public:
    Account(const std::string& name, const std::string& surname, const std::string& iban, const account_type& type);
    ~Account();

    //setters
    void set_surname(const std::string& surname);
    void set_name(const std::string& name);
    void set_balance(const int& balance);
    void set_type(const account_type& type);

    //getters
    const std::string get_surname() const;
    const std::string get_name() const;
    const std::string get_iban() const;
    const int get_balance() const;
    const account_type get_type() const;

    //get type in string format
    const std::string get_type_name() const;
    

private:
    std::string surname;
    std::string name;
    const std::string iban;
    int balance;
    account_type type;
};

#endif