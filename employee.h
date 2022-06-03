#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

map<string, int> weekDays = {
    { "Mon", 1 },
    { "Tue", 2 },
    { "Wed", 3 },
    { "Thu", 4 },
    { "Fri", 5 },
    { "Sat", 6 },
    { "Sun", 7 }
};

class Employee
{
    private:
        string _name;
        int _age;
        string _department;
        string _position;
        string _bossName;
        vector<int> _workingDays;

   public:
        Employee(const string row)
        {
            string attr;
            stringstream str(row);

            int count = 0;

            while (getline(str, attr, '\t'))
            {
                switch (count)
                {
                    case 0:
                        this->_name = attr;
                        break;
                    case 1:
                        this->_age = stoi(attr);
                        break;
                    case 2:
                        this->_department = attr;
                        break;
                    case 3:
                        this->_position = attr;
                        break;
                    case 4:
                        this->_bossName = attr;
                        break;
                    default:
                        this->_workingDays.push_back(weekDays[attr]);
                }

                ++count;
            }
        }

        Employee(const Employee* other)
        {
            this->_name = other->getName();
            this->_age = other->getAge();
            this->_department = other->getDepartment();
            this->_position = other->getPosition();
            this->_bossName = other->getBoss();
            this->_workingDays = other->getWorkingDays();
        }

        string getName() const { return _name; }
        int getAge() const { return _age; }
        string getDepartment() const { return _department; }
        string getPosition() const { return _position; }
        string getBoss() const { return _bossName; }
        vector<int> getWorkingDays() const { return _workingDays; }
};

ostream& operator<<(ostream& os, Employee* r)
{
    os << "Name: " << r->getName() << ",\tage: " << r->getAge() << ",\tdept: " <<
    r->getDepartment() << ",\tposition: " << r->getPosition() << ",\tboss: " << r->getBoss();

    return os;
}

#endif // RECORD_H
