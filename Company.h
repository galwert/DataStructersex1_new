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
        BinarySearchTree<std::shared_ptr<Employee>,IDSalary> employees_by_salary;
        BinarySearchTree<std::shared_ptr<Employee>,int> employees_by_id;
        std::shared_ptr<Employee> highest_salary;
        int company_value;


        explicit Company(int company_id, int company_value);
        ~Company();

        void HireEmployee(const std::shared_ptr<Employee>& employee);
        void RemoveEmployee(int employee_salary,int employee_id);
        void AcquireCompany(std::shared_ptr<Company>& replacement, double factor);
        void IncreaseSalary (int employee_salary, int employee_id, int SalaryIncrease);

        void fillArrayWithIdsInAscendingOrder(int *array,int* numOfPlayers, BSTNode<std::shared_ptr<Employee>,IDSalary> *node);

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
