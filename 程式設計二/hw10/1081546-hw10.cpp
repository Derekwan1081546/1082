#include<iostream>
#include<iomanip>
#include"s1081546-hw10.h"
using namespace std;
struct Account1
{
    char accountnumber[10] = "12345"; // used as the account number
    char PIN[10] = "54321";// used as the PIN number
    double availablebalance = 1000;
    double totalbalance = 1200;
};
struct Account2
{
    char accountnumber[10] = "98765"; // used as the account number
    char PIN[10] = "56789";// used as the PIN number
    double availablebalance = 200;
    double totalbalance = 200;
};
int main()
{
    Account1 a;
    Account2 b;
    MyClass account;
    int choice = 0;
    int options = 0;
    double depositamount = 0;
    char accountnumber[10];
    char PIN[10];
    cout << "Welcome!\n" << endl;
    cout << "Please enter your account number: ";
    cin >> accountnumber;
    cout << "Enter your PIN: ";
    cin >> PIN;
    while (true)
    {
        if ((strcmp(accountnumber, a.accountnumber) == 0 && strcmp(PIN, a.PIN) == 0) || (strcmp(accountnumber, b.accountnumber) == 0 && strcmp(PIN, b.PIN) == 0))
        {
            cout << "\nMain menu:\n";
            cout << "1 - View my balance\n";
            cout << "2 - Withdraw cash\n";
            cout << "3 - Deposit funds\n";
            cout << "4 - Exit\n\n";
            cout << "Enter a choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                account.view(accountnumber);
                break;

            case 2:

                cout << "\nWithdrawal options:\n";
                cout << "1 - $20\n";
                cout << "2 - $40\n";
                cout << "3 - $60\n";
                cout << "4 - $100\n";
                cout << "5 - $200\n";
                cout << "6 - Cancel transaction\n\n";
                cout << "Choose a withdrawal option (1-6): ";
                cin >> options;
                account.withdraw(options, accountnumber);
                break;
            case 3:
                cout << "Please enter a deposit amount in CENTS (or 0 to cancel): ";
                cin >> depositamount;
                if (depositamount == 0)
                    break;
                depositamount /= 100;
                account.deposit(depositamount, accountnumber);
            }
            if (choice == 4)
            {
                cout << "\nExiting the system...\n\n";
                cout << "Thank you! Goodbye!\n\n";
                cout << "Welcome!" << endl << endl;
                cout << "Please enter your account number: ";
                cin >> accountnumber;
                cout << "\nEnter your PIN: ";
                cin >> PIN;
            }
        }
        else
        {
            cout << "invalid account number or an incorrect PIN!Please try again \n";
            cout << "Welcome!" << endl;
            cout << "Please enter your account number: ";
            cin >> accountnumber;
            cout << "Enter your PIN: ";
            cin >> PIN;
        }
    }

    system("pause");
    return 0;
}