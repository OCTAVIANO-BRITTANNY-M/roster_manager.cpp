
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int MAX_CAPACITY = 50;

struct Student {
    int id;
    string name;
};

int findStudentById(const Student roster[], int count, int targetId, int &comparisons);
bool addStudent(Student roster[], int &count, int id, const string &name);
bool removeStudentById(Student roster[], int &count, int targetId);
bool safeGetRecord(const Student roster[], int count, int index, Student &outStudent);
void printRoster(const Student roster[], int count);

int main() {

    Student roster[MAX_CAPACITY];
    int currentCount = 0;
    int choice = 0;

    do {

        cout << "\n=========================================\n";
        cout << "       NTC CC105: STUDENT ROSTER        \n";
        cout << "               MANAGER                  \n";
        cout << "=========================================\n";
        cout << "1. Add Student Record\n";
        cout << "2. Search Student by ID\n";
        cout << "3. Remove Student by ID\n";
        cout << "4. Safe Inspect Record by Index\n";
        cout << "5. Display Full Roster\n";
        cout << "6. Exit\n";
        cout << "=========================================\n";
        cout << "Enter selection [1-6]: ";

        cin >> choice;

        switch (choice) {

            case 1:
                cout << "\nAdd Student Record selected.\n";
                break;

            case 2:
                cout << "\nSearch Student by ID selected.\n";
                break;

            case 3:
                cout << "\nRemove Student by ID selected.\n";
                break;

            case 4:
                cout << "\nSafe Inspect Record by Index selected.\n";
                break;

            case 5:
                cout << "\nDisplay Full Roster selected.\n";
                break;

            case 6:
                cout << "\nExiting system.\n";
                break;

            default:
                cout << "\nInvalid selection. Please choose between 1 and 6.\n";
        }

    } while (choice != 6);

    return 0;
}

