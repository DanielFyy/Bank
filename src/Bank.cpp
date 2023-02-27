#include "Bank.h"

Bank::Bank()
{

}

Bank::~Bank()
{
    for (Account*& account : database)
        delete account;
    database.clear();
}

void Bank::main_terminal()
{   
    csv.load_database(database);
    csv.load_ibans(unique_ibans);
    char input;
    do 
    {   
        clear_screen();
        std::cout << "IT School Bank:\n[1]Login\n[2]Create New Account\n[3]Account Database\n[E]Exit\n";
        input = getch();
        if (isalpha(input))
            input = toupper(input);
        switch (input)
        {
        case '1':
            login();
            break;
        case '2':
            create_new_account();
            break;
        case '3':
            get_database();
            break;
        case 'E':
            return;
        default:
            break;
        }
    } while (true);
}

void Bank::get_database()
{
    clear_screen();
    std::cout << "Number of accounts: " << database.size() << "\n";
    if (database.size() > 0) 
        for (const Account* account : database)
            std::cout << account->get_surname() + " " + account->get_name() + " " + account->get_iban() + "\n";
    getch();
}

void Bank::create_new_account()
{   
    clear_screen();
    std::cout << "[1]Create New Account\n[B]Back\n";
    char input;
    do 
    {   
        input = getch();
        if (isalpha(input))
            input = toupper(input);
        switch (input)
        {
        case '1':
            break;
        case 'B':
            return;
        default:
            break;
        }
    } while (input != '1');

    clear_screen();
    std::cout << "Creating New Account:\n";
    
    std::cout << "Full Name: ";
    std::string surname;
    std::cin >> surname;
    surname[0] = toupper(surname[0]);
    for (int i = 1; i < surname.size(); i++) 
        surname[i] = tolower(surname[i]);

    std::string name;
    std::cin >> name;
    name[0] = toupper(name[0]);
    for (int i = 1; i < name.size(); i++)
        name[i] = tolower(name[i]);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (const Account* const account : database) 
        if (account->get_surname() == surname && account->get_name() == name)  
        {   
            clear_screen();
            std::cout << "Account under the name " + surname + " " + name + " already exists.\n";
            std::cout << "Do you still wish to continue creating new account?\n[Y]Yes\n[N]No\n";
            input = getch();
            if (isalpha(input))
                input = toupper(input);
            do 
            {
                switch (input)
                {
                case 'Y':
                    break;
                case 'N':
                    return;
                default:
                    break;
                }
            } while (input != 'Y');
            break;
        }
    
    clear_screen();
    std::cout << "Account Type:\n[1]lei\n[2]currency\n";
    std::string type;
    do 
    {   
        input = getch();
        switch (input)
        {
        case '1':
            type = "Lei";
            break;
        case '2':
            type = "Currency";
            break;
        default:
            break;
        }
    } while (input != '1' && input != '2');

    clear_screen();
    
    database.push_back(new Account(surname, name, generate_iban(), 0, type));

    csv.save_database(database);
    
    std::cout << "New account " + surname + " " + name + " has been created.\n";
    getch();
}

