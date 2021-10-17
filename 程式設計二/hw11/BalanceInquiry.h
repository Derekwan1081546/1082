// BalanceInquiry.h
// BalanceInquiry class definition. Represents a balance inquiry.
#ifndef BALANCE_INQUIRY_H
#define BALANCE_INQUIRY_H
#include <iostream>
#include <vector> // class uses vector to store Account objects
using namespace std;
#include "Account.h" // Account class definition
#include<iomanip>

class BalanceInquiry
{
public:
   BalanceInquiry( int userAccountNumber, vector< Account > &atmAccounts ); // constructor
   void execute(); // perform the balance inquiry transaction
private:
   int accountNumber; // indicates account involved
   vector< Account > &accounts; // reference to the vector of the bank's Accounts

   // get pointer to Account object in "accounts" whose account number is equal to "accountNumber"
   Account * getAccount( int accountNumber, vector< Account > &accounts ); 
}; // end class BalanceInquiry
BalanceInquiry::BalanceInquiry(int userAccountNumber, vector< Account >& atmAccounts)
    :accounts(atmAccounts),accountNumber(userAccountNumber){}
//BalanceInquiry::BalanceInquiry(int userAccountNumber, vector< Account >& atmAccounts)
void BalanceInquiry::execute()
{
    for (size_t i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].getAccountNumber() == accountNumber)
        {
            cout << "\nBalance Information:\n";
            cout << " - Available balance: ";
            cout << "$" << fixed << setprecision(2) << accounts[i].getAvailableBalance() << endl;
            cout << " - Total balance: ";
            cout << "$" << fixed << setprecision(2) << getAccount(accountNumber,accounts)->getTotalBalance()<< endl;
        }
    }
    
}
inline Account* BalanceInquiry::getAccount(int accountNumber, vector<Account>& accounts)
{
    for (size_t i = 0; i < accounts.size(); i++)
    {
        // return current account if match found
        if (accounts[i].getAccountNumber() == accountNumber)
            return &accounts[i];
    } // end for

    return NULL;
}
#endif // BALANCE_INQUIRY_H