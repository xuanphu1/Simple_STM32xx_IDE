#include "RegisterModel.h"

Register *RegisterModel::FindRegisterByName(const std::string &name)
{

    // for (const auto &group : groups)
    // {
    //     for (auto &reg : group.GetRegisters())
    //     {
    //         if (reg.GetName() == name)
    //         {
    //             return const_cast<Register *>(&reg); // Trả về con trỏ không const
    //         }
    //     }
    // }
    return nullptr; // Không tìm thấy register
}
Register *RegisterModel::FindRegisterByAddress(uint32_t address)
{
    // for (const auto &group : groups){
    //     for (auto &reg: group.GetRegisters()){
    //         if(reg.GetAddress() == address){
    //             return const_cast<Register *>(&reg); // Trả về con trỏ không const
    //         }
    //     }
    // }
    return nullptr;
}

