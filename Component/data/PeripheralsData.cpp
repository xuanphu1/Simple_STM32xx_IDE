// data/PeripheralsData.cpp
#include "../data/PeripheralsData.h"

// Dữ liệu System Viewer
std::vector<PeripheralInfo> systemPeripherals = {
    {"ADC", 0x40012400, {{"CR1", 0x40012404, 0}, {"CR2", 0x40012408, 0}}},
    {"GPIOA", 0x40010800, {{"CRL", 0x40010800, 0}, {"CRH", 0x40010804, 0}}},
    {"USART1", 0x40013800, {{"SR", 0x40013800, 0}, {"DR", 0x40013804, 0}}}
};

// Dữ liệu Core Peripherals
std::vector<PeripheralInfo> corePeripherals = {
    {"NVIC", 0xE000E100, {{"ISER", 0xE000E100, 0}, {"ICER", 0xE000E180, 0}}},
    {"SysTick", 0xE000E010, {{"CTRL", 0xE000E010, 0}, {"LOAD", 0xE000E014, 0}}}
};