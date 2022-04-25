

#include "Company.h"

namespace Ehsan
{

    Company::Company(int company_id, int company_value):
            company_id(company_id),
            num_of_employee(0),
            employees_by_rank(),
            highest_salary(nullptr),
            company_value(company_value)
    {}

    void Company::HireEmployee(const std::shared_ptr<Employee>& employee) {
        this->employees_by_rank.insert(IDSalary(employee->employee_salary, employee->employee_id), employee);
        (this->num_of_employee)++;
        if ((this->highest_salary) == nullptr) {
            this->highest_salary = employee;
            return;
        }
        if ((this->highest_salary->employee_salary) < (employee->employee_salary)) {
            this->highest_salary = employee;
            return;
        }
        if ((this->highest_salary->employee_salary) == (employee->employee_salary) &&
            (this->highest_salary->employee_id) > (employee->employee_id)) {
            this->highest_salary = employee;
            return;

        }
    }
    void Company::GetCompanyInfo(int *Value, int *NumEmployees)
    {
        *Value=this->company_value;
        *NumEmployees=this->num_of_employee;
    }
    void Company::IncreaseCompanyValue(int ValueIncrease)
    {
        this->company_value+=ValueIncrease;
    }
    void Company::RemoveEmployee(int employee_salary,int employee_id)
    {
        (this->num_of_employee)--;
        this->employees_by_rank.remove(IDSalary(employee_salary,employee_id));
        if( (this->highest_salary->employee_id) == employee_id)
        {
            BSTNode<std::shared_ptr<Employee>,IDSalary> *maxnode = this->employees_by_rank.getMaxNode();
            if (maxnode != nullptr)
            {
                this->highest_salary = maxnode->data;
            }
            else
            {
                this->highest_salary = nullptr;
            }
        }

    }

    void Company::UpdateHighestSalaryBeforeGroupReplacement(const std::shared_ptr<Company>& replacement)
    {
        if(this->highest_salary== nullptr)
        {
            return;
        }
        if( (replacement->highest_salary) == nullptr )
        {
            replacement->highest_salary = this->highest_salary;
            return;
        }
        if( (this->highest_salary->employee_salary) > (replacement->highest_salary->employee_salary) )
        {
            replacement->highest_salary = this->highest_salary;
            return;
        }
        if ( ((this->highest_salary->employee_salary) == (replacement->highest_salary->employee_salary))
             && (((this->highest_salary->employee_id) < (replacement->highest_salary->employee_id))) )
        {
            replacement->highest_salary = this->highest_salary;
        }
    }

    void Company::AcquireCompany(std::shared_ptr<Company>& replacement, double factor)
    {
        this->UpdateHighestSalaryBeforeGroupReplacement(replacement);
        (replacement->num_of_employee) += (this->num_of_employee);
        updatePlayersGroupID(this->employees_by_rank.root,replacement->company_id);
        this->employees_by_rank.uniteTrees(replacement->employees_by_rank);
        replacement->company_value=(int)((this->company_value+replacement->company_value)*factor);
    }

    void Company::IncreaseSalary (int employee_salary, int employee_id, int SalaryIncrease, int BumpGrade)
    {
        std::shared_ptr<Employee> employee = this->employees_by_rank.find(IDSalary(employee_salary,employee_id))->data;//this player should definitely exist
        int newsalary = SalaryIncrease + (employee->employee_salary);
        this->employees_by_rank.remove(IDSalary(employee->employee_salary,employee_id));
        this->employees_by_rank.insert(IDSalary( newsalary,employee_salary),employee);
        // player->playerlevel = newlevel; this addition is done in SquidGame
        if( newsalary > (this->highest_salary->employee_salary) )
        {
            this->highest_salary = employee;
        }
        if( newsalary == this->highest_salary->employee_salary && (employee->employee_id) < (this->highest_salary->employee_id) )
        {
            this->highest_salary = employee;
        }
    }

    void Company::GetHighestSalary(int *EmployeeID)
    {
        (*EmployeeID) = this->highest_salary->employee_id;
    }
    void Company::GetAllEmployeesBySalary (int **Employees_array, int *numOfEmployees)
    {
        *Employees_array = (int*)malloc(sizeof(int) *(*numOfEmployees));
        fillArrayWithIdsInAscendingOrder(*Employees_array,numOfEmployees, this->employees_by_rank.root );
    }

    void Company::fillArrayWithIdsInAscendingOrder(int *array,int* numOfPlayers, BSTNode<std::shared_ptr<Employee>,IDSalary> *node)
    {
        //I'm assuming there's enough room for every player.
        //It is the responsibility of the calling function to make that there's enough room for each player.
        if (node == nullptr||*numOfPlayers==0)
        {
            return;
        }
        fillArrayWithIdsInAscendingOrder(array,numOfPlayers,node->right);
        if(*numOfPlayers==0)
        {
            return;
        }
        array[*numOfPlayers] = (node->data->employee_id);
        (*numOfPlayers)--;
        fillArrayWithIdsInAscendingOrder(array,numOfPlayers,node->left);
    }
}