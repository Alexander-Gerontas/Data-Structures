/// Γέροντας Αλέξανδρος - 321/2015029

#include <iostream>
#include <fstream>

using namespace std;

struct DataItem /// Δομή για την αποθήκευση των στοιχείων του χρήστη.
{
    string username,password;
    DataItem *next = NULL;

    DataItem(string username,string password)
    {
        this->username = username;
        this->password = password;
    }
};

class hashArray
{
private:
    int size;
    DataItem **hashArr;

public:
    hashArray(int size) /// Αρχικοποιήση του Λεξικού.
    {
        this->size = size;
        hashArr = new DataItem*[size];

        for (int i=0; i<size; i++) hashArr[i] = NULL;
    }

    void initializeHashTable() /// Διάβασμα αρχείου και πέρασμα τιμών στο Λεξικό.
    {
        string username,password;
        ifstream file ("passwords.dat");

        while (!file.eof())
        {
            file >> username >> password;
            insert(username,password);
        }
    }

    int hash(string username) /// Δημιουργία κλειδιού με βασή τον αριθμό ASCII κάθε χαρακτήρα.
    {
        int sum = 0;

        for (int i = 0; i < username.length(); i++)
            sum += username.at(i);

        return sum % size;
    }

    void insert(string username,string password) /// Εισαγωγή του χρήστη.
    {
        DataItem *temp = hashArr[hash(username)];
        hashArr[hash(username)] = new DataItem(username,password); /// O χρήστης εισάγεται στην πρώτη θέση της λίστας.
        if (hashArr[hash(username)] != NULL) hashArr[hash(username)]->next = temp; /// Διασύνδεση με τα υπολοιπα στοιχεια της λίστας.
    }

    void print() /// Tύπωση όλου του λεξικού.
    {
        DataItem *dataTemp;
        int count = 0;

        for (int i = 0; i < size; i++)
        {
            dataTemp = hashArr[i];

            while (dataTemp != NULL)
            {
                cout << ++count << ". " << dataTemp->username << " " << dataTemp->password << endl;
                dataTemp = dataTemp->next;
            }
        }
    }

    DataItem* search(string username) /// Επιστρέφει τον χρήστη με κλειδί το username του, εάν υπάρχει, διαφορετικά επιστρέφει null.
    {
        DataItem *dataTemp = hashArr[hash(username) % size];

        while ( dataTemp != NULL) /// Διάσχιση λίστας μέχρι να βρεθεί το στοιχείο
        {
            if (dataTemp->username == username) return dataTemp;
            dataTemp = dataTemp->next;
        }

        return NULL; /// Αν δεν βρεθεί το στοιχείο επιστέφει NULL
    }
};

int main()
{
    hashArray *h = new hashArray(5);
    DataItem *user;
    string username,password,choice = "y";

    h->initializeHashTable();
    h->print();

    while (choice == "y") /// Αυθεντικοποίηση χρηστών.
    {
        cout << "Enter Login Name : ";
        cin >> username;

        cout << "Enter Password : ";
        cin >> password;

        user = h->search(username);

        if ( user == NULL ) cout << "Unknown User Name\n";
        else if ( user->username == username && user->password == password ) cout << "Authentication Successful\n";
        else cout << "Authentication Fail\n";

        cout << "Do you want to continue (y/n) ? ";
        cin >> choice;
    }

    return 0;
}
