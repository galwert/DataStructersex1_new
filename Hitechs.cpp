#include "Hitechs.h";

namespace Ehsan {

	Hitechs::Hitechs()
	{
		num_of_employees = 0;
		num_of_companies_with_employees = 0;

		BinarySearchTree<std::shared_ptr<Employee>, int> employees = BinarySearchTree<std::shared_ptr<Employee>, int>();
		BinarySearchTree<std::shared_ptr<Employee>, IDSalary> employees_by_salary = BinarySearchTree<std::shared_ptr<Employee>, IDSalary>();
		BinarySearchTree<std::shared_ptr<Company>, int> companies = BinarySearchTree<std::shared_ptr<Company>, int>();
		BinarySearchTree<std::shared_ptr<Company>, int> companies_with_employees = BinarySearchTree<std::shared_ptr<Company>, int>();

		std::shared_ptr<Employee> highest_salary = nullptr;
	}


	Hitechs::~Hitechs() 
	{
		DeleteHitechs();
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

		std::shared_ptr<Company> company = std::shared_ptr<Company>(new Company(CompanyID, Value));
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
		if (companies.find(CompanyID) == nullptr || employees_by_salary.find(idSalary) != nullptr)
		{
			return FAILURE;
		}

		std::shared_ptr<Company> company = companies.find(CompanyID)->data;
		std::shared_ptr<Employee> newEmployee = std::shared_ptr<Employee>(new Employee(EmployeeID, CompanyID, Salary, Grade));
		

		if (company->num_of_employee == 0)  //Checks if the company has no employees
		{
			num_of_companies_with_employees++;
			companies_with_employees.insert(CompanyID, company);
		}

		num_of_employees++;		//Updates the trees
		company->HireEmployee(newEmployee);
		employees.insert(EmployeeID, newEmployee);
		employees_by_salary.insert(idSalary, newEmployee);

		if (newEmployee->employee_salary > highest_salary->employee_salary || (newEmployee->employee_salary == highest_salary->employee_salary && newEmployee->employee_id < highest_salary->employee_id)) //New highest earner
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

		if (employeeToRemove == company->highest_salary)  //Checks if the employee earns the most in the company
		{
			company->UpdateHighestSalaryBeforeGroupReplacement(company);
		}

		if (employeeToRemove == highest_salary)    //Checks if the employee earns the most
		{
			highest_salary = employees.find(EmployeeID)->parent->data;
		}

		company->num_of_employee--;
		company->employees_by_rank.remove(idSalary);
		employees.remove(EmployeeID);     //Removing from employees trees
		employees_by_salary.remove(idSalary);
		
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
		if (EmployeeID <= 0 || SalaryIncrease == 0)
		{
			return INVALID_INPUT;
		}

		if (employees.find(EmployeeID) == nullptr)
		{
			return FAILURE;
		}

		std::shared_ptr<Employee> employee = employees.find(EmployeeID)->data;

		companies.find(employee->company_id)->data->IncreaseSalary(employee->employee_salary, EmployeeID, SalaryIncrease, BumpGrade);

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

		Employee employee = *(employees.find(EmployeeID)->data);
		if (employee.company_id == NewCompanyID)
		{
			return FAILURE;
		}

		RemoveEmployee(EmployeeID);

		return AddEmployee(EmployeeID, NewCompanyID, employee.employee_salary, employee.rank);
	}

	StatusType Hitechs::AcquireCompany(int AcquirerID, int TargetID, double Factor)
	{
		if (AcquirerID <= 0 || TargetID <= 0 || Factor < 1.00 || AcquirerID == TargetID)
		{
			return INVALID_INPUT;
		}

		if (companies.find(AcquirerID) == nullptr || companies.find(TargetID) == nullptr)
		{
			return FAILURE;
		}

		std::shared_ptr<Company> acquirerCompany = companies.find(AcquirerID)->data;
		std::shared_ptr<Company> targetCompany = companies.find(TargetID)->data;

		if (acquirerCompany->company_value < 10 * targetCompany->company_value)
		{
			return FAILURE;
		}

		if (targetCompany->num_of_employee > 0 && acquirerCompany->num_of_employee != 0)
		{
			num_of_companies_with_employees--;
		}

		acquirerCompany->AcquireCompany(targetCompany, Factor);

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

	StatusType Hitechs::GetAllEmployeesBySalary(int CompanyID, int** Employees, int* NumOfEmployees)
	{
		if (CompanyID == 0 || Employees == nullptr || NumOfEmployees == nullptr)
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
			//TO DO: INORDER SEARCH (ALL EMPLOYEES)
		}
		else
		{
			//TO DO: INORDER SEARCH (ALL EMPLOYEES IN COMPANY)
		}
	}

	StatusType Hitechs::GetHighestEarnerInEachCompany(int NumOfCompanies, int** Employees)
	{

	}

	StatusType Hitechs::GetNumEmployeesMatching(int CompanyID, int MinEmployeeID, int MaxEmployeeId,
		int MinSalary, int MinGrade, int* TotalNumOfEmployees, int* NumOfEmployees)
	{

	}

	void Hitechs::DeleteHitechs()
	{

	}

}
