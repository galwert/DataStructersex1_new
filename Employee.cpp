

#include "Employee.h"

std::ostream &Ehsan::operator<<(std::ostream &os, const Ehsan::IDSalary &IDSalary) {
    os << "rank: "<<IDSalary.salary <<" id: " <<IDSalary.ID;
    return os;
}
