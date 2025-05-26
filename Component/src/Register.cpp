#include "Register.h"

std::vector<Register>Register::createGPIORegisters()
{
    std::vector<Register> gpioRegisters;
    gpioRegisters.push_back(Register("CRL", 0x00, Register::RegType::Peripheral, "Configuration Register Low"));
    gpioRegisters.push_back(Register("CRH", 0x04, Register::RegType::Peripheral, "Configuration Register High"));
    gpioRegisters.push_back(Register("IDR", 0x08, Register::RegType::Peripheral, "Input Data Register"));
    gpioRegisters.push_back(Register("ODR", 0x0C, Register::RegType::Peripheral, "Output Data Register"));
    gpioRegisters.push_back(Register("BSRR", 0x10, Register::RegType::Peripheral, "Bit Set/Reset Register"));
    gpioRegisters.push_back(Register("BRR", 0x14, Register::RegType::Peripheral, "Bit Reset Register"));
    gpioRegisters.push_back(Register("LCKR", 0x18, Register::RegType::Peripheral, "Lock Register"));
    return gpioRegisters;
}

std::vector<Register>Register::createADCRegisters()
{
    std::vector<Register> adcRegisters;
    adcRegisters.push_back(Register("CR1", 0x00, Register::RegType::Peripheral, "Control Register 1"));
    adcRegisters.push_back(Register("CR2", 0x04, Register::RegType::Peripheral, "Control Register 2"));
    adcRegisters.push_back(Register("SMPR1", 0x0C, Register::RegType::Peripheral, "Sample Time Register 1"));
    adcRegisters.push_back(Register("SMPR2", 0x10, Register::RegType::Peripheral, "Sample Time Register 2"));
    adcRegisters.push_back(Register("SQR1", 0x2C, Register::RegType::Peripheral, "Regular Sequence Register 1"));
    adcRegisters.push_back(Register("SQR2", 0x30, Register::RegType::Peripheral, "Regular Sequence Register 2"));
    adcRegisters.push_back(Register("SQR3", 0x34, Register::RegType::Peripheral, "Regular Sequence Register 3"));
    return adcRegisters;
}

std::vector<Register>Register::createSPIRegisters()
{
    std::vector<Register> spiRegisters;
    spiRegisters.push_back(Register("CR1", 0x00, Register::RegType::Peripheral, "Control Register 1"));
    spiRegisters.push_back(Register("CR2", 0x04, Register::RegType::Peripheral, "Control Register 2"));
    spiRegisters.push_back(Register("SR", 0x08, Register::RegType::Peripheral, "Status Register"));
    spiRegisters.push_back(Register("DR", 0x0C, Register::RegType::Peripheral, "Data Register"));
    spiRegisters.push_back(Register("CRCPR", 0x10, Register::RegType::Peripheral, "CRC Polynomial Register"));
    spiRegisters.push_back(Register("RXCRCR", 0x14, Register::RegType::Peripheral, "RX CRC Register"));
    spiRegisters.push_back(Register("TXCRCR", 0x18, Register::RegType::Peripheral, "TX CRC Register"));
    return spiRegisters;
}

std::vector<Register>Register::createUSARTRegisters()
{
    std::vector<Register> usartRegisters;
    usartRegisters.push_back(Register("SR", 0x00, Register::RegType::Peripheral, "Status Register"));
    usartRegisters.push_back(Register("DR", 0x04, Register::RegType::Peripheral, "Data Register"));
    usartRegisters.push_back(Register("BRR", 0x08, Register::RegType::Peripheral, "Baud Rate Register"));
    usartRegisters.push_back(Register("CR1", 0x0C, Register::RegType::Peripheral, "Control Register 1"));
    usartRegisters.push_back(Register("CR2", 0x10, Register::RegType::Peripheral, "Control Register 2"));
    usartRegisters.push_back(Register("CR3", 0x14, Register::RegType::Peripheral, "Control Register 3"));
    return usartRegisters;
}

std::vector<Register>Register::createI2CRegisters()
{
    std::vector<Register> i2cRegisters;
    i2cRegisters.push_back(Register("CR1", 0x00, Register::RegType::Peripheral, "Control Register 1"));
    i2cRegisters.push_back(Register("CR2", 0x04, Register::RegType::Peripheral, "Control Register 2"));
    i2cRegisters.push_back(Register("OAR1", 0x08, Register::RegType::Peripheral, "Own Address Register 1"));
    i2cRegisters.push_back(Register("OAR2", 0x0C, Register::RegType::Peripheral, "Own Address Register 2"));
    i2cRegisters.push_back(Register("DR", 0x10, Register::RegType::Peripheral, "Data Register"));
    i2cRegisters.push_back(Register("SR1", 0x14, Register::RegType::Peripheral, "Status Register 1"));
    i2cRegisters.push_back(Register("SR2", 0x18, Register::RegType::Peripheral, "Status Register 2"));
    return i2cRegisters;
}

std::vector<Register>Register::createTIMRegisters()
{
    std::vector<Register> timRegisters;
    timRegisters.push_back(Register("CR1", 0x00, Register::RegType::Peripheral, "Control Register 1"));
    timRegisters.push_back(Register("CR2", 0x04, Register::RegType::Peripheral, "Control Register 2"));
    timRegisters.push_back(Register("SMCR", 0x08, Register::RegType::Peripheral, "Slave Mode Control Register"));
    timRegisters.push_back(Register("DIER", 0x0C, Register::RegType::Peripheral, "DMA/Interrupt Enable Register"));
    timRegisters.push_back(Register("SR", 0x10, Register::RegType::Peripheral, "Status Register"));
    timRegisters.push_back(Register("EGR", 0x14, Register::RegType::Peripheral, "Event Generation Register"));
    return timRegisters;
}

