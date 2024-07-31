// Personal Project Manager

#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class Contact
{
    int id;
    char name[40];
    char email[40];
    char mobile[12];
    char fbID[40];
    char city[100];

public:
    Contact()
    {
    }
    Contact(int cid, const char *cname, const char *cemail, const char *cmobile, const char *cfbID, const char *ccity)
    {
        id = cid;
        strcpy(mobile, cmobile);
        strcpy(name, cname);
        strcpy(fbID, cfbID);
        strcpy(email, cemail);
        strcpy(city, ccity);
    }

    void disp()
    {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "email: " << email << endl;
        cout << "Mobile: " << mobile << endl;
        cout << "Facebook ID: " << fbID << endl;
        cout << "City: " << city << endl;
        cout << "\n";
    }
    friend void search(int id);
    friend void deleteRecord(int id);
};

void addContact(Contact c)
{
    ofstream fout("contacts.dat", ios::app);
    fout.write((char *)&c, sizeof(c));
    fout.close();
    cout << "Contact Added sucessfully" << endl;
}

void dispAll()
{
    Contact temp;
    ifstream fin("contacts.dat");
    while (1)
    {
        fin.read((char *)&temp, sizeof(temp));
        if (fin.eof())
        {
            break;
        }
        else
        {
            temp.disp();
        }
    }
}

void search(int id)
{
    ifstream fin("contacts.dat");
    Contact temp;
    while (1)
    {
        fin.read((char *)&temp, sizeof(temp));
        if (fin.eof() == true)
        {
            break;
        }
        if (temp.id == id)
        {
            cout << "Record Found" << endl;
            temp.disp();
        }
    }
}

void deleteRecord(int id)
{
    ifstream fin("contacts.dat");
    ofstream fout("temp.dat");

    Contact obj;

    while (1)
    {
        fin.read((char *)&obj, sizeof(obj));
        if (fin.eof())
        {
            break;
        }
        else
        {
            if (obj.id != id)
            {
                fout.write((char *)&obj, sizeof(obj));
            }
        }
    }
    fin.close();
    fout.close();
    remove("contacts.dat");
    rename("temp.dat", "contacts.dat");
}

int main()
{
    Contact c1(1, "Ajay", "ajay@gmail.com", "9225875637", "fb.com/abk", "kolhapur");

    while (1)
    {
        int ch;
        cout << "Select choice:" << endl;
        cout << "1. Add Contact 2. Display All 3. Search Contact 4. Delete Contact 5. Exit" << endl;
        cin >> ch;

        switch (ch)
        {
        case 1:
        {
            int id;
            char name[50], email[50], phone[12], fb[50], city[50];
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Email: ";
            cin >> email;
            cout << "Enter phone: ";
            cin >> phone;
            cout << "Enter fbId: ";
            cin >> fb;
            cout << "Enter city: ";
            cin >> city;
            Contact c1(id, name, email, phone, fb, city);
            addContact(c1);
        }
        break;

        case 2:
        {
            dispAll();
        }
        break;

        case 3:
        {
            int id;
            cout << "Enter the id Searched for: ";
            cin >> id;
            search(id);
        }
        break;

        case 4:
        {
            int id;
            cout << "Enter the id to be deleted: ";
            cin >> id;
            deleteRecord(id);
        }
        break;
        case 5:
        {
            exit(0);
        }
        }
    }
}