void Bank::login()
{   
    char input;
    do 
    {   
        do 
        {   
            clear_screen();
            std::cout << "[1]Find Account\n[B]Back\n";
            input = getch();
            if (isalpha(input))
                input = toupper(input);
            switch (input)
            {
            case '1':
                break;
            case 'B':
                return;
            default:
                break;
            }
        } while (input != '1');

        if (database.size() > 0) 
        {
            clear_screen();
            std::cout << "Account Name: ";
            std::string surname;
            std::cin >> surname;
            surname[0] = toupper(surname[0]);
            for (int i = 1; i < surname.size(); i++) 
                surname[i] = tolower(surname[i]);

            std::string name;
            std::cin >> name;
            name[0] = toupper(name[0]);
            for (int i = 1; i < name.size(); i++)
                name[i] = tolower(name[i]);

            std::string iban;
            std::cout << "Enter IBAN: ";
            while (iban.size() < 4) 
            {
                std::cin >> input;
                if (isdigit(input))
                    iban += input;
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            bool match = false;
            for (Account* account : database) 
                if (account->get_surname() == surname && account->get_name() == name && account->get_iban() == iban)
                {   
                    match = true;
                    modify_account(account);
                    break;
                }
            if (match == false)
            {   
                clear_screen();
                std::cout << "Account not found.\n";
                getch();
            }
        } 
        else
        {   
            clear_screen();
            std::cout << "No registered accounts found." << std::endl;
            getch();
        }
    } while (true);
}

void Bank::account_balance(Account* const account)
{
    
    int amount;
    char input;
    do 
    {
        clear_screen();
        std::cout << "Account Balance for " + account->get_surname() + " " + account->get_name() + ": " << std::to_string(account->get_balance()) << std::endl; 
        std::cout << "[1]Deposit\n[2]Withdraw\n[B]Back\n";
        input = getch();
        if (isalpha(input))
            input = toupper(input);
        switch (input)
        {
        case '1':
            std::cout << "Enter amount to deposit: ";
            std::cin >> amount;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            account->set_balance(account->get_balance() + abs(amount));
            break;
        case '2':
            std::cout << "Enter amount to withdraw: ";
            std::cin >> amount;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            account->set_balance(account->get_balance() - abs(amount));
            break;
        case 'B':
            return;
        default:
            break;
        }
    } while (true);
    

    csv.save_database(database);
}

void Bank::modify_account(Account* const account)
{   
    char input;
    do 
    {   
        clear_screen();
        std::cout << "Account Name: " + account->get_surname() + " " + account->get_name() + "\nIBAN: " + account->get_iban() + 
        "\nAccount Type: " + account->get_type() + "\nBalance: " << account->get_balance() << 
        "\n[1]Change Balance\n[2]Change Surname\n[3]Change Name\n[4]Change Type\n[5]Delete Account\n[B]Back\n";
        input = getch();
        if (isalpha(input))
            input = toupper(input);
        switch (input)
        {
        case '1':
            account_balance(account);
            break;
        case '2':
            change_surname(account);
            break;
        case '3':
            change_name(account);
            break;
        case '4':
            change_type(account);
            break;
        case '5':
            delete_account(account);
            return;
        case 'B':
            return;
        default:
            break;
        }
    } while (true);
}

void Bank::change_surname(Account* const account)
{   
    clear_screen();
    std::string surname;
    std::cout << "Enter new surname: ";
    std::cin >> surname;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    surname[0] = toupper(surname[0]);
    for (int i = 1; i < surname.size(); i++) 
        surname[i] = tolower(surname[i]);
    account->set_surname(surname);
    

    csv.save_database(database);
}

void Bank::change_name(Account* const account)
{   
    clear_screen();
    std::string name;
    std::cout << "Enter new name: ";
    std::cin >> name;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    name[0] = toupper(name[0]);
    for (int i = 1; i < name.size(); i++)
        name[i] = tolower(name[i]);
    account->set_name(name);

    csv.save_database(database);
}

void Bank::change_type(Account* const account)
{
    clear_screen();
    std::cout << "Account Type:\n[1]lei\n[2]currency\n";
    std::string type;
    char case_4_input;
    do 
    {   
        case_4_input = getch();
        switch (case_4_input)
        {
        case '1':
            account->set_type("Lei");
            break;
        case '2':
            account->set_type("Currency");
            break;
        default:
            break;
        }
    } while (case_4_input != '1' && case_4_input != '2');

    csv.save_database(database);
}

void Bank::delete_account(Account* const account)
{
    clear_screen();
    std::cout << "Are you sure you want to delete this account?\n[Y]Yes\n[N]No\n";
    char input;
    input = getch();
    if (isalpha(input))
            input = toupper(input);
    switch (input)
    {
    case 'Y':
        for(int i = 0; i < database.size(); i++) 
            if (account == database[i]) 
            {   
                clear_screen();
                std::cout << "Deleted Account " + account->get_surname() + " " + account->get_name() + ".\n";
                delete database[i];
                database.erase(database.begin() + i);
                csv.save_database(database);
                getch();
            }
        return;
    default:
        break;
    }

}

const std::string Bank::generate_iban()
{   
    
    std::random_device random;
    std::mt19937 rng(random());
    std::uniform_int_distribution<std::mt19937::result_type> number(0,9);

    std::string generated_iban;
    bool is_unique;

    do 
    {   
        generated_iban.clear();
        is_unique = true;

        for (int i = 0; i < 4; i++)
            generated_iban += std::to_string(number(rng));
        for (const std::string& iban : unique_ibans) 
            if (generated_iban == iban) 
            {
                is_unique = false;
                break;
            } 
    } while (is_unique == false);

    unique_ibans.push_back(generated_iban);
    csv.save_ibans(unique_ibans);
    
    return generated_iban;
}

void Bank::clear_screen()
{
    COORD topLeft  = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
}