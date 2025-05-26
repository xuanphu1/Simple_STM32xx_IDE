#ifndef REGISTERGROUP_H
#define REGISTERGROUP_H
#include "Register.h"

class RegisterGroup
{
public:
    RegisterGroup(const std::string &groupName, uint32_t address, const std::vector<Register> &registers)
        : groupName(groupName), registers(registers), address(address)
    {
        for (auto &reg : this->registers)
        {
            reg.SetAddress(address + reg.GetAddress());
        }
    }
    // Constructor with group name and address, initializes the group name and addres
    void AddRegister(const Register &reg)
    {
        Register r = reg;
        r.SetAddress(address + r.GetAddress());
        registers.push_back(r);
    }
    const std::string &GetGroupName() const { return groupName; }
    std::vector<Register> &GetRegisters() { return registers; }


private:
    std::string groupName;
    uint32_t address; // Optional: address for the group, if needed
    std::vector<Register> registers;
};

#endif // REGISTERGROUP_H