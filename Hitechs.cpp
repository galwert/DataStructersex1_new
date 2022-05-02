#include "Hitechs.h"

#include <memory>

namespace Ehsan {

	Hitechs::Hitechs():
		num_of_employees(0),
		num_of_companies_with_employees(0),
		 employees(),
		employees_by_salary(),
		 companies(),
		 companies_with_employees()
        {
         highest_salary = nullptr;
	}

	StatusType Hitechs::AddCompany(int CompanyID, int Value)
	{
		if (CompanyID <= 0 || Value <= 0)
		{
			return INVALID_INPUT;
		}

		if (companies.find(CompanyID) != nullptr)
		{
			return FAILURE;
		}

		std::shared_ptr<Company> company = std::make_shared<Company>(CompanyID, Value);
		companies.insert(CompanyID, company);

		return SUCCESS;
	}

	StatusType Hitechs::AddEmployee(int EmployeeID, int CompanyID, int Salary, int Grade)
	{
		if (CompanyID <= 0 || EmployeeID <= 0 || Salary <= 0 || Grade < 0)
		{
			return INVALID_INPUT;
		}

		IDSalary idSalary = IDSalary(Salary, EmployeeID);
		if (companies.find(CompanyID) == nullptr || employees.find(EmployeeID) != nullptr)
		{
			return FAILURE;
		}

		std::shared_ptr<Company> company = companies.find(CompanyID)->data;
		std::shared_ptr<Employee> newEmployee = std::make_shared<Employee>(EmployeeID, CompanyID, Salary, Grade);


		if (company->num_of_employee == 0)  //Checks if the company has no employees
		{
			num_of_companies_with_employees++;
			companies_with_employees.insert(CompanyID, company);
		}

		num_of_employees++;		//Updates the trees
        company->num_of_employee++;
		company->HireEmployee(newEmployee);
		employees.insert(EmployeeID, newEmployee);
		employees_by_salary.insert(idSalary, newEmployee);

		if (num_of_employees==1||newEmployee->employee_salary > highest_salary->employee_salary ||
        (newEmployee->employee_salary == highest_salary->employee_salary && newEmployee->employee_id < highest_salary->employee_id)) //New highest earner
		{
			highest_salary = newEmployee;
		}

		return SUCCESS;
	}

	StatusType Hitechs::RemoveEmployee(int EmployeeID)
	{
		if (EmployeeID <= 0)
		{
			return INVALID_INPUT;
		}

		if (employees.find(EmployeeID) == nullptr) //Checks if employee exists
		{
			return FAILURE;
		}

		std::shared_ptr<Employee> employeeToRemove = employees.find(EmployeeID)->data;
		IDSalary idSalary( employeeToRemove->employee_salary, EmployeeID);

		std::shared_ptr<Company> company = companies.find(employeeToRemove->company_id)->data;




		company->num_of_employee--;
        this->num_of_employees--;
        company->RemoveEmployee(idSalary.salary,idSalary.ID);

		employees.remove(EmployeeID);     //Removing from employees trees
		employees_by_salary.remove(idSalary);
        if ((this->highest_salary->employee_id) == EmployeeID) {
            BSTNode<std::shared_ptr<Employee>, IDSalary> *maxnode = this->employees_by_salary.getMaxNode();
            if (maxnode != nullptr) {
                this->highest_salary = maxnode->data;
            } else {
                this->highest_salary = nullptr;
            }

        }
		//if the company has no employees
		if (company->num_of_employee == 0)
		{
			companies_with_employees.remove(company->company_id);
		}

		return SUCCESS;
	}

	StatusType Hitechs::RemoveCompany(int CompanyID)
	{
		if (CompanyID <= 0)
		{
			return INVALID_INPUT;
		}

		if (companies.find(CompanyID) == nullptr)
		{
			return FAILURE;
		}

		std::shared_ptr<Company> company = companies.find(CompanyID)->data;
		if (company->num_of_employee > 0)
		{
			return FAILURE;
		}

		companies.remove(CompanyID);
        return SUCCESS;
	}

	StatusType Hitechs::GetCompanyInfo(int CompanyID, int* Value, int* NumEmployees)
	{
		if (CompanyID <= 0 || Value == nullptr || NumEmployees == nullptr)
		{
			return INVALID_INPUT;
		}

		if (companies.find(CompanyID) == nullptr)
		{
			return FAILURE;
		}

		std::shared_ptr<Company> company = companies.find(CompanyID)->data;

		*Value = company->company_value;
		*NumEmployees = company->num_of_employee;;

		return SUCCESS;
	}