std::vector<Register>Register::createDMARegisters()
{
    std::vector<Register> dmaRegisters;
    dmaRegisters.push_back(Register("ISR", 0x00, Register::RegType::Peripheral, "Interrupt Status Register"));
    dmaRegisters.push_back(Register("IFCR", 0x04, Register::RegType::Peripheral, "Interrupt Flag Clear Register"));
    dmaRegisters.push_back(Register("CCR1", 0x08, Register::RegType::Peripheral, "Channel 1 Configuration Register"));
    dmaRegisters.push_back(Register("CNDTR1", 0x0C, Register::RegType::Peripheral, "Channel 1 Number of Data Register"));
    dmaRegisters.push_back(Register("CPAR1", 0x10, Register::RegType::Peripheral, "Channel 1 Peripheral Address Register"));
    dmaRegisters.push_back(Register("CMAR1", 0x14, Register::RegType::Peripheral, "Channel 1 Memory Address Register"));
    return dmaRegisters;
}

std::vector<Register>Register::createRCCRegisters()
{
    std::vector<Register> rccRegisters;
    rccRegisters.push_back(Register("CR", 0x00, Register::RegType::Peripheral, "Clock Control Register"));
    rccRegisters.push_back(Register("CFGR", 0x04, Register::RegType::Peripheral, "Clock Configuration Register"));
    rccRegisters.push_back(Register("CIR", 0x08, Register::RegType::Peripheral, "Clock Interrupt Register"));
    rccRegisters.push_back(Register("APB2RSTR", 0x0C, Register::RegType::Peripheral, "APB2 Peripheral Reset Register"));
    rccRegisters.push_back(Register("APB1RSTR", 0x10, Register::RegType::Peripheral, "APB1 Peripheral Reset Register"));
    return rccRegisters;
}

std::vector<Register>Register::createFlashRegisters()
{
    std::vector<Register> flashRegisters;
    flashRegisters.push_back(Register("ACR", 0x00, Register::RegType::Peripheral, "Access Control Register"));
    flashRegisters.push_back(Register("KEYR", 0x04, Register::RegType::Peripheral, "Key Register"));
    flashRegisters.push_back(Register("OPTKEYR", 0x08, Register::RegType::Peripheral, "Option Key Register"));
    flashRegisters.push_back(Register("SR", 0x0C, Register::RegType::Peripheral, "Status Register"));
    flashRegisters.push_back(Register("CR", 0x10, Register::RegType::Peripheral, "Control Register"));
    return flashRegisters;
}

std::vector<Register>Register::createCoreRegisters()
{
    std::vector<Register> coreRegisters;
    coreRegisters.push_back(Register("r0", 0x00, Register::RegType::Core, "General Purpose Register 0"));
    coreRegisters.push_back(Register("r1", 0x04, Register::RegType::Core, "General Purpose Register 1"));
    coreRegisters.push_back(Register("r2", 0x08, Register::RegType::Core, "General Purpose Register 2"));
    coreRegisters.push_back(Register("r3", 0x0C, Register::RegType::Core, "General Purpose Register 3"));
    coreRegisters.push_back(Register("r4", 0x10, Register::RegType::Core, "General Purpose Register 4"));
    coreRegisters.push_back(Register("r5", 0x14, Register::RegType::Core, "General Purpose Register 5"));
    coreRegisters.push_back(Register("r6", 0x18, Register::RegType::Core, "General Purpose Register 6"));
    coreRegisters.push_back(Register("r7", 0x1C, Register::RegType::Core, "General Purpose Register 7"));
    coreRegisters.push_back(Register("r8", 0x20, Register::RegType::Core, "General Purpose Register 8"));
    coreRegisters.push_back(Register("r9", 0x24, Register::RegType::Core, "General Purpose Register 9"));
    coreRegisters.push_back(Register("r10", 0x28, Register::RegType::Core, "General Purpose Register 10"));
    coreRegisters.push_back(Register("r11", 0x2C, Register::RegType::Core, "General Purpose Register 11"));
    coreRegisters.push_back(Register("r12", 0x30, Register::RegType::Core, "General Purpose Register 12"));
    coreRegisters.push_back(Register("sp", 0x34, Register::RegType::Core, "Stack Pointer"));
    coreRegisters.push_back(Register("lr", 0x38, Register::RegType::Core, "Link Register"));
    coreRegisters.push_back(Register("pc", 0x3C, Register::RegType::Core, "Program Counter"));
    coreRegisters.push_back(Register("xpsr", 0x40, Register::RegType::Core, "Program Status Register (xPSR)"));
    coreRegisters.push_back(Register("msp", 0x44, Register::RegType::Core, "Main Stack Pointer (MSP)"));
    coreRegisters.push_back(Register("psp", 0x48, Register::RegType::Core, "Process Stack Pointer (PSP)"));
    coreRegisters.push_back(Register("primask", 0x4C, Register::RegType::Core, "Interrupt Mask Register (PRIMASK)"));
    coreRegisters.push_back(Register("faultmask", 0x50, Register::RegType::Core, "Fault Mask Register (FAULTMASK)"));
    coreRegisters.push_back(Register("basepri", 0x54, Register::RegType::Core, "Base Priority Mask Register (BASEPRI)"));
    coreRegisters.push_back(Register("control", 0x58, Register::RegType::Core, "Control Register (CONTROL)"));
    coreRegisters.push_back(Register("fpscr", 0x5C, Register::RegType::Core, "Floating Point Status and Control Register (FPSCR)"));
    return coreRegisters;
}
