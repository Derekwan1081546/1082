// Withdrawal.h
// Withdrawal class definition. Represents a withdrawal transaction.
#ifndef WITHDRAWAL_H
#define WITHDRAWAL_H

#include <iostream>
#include <vector> // class uses vector to store Account objects
using namespace std;
#include "Account.h" // Account class definition
#include<iomanip>

class Withdrawal
{
public:
   Withdrawal( int userAccountNumber, vector< Account > &atmAccounts, int &atmRemainingBills );
   void execute(); // perform the withdrawal transaction
private:
   int accountNumber; // indicates account involved
   vector< Account > &accounts; // reference to the vector of the bank's Accounts
   int amount; // amount to withdraw
   int &remainingBills; // number of $20 bills remaining 

   // get pointer to Account object in "accounts" whose account number is equal to "accountNumber"
   Account * getAccount( int accountNumber, vector< Account > &accounts );

   // display a menu of withdrawal amounts and the option to cancel;
   // return the chosen amount or 0 if the user chooses to cancel
   int displayMenuOfAmounts() const;
};
Withdrawal::Withdrawal(int userAccountNumber, vector<Account>& atmAccounts, int& atmRemainingBills)
    :accounts(atmAccounts),remainingBills(atmRemainingBills),accountNumber(userAccountNumber){}

// end class Withdrawal
void Withdrawal::execute()
{
    switch (displayMenuOfAmounts())
    {
    case 1:
        for (size_t i = 0; i < accounts.size(); i++)
        {
            if (accounts[i].getAccountNumber() == accountNumber)
            {
                if (accounts[i].getAvailableBalance() >= 20 && accounts[i].getTotalBalance() >= 20)
                {
                    remainingBills -= 1;
                    //accounts[i].debit(20);
                    getAccount(accountNumber, accounts)->debit(20);
                    cout << "\nPlease take your cash from the cash dispenser.\n\n";
                }
                else if (remainingBills <= 0)
                {
                    cout << "\nNot enough money.There is no money to withdrawal.";
                }
                else
                {
                    cout << "\nNot enough money.Please deposit money!\n";
                }
                break;
            }
        }
        break;
    case 2:
        for (size_t i = 0; i < accounts.size(); i++)
        {
            if (accounts[i].getAccountNumber() == accountNumber)
            {
                if (accounts[i].getAvailableBalance() >= 40 && accounts[i].getTotalBalance() >= 40)
                {
                    remainingBills -= 2;
                    //accounts[i].debit(40);
                    getAccount(accountNumber, accounts)->debit(40);
                    cout << "\nPlease take your cash from the cash dispenser.\n\n";
                }
                else if (remainingBills <= 0)
                {
                    cout << "\nNot enough money.There is no money to withdrawal.";
                }
                else
                {
                    cout << "\nNot enough money.Please input a smaller withdrawal amount!\n";
                }
                break;
            }
        }
        break;
    case 3:
        for (size_t i = 0; i < accounts.size(); i++)
        {
            if (accounts[i].getAccountNumber() == accountNumber)
            {
                if (accounts[i].getAvailableBalance() >= 60 && accounts[i].getTotalBalance() >= 60)
                {
                    remainingBills -= 3;
                    //accounts[i].debit(60);
                    getAccount(accountNumber, accounts)->debit(60);
                    cout << "\nPlease take your cash from the cash dispenser.\n\n";
                }
                else if (remainingBills <= 0)
                {
                    cout << "\nNot enough money.There is no money to withdrawal.";
                }
                else
                {
                    cout << "\nNot enough money.Please input a smaller withdrawal amount!\n";
                }
                break;
            }
        }
        break;
    case 4:
        for (size_t i = 0; i < accounts.size(); i++)
        {
            if (accounts[i].getAccountNumber() == accountNumber)
            {
                if (accounts[i].getAvailableBalance() >= 100 && accounts[i].getTotalBalance() >= 100)
                {
                    remainingBills -= 5;
                    //accounts[i].debit(100);
                    getAccount(accountNumber, accounts)->debit(100);
                    cout << "\nPlease take your cash from the cash dispenser.\n\n";
                }
                else if (remainingBills <= 0)
                {
                    cout << "\nNot enough money.There is no money to withdrawal.";
                }
                else
                {
                    cout << "\nNot enough money.Please input a smaller withdrawal amount!\n";
                }
                break;
            }
        }
        break;
    case 5:
        for (size_t i = 0; i < accounts.size(); i++)
        {
            if (accounts[i].getAccountNumber() == accountNumber)
            {
                if (accounts[i].getAvailableBalance() >= 200 && accounts[i].getTotalBalance() >= 200)
                {
                    remainingBills -= 10;
                    //accounts[i].debit(200);
                    getAccount(accountNumber, accounts)->debit(200);
                    cout << "\nPlease take your cash from the cash dispenser.\n\n";
                }
                else if (remainingBills <= 0)
                {
                    cout << "\nNot enough money.There is no money to withdrawal.";
                }
                else
                {
                    cout << "\nNot enough money.Please input a smaller withdrawal amount!\n";
                }
                break;
            }
        }
        break;
    case 6:
        break;
    }

}
int Withdrawal::displayMenuOfAmounts()const
{
    int options;
    cout << "\nWithdrawal options:\n";
    cout << "1 - $20\n";
    cout << "2 - $40\n";
    cout << "3 - $60\n";
    cout << "4 - $100\n";
    cout << "5 - $200\n";
    cout << "6 - Cancel transaction\n\n";
    cout << "Choose a withdrawal option (1-6): ";
    cin >> options;
    return options;
}
inline Account* Withdrawal::getAccount(int accountNumber, vector<Account>& accounts)
{
    for (size_t i = 0; i < accounts.size(); i++)
    {
        // return current account if match found
        if (accounts[i].getAccountNumber() == accountNumber)
            return &accounts[i];
    } // end for

    return NULL;
}
#endif // WITHDRAWAL_H