	StatusType Hitechs::GetEmployeeInfo(int EmployeeID, int* EmployerID, int* Salary, int* Grade)
	{
		if (EmployeeID <= 0 || EmployerID == nullptr || Salary == nullptr || Grade == nullptr)
		{
			return INVALID_INPUT;
		}

		if (employees.find(EmployeeID) == nullptr)
		{
			return FAILURE;
		}

		std::shared_ptr<Employee> employee = employees.find(EmployeeID)->data;

		*EmployerID = employee->company_id;
		*Salary = employee->employee_salary;
		*Grade = employee->rank;

		return SUCCESS;
	}

	StatusType Hitechs::IncreaseCompanyValue(int CompanyID, int ValueIncrease)
	{
		if (CompanyID <= 0 || ValueIncrease <= 0)
		{
			return INVALID_INPUT;
		}

		if (companies.find(CompanyID) == nullptr)
		{
			return FAILURE;
		}
		companies.find(CompanyID)->data->IncreaseCompanyValue(ValueIncrease);
		return SUCCESS;
	}

	StatusType Hitechs::PromoteEmployee(int EmployeeID, int SalaryIncrease, int BumpGrade)
	{
		if (EmployeeID <= 0 || SalaryIncrease <= 0)
		{
			return INVALID_INPUT;
		}

		if (employees.find(EmployeeID) == nullptr)
		{
			return FAILURE;
		}

		std::shared_ptr<Employee> employee = employees.find(EmployeeID)->data;
        if (companies.find(employee->company_id) == nullptr)
        {
            return FAILURE;
        }
        int newsalary = SalaryIncrease + (employee->employee_salary);
        std::shared_ptr<Company> company = companies.find(employee->company_id)->data;
		company->IncreaseSalary(employee->employee_salary, EmployeeID, SalaryIncrease);
        this->employees_by_salary.remove(IDSalary(employee->employee_salary,EmployeeID));
        this->employees_by_salary.insert(IDSalary( newsalary,EmployeeID),employee);
        employee->employee_salary=newsalary;
        if( newsalary > (this->highest_salary->employee_salary) )
        {
            this->highest_salary = employee;
        }
        if( newsalary == this->highest_salary->employee_salary && (employee->employee_id) < (this->highest_salary->employee_id) )
        {
            this->highest_salary = employee;
        }
        if(BumpGrade>0)
        {
            employee->rank++;
        }
		return SUCCESS;
	}

	StatusType Hitechs::HireEmployee(int EmployeeID, int NewCompanyID)
	{
		if (EmployeeID <= 0 || NewCompanyID <= 0)
		{
			return INVALID_INPUT;
		}

		if (companies.find(NewCompanyID) == nullptr || employees.find(EmployeeID) == nullptr)
		{
			return FAILURE;
		}

		std::shared_ptr<Employee> employee = employees.find(EmployeeID)->data;
		if (employee->company_id == NewCompanyID)
		{
			return FAILURE;
		}
		RemoveEmployee(EmployeeID);
        return AddEmployee(EmployeeID, NewCompanyID, employee->employee_salary, employee->rank);
	}

