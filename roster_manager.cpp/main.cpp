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

int findStudentById(const Student roster[], int count, int targetId, int &comparisons) {
    comparisons = 0;

    for (int i = 0; i < count; i++) {
        comparisons++;

        if (roster[i].id == targetId) {
            return i;
        }
    }

    return -1;
}

bool addStudent(Student roster[], int &count, int id, const string &name) {

    if (count >= MAX_CAPACITY) {
        cout << "\nCannot add student. Roster is full (maximum of "
             << MAX_CAPACITY << " students).\n";
        return false;
    }

    int comparisons = 0;

    if (findStudentById(roster, count, id, comparisons) != -1) {
        cout << "\nCannot add student. ID " << id
             << " already exists.\n";
        return false;
    }

    roster[count].id = id;
    roster[count].name = name;
    count++;

    cout << "\nStudent added successfully.\n";
    cout << "ID: " << id << "\n";
    cout << "Name: " << name << "\n";

    return true;
}

bool removeStudentById(Student roster[], int &count, int targetId) {

    if (count == 0) {
        cout << "\nRoster is currently empty.\n";
        return false;
    }

    int comparisons = 0;
    int index = findStudentById(roster, count, targetId, comparisons);

    if (index == -1) {
        cout << "\nStudent with ID " << targetId
             << " was not found.\n";
        cout << "Comparisons performed: " << comparisons << "\n";
        return false;
    }

    for (int i = index; i < count - 1; i++) {
        roster[i] = roster[i + 1];
    }

    count--;

    cout << "\nStudent with ID " << targetId
         << " was removed successfully.\n";

    cout << "Comparisons performed: " << comparisons << "\n";

    return true;
}

bool safeGetRecord(const Student roster[], int count, int index, Student &outStudent) {

    if (index < 0 || index >= count) {
        return false;
    }

    outStudent = roster[index];

    return true;
}

void printRoster(const Student roster[], int count) {

    if (count == 0) {
        cout << "\nRoster is currently empty.\n";
        return;
    }

    cout << "\n=====================================================\n";
    cout << "                 STUDENT ROSTER\n";
    cout << "=====================================================\n";

    cout << left
         << setw(10) << "Index"
         << setw(15) << "Student ID"
         << setw(25) << "Name" << endl;

    cout << "-----------------------------------------------------\n";

    for (int i = 0; i < count; i++) {
        cout << left
             << setw(10) << i
             << setw(15) << roster[i].id
             << setw(25) << roster[i].name
             << endl;
    }

    cout << "-----------------------------------------------------\n";
    cout << "Total Students: " << count << "/" << MAX_CAPACITY << "\n";
    cout << "=====================================================\n";
}

int main() {

    Student roster[MAX_CAPACITY];
    int currentCount = 0;
    int choice = 0;

    do {

        cout << "\n=========================================\n";
        cout << "       NTC CC105: STUDENT ROSTER        \n";
        cout << "               MANAGER                 \n";
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

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "\nInvalid input. Please enter a number from 1 to 6.\n";
            continue;
        }

        switch (choice) {

            case 1: {
                int id;
                string name;

                cout << "\nEnter Student ID: ";
                cin >> id;

                cin.ignore(1000, '\n');

                cout << "Enter Student Name: ";
                getline(cin, name);

                if (name.empty()) {
                    cout << "\nStudent name cannot be empty.\n";
                    break;
                }

                addStudent(roster, currentCount, id, name);

                break;
            }

            case 2: {
                if (currentCount == 0) {
                    cout << "\nRoster is currently empty.\n";
                    break;
                }

                int targetId;
                int comparisons = 0;

                cout << "\nEnter Student ID to search: ";
                cin >> targetId;

                int index = findStudentById(
                    roster,
                    currentCount,
                    targetId,
                    comparisons
                );

                if (index != -1) {
                    cout << "\nStudent found!\n";
                    cout << "Array Index: " << index << "\n";
                    cout << "Student ID: " << roster[index].id << "\n";
                    cout << "Student Name: " << roster[index].name << "\n";
                }
                else {
                    cout << "\nStudent with ID " << targetId
                         << " was not found.\n";
                }

                cout << "Total comparisons: "
                     << comparisons << "\n";

                break;
            }

            case 3: {
                if (currentCount == 0) {
                    cout << "\nRoster is currently empty.\n";
                    break;
                }

                int targetId;

                cout << "\nEnter Student ID to remove: ";
                cin >> targetId;

                removeStudentById(
                    roster,
                    currentCount,
                    targetId
                );

                break;
            }

            case 4: {
                if (currentCount == 0) {
                    cout << "\nRoster is currently empty.\n";
                    break;
                }

                int index;
                Student result;

                cout << "\nEnter array index to inspect: ";
                cin >> index;

                if (safeGetRecord(
                        roster,
                        currentCount,
                        index,
                        result
                    )) {

                    cout << "\nRecord retrieved successfully.\n";
                    cout << "Index: " << index << "\n";
                    cout << "Student ID: " << result.id << "\n";
                    cout << "Student Name: " << result.name << "\n";

                }
                else {
                    cout << "\nInvalid index: " << index << "\n";
                    cout << "Safe retrieval prevented an "
                         << "out-of-bounds memory access.\n";
                    cout << "Valid indexes are from 0 to "
                         << currentCount - 1 << ".\n";
                }

                break;
            }

            case 5:
                printRoster(roster, currentCount);
                break;

            case 6:
                cout << "\nExiting system. Memory cleaned successfully.\n";
                break;

            default:
                cout << "\nInvalid selection. "
                     << "Please choose between 1 and 6.\n";
        }

    } while (choice != 6);
    return 0;
}

/*
PERFORMANCE REFLECTION

11. RANDOM ACCESS VS. LINEAR SEARCH
The safeGetRecord function is O(1) because it goes directly to the array index that the user gives.
It only needs one step to get the record. The findStudentById function is O(n) in the worst case
because it checks the students one by one until it finds the ID. If the ID is at the end or does
not exist, it may need to check all n students.

12. DELETION COST
Deleting a student at index 0 takes more work because all the students after it need to move one position
to the left. This makes the operation O(n). Deleting the student at index currentCount - 1 is easier because
it is already the last student, so no other students need to be moved. This makes the deletion O(1).
*/
