#include "Hitechs.h"
#include "Library1.h"


void *Init()
{
    return(static_cast<void*> (new Ehsan::Hitechs()));
}

StatusType AddCompany(void *DS, int CompanyID, int Value)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    return(static_cast<Ehsan::Hitechs*>(DS)->AddCompany(CompanyID, Value));
}

StatusType AddEmployee(void *DS, int EmployeeID, int CompanyID, int Salary, int Grade)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    return(static_cast<Ehsan::Hitechs*>(DS)->AddEmployee(EmployeeID, CompanyID, Salary, Grade));
}

StatusType RemoveEmployee(void *DS, int EmployeeID)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    return(static_cast<Ehsan::Hitechs*>(DS)->RemoveEmployee(EmployeeID));
}
StatusType GetCompanyInfo(void *DS, int CompanyID, int *Value, int *NumEmployees)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    return(static_cast<Ehsan::Hitechs*>(DS)->GetCompanyInfo(CompanyID,  Value, NumEmployees));
}
StatusType GetEmployeeInfo(void *DS, int EmployeeID, int *EmployerID, int *Salary, int *Grade)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    return(static_cast<Ehsan::Hitechs*>(DS)->GetEmployeeInfo(EmployeeID, EmployerID, Salary, Grade));
}
StatusType AcquireCompany(void *DS, int GroupID, int ReplacementID, double Factor)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    return(static_cast<Ehsan::Hitechs*>(DS)->AcquireCompany(GroupID, ReplacementID,  Factor));
}

StatusType PromoteEmployee(void *DS, int EmployeeID, int SalaryIncrease, int BumpGrade)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    return(static_cast<Ehsan::Hitechs*>(DS)->PromoteEmployee( EmployeeID,  SalaryIncrease,  BumpGrade));
}
StatusType IncreaseCompanyValue(void *DS, int CompanyID, int ValueIncrease)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    return(static_cast<Ehsan::Hitechs*>(DS)->IncreaseCompanyValue(  CompanyID, ValueIncrease));
}
StatusType RemoveCompany(void *DS, int CompanyID)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    return(static_cast<Ehsan::Hitechs*>(DS)->RemoveCompany(CompanyID));
}
StatusType HireEmployee(void *DS, int EmployeeID, int NewCompanyID)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    return(static_cast<Ehsan::Hitechs*>(DS)->HireEmployee(EmployeeID, NewCompanyID));
}
StatusType GetHighestEarner(void *DS, int CompanyID, int *EmployeeID)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    return(static_cast<Ehsan::Hitechs*>(DS)->GetHighestEarner(CompanyID, EmployeeID));
}
StatusType GetAllEmployeesBySalary(void *DS, int CompanyID, int **Employees, int *NumOfEmployees)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    return(static_cast<Ehsan::Hitechs*>(DS)->GetAllEmployeesBySalary( CompanyID, Employees, NumOfEmployees));
}
StatusType GetHighestEarnerInEachCompany(void *DS, int NumOfCompanies, int **Employees)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    return(static_cast<Ehsan::Hitechs*>(DS)->GetHighestEarnerInEachCompany( NumOfCompanies, Employees));
}
StatusType GetNumEmployeesMatching(void *DS, int CompanyID, int MinEmployeeID, int MaxEmployeeId,
                                   int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    return(static_cast<Ehsan::Hitechs*>(DS)->GetNumEmployeesMatching(CompanyID,  MinEmployeeID,  MaxEmployeeId,
             MinSalary,  MinGrade, TotalNumOfEmployees, NumOfEmployees));
}

void Quit(void** DS)
{
    static_cast<Ehsan::Hitechs*>(*DS)->DeleteHitechs();
    *DS = NULL;
}
