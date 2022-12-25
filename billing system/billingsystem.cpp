
#include "classes.h"
using namespace std;
int k = 7, r = 0, flag = 0;
COORD coord = { 0, 0 };


int main()
{
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout << setprecision(2);
    fstream tmp("temp.dat", ios::binary | ios::out);
menu:
    system("cls");
    gotoxy(25, 2);
    cout << "Super Market Billing ";
    gotoxy(25, 3);
    cout << "===========================\n\n";
    cout << "\n\t\t1.Bill Report\n\n";
    cout << "\t\t2.Add/Remove/Edit Item\n\n";
    cout << "\t\t3.Show Item Details\n\n";
    cout << "\t\t4.Exit\n\n";
    cout << "\t\t5.Select Mode\n\n";
    cout << "\t\tPlease Enter Required Option: ";
    int ch, ff;
    float gtotal;
    cin >> ch;
    switch (ch)
    {
    case 1:
    ss:
        system("cls");
        gotoxy(25, 2);
        cout << "Bill Details";
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
            gotoxy(30, 3);
            cout << " BILL DETAILS ";
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
                cout << "\n\nFile Not Found...";
                goto menu;
            }
            fin.seekg(0);
            gtotal = 0;
            while (!fin.eof())
            {
                fin.read((char*)&amt, sizeof(amt));
                if (!fin.eof())
                {
                    amt.report(k);
                    k = k + 1;
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
    case 2:
    db:
        system("cls");
        gotoxy(25, 2);
        cout << "Bill Editor";
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
            cout << "\n\t\tItem Added Successfully!";
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
                cout << "\n\nFile Not Found...";
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
    case 3:
        system("cls");
        flag = 0;
        int ino;
        cout << "\n\n\t\tEnter Item Number :";
        cin >> ino;
        fin.open("itemstore.dat", ios::binary);
        if (!fin)
        {
            cout << "\n\nFile Not Found...\nProgram Terminated!";
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
    case 4:
        system("cls");
        gotoxy(20, 20);
        cout << "ARE YOU SURE, YOU WANT TO EXIT (Y/N)?";
        char yn;
        cin >> yn;
        if ((yn == 'Y') || (yn == 'y'))
        {
            gotoxy(12, 20);
            system("cls");
            cout << "************************** THANKS **************************************";
            _getch();
            exit(0);
        }
        else if ((yn == 'N') || (yn == 'n'))
            goto menu;
        else
        {
            goto menu;
        }
    case 5:
        system("cls");
        gotoxy(25, 2);
        cout << "Choose Mode";
        gotoxy(25, 3);
        cout << "=================\n\n";
        cout << "\n\t\t1.Education Mode\n\n";
        cout << "\t\t2.Regular Mode\n\n";
        cout << "\t\t3.Back to Main Menu ";
        int Mod,a;
        cin >> Mod;
        switch (Mod) {
            case 1:
                 a = 1;
            case 2:
                 a = 0;
            case 3:
                goto menu;
            default:
                cout << "\n\n\t\tWrong Choice!!! Retry";
                _getch();
                goto db;

        }
    default:
        cout << "\n\n\t\tWrong Choice....Please Retry!";
        _getch();
        goto menu;
    }
    return 0;
}



