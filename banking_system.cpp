#include <iostream>
#include <fstream>
#include <ctype.h>

using namespace std;

class bank
{
public:
    int account_no;
    char name[20];
    string account_type;
    int deposit;

    void create_account();
    void display_account();
    int retaccount_no();
    int retdeposit();
    int retwithdraw();
};
// Defining member function outside the class!!

void bank::create_account()
{
    cout << "\n\t\t\t\tEnter Your Account no. :";
    cin >> account_no;
    cout << "\n\t\t\t\tEnter Your Name : ";
    cin.ignore();  //after entering into the cin statement, we need to input a character array or string. So we need to clear the input buffer, otherwise it will occupy the buffer of previous variable
    cin.getline(name, 20);
    cout << "\n\t\t\t\tEnter Account Type (C/S) :";
    cin >> account_type; //
    cout << "\n\t\t\t\tEnter the Amount to deposit : ";
    cin >> deposit;
    cout << "\n\t\t\t\tAccount created ........\n";
    cout << "\n";
}
void bank::display_account()
{
    cout << "--------------------------------------" << endl;
    cout << "Account no. is : " << account_no << endl;
    cout << "Name  is : " << name << endl;
    cout << "Account type is : " << account_type << endl;
    cout << "Amount to deposit : " << deposit << endl;
    cout << "--------------------------------------" << endl;
}
int bank::retaccount_no()
{
    return account_no;
}
int bank::retdeposit()
{
    return deposit;
}
int bank::retwithdraw()
{
    return deposit;
}

// prototype of function called in main function!!

void write_account();
void delete_account();
void modify_account();
void deposit_withdraw(int, int);
void list_account();
void list_single_account();
void account_balance();
void delete_all();

int main()
{
    int value;
    int num;
    cout << "\n\t\t\t\tBANKING SYSTEM PRIVATE LIMITED !!" << endl;
    cout << "\t\t\t----  Feel Free to To Join With Us !!-----" << endl;
    cout << "(----------------We are Here to help you and Build Amazing Community!!!!!----------------)" << endl;
    do
    {
        cout << "\n\t\t\t\t 1. NEW ACCOUNT " << endl;
        cout << "\n\t\t\t\t 2. DEPOSIT AMOUNT " << endl;
        cout << "\n\t\t\t\t 3. WITHDRAW AMOUNT " << endl;
        cout << "\n\t\t\t\t 4. BANANCE ENQUARY " << endl;
        cout << "\n\t\t\t\t 5. SHOW ACCOUNT DETAIL " << endl;
        cout << "\n\t\t\t\t 6. LIST ALL ACCOUNT " << endl;
        cout << "\n\t\t\t\t 7. CLOSE ACCOUNT " << endl;
        cout << "\n\t\t\t\t 8. MODIFY ACCOUNT " << endl;
        cout << "\n\t\t\t\t  9. CLOSE ALL ACCOUNT " << endl;
        cout << "\n\t\t\t\t 10.EXIT " << endl;
        cout << "\n\t\t\t\t Enter your choice (1-10) :";
        cin >> num;

        switch (num)
        {
        case 1:

            write_account();

            break;
        case 2:
            int depo;
            cout << "Enter the amount to deposit :" << endl;
            cin >> depo;
            deposit_withdraw(depo, 1);
            break;
        case 3:
            int draw;
            cout << "Enter the amount to withdraw :" << endl;
            cin >> draw;
            deposit_withdraw(draw, 2);
            break;
        case 4:
            account_balance();
            break;
        case 5:
            list_single_account();
            break;
        case 6:
            list_account();
            break;
        case 7:
            delete_account();
            break;
        case 8:
            modify_account();
            break;
        case 9:
            delete_all();
            break;
        case 10:
            cout << "Thank YOU for Accessing our services........" << endl;
            break;

        default:
            cout << "invalid input!!";
            break;
        }
    } while (num != 10);

    return 0;
}
// Definition of function which is called in main function!!

// Defining write_account() function !!!
void write_account()
{
    bank b;
    char more;
    ofstream out1("Cust_detail.dat", ios::binary | ios::out);
    if (!out1)
    {
        cout << "file is not opend !!" << endl;
    }
    while (1)
    {

        b.create_account();
        out1.write((char *)&b, sizeof(b));

        cout << "Want to add more customer if yes-(Y/y) else -(N/n)\n";
        cin >> more;
        more = toupper(more);
        if (more == 'Y')
            continue;
        else
            break;
    }
    out1.close();
}

