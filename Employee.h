
#ifndef WET1_NEW_EMPLOYEE_H
#define WET1_NEW_EMPLOYEE_H
#include "BinarySearchTree.h"
#include <memory>
#include <algorithm>
#include <iostream>

namespace Ehsan {

    class IDSalary
    {
    public:
        int salary;
        int ID;
        IDSalary()=default;
        explicit IDSalary(int salary,int id):
                salary(salary),
                ID(id)
        {}
        bool operator==(const IDSalary& other)const
        {
            return( (this->ID == other.ID) && (this->salary == other.salary) );
        }
        bool operator!=(const IDSalary& other)const
        {
            return( !( (*this) == other) );
        }
        bool operator<(const IDSalary& other) const
        {
            if(this->salary != other.salary)
            {
                return ( this->salary < other.salary );
            }
            return (this->ID > other.ID);
        }
        bool operator>=(const IDSalary& other) const
        {
            return (!( (*this) < other));
        }
        bool operator>(const IDSalary& other) const
        {
            return ( ( (*this) >= other ) &&  !( (*this) == other )  );
        }
        bool operator<=(const IDSalary& other) const
        {
            return (!( (*this) > other));
        }
        friend std::ostream& operator<<(std::ostream& os, const IDSalary& IDSalary);
    };

    class Employee {
    public:

        int employee_id;
        int employee_salary;
        int company_id;
        int rank;

        Employee(int employee_id, int company_id,int employee_salary, int rank):
                employee_id(employee_id),
                employee_salary(employee_salary),
                company_id(company_id),
                rank(rank)
        {}
        Employee(const Employee& copy) = default;
        Employee& operator=(const Employee& copy) = default;
        ~Employee() = default;
    };



}
#endif //WET1_NEW_EMPLOYEE_H
