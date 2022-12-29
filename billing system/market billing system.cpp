#include<iostream>
#include<windows.h>
#include<conio.h>
#include<fstream>
#include<sstream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<iomanip>
using namespace std;
//global variable declaration
int k = 7, r = 0, flag = 0, a = 0, l = 7, m = 0, chf[50], n = 0, bcount = 1;
float total = 0.0;
COORD coord = { 0, 0 };


void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
struct date
{
    int mm, dd, yy;
};

ofstream fout;
ifstream fin;




class item
{
    int itemno;
    char name[25];
    date d;
public:
    void add()
    {
        gotoxy(25, 14);
        cout << "\n\n\tItem No: ";
        cin >> itemno;
        cout << "\n\n\tName of the item: ";
        cin >> name;
        //gets(name);
        cout << "\n\n\tExpired Date(dd-mm-yy): ";
        cin >> d.mm >> d.dd >> d.yy;
    }
    void show()
    {
        gotoxy(25, 5);
        cout << "\n\tItem No: ";
        cout << itemno;
        cout << "\n\n\tName of the item: ";
        cout << name;
        cout << "\n\n\tDate : ";
        cout << d.mm << "-" << d.dd << "-" << d.yy;
    }
    void report()
    {
        gotoxy(3, k);
        cout << itemno;
        gotoxy(13, k);
        puts(name);
    }
    void bill() {
        gotoxy(3, l);
        cout << itemno;
        gotoxy(13, l);
        puts(name);

    }
    int retno()
    {
        if (a == 1) {
            gotoxy(10, 1);
            cout << "EDU_MOD:amount-bill";
        }
        else {
            gotoxy(10, 1);
            cout << "REG_MOD:ON";
        }
        return(itemno);

    }
    string retname() {
        if (a == 1) {
            gotoxy(10, 1);
            cout << "EDU_MOD:amount-bill";
        }
        else {
            gotoxy(10, 1);
            cout << "REG_MOD:ON";
        }
        string namb = name;
        return(namb);
    }

};

class amount : public item
{
    float price, qty, tax, gross, dis, netamt;
public:
    void add();
    void show();
    void report();
    void calculate();
    void pay();
    void bill();
    float retnetamt()
    {
        return(netamt);
    }
    float retqty() {
        return(qty);
    }
} amt;

void amount::add()
{
    if (a == 1) {
        gotoxy(10, 1);
        cout << "EDU_MOD:amount-add";
    }
    else {
        gotoxy(10, 1);
        cout << "REG_MOD:ON";
    }
    item::add();
    cout << "\n\n\tPrice: ";
    cin >> price;
    cout << "\n\n\tQuantity: ";
    cin >> qty;
    cout << "\n\n\tTax percent: ";
    cin >> tax;
    cout << "\n\n\tDiscount percent: ";
    cin >> dis;
    calculate();
    fout.write((char*)&amt, sizeof(amt));
    fout.close();
    gotoxy(25, 35);
    cout << "\n\t\tItem Added Successfully!";
}
void amount::calculate()
{
    if (a == 1) {
        gotoxy(10, 1);
        cout << "EDU_MOD:amount-calculate";
    }
    else {
        gotoxy(10, 1);
        cout << "REG_MOD:ON";
    }
    gross = price + (price * (tax / 100));
    netamt = qty * (gross - (gross * (dis / 100)));
}
void amount::show()
{

    if (a == 1) {
        gotoxy(10, 1);
        cout << "EDU_MOD:amount-show";
    }
    else {
        gotoxy(10, 1);
        cout << "REG_MOD:ON";
    }
    fin.open("itemstore.dat", ios::binary);
    fin.read((char*)&amt, sizeof(amt));
    item::show();
    cout << "\n\n\tNet amount: ";
    cout << netamt;
    fin.close();
}

