// Deposit.h
// Deposit class definition. Represents a deposit transaction.
#ifndef DEPOSIT_H
#define DEPOSIT_H
#include <iostream>
#include <vector> // class uses vector to store Account objects
using namespace std;
#include "Account.h" // Account class definition
#include<iomanip>
class Deposit
{
public:
   Deposit( int userAccountNumber, vector< Account > &atmAccounts );
   void execute(); // perform the deposit transaction
private:
   int accountNumber; // indicates account involved
   vector< Account > &accounts; // reference to the vector of the bank's Accounts
   double amount; // amount to deposit

   // get pointer to Account object in "accounts" whose account number is equal to "accountNumber"
   Account * getAccount( int accountNumber, vector< Account > &accounts ); 
   double promptForDepositAmount() const; // prompt user to enter a deposit amount in cents 
};
Deposit::Deposit(int userAccountNumber, vector<Account>& atmAccounts)
    :accounts(atmAccounts),accountNumber(userAccountNumber){}
// end class Deposit
void Deposit::execute()
{
    cout << "Please enter a deposit amount in CENTS (or 0 to cancel): ";
    cin >> amount;
    if (amount == 0)
        return;
    cout << "\nPlease insert a deposit envelope containing $" << fixed << setprecision(2) << promptForDepositAmount() << " in the deposit slot.\n\n";
    cout << "Your envelope has been received.\n";
    cout << "NOTE: The money deposited will not be available until we verify the amount of any enclosed cash, and any enclosed checks clear.\n\n";
    for (size_t i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].getAccountNumber() == accountNumber)
        {
            //accounts[i].credit(promptForDepositAmount());
            getAccount(accountNumber, accounts)->credit(promptForDepositAmount());
        }
    }
}
inline Account* Deposit::getAccount(int accountNumber, vector<Account>& accounts)
{
    for (size_t i = 0; i < accounts.size(); i++)
    {
        // return current account if match found
        if (accounts[i].getAccountNumber() == accountNumber)
            return &accounts[i];
    } // end for

    return NULL;
}
double Deposit::promptForDepositAmount() const
{
    return amount / 100;
}
#endif // DEPOSIT_H