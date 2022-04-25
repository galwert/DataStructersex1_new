

#ifndef WET1_NEW_HITECHS_H
#define WET1_NEW_HITECHS_H

#include "Library1.h"
#include "Company.h"
namespace Ehsan {
    class Hitechs {

    public:
        int num_of_employees;
        int num_of_companies_with_employees;
        BinarySearchTree<std::shared_ptr<Employee>,int> players_by_id;
        BinarySearchTree<std::shared_ptr<Employee>,IDSalary> employees_by_salary;
        BinarySearchTree<std::shared_ptr<Company>,int> companies;
        BinarySearchTree<std::shared_ptr<Company>,int> companies_with_employees;
        std::shared_ptr<Employee> highest_salary;
        Hitechs();
~Hitechs();
        StatusType AddCompany(int CompanyID, int Value);

        StatusType AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade);

        StatusType RemoveEmployee(int EmployeeID);

        StatusType RemoveCompany(int CompanyID);

        StatusType GetCompanyInfo(int CompanyID, int *Value, int *NumEmployees);

        StatusType GetEmployeeInfo(int EmployeeID, int *EmployerID, int *Salary, int *Grade);

        StatusType IncreaseCompanyValue(int CompanyID, int ValueIncrease);

        StatusType PromoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade);

        StatusType HireEmployee(int EmployeeID, int NewCompanyID);

        StatusType AcquireCompany(int AcquirerID, int TargetID, double Factor);

        StatusType GetHighestEarner(int CompanyID, int *EmployeeID);

        StatusType GetAllEmployeesBySalary(int CompanyID, int **Employees, int *NumOfEmployees);

        StatusType GetHighestEarnerInEachCompany(int NumOfCompanies, int **Employees);

        StatusType GetNumEmployeesMatching(int CompanyID, int MinEmployeeID, int MaxEmployeeId,
                                           int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees);
        void DeleteHitechs();
    };
}

#endif //WET1_NEW_HITECHS_H