void amount::report()
{

    if (a == 1) {
        gotoxy(10, 1);
        cout << "EDU_MOD:amount-report";
    }
    else {
        gotoxy(10, 1);
        cout << "REG_MOD:ON";
    }
    item::report();
    gotoxy(23, k);
    cout << price;
    gotoxy(33, k);
    cout << qty;
    gotoxy(44, k);
    cout << tax;
    gotoxy(52, k);
    cout << dis;
    gotoxy(64, k);
    cout << netamt;
    k = k + 1;
    if (k == 50)
    {
        gotoxy(25, 50);
        cout << "PRESS ANY KEY TO CONTINUE...";
        _getch();
        k = 7;
        system("cls");
        gotoxy(30, 3);
        cout << " ITEM DETAILS ";
        gotoxy(3, 5);
        cout << "NUMBER";
        gotoxy(13, 5);
        cout << "NAME";
        gotoxy(23, 5);
        cout << "PRICE";
        gotoxy(33, 5);
        cout << "QUANTITY";
        gotoxy(44, 5);
        cout << "TAX";
        gotoxy(52, 5);
        cout << "DEDUCTION";
        gotoxy(64, 5);
        cout << "NET AMOUNT";
    }
}

void amount::pay()
{

    if (a == 1) {
        gotoxy(10, 1);
        cout << "EDU_MOD:amount-pay";
    }
    else {
        gotoxy(10, 1);
        cout << "REG_MOD:ON";
    }
    show();
    cout << "\n\n\n\t\t*********************************************";
    cout << "\n\t\t                 DETAILS                  ";
    cout << "\n\t\t*********************************************";
    cout << "\n\n\t\tPRICE                     :" << price;
    cout << "\n\n\t\tQUANTITY                  :" << qty;
    cout << "\n\t\tTAX PERCENTAGE              :" << tax;
    cout << "\n\t\tDISCOUNT PERCENTAGE         :" << dis;
    cout << "\n\n\n\t\tNET AMOUNT              :Rs." << netamt;
    cout << "\n\t\t*********************************************";
}

void amount::bill() {
    if (a == 1) {
        gotoxy(10, 1);
        cout << "EDU_MOD:amount-bill";
    }
    else {
        gotoxy(10, 1);
        cout << "REG_MOD:ON";
    }

    item::bill();
    gotoxy(23, l);
    cout << qty;
    gotoxy(33, l);
    cout << netamt;

}

bool empty(ifstream& pFile)
{
    return pFile.peek() == ifstream::traits_type::eof();
}

