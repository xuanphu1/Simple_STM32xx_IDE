#ifndef STM32IDE_H
#define STM32IDE_H

#include "main.h"
#include "DirectoryTreeManager.h"
#include "ConfigSystemDialog.h"

class STM32IDE : public wxFrame {
public:
    STM32IDE();

private:
enum {
        ID_BUILD = wxID_HIGHEST + 1,
        ID_UPLOAD,
        ID_RUN,
        ID_OPEN_PROJECT,
        ID_NEW_FOLDER,
        ID_DEBUG,
        ID_SYSTEM_VIEWER,
        ID_CORE_PERIPHERALS,
        ID_PERIPH_ADC,
        ID_PERIPH_ADC1,
        ID_PERIPH_ADC2,
        ID_PERIPH_ADC3,
        ID_PERIPH_AFIO,
        ID_PERIPH_BKP,
        ID_PERIPH_CAN,
        ID_PERIPH_CRC,
        ID_PERIPH_DAC,
        ID_PERIPH_DBG,
        ID_PERIPH_DMA,
        ID_PERIPH_DMA1,
        ID_PERIPH_DMA2,
        ID_PERIPH_EXTI,
        ID_PERIPH_FLASH,
        ID_PERIPH_FSMC,
        ID_PERIPH_GPIO,
        ID_PERIPH_GPIOA,
        ID_PERIPH_GPIOB,
        ID_PERIPH_GPIOC,
        ID_PERIPH_GPIOD,
        ID_PERIPH_GPIOE,
        ID_PERIPH_GPIOF,
        ID_PERIPH_GPIOG,
        ID_PERIPH_I2C,
        ID_PERIPH_I2C1,
        ID_PERIPH_I2C2,
        ID_PERIPH_IWDG,
        ID_PERIPH_NVIC,
        ID_PERIPH_PWR,
        ID_PERIPH_RCC,
        ID_PERIPH_RTC,
        ID_PERIPH_SDIO,
        ID_PERIPH_SPI,
        ID_PERIPH_SPI1,
        ID_PERIPH_SPI2,
        ID_PERIPH_SPI3,

        ID_PERIPH_TIM,
        ID_PERIPH_TIM1,
        ID_PERIPH_TIM2,
        ID_PERIPH_TIM3,
        ID_PERIPH_TIM4,
        ID_PERIPH_TIM5,
        ID_PERIPH_TIM6,
        ID_PERIPH_TIM7,
        ID_PERIPH_TIM8,
        ID_PERIPH_TIM9,
        ID_PERIPH_TIM10,
        ID_PERIPH_TIM11,
        ID_PERIPH_TIM12,
        ID_PERIPH_TIM13,
        ID_PERIPH_TIM14,

        ID_PERIPH_USART,
        ID_PERIPH_USART1,
        ID_PERIPH_USART2,
        ID_PERIPH_USART3,
        ID_PERIPH_UART4,
        ID_PERIPH_UART5,
        ID_PERIPH_USB,
        ID_PERIPH_WWDG,

        ID_CONFIG_SYSTEM
    };

    wxTreeCtrl* tree;
    wxTextCtrl* editor;
    wxTextCtrl* console;

    // Thêm các biến để lưu đường dẫn
    wxString linkerPath;   // Đường dẫn tới linker script
    wxString startupPath;  // Đường dẫn tới startup file
    wxString makefilePath; // Đường dẫn tới Makefile
    wxString currentWorkingDir; // Biến mới để lưu đường dẫn hiện tại

    wxString projectPath;
    DirectoryTreeManager* treeManager; // Thêm con trỏ đến DirectoryTreeManager

    void OnNewFile(wxCommandEvent& event);
    void OnOpenFile(wxCommandEvent& event);
    void OnOpenProject(wxCommandEvent& event);
    void OnBuild(wxCommandEvent& event);
    void OnUpload(wxCommandEvent& event);
    void OnRun(wxCommandEvent& event);
    void OnPeripheralSelected(wxCommandEvent& event);
    void OnConfigSystem(wxCommandEvent& event); // Thêm hàm xử lý sự kiện Config System
};

#endif // STM32IDE_H