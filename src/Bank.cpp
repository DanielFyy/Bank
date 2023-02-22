#include "Bank.h"

Bank::Bank()
{

}

Bank::~Bank()
{

}

void Bank::main_terminal() //t
{   
    char input;
    do 
    {   
        clear_screen();

        std::cout << "IT School Bank:\n[1]Number of accounts\n[2]Create New Account\n[3]Modify Existing Account\n[4]Exit\n";
        switch (getch())
        {
        case '1':
            clear_screen();
            std::cout << "Number of accounts: " << database.size() << std::endl;
            getch();
            break;
        case '2':
            create_new_account();
            break;
        case '3':
            modify_account();
            break;
        case '4':
            return;
        default:
            break;
        }
    
    } while (true);
}

void Bank::create_new_account()
{   
    clear_screen();

    std::cout << "Create New Account:\n";
    
    std::cout << "Name: ";
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

    for (const std::unique_ptr<Account>& account : database) 
        if (account->get_surname() == surname && account->get_name() == name)  
        {
            std::cout << "Account under the name " + surname + " " + name + " already exists.\n";
            getch();
            return;
        }
    
    clear_screen();
    std::cout << "Account Type:\n[1]lei\n[2]currency\n";
    account_type type;
    char input;
    do 
    {   
        input = getch();
        switch (input)
        {
        case '1':
            type = lei;
            break;
        case '2':
            type = currency;
            break;
        default:
            break;
        }
    } while (input != '1' && input != '2');

    std::string iban = generate_iban();

    database.push_back(std::make_unique <Account>(surname, name, iban, type));

    std::cout << "New account " + surname + " " + name + " has been created.\n";
    getch();
}

void Bank::modify_account()
{   
    do 
    {
        clear_screen();

        std::cout << "[1]Enter Account\n[2]Back\n";
        char input;
        do 
        {   input = getch();
            switch (input)
            {
            case '1':
                break;
            case '2':
                return;
            default:
                break;
            }
        } while (input != '1' && input != '2');
        
        if (database.size() > 0) 
        {
            clear_screen();
            std::cout << "Enter Account Name: ";
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

            
            bool end_loop = false;
            do 
            {   
                clear_screen();
                for (const std::unique_ptr<Account>& account : database) 
                if (account->get_surname() == surname && account->get_name() == name)  
                {   
                    std::cout << "Account Name: " + surname + " " + name + "\nIBAN: " + account->get_iban() + "\nAccount Type: " + account->get_type_name() + "\nBalance: " << account->get_balance() << "\n[1]Modify Balance\n[2]Change Surname\n[3]Change Name\n[4]Change Type\n[5]Delete Account\n[6]Back\n";
                    input = getch();    
                    switch (input)
                    {
                    case '1':
                        clear_screen();
                        std::cout << "\nModify Account Balance: ";
                        int amount;
                        std::cin >> amount;
                        account->set_balance(account->get_balance() + amount);
                        std::cout << "New Account Balance: " << account->get_balance() << "\n";
                        getch();
                        break;
                    case '2':
                        std::cout << "Enter new surname: ";
                        std::cin >> surname;
                        surname[0] = toupper(surname[0]);
                        for (int i = 1; i < surname.size(); i++) 
                            surname[i] = tolower(surname[i]);
                        account->set_surname(surname);
                        break;
                    case '3':
                        std::cout << "Enter new name: ";
                        std::cin >> name;
                        name[0] = toupper(name[0]);
                        for (int i = 1; i < name.size(); i++)
                            name[i] = tolower(name[i]);
                        account->set_name(name);
                        break;
                    case '4':
                        std::cout << "Account Type:\n[1]lei\n[2]currency\n";
                        account_type type;
                        char case_4_input;
                        do 
                        {   
                            case_4_input = getch();
                            switch (case_4_input)
                            {
                            case '1':
                                account->set_type(lei);
                                break;
                            case '2':
                                account->set_type(currency);
                                break;
                            default:
                                break;
                            }
                        } while (case_4_input != '1' && case_4_input != '2');
                        break;
                    case '5':
                        std::cout << "Are you sure you want to delete this account?\n[y]Yes\n[n]No\n";
                        switch (getch())
                        {
                        case 'y':
                            delete_account(account);
                            return;
                        default:
                            break;
                        }
                        break;
                    case '6':
                        end_loop = true;
                        return;
                    default:
                        break;
                    }
                    break;
                } 
                else
                {
                    std::cout << "Account not found." << std::endl;
                    getch();
                    end_loop = true;
                }
                
            } while (end_loop == false);
        }
        else
        {
            std::cout << "No accounts currently registered." << std::endl;
            getch();
            break;
        }
    } while(true); 
        
    
    
}

void Bank::delete_account(const std::unique_ptr<Account>& account)
{
    clear_screen();
    for(int i = 0; i < database.size(); i++) 
    {
        if (account == database[i]) 
        {   
            std::cout << "Deleted Account " + account->get_surname() + " " + account->get_name() + ".\n";
            database[i].reset(nullptr);
            database.erase(database.begin() + i);
            getch();
        }
    }
    
}

const std::string Bank::generate_iban()
{   
    std::string generated_iban = "ROITSCHOOL";

    std::random_device random;
    std::mt19937 rng(random());
    std::uniform_int_distribution<std::mt19937::result_type> number(0,9);

    bool unique_iban = true;
    do 
    {
        for (int i = 0; i < 15; i++) 
            generated_iban += std::to_string(number(rng));

        for (const std::string& iban : used_iban) 
            if (generated_iban == iban) 
            bool unique_iban = false;

    } while(unique_iban == false);

    //never use the same iban twice
    used_iban.push_back(generated_iban);
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