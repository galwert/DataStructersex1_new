//
// Created by galwe on 24/11/2021.
//

#ifndef WET1_NEW_GROUP_H
#define WET1_NEW_GROUP_H
#include "Employee.h"
#include "BinarySearchTree.h"
#include <memory>
#include <iostream>


namespace Ehsan {
    class Company {

    public:
        int company_id;
        int num_of_employee;
        BinarySearchTree<std::shared_ptr<Employee>,IDSalary> employees_by_rank;
        std::shared_ptr<Employee> highest_salary;
        int company_value;


        explicit Company(int company_id, int company_value);
        ~Company()=default;

        void HireEmployee(const std::shared_ptr<Employee>& employee);
        void RemoveEmployee(int employee_salary,int employee_id);
        void AcquireCompany(std::shared_ptr<Company>& replacement, double factor);
        void IncreaseSalary (int employee_salary, int employee_id, int SalaryIncrease, int BumpGrade);
        void GetHighestSalary(int *EmployeeID);
        void GetAllEmployeesBySalary (int **Employees_array, int *numOfEmployees);
        void fillArrayWithIdsInAscendingOrder(int *array,int* numOfPlayers, BSTNode<std::shared_ptr<Employee>,IDSalary> *node);
        void GetCompanyInfo(int *Value, int *NumEmployees);
        void IncreaseCompanyValue(int ValueIncrease);
        static void updatePlayersGroupID(BSTNode<std::shared_ptr<Employee>,IDSalary> *node,int newcompanyid)
        {
            if (node == nullptr)
            {
                return;
            }
            updatePlayersGroupID(node->left,newcompanyid);
            node->data->company_id = newcompanyid;
            updatePlayersGroupID(node->right,newcompanyid);
        }
        void UpdateHighestSalaryBeforeGroupReplacement(const std::shared_ptr<Company>& replacement);
    };
}
#endif //WET1_NEW_GROUP_H