    void Hitechs::fillArrayWithIdsInDescendingOrder(int *array,int *index,int max, BSTNode<std::shared_ptr<Employee>,IDSalary> *node)
    {

        if (node == nullptr||(*index)==max)
        {
            return;
        }
        fillArrayWithIdsInDescendingOrder(array,index,max,node->right);
        if((*index)==max)
        {
            return;
        }
        array[*index] = (node->data->employee_id);
        (*index)++;
        fillArrayWithIdsInDescendingOrder(array,index,max,node->left);
    }

StatusType Ehsan::Hitechs::GetAllEmployeesBySalary(int CompanyID, int **Employees, int *NumOfEmployees) {

    if( CompanyID == 0 || Employees == nullptr || NumOfEmployees == nullptr )
    {
        return INVALID_INPUT;
    }

    try{
        int* index = new int();
        if (CompanyID < 0 )
        {
            if (this->num_of_employees == 0)
            {
                *(NumOfEmployees) = 0;
                *Employees = nullptr;
                return FAILURE;
            }
            else
            {
                *(NumOfEmployees) = this->num_of_employees;
                int* myarray=((int*)malloc(sizeof(int)* (this->num_of_employees)));
                if(myarray== nullptr)
                {
                    throw std::bad_alloc();
                }
                fillArrayWithIdsInDescendingOrder(myarray,index,this->num_of_employees,this->employees_by_salary.root);
                *Employees=myarray;
            }
            delete index;
            return SUCCESS;
        }
        else
        {
            BSTNode<std::shared_ptr<Company>,int> *group_to_find_node = this->companies.find(CompanyID);//find should be in BST
            if (group_to_find_node == nullptr )
            {
                //a group with this identifier doesn't exist
                delete index;
                return FAILURE;
            }
            std::shared_ptr<Company> group_to_find = group_to_find_node->data;
            if (group_to_find->num_of_employee <= 0)
            {
                *(NumOfEmployees) = 0;
                *Employees = nullptr;
                return FAILURE;
            }
            else
            {
                *(NumOfEmployees) = group_to_find->num_of_employee;
                int* myarray=(int*)malloc(sizeof(int)* (*NumOfEmployees));
                if(myarray== nullptr)
                {
                    throw std::bad_alloc();
                }
                fillArrayWithIdsInDescendingOrder(myarray,index,group_to_find->num_of_employee,group_to_find->employees_by_salary.root);
                *Employees=myarray;
            }
        }
        delete index;
    }catch(const std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

    StatusType Hitechs::GetHighestEarnerInEachCompany(int NumOfCompanies, int **Employees) {
        if ( (Employees == nullptr) || (NumOfCompanies < 1) )
        {
            return INVALID_INPUT;
        }

        if ( NumOfCompanies > (this->num_of_companies_with_employees) )
        {
            return FAILURE;
        }
        try{
            int *index = new int();
            int* myarray=(int*)malloc( sizeof(int) * (NumOfCompanies));
            if(myarray== nullptr)
            {
                delete index;
                throw std::bad_alloc();
            }
            fillArrayWithHighestSalaryIdsInAscendingOrder(myarray,index,NumOfCompanies,this->companies_with_employees.root);
            *Employees=myarray;
            delete index;
        }catch(const std::bad_alloc& e){
            return ALLOCATION_ERROR;
        }
        return SUCCESS;
    }

    void Hitechs::fillArrayWithHighestSalaryIdsInAscendingOrder(int *array, int *index, int max,
                                                           BSTNode<std::shared_ptr<Company>, int> *node)
                                                           {
        if (node == nullptr||(*index)==max)
        {
            return;
        }
        fillArrayWithHighestSalaryIdsInAscendingOrder(array,index,max,node->left);
        if((*index)==max)
        {
            return;
        }
        array[*index] = (node->data->highest_salary->employee_id);
        (*index)++;
        fillArrayWithHighestSalaryIdsInAscendingOrder(array,index,max,node->right);

    }
    void FindInSubtree(BSTNode<std::shared_ptr<Employee>,int> *node,int MinEmployeeID,int MaxEmployeeId,int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees )
    {
        if(node== nullptr)
        {
            return;
        }
        if(node->key>=MinEmployeeID&&node->key<=MaxEmployeeId)//in range, we increase total counter and check to maybe increase other counter
        {
            (*TotalNumOfEmployees)++;
            if(node->data->rank>=MinGrade&&node->data->employee_salary>=MinSalary)
            {
                (*NumOfEmployees)++;
            }
            FindInSubtree(node->right,MinEmployeeID,  MaxEmployeeId, MinSalary,  MinGrade, TotalNumOfEmployees, NumOfEmployees);//checking for both sons, could be more node in range in subtree
            FindInSubtree(node->left,MinEmployeeID,  MaxEmployeeId, MinSalary,  MinGrade, TotalNumOfEmployees, NumOfEmployees);
        }
        else if (node->key<=MaxEmployeeId)
        {
            FindInSubtree(node->right,MinEmployeeID,  MaxEmployeeId, MinSalary,  MinGrade, TotalNumOfEmployees, NumOfEmployees);
        }
        else if (node->key>=MinEmployeeID)
        {
            FindInSubtree(node->left,MinEmployeeID,  MaxEmployeeId, MinSalary,  MinGrade, TotalNumOfEmployees, NumOfEmployees);
        }
    }
    void CountInSubtree(BSTNode<std::shared_ptr<Employee>,int> *node,BSTNode<std::shared_ptr<Employee>,int> *no_entry1,BSTNode<std::shared_ptr<Employee>,int> *no_entry2
                       ,int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees )
    {
        if(node== nullptr||node==no_entry1||node==no_entry2)
        {
            return;
        }
            (*TotalNumOfEmployees)++;
            if(node->data->rank>=MinGrade&&node->data->employee_salary>=MinSalary)
            {
                (*NumOfEmployees)++;
            }
        CountInSubtree(node->right,no_entry1,  no_entry2, MinSalary,  MinGrade, TotalNumOfEmployees, NumOfEmployees);
        CountInSubtree(node->left,no_entry1,  no_entry2, MinSalary,  MinGrade, TotalNumOfEmployees, NumOfEmployees);
    }
    StatusType Hitechs::GetNumEmployeesMatching(int CompanyID, int MinEmployeeID,
                                                int MaxEmployeeId, int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees) {
        if (  CompanyID==0|| MinEmployeeID<0|| MaxEmployeeId<0|| MinSalary<0||MinGrade<0||
        TotalNumOfEmployees==nullptr|| NumOfEmployees==nullptr||MinEmployeeID>MaxEmployeeId )
        {
            return INVALID_INPUT;
        }
        BSTNode<std::shared_ptr<Employee>,int> *root;
        if(CompanyID<0)
        {
            root=this->employees.root;
        }
        else
        {
            BSTNode<std::shared_ptr<Company>,int> *company_to_find_node = this->companies.find(CompanyID);
            if (company_to_find_node == nullptr||company_to_find_node->data->num_of_employee==0)
            {
                //a group with this identifier doesn't exist
                return FAILURE;
            }
            root=company_to_find_node->data->employees_by_id.root;
        }
        *TotalNumOfEmployees=0;
        *NumOfEmployees=0;
        FindInSubtree(root,MinEmployeeID,MaxEmployeeId, MinSalary,  MinGrade, TotalNumOfEmployees, NumOfEmployees);
        return SUCCESS;
    }


	StatusType Hitechs::GetHighestEarner(int CompanyID, int* EmployeeID)
	{
		if (CompanyID == 0 || EmployeeID == nullptr)
		{
			return INVALID_INPUT;
		}

		if (CompanyID > 0 && companies.find(CompanyID) == nullptr)
		{
			return FAILURE;
		}

		if (CompanyID > 0 && companies.find(CompanyID)->data->num_of_employee == 0)
		{
			return FAILURE;
		}

		if (CompanyID < 0 && num_of_employees == 0)
		{
			return FAILURE;
		}

		if (CompanyID < 0)
		{
			*EmployeeID = highest_salary->employee_id;
		}
		else
		{
			*EmployeeID = companies.find(CompanyID)->data->highest_salary->employee_id;
		}

		return SUCCESS;
	}

    StatusType Hitechs::AcquireCompany(int AcquirerID, int TargetID, double Factor) {
        if (AcquirerID<=0||TargetID<=0||AcquirerID==TargetID||Factor<1.0)
        {
            return INVALID_INPUT;
        }
        if(companies.find(AcquirerID) == nullptr || companies.find(TargetID) == nullptr)
        {
            return FAILURE;
        }
        std::shared_ptr<Company> acquirerCompany = companies.find(AcquirerID)->data;//buyer
        std::shared_ptr<Company> targetCompany = companies.find(TargetID)->data;

        if (acquirerCompany->company_value <  targetCompany->company_value*10)
        {
            return FAILURE;
        }


        if(acquirerCompany->num_of_employee==0)
        {
            if(targetCompany->num_of_employee>0)
            {
                num_of_companies_with_employees++;
                this->companies_with_employees.insert(AcquirerID,acquirerCompany);
            }
        }
        if (targetCompany->num_of_employee > 0 )
        {
            num_of_companies_with_employees--;
            companies_with_employees.remove(targetCompany->company_id);
        }

        targetCompany->AcquireCompany(acquirerCompany, Factor);

        this->companies.remove(TargetID);
        return SUCCESS;
    }

    void Hitechs::DeleteHitechs()
    {
        delete this;
    }


}
