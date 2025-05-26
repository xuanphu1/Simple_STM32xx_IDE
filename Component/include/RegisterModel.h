#ifndef REGISTERMODEL_H
#define REGISTERMODEL_H
#include "RegisterGroup.h"


class RegisterModel {
public:
    void AddGroup(const RegisterGroup& group) {
        groups.push_back(group);
    }

    std::vector<RegisterGroup>& GetGroups(){
        return groups;
    }

    // Tìm register theo tên hoặc địa chỉ
    Register* FindRegisterByName(const std::string& name);
    Register* FindRegisterByAddress(uint32_t address);


private:
    std::vector<RegisterGroup> groups;
};


#endif // REGISTERMODEL_H