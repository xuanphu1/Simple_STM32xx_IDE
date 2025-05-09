// data/PeripheralsData.h
#ifndef PERIPHERALSDATA_H
#define PERIPHERALSDATA_H

#include <vector>
#include <string>
#include <stdint.h>

// Cấu trúc cho một thanh ghi
struct RegisterInfo {
    std::string name;
    uint32_t address;
    uint32_t value;
};

// Cấu trúc cho một ngoại vi
struct PeripheralInfo {
    std::string name;
    uint32_t baseAddress;
    std::vector<RegisterInfo> registers;
};

// Dữ liệu ngoại vi (System Viewer)
extern std::vector<PeripheralInfo> systemPeripherals;

// Dữ liệu Core Peripherals
extern std::vector<PeripheralInfo> corePeripherals;

#endif // PERIPHERALSDATA_H