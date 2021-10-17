#ifndef S1081546_HW10_H
#define S1081546_HW10_H
using namespace std;
class MyClass
{
public:
	MyClass();
	~MyClass();

    char Aaccountnumber[10]="12345"; // used as the account number
    char APIN[10] = "54321";// used as the PIN number
    char Baccountnumber[10] = "98765"; // used as the account number
    char BPIN[10] = "56789";// used as the PIN number
    double Aavailablebalance = 1000;
    double Atotalbalance = 1200;
    double Bavailablebalance = 200;
    double Btotalbalance = 200;

    void view(char accountnumber[10])
    {
        cout << "\nBalance Information:\n";
        cout << " - Available balance: ";
        if (strcmp(accountnumber, Aaccountnumber) == 0)
            cout << "$" << fixed << setprecision(2) << Aavailablebalance << endl;
        else
            cout << "$" << fixed << setprecision(2) << Bavailablebalance << endl;
        cout << " - Total balance: ";
        if (strcmp(accountnumber, Aaccountnumber) == 0)
            cout << "$" << fixed << setprecision(2) << Atotalbalance << endl;
        else
            cout << "$" << fixed << setprecision(2) << Btotalbalance << endl;
    }
    void withdraw(int options,char accountnumber[10])
    {
        switch (options)
        {
        case 1:
            if (strcmp(accountnumber, Aaccountnumber) == 0)
            {
                if (Aavailablebalance >= 20 && Atotalbalance >= 20)
                {
                    Aavailablebalance -= 20;
                    Atotalbalance -= 20;
                    cout << "\nPlease take your cash from the cash dispenser.\n\n";
                }
                else
                {
                    cout << "\nNot enough money.Please deposit money!\n";
                }
                break;
            }
            else
            {
                if (Bavailablebalance >= 20 && Btotalbalance >= 20)
                {
                    Bavailablebalance -= 20;
                    Btotalbalance -= 20;
                    cout << "\nPlease take your cash from the cash dispenser.\n\n";
                }
                else
                {
                    cout << "\nNot enough money.Please deposit money!\n";
                }
                break;
            }
        case 2:
            if (strcmp(accountnumber, Aaccountnumber) == 0)
            {
                if (Aavailablebalance >= 40 && Atotalbalance >= 40)
                {
                    Aavailablebalance -= 40;
                    Atotalbalance -= 40;
                    cout << "\nPlease take your cash from the cash dispenser.\n\n";
                }
                else
                {
                    cout << "\nNot enough money.Please input a smaller withdrawal amount!\n";
                }
                break;
            }
            else
            {
                if (Bavailablebalance >= 40 && Btotalbalance >= 40)
                {
                    Bavailablebalance -= 40;
                    Btotalbalance -= 40;
                    cout << "\nPlease take your cash from the cash dispenser.\n\n";
                }
                else
                {
                    cout << "\nNot enough money.Please input a smaller withdrawal amount!\n";
                }
                break;
            }
        case 3:
            if (strcmp(accountnumber, Aaccountnumber) == 0)
            {
                if (Aavailablebalance >= 60 && Atotalbalance >= 60)
                {
                    Aavailablebalance -= 60;
                    Atotalbalance -= 60;
                    cout << "\nPlease take your cash from the cash dispenser.\n\n";
                }
                else
                {
                    cout << "\nNot enough money.Please input a smaller withdrawal amount!\n";
                }
                break;
            }
            else
            {
                if (Bavailablebalance >= 60 && Btotalbalance >= 60)
                {
                    Bavailablebalance -= 60;
                    Btotalbalance -= 60;
                    cout << "\nPlease take your cash from the cash dispenser.\n\n";
                }
                else
                {
                    cout << "\nNot enough money.Please input a smaller withdrawal amount!\n";
                }
                break;
            }
        case 4:
            if (strcmp(accountnumber, Aaccountnumber) == 0)
            {
                if (Aavailablebalance >= 100 && Atotalbalance >= 100)
                {
                    Aavailablebalance -= 100;
                    Atotalbalance -= 100;
                    cout << "\nPlease take your cash from the cash dispenser.\n\n";
                }
                else
                {
                    cout << "\nNot enough money.Please input a smaller withdrawal amount!\n";
                }
                break;
            }
            else
            {
                if (Bavailablebalance >= 100 && Btotalbalance >= 100)
                {
                    Bavailablebalance -= 100;
                    Btotalbalance -= 100;
                    cout << "\nPlease take your cash from the cash dispenser.\n\n";
                }
                else
                {
                    cout << "\nNot enough money.Please input a smaller withdrawal amount!\n";
                }
                break;
            }
        case 5:
            if (strcmp(accountnumber, Aaccountnumber) == 0)
            {
                if (Aavailablebalance >= 200 && Atotalbalance >= 200)
                {
                    Aavailablebalance -= 200;
                    Atotalbalance -= 200;
                    cout << "\nPlease take your cash from the cash dispenser.\n\n";
                }
                else
                {
                    cout << "\nNot enough money.Please input a smaller withdrawal amount!\n";
                }
                break;
            }
            else
            {
                if (Bavailablebalance >= 200 && Btotalbalance >= 200)
                {
                    Bavailablebalance -= 200;
                    Btotalbalance -= 200;
                    cout << "\nPlease take your cash from the cash dispenser.\n\n";
                }
                else
                {
                    cout << "\nNot enough money.Please input a smaller withdrawal amount!\n";
                }
                break;
            }
        case 6:
            break;
        }
    }
    void deposit(double depositamount,char accountnumber[10])
    {
        cout << "\nPlease insert a deposit envelope containing $" << fixed << setprecision(2) << depositamount << " in the deposit slot.\n\n";
        cout << "Your envelope has been received.\n";
        cout << "NOTE: The money deposited will not be available until we verify the amount of any enclosed cash, and any enclosed checks clear.\n\n";
        if (strcmp(accountnumber, Aaccountnumber) == 0)
        {
            Atotalbalance += depositamount;
        }
        else
        {
            Btotalbalance += depositamount;
        }
    }

};

MyClass::MyClass()
{
}

MyClass::~MyClass()
{
}
#endif