int main()
{
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout << setprecision(2);
    fstream tmp("temp.dat", ios::binary | ios::out);

menu:
    system("cls");
    if (a == 1) {
        gotoxy(10, 1);
        cout << "EDU_MOD:ON";
    }
    else {
        gotoxy(10, 1);
        cout << "REG_MOD:ON";
    }
    gotoxy(25, 2);
    cout << "Super Market Inventory Manage System ";
    gotoxy(25, 3);
    cout << "====================================\n\n";
    cout << "\n\t\t1.Select Mode\n\n";
    cout << "\t\t2.Inventory Report\n\n";
    cout << "\t\t3.Add/Remove/Edit Item\n\n";
    cout << "\t\t4.Show Item Details In Inventory\n\n";
    cout << "\t\t5.Generate Bill\n\n";
    cout << "\t\t6.Exit\n\n";
    cout << "\t\tPlease Enter Required Option: ";
    int ch, ff;
    float gtotal;
    cin >> ch;
    switch (ch)
    {
    case 1:
        system("cls");
        gotoxy(25, 2);
        cout << "Choose Mode";
        gotoxy(25, 3);
        cout << "=================\n\n";
        cout << "\n\t\t1.Education Mode\n\n";
        cout << "\t\t2.Regular Mode\n\n";
        cout << "\t\t3.Back to Main Menu ";
        int mod;
        cin >> mod;
        if (mod == 1) {
            a = 1;
            goto menu;
        }
        else if (mod == 2) {
            a = 0;
            goto menu;
        }
        else if (mod == 3) {
            goto menu;
        }

    case 2:
    ss:
        system("cls");
        if (a == 1) {
            gotoxy(10, 1);
            cout << "EDU_MOD:ON";
        }
        else {
            gotoxy(10, 1);
            cout << "REG_MOD:ON";
        }
        gotoxy(25, 2);
        cout << "Inventory Details";
        gotoxy(25, 3);
        cout << "================\n\n";
        cout << "\n\t\t1.All Items\n\n";
        cout << "\t\t2.Back to Main menu\n\n";
        cout << "\t\tPlease Enter Required Option: ";
        int cho;
        cin >> cho;
        if (cho == 1)
        {
            system("cls");
            if (a == 1) {
                gotoxy(10, 1);
                cout << "EDU_MOD:ON";
            }
            else {
                gotoxy(10, 1);
                cout << "REG_MOD:ON";
            }
            gotoxy(30, 3);
            cout << " INVENTORY DETAILS ";
            gotoxy(3, 5);
            cout << "ITEM NO";
            gotoxy(13, 5);
            cout << "NAME";
            gotoxy(23, 5);
            cout << "PRICE";
            gotoxy(33, 5);
            cout << "QUANTITY";
            gotoxy(44, 5);
            cout << "TAX %";
            gotoxy(52, 5);
            cout << "DISCOUNT %";
            gotoxy(64, 5);
            cout << "NET AMOUNT";
            fin.open("itemstore.dat", ios::binary);

            if (!fin)
            {
                cout << "\n\n\t\tInventory is empty add details...";
                cout << "\n\t\tReturning to main menu in 10s...";
                Sleep(10000);
                goto menu;
            }
            else if (empty(fin)) {

                cout << "\n\n\t\tInventory is empty add details...";
                cout << "\n\t\tReturning to main menu in 10s...";
                Sleep(10000);
                goto menu;
            }
            fin.seekg(0);
            gtotal = 0;
            while (!fin.eof())
            {
                fin.read((char*)&amt, sizeof(amt));
                if (!fin.eof())
                {
                    amt.report();
                    gtotal += amt.retnetamt();
                    ff = 0;
                }
                if (ff != 0) gtotal = 0;
            }
            gotoxy(17, k);
            cout << "\n\n\n\t\t\tGrand Total=" << gtotal;
            _getch();
            fin.close();
        }
        if (cho == 2)
        {
            goto menu;
        }
        goto ss;
    case 3:
    db:
        system("cls");
        if (a == 1) {
            gotoxy(10, 1);
            cout << "EDU_MOD:ON";
        }
        else {
            gotoxy(10, 1);
            cout << "REG_MOD:ON";
        }
        gotoxy(25, 2);
        cout << "Inventory Editor";
        gotoxy(25, 3);
        cout << "=================\n\n";
        cout << "\n\t\t1.Add Item Details\n\n";
        cout << "\t\t2.Edit Item Details\n\n";
        cout << "\t\t3.Delete Item Details\n\n";
        cout << "\t\t4.Back to Main Menu ";
        int apc;
        cin >> apc;
        switch (apc)
        {
        case 1:
            fout.open("itemstore.dat", ios::binary | ios::app);
            amt.add();
            //cout<<"\n\t\tItem Added Successfully!";
            _getch();
            goto db;

        case 2:
            int ino;
            flag = 0;
            cout << "\n\n\tEnter Item Number to be Edited :";
            cin >> ino;
            fin.open("itemstore.dat", ios::binary);
            fout.open("itemstore.dat", ios::binary | ios::app);
            if (!fin)
            {
                cout << "\n\n\t\tInventory is empty add details...";
                cout << "\n\t\tReturning to main menu in 10s...";
                Sleep(10000);
                goto menu;
            }
            else if (empty(fin)) {

                cout << "\n\n\t\tInventory is empty add details...";
                cout << "\n\t\tReturning to main menu in 10s...";
                Sleep(10000);
                goto menu;
            }
            fin.seekg(0);
            r = 0;
            while (!fin.eof())
            {
                fin.read((char*)&amt, sizeof(amt));
                if (!fin.eof())
                {
                    int x = amt.item::retno();
                    if (x == ino)
                    {
                        flag = 1;
                        fout.seekp(r * sizeof(amt));
                        system("cls");
                        gotoxy(25, 4);
                        cout << "\n\t\tCurrent Details are\n";
                        amt.show();
                        cout << "\n\n\t\tEnter New Details\n";
                        amt.add();
                        cout << "\n\t\tItem Details editted";
                    }
                }
                r++;
            }
            if (flag == 0)
            {
                cout << "\n\t\tItem No does not exist...Please Retry!";
                _getch();
                goto db;
            }
            fin.close();
            _getch();
            goto db;

        case 3:
            flag = 0;
            cout << "\n\n\tEnter Item Number to be deleted :";
            cin >> ino;
            fin.open("itemstore.dat", ios::binary);
            if (!fin)
            {
                cout << "\n\nFile Not Found...";
                goto menu;
            }
            //fstream tmp("temp.dat",ios::binary|ios::out);
            fin.seekg(0);
            while (fin.read((char*)&amt, sizeof(amt)))
            {
                int x = amt.item::retno();
                if (x != ino)
                    tmp.write((char*)&amt, sizeof(amt));
                else
                {
                    flag = 1;
                }
            }
            fin.close();
            tmp.close();
            fout.open("itemstore.dat", ios::trunc | ios::binary);
            fout.seekp(0);
            tmp.open("temp.dat", ios::binary | ios::in);
            if (!tmp)
            {
                cout << "Error in File";
                goto db;
            }
            while (tmp.read((char*)&amt, sizeof(amt)))
                fout.write((char*)&amt, sizeof(amt));
            tmp.close();
            fout.close();
            if (flag == 1)
                cout << "\n\t\tItem Succesfully Deleted";
            else if (flag == 0)
                cout << "\n\t\tItem does not Exist! Please Retry";
            _getch();
            goto db;
        case 4:
            goto menu;
        default:
            cout << "\n\n\t\tWrong Choice!!! Retry";
            _getch();
            goto db;
        }
    case 4:
        system("cls");
        if (a == 1) {
            gotoxy(10, 1);
            cout << "EDU_MOD:ON";
        }
        else {
            gotoxy(10, 1);
            cout << "REG_MOD:ON";
        }
        flag = 0;
        int ino;
        cout << "\n\n\t\tEnter Item Number :";
        cin >> ino;
        fin.open("itemstore.dat", ios::binary);
        if (!fin)
        {
            cout << "\n\n\t\tInventory is empty add details...";
            cout << "\n\t\tReturning to main menu in 10s...";
            Sleep(10000);
            goto menu;
        }
        else if (empty(fin)) {

            cout << "\n\n\t\tInventory is empty add details...";
            cout << "\n\t\tReturning to main menu in 10s...";
            Sleep(10000);
            goto menu;
        }
        fin.seekg(0);
        while (fin.read((char*)&amt, sizeof(amt)))
        {
            int x = amt.item::retno();
            if (x == ino)
            {
                amt.pay();
                flag = 1;
                break;
            }
        }
        if (flag == 0)
            cout << "\n\t\tItem does not exist....Please Retry!";
        _getch();
        fin.close();
        goto menu;
    case 5:
    bill:
        system("cls");
        if (a == 1) {
            gotoxy(10, 1);
            cout << "EDU_MOD:ON";
        }
        else {
            gotoxy(10, 1);
            cout << "REG_MOD:ON";
        }
        gotoxy(25, 2);
        cout << "Bill";
        gotoxy(25, 3);
        cout << "======\n\n";
        gotoxy(3, 5);
        cout << "ITEM NO";
        gotoxy(13, 5);
        cout << "NAME";
        gotoxy(23, 5);
        cout << "QUANTITY";
        gotoxy(33, 5);
        cout << "PRICE";


        int  sel;
        fin.open("itemstore.dat", ios::binary);
        fin.seekg(0);
        m = 0;
        l = 7;
        total = 0.0;
        while (!fin.eof())
        {
            fin.read((char*)&amt, sizeof(amt));
            if (!fin.eof())
            {
                int x = amt.item::retno();
                for (int i = 0; i <= n; i++) {
                    if (x == chf[i] && chf[i] > 0)
                    {
                        fout.seekp(m * sizeof(amt));
                        amt.bill();
                        total = total + amt.retnetamt();
                        l = l + 1;


                    }

                }


            }
            m++;
        }

        fin.close();
        gotoxy(17, l + 5);
        cout << "\n\t\t1.Add Item From Inventory\n\n";
        cout << "\t\t2.Generate Bill\n\n";
        cout << "\t\t3.Clear Bill\n\n";
        cout << "\t\t4.Back\n\n";
        cout << "\t\tPlease Enter Required Option: ";
        cin >> sel;
        if (sel == 1) {
            cout << "\n\t\tEnter Item NO:";
            cin >> chf[n];
            n++;
            goto bill;
        }
        else if (sel == 2) {
            gotoxy(33, l + 1);
            cout << "------------\r";
            gotoxy(33, l + 2);
            cout << total << "\r";
            gotoxy(33, l + 3);
            cout << "------------\r";
            stringstream stream;
            stream << bcount;
            string billd;
            stream >> billd;
            string billkey = "bill";
            string billamt = billkey.append(billd);
            billamt.append(".txt");
            ofstream bill(billamt);
            bill << "\t\t\t\t\tSuper Market bill\n";
            bill << "\t\t\t\t\t===========================\n\n";
            fin.open("itemstore.dat", ios::binary);
            fin.seekg(0);
            bill << "\t\tITEM NO" << "\t\t\tNAME" << "\t\t\tQUANTITY" << "\t\tPRICE\n\n";
            while (!fin.eof()) {
                fin.read((char*)&amt, sizeof(amt));
                int x = amt.item::retno();
                for (int i = 0; i <= n; i++) {
                    if (x == chf[i] && chf[i] > 0)
                    {

                        bill << "\t\t" << amt.retno() << "\t\t\t" << amt.retname() << "\t\t\t" << amt.retqty() << "\t\t\t" << amt.retnetamt() << "\n\n";


                    }
                }
            }
            bill << "\t\t******************************************************************************\n";
            bill << "\t\t\t\t\t\tTOTAL = Rs." << total << "\n\n";
            bill << "\t\t*********************************** THANKS ************************************";
            fin.close();
            bill.close();
            gotoxy(20, l + 17);
            cout << "\tWait A Second...Generating Bill..";
            Sleep(10000);
            goto clearb;


        }
        else if (sel == 3) {
        clearb:
            system("cls");
            //emptying array
            for (int i : chf) {
                chf[i] = 0;
            }
            n = 0;
            goto bill;
        }
        else if (sel = 4) {
            goto menu;
        }


    case 6:
        system("cls");
        gotoxy(25, 2);
        cout << "Super Market Inventory Manage System ";
        gotoxy(25, 3);
        cout << "====================================\n\n";
        gotoxy(20, 5);
        cout << "ARE YOU SURE, YOU WANT TO EXIT (Y/N)?";
        char yn;
        cin >> yn;
        if ((yn == 'Y') || (yn == 'y'))
        {
            gotoxy(12, 20);
            system("cls");
            gotoxy(25, 2);
            cout << "Super Market Inventory Manage System ";
            gotoxy(25, 3);
            cout << "====================================\n\n";
            gotoxy(20, 5);
            cout << "******************************** THANKS ***********************************";
            _getch();
            exit(0);
        }
        else if ((yn == 'N') || (yn == 'n'))
            goto menu;
        else
        {
            goto menu;
        }

    default:
        cout << "\n\n\t\tWrong Choice....Please Retry!";
        _getch();
        goto menu;
    }
    return 0;
}