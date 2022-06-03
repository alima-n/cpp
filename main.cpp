#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>

#include "employee.h"
#include "registry.h"

using namespace std;

int main()
{
    Registry* reg = new Registry();
    char action;

    cout << "\n\nEmployee database\n=================\n";
    cout << "(L) Load a file" << endl;
    cout << "(C) Clear a dataset" << endl;
    cout << "(N) Print number of records in a dataset" << endl;
    cout << "(P) Print all records" << endl;
    cout << "(E) Print an employee by their name" << endl;
    cout << "(A) Print all employees with an age in a given range" << endl;
    cout << "(D) Print all employees of a department" << endl;
    cout << "(S) Print all subordinates of a boss" << endl;
    cout << "(W) Print employees working on certain weekdays" << endl;
    cout << "...\n(X) Exit\n\n";

    do
    {
        cout << "Choose an action: ";
        cin >> action;

        if (toupper(action) == 'X')
        {
            cin.clear();
            delete reg;
            break;
        }

        switch (toupper(action)) {
        case 'L': {
            string path;
            cout << "Provide path to a file: ";
            cin >> path;
            reg->load(path);
            cout << "Successfully loaded dataset." << endl;
            break;
        }
        case 'C': {
            reg->clearAll();
            break;
        }
        case 'N': {
            cout << reg->getStorage().size() << endl;
            break;
        }
        case 'P': {
            for (Employee* emp : reg->getStorage())
                cout << emp << endl;
            break;
        }
        case 'E': {
            string name, lastName;

            cout << "Type an employee's full name: ";
            cin >> name >> lastName;
            cout << reg->getByName(name + ' ' + lastName) << endl;
            break;
        }
        case 'A': {
            int min, max;
            cout << "Type age interval separated with space: ";
            cin >> min >> max;

            for (Employee* emp : reg->getStorage(min, max))
                cout << emp << endl;
            break;
        }
        case 'D': {
            string dept;
            cout << "Type department acronym (acc | it | office | crm): ";
            cin >> dept;

            for (Employee* emp : reg->getByDepartment(dept))
                cout << emp << endl;
            break;
        }

        case 'S': {
            string name, lastName;
            cout << "Type a boss full name: ";
            cin >> name >> lastName;

            for (Employee* emp : reg->getSubordinates(name + ' ' + lastName))
                cout << emp << endl;
            break;
        }

        case 'W': {
            set<int> days;
            string day;
            cout << "Type a weekdays acronyms space separated (Mon | Tue | Wed): ";

            while (true) {
                cin >> day;
                days.insert(weekDays[day]);

                if (cin.peek() == '\n')
                    break;
            }

            for (Employee* emp : reg->getEmployeesByWeekDays(days))
                cout << emp << endl;

            break;
        }
        }
    }
    while (true);

    return 0;
}
