#ifndef REGISTER_H
#define REGISTER_H
#include <string>
#include <cstdint>
#include <vector>
#include <iomanip>


class Register {
public:
    enum class RegType { Core, Peripheral };

    Register(const std::string& name, uint32_t address, RegType type, const std::string& description = "")
        : name(name), address(address), type(type), description(description), value(0) {}

    // Getters/Setters
    const std::string& GetName() const { return name; }
    uint32_t GetAddress() const { return address; }
    uint32_t SetAddress(uint32_t addr) { address = addr; return address; }
    RegType GetType() const { return type; }
    const std::string& GetDescription() const { return description; }
    uint32_t GetValue() const { return value; }
    void SetValue(uint32_t val) { value = val; }
    static std::vector<Register> createGPIORegisters();
    static std::vector<Register> createADCRegisters();
    static std::vector<Register> createSPIRegisters();
    static std::vector<Register> createUSARTRegisters();
    static std::vector<Register> createI2CRegisters();
    static std::vector<Register> createTIMRegisters();
    static std::vector<Register> createDMARegisters();
    static std::vector<Register> createCoreRegisters();
    static std::vector<Register> createRCCRegisters();
    static std::vector<Register> createFlashRegisters();

private:
    std::string name;
    uint32_t address;     // Địa chỉ offset hoặc địa chỉ vật lý
    RegType type;
    std::string description;
    uint32_t value;
};


#endif // REGISTER_H