// Defining detete_account() function !!!

void delete_account()
{
    bank b;
    int num;
    ifstream in2("cust_detail.dat", ios::binary | ios::in);
    ofstream out2("New.dat", ios::binary | ios::out);
    if (!in2 && !out2)
    {
        cout << "The reading /writing file is not opend" << endl;
    }
    cout << "Enter the account no. :" << endl;
    cin >> num;
    while (in2.read((char *)&b, sizeof(b)))
    {
        if (num != b.retaccount_no())
        {
            out2.write((char *)&b, sizeof(b));
        }
    }
    in2.close();
    out2.close();

    remove("cust_detail.dat");
    rename("New.dat", "cust_detail.dat");

    cout << "Data deleted successfully !!!!" << endl;
}

// Defining modify_account() function !!!

void modify_account()
{
    bank b;
    int num;
    ifstream in2("cust_detail.dat", ios::binary | ios::in);
    ofstream out2("New.dat", ios::binary | ios::out);
    if (!in2 && !out2)
    {
        cout << "The reading /writing file is not opend" << endl;
    }
    cout << "Enter the account no. :" << endl;
    cin >> num;
    while (in2.read((char *)&b, sizeof(b)))
    {
        if (num == b.retaccount_no())
        {
            b.create_account();
        }
        out2.write((char *)&b, sizeof(b));
    }
    in2.close();
    out2.close();

    remove("cust_detail.dat");
    rename("New.dat", "cust_detail.dat");

    cout << "Data updated successfully !!!!" << endl;
}

// Defining deposit_withdraw() function !!!

void deposit_withdraw(int cal, int i)
{
    bank b;
    int num;
    ifstream in3("cust_detail.dat", ios::binary | ios::in);
    ofstream out3("New.dat", ios::binary | ios::out);
    if (!in3 && !out3)
    {
        cout << "The reading /writing file is not opend" << endl;
    }
    cout << "Enter the account no. :" << endl;
    cin >> num;
    while (in3.read((char *)&b, sizeof(b)))
    {
        if (num == b.retaccount_no())
        {
            if (i == 1)
            {
                b.deposit += cal;
            }
            else if (i == 2)
            {
                if (b.deposit > cal)
                {
                    b.deposit -= cal;
                }
                else
                {
                    cout << "insufficient fund !!" << endl;
                }
            }
        }
        out3.write((char *)&b, sizeof(b));
    }
    in3.close();
    out3.close();

    remove("cust_detail.dat");
    rename("New.dat", "cust_detail.dat");

    cout << "Balance updated successfully !!!!" << endl;
}
// Defining account_balance() function !!!

void account_balance()
{
    bank b;
    int num;
    ifstream in4("cust_detail.dat", ios::binary | ios::in);
    if (!in4)
    {
        cout << "The reading /writing file is not opend" << endl;
    }
    cout << "Enter the account no. :" << endl;
    cin >> num;
    while (in4.read((char *)&b, sizeof(b)))
    {
        if (num == b.retaccount_no())
        {
            cout << "Account Balance :" << b.deposit << endl;
        }
    }
    in4.close();
}
// Defining list_account() function !!!

void list_account()
{
    bank b;

    ifstream in4("cust_detail.dat", ios::binary | ios::in);
    if (!in4)
    {
        cout << "The reading /writing file is not opend" << endl;
    }

    while (in4.read((char *)&b, sizeof(b)))
    {
        b.display_account();
    }
    in4.close();
}

// Defining delete_all() function !!!

void delete_all()
{
    bank b;

    ifstream in4("cust_detail.dat", ios::binary | ios::in);
    ofstream out4("New.dat", ios::binary | ios::out);
    if (!in4 && !out4)
    {
        cout << "The reading /writing file is not opend" << endl;
    }

    // while (in4.read((char *)&b,sizeof(b)))
    // {
    //     b.display_account();
    // }

    in4.close();
    out4.close();
    remove("cust_detail.dat");
    rename("New.dat", "cust_detail.dat");
    cout << " All account successfully closed !!!" << endl;
}

// Defining list_single_account() function !!!

void list_single_account()
{
    bank b;
    int num;
    ifstream in4("cust_detail.dat", ios::binary | ios::in);
    cout << "Enter your account number :" << endl;
    cin >> num;
    while (in4.read((char *)&b, sizeof(b)))
    {
        if (num == b.retaccount_no())
        {
            b.display_account();
        }
    }
}