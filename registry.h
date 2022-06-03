#ifndef REGISTRY_H
#define REGISTRY_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>

#include "employee.h"

using namespace std;

typedef vector<Employee*> EmplVector;
typedef set<Employee*> EmplSet;
class Registry
{

    private:
        EmplVector _records;
        map<string, Employee*> _nameIndex;
        map<string, EmplVector> _deptIndex;
        map<string, EmplVector> _subordinatesIndex;
        map<int, EmplSet> _weekDaysIndex;

    public:
        Registry() {}

        Registry(const Registry* other)
        {
            for (const Employee* r : other->_records)
                updateIndices(new Employee(r));
        }

        ~Registry()
        {
            this->clearAll();
        }

        const EmplVector getStorage(int ageMin=0, int ageMax=INT_MAX) const
        {
            EmplVector result;

            for (Employee* r : this->_records)
            {
                if (r->getAge() >= ageMin && r->getAge() <= ageMax)
                    result.push_back(r);
            }

            return result;
        }

        void updateIndices(Employee* emp)
        {
            this->_records.push_back(emp);
            this->_nameIndex.insert({emp->getName(), emp});

            string dept = emp->getDepartment();

            if (this->_deptIndex.count(dept) > 0)
                this->_deptIndex[dept].push_back(emp);
            else
                this->_deptIndex.insert({dept, {emp}});

            string boss = emp->getBoss();

            if (boss.length())
            {
                if (this->_subordinatesIndex.count(boss) > 0)
                    this->_subordinatesIndex[boss].push_back(emp);
                else
                   this->_subordinatesIndex.insert({boss, {emp}});
            }

            for (int day : emp->getWorkingDays())
            {
                if (this->_weekDaysIndex.count(day) > 0)
                    this->_weekDaysIndex[day].insert(emp);
                else
                    this->_weekDaysIndex.insert({day, {emp}});
            }
        }

        void load(string pathToCsv)
        {
            string line;
            fstream file (pathToCsv, ios::in);

            this->_records.clear();

            if (file.is_open())
            {
                while (getline(file, line))
                    updateIndices(new Employee(line));
            }
            else
                cout<<"Could not open the file\n";
        }

        Employee* getByName(string name)
        {
            return this->_nameIndex[name];
        }

        const EmplVector getByDepartment(string dept)
        {
            return this->_deptIndex[dept];
        }

        const EmplVector getSubordinates(string boss)
        {
            return this->_subordinatesIndex[boss];
        }

        EmplSet getEmployeesByWeekDays(set<int> days)
        {
            EmplSet result = {};

            for (const int day : days)
                result.insert(this->_weekDaysIndex[day].begin(), this->_weekDaysIndex[day].end());

            return result;
        }

        void clearAll()
        {
            for (const Employee* r : this->_records)
                delete r;

            this->_records.clear();
            this->_nameIndex.clear();
            this->_deptIndex.clear();
            this->_subordinatesIndex.clear();
        }
};

#endif // REGISTRY_H
