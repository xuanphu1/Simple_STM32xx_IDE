// src/STM32IDE.cpp
#include "../include/STM32IDE.h"

const char *path_Debug_Icon = "D:/Simple_STM32xx_IDE/Component/Assets/DebugIcon.png";
const char *path_System_Icon = "D:/Simple_STM32xx_IDE/Component/Assets/System.png";
const char *path_Run_Icon = "D:/Simple_STM32xx_IDE/Component/Assets/RunIcon.png";
const char *path_Build_Icon = "D:/Simple_STM32xx_IDE/Component/Assets/BuildIcon.png";
const char *path_StepInto_Icon = "D:/Simple_STM32xx_IDE/Component/Assets/debug-step-into.png";
const char *path_StepOver_Icon = "D:/Simple_STM32xx_IDE/Component/Assets/debug-step-over.png";
const char *path_StepOut_Icon = "D:/Simple_STM32xx_IDE/Component/Assets/debug-step-out.png";
const char *path_Restart_Icon = "D:/Simple_STM32xx_IDE/Component/Assets/reboot.png";
const char *path_Stop_Icon = "D:/Simple_STM32xx_IDE/Component/Assets/debug-stop.png";

STM32IDE::STM32IDE() : wxFrame(nullptr, wxID_ANY, "STM32 IDE Handmade", wxDefaultPosition, wxSize(800, 600)),
                       isDebugRunning(false)
{
    Maximize();

    currentWorkingDir = wxGetCwd(); // Biến mới để lưu đường dẫn hiện tại
    currentWorkingDir.Replace("\\", "/");
    makefilePath = currentWorkingDir + "/../Component/Tools/System/Makefile";
    configMakefile = currentWorkingDir + "/../Component/Tools/System/Config.mk";
    startupPath = currentWorkingDir + "/../Component/Tools/System/Startup.c";
    linkerPath = currentWorkingDir + "/../Component/Tools/System/Linker.ld";
    toolPath = currentWorkingDir + "/../Component/Tools";

    currentFilePath = "";

    debugmanager = new DebugManager(this);

    // Menu Bar
    wxMenuBar *menubar = new wxMenuBar();
    wxMenu *fileMenu = new wxMenu();
    fileMenu->Append(wxID_NEW, "New File");
    fileMenu->Append(wxID_OPEN, "Open File");
    fileMenu->Append(ID_NEW_FOLDER, "New Folder");
    fileMenu->Append(ID_OPEN_PROJECT, "Open Project");
    fileMenu->Append(wxID_SAVE, "Save file");
    menubar->Append(fileMenu, "File");

    wxMenu *buildMenu = new wxMenu();
    buildMenu->Append(ID_BUILD, "Build");
    buildMenu->Append(ID_UPLOAD, "Upload");
    menubar->Append(buildMenu, "Build");

    wxMenu *ViewMenu = new wxMenu();
    ViewMenu->Append(ID_VIEW_MEMORY, "Memory");
    ViewMenu->Append(ID_VIEW_CORE_REGISTERS, "Core Registers");
    ViewMenu->Append(ID_VIEW_ASM, "Assembly Viewer");
    menubar->Append(ViewMenu, "View");

    wxMenu *PeripheralsMenu = new wxMenu();
    wxMenu *systemViewerMenu = new wxMenu();
    wxMenu *coreViewerMenu = new wxMenu();

    // Submenu for ADC
    wxMenu *ADCSubsystemMenu = new wxMenu();
    ADCSubsystemMenu->Append(ID_PERIPH_ADC1, "ADC1");
    ADCSubsystemMenu->Append(ID_PERIPH_ADC2, "ADC2");
    ADCSubsystemMenu->Append(ID_PERIPH_ADC3, "ADC3");
    systemViewerMenu->Append(ID_PERIPH_ADC, "ADC", ADCSubsystemMenu);

    // Submenu for DMA
    wxMenu *DMASubsystemMenu = new wxMenu();
    DMASubsystemMenu->Append(ID_PERIPH_DMA1, "DMA1");
    DMASubsystemMenu->Append(ID_PERIPH_DMA2, "DMA2");
    systemViewerMenu->Append(ID_PERIPH_DMA, "DMA", DMASubsystemMenu);

    // Submenu for GPIO
    wxMenu *GPIOSubsystemMenu = new wxMenu();
    GPIOSubsystemMenu->Append(ID_PERIPH_GPIOA, "GPIOA");
    GPIOSubsystemMenu->Append(ID_PERIPH_GPIOB, "GPIOB");
    GPIOSubsystemMenu->Append(ID_PERIPH_GPIOC, "GPIOC");
    GPIOSubsystemMenu->Append(ID_PERIPH_GPIOD, "GPIOD");
    GPIOSubsystemMenu->Append(ID_PERIPH_GPIOE, "GPIOE");
    GPIOSubsystemMenu->Append(ID_PERIPH_GPIOF, "GPIOF");
    GPIOSubsystemMenu->Append(ID_PERIPH_GPIOG, "GPIOG");
    systemViewerMenu->Append(ID_PERIPH_GPIO, "GPIO", GPIOSubsystemMenu);

    // Submenu for I2C
    wxMenu *I2CSubsystemMenu = new wxMenu();
    I2CSubsystemMenu->Append(ID_PERIPH_I2C1, "I2C1");
    I2CSubsystemMenu->Append(ID_PERIPH_I2C2, "I2C2");
    systemViewerMenu->Append(ID_PERIPH_I2C, "I2C", I2CSubsystemMenu);

    // Submenu for SPI
    wxMenu *SPISubsystemMenu = new wxMenu();
    SPISubsystemMenu->Append(ID_PERIPH_SPI1, "SPI1");
    SPISubsystemMenu->Append(ID_PERIPH_SPI2, "SPI2");
    SPISubsystemMenu->Append(ID_PERIPH_SPI3, "SPI3");
    systemViewerMenu->Append(ID_PERIPH_SPI, "SPI", SPISubsystemMenu);

    // Submenu for TIM
    wxMenu *TIMSubsystemMenu = new wxMenu();
    TIMSubsystemMenu->Append(ID_PERIPH_TIM1, "TIM1");
    TIMSubsystemMenu->Append(ID_PERIPH_TIM2, "TIM2");
    TIMSubsystemMenu->Append(ID_PERIPH_TIM3, "TIM3");
    TIMSubsystemMenu->Append(ID_PERIPH_TIM4, "TIM4");
    TIMSubsystemMenu->Append(ID_PERIPH_TIM5, "TIM5");
    TIMSubsystemMenu->Append(ID_PERIPH_TIM6, "TIM6");
    TIMSubsystemMenu->Append(ID_PERIPH_TIM7, "TIM7");
    TIMSubsystemMenu->Append(ID_PERIPH_TIM8, "TIM8");
    TIMSubsystemMenu->Append(ID_PERIPH_TIM9, "TIM9");
    TIMSubsystemMenu->Append(ID_PERIPH_TIM10, "TIM10");
    TIMSubsystemMenu->Append(ID_PERIPH_TIM11, "TIM11");
    TIMSubsystemMenu->Append(ID_PERIPH_TIM12, "TIM12");
    TIMSubsystemMenu->Append(ID_PERIPH_TIM13, "TIM13");
    TIMSubsystemMenu->Append(ID_PERIPH_TIM14, "TIM14");
    systemViewerMenu->Append(ID_PERIPH_TIM, "TIM", TIMSubsystemMenu);

    // Submenu for USART
    wxMenu *USARTSubsystemMenu = new wxMenu();
    USARTSubsystemMenu->Append(ID_PERIPH_USART1, "USART1");
    USARTSubsystemMenu->Append(ID_PERIPH_USART2, "USART2");
    USARTSubsystemMenu->Append(ID_PERIPH_USART3, "USART3");
    USARTSubsystemMenu->Append(ID_PERIPH_UART4, "UART4");
    USARTSubsystemMenu->Append(ID_PERIPH_UART5, "UART5");
    systemViewerMenu->Append(ID_PERIPH_USART, "USART", USARTSubsystemMenu);

    // Các peripheral khác không có submenu
    systemViewerMenu->Append(ID_PERIPH_AFIO, "AFIO");
    systemViewerMenu->Append(ID_PERIPH_BKP, "BKP");
    systemViewerMenu->Append(ID_PERIPH_CAN, "CAN");
    systemViewerMenu->Append(ID_PERIPH_CRC, "CRC");
    systemViewerMenu->Append(ID_PERIPH_DAC, "DAC");
    systemViewerMenu->Append(ID_PERIPH_DBG, "DBG");
    systemViewerMenu->Append(ID_PERIPH_EXTI, "EXTI");
    systemViewerMenu->Append(ID_PERIPH_FLASH, "FLASH");
    systemViewerMenu->Append(ID_PERIPH_FSMC, "FSMC");
    systemViewerMenu->Append(ID_PERIPH_IWDG, "IWDG");
    systemViewerMenu->Append(ID_PERIPH_NVIC, "NVIC");
    systemViewerMenu->Append(ID_PERIPH_PWR, "PWR");
    systemViewerMenu->Append(ID_PERIPH_RCC, "RCC");
    systemViewerMenu->Append(ID_PERIPH_RTC, "RTC");
    systemViewerMenu->Append(ID_PERIPH_SDIO, "SDIO");
    systemViewerMenu->Append(ID_PERIPH_USB, "USB");
    systemViewerMenu->Append(ID_PERIPH_WWDG, "WWDG");

    coreViewerMenu->Append(ID_DEBUG_CORE_NVIC, "Nested Vectored Interrupt Controller (NVIC)");
    coreViewerMenu->Append(ID_DEBUG_CORE_SCAC, "System Control and Configuration");
    coreViewerMenu->Append(ID_DEBUG_CORE_SYSTICK, "System Tick Timer (SysTick)");
    coreViewerMenu->Append(ID_DEBUG_CORE_FAULTRP, "Fault Reports");

    PeripheralsMenu->AppendSubMenu(systemViewerMenu, "System Viewer");
    PeripheralsMenu->AppendSubMenu(coreViewerMenu, "Core Peripherals");
    menubar->Append(PeripheralsMenu, "Peripherals");
    SetMenuBar(menubar);

    _registerGroupCore = new RegisterGroup("Core Registers", 0xE000E000, Register::createCoreRegisters());

    _registerGroupPeripheral = {
        RegisterGroup("ADC1 Registers", 0x40012400, Register::createADCRegisters()),
        RegisterGroup("ADC2 Registers", 0x40012800, Register::createADCRegisters()),
        RegisterGroup("ADC3 Registers", 0x40013C00, Register::createADCRegisters()),
        RegisterGroup("GPIOA Registers", 0x40010800, Register::createGPIORegisters()),
        RegisterGroup("GPIOB Registers", 0x40010C00, Register::createGPIORegisters()),
        RegisterGroup("GPIOC Registers", 0x40011000, Register::createGPIORegisters()),
        RegisterGroup("GPIOD Registers", 0x40011400, Register::createGPIORegisters()),
        RegisterGroup("GPIOE Registers", 0x40011800, Register::createGPIORegisters()),
        RegisterGroup("GPIOF Registers", 0x40011C00, Register::createGPIORegisters()),
        RegisterGroup("GPIOG Registers", 0x40012000, Register::createGPIORegisters()),
        RegisterGroup("I2C1 Registers", 0x40005400, Register::createI2CRegisters()),
        RegisterGroup("I2C2 Registers", 0x40005800, Register::createI2CRegisters()),
        RegisterGroup("SPI1 Registers", 0x40013000, Register::createSPIRegisters()),
        RegisterGroup("SPI2 Registers", 0x40003800, Register::createSPIRegisters()),
        RegisterGroup("SPI3 Registers", 0x40003C00, Register::createSPIRegisters()),
        RegisterGroup("DMA1 Registers", 0x40020000, Register::createDMARegisters()),
        RegisterGroup("DMA2 Registers", 0x40020400, Register::createDMARegisters()),
        RegisterGroup("TIM1 Registers", 0x40012C00, Register::createTIMRegisters()),
        RegisterGroup("TIM2 Registers", 0x40000000, Register::createTIMRegisters()),
        RegisterGroup("TIM3 Registers", 0x40000400, Register::createTIMRegisters()),
        RegisterGroup("TIM4 Registers", 0x40000800, Register::createTIMRegisters()),
        RegisterGroup("TIM5 Registers", 0x40000C00, Register::createTIMRegisters()),
        RegisterGroup("TIM6 Registers", 0x40001000, Register::createTIMRegisters()),
        RegisterGroup("TIM7 Registers", 0x40001400, Register::createTIMRegisters()),
        RegisterGroup("TIM8 Registers", 0x40013400, Register::createTIMRegisters()),
        RegisterGroup("TIM9 Registers", 0x40014000, Register::createTIMRegisters()),
        RegisterGroup("TIM10 Registers", 0x40014400, Register::createTIMRegisters()),
        RegisterGroup("TIM11 Registers", 0x40014800, Register::createTIMRegisters()),
        RegisterGroup("TIM12 Registers", 0x40001800, Register::createTIMRegisters()),
        RegisterGroup("TIM13 Registers", 0x40001C00, Register::createTIMRegisters()),
        RegisterGroup("TIM14 Registers", 0x40002000, Register::createTIMRegisters()),
        RegisterGroup("USART1 Registers", 0x40013800, Register::createUSARTRegisters()),
        RegisterGroup("USART2 Registers", 0x40004400, Register::createUSARTRegisters()),
        RegisterGroup("USART3 Registers", 0x40004800, Register::createUSARTRegisters()),
        RegisterGroup("UART4 Registers", 0x40004C00, Register::createUSARTRegisters()),
        RegisterGroup("UART5 Registers", 0x40005000, Register::createUSARTRegisters()),
        RegisterGroup("RCC Registers", 0x40021000, Register::createRCCRegisters()),
        RegisterGroup("FLASH Registers", 0x40022000, Register::createFlashRegisters())};

    _registerModel = new RegisterModel();
    _registerModel->AddGroup(*_registerGroupCore);
    for (const auto &group : _registerGroupPeripheral)
    {
        _registerModel->AddGroup(group);
    }

    // Toolbar
    toolbar = CreateToolBar();
    toolbar->SetToolBitmapSize(wxSize(24, 24));

    // Tạo bitmap cho các icon chính, scale đúng kích thước
    wxBitmap runBitmap = wxArtProvider::GetBitmap(wxART_EXECUTABLE_FILE, wxART_TOOLBAR);

    wxImage buildImage(path_Build_Icon, wxBITMAP_TYPE_PNG);
    buildImage = buildImage.Scale(24, 24, wxIMAGE_QUALITY_HIGH);
    wxBitmap buildBitmap(buildImage);

    wxImage configSystemImage(path_System_Icon, wxBITMAP_TYPE_PNG);
    configSystemImage = configSystemImage.Scale(24, 24, wxIMAGE_QUALITY_HIGH);
    wxBitmap configSystemBitmap(configSystemImage);

    wxImage debugImage(path_Debug_Icon, wxBITMAP_TYPE_PNG);
    debugImage = debugImage.Scale(24, 24, wxIMAGE_QUALITY_HIGH);
    wxBitmap debugBitmap(debugImage);

    wxBitmap saveBitmap = wxArtProvider::GetBitmap(wxART_FILE_SAVE, wxART_TOOLBAR);

    // Thêm các tool với wxBitmapBundle::FromBitmap()
    toolbar->AddTool(wxID_SAVE, "Save file", wxBitmapBundle::FromBitmap(saveBitmap), "Save file", wxITEM_NORMAL);
    toolbar->AddTool(ID_RUN, "Run", wxBitmapBundle::FromBitmap(runBitmap), "Run", wxITEM_NORMAL);
    toolbar->AddTool(ID_BUILD, "Build", wxBitmapBundle::FromBitmap(buildBitmap), "Build the project", wxITEM_NORMAL);
    toolbar->AddTool(ID_DEBUG, "Debug", wxBitmapBundle::FromBitmap(debugBitmap), "Debug", wxITEM_NORMAL);
    toolbar->AddTool(ID_CONFIG_SYSTEM, "Config System", wxBitmapBundle::FromBitmap(configSystemBitmap), "Config System", wxITEM_NORMAL);

    // Bitmap nhỏ hơn cho debug step
    wxImage stepIntoImage(path_StepInto_Icon, wxBITMAP_TYPE_PNG);
    stepIntoImage = stepIntoImage.Scale(24, 24, wxIMAGE_QUALITY_HIGH);
    wxBitmap stepIntoBitmap(stepIntoImage);

    wxImage stepOverImage(path_StepOver_Icon, wxBITMAP_TYPE_PNG);
    stepOverImage = stepOverImage.Scale(24, 24, wxIMAGE_QUALITY_HIGH);
    wxBitmap stepOverBitmap(stepOverImage);

    wxImage stepOutImage(path_StepOut_Icon, wxBITMAP_TYPE_PNG);
    stepOutImage = stepOutImage.Scale(24, 24, wxIMAGE_QUALITY_HIGH);
    wxBitmap stepOutBitmap(stepOutImage);

    wxImage StopImage(path_Stop_Icon, wxBITMAP_TYPE_PNG);
    StopImage = StopImage.Scale(24, 24, wxIMAGE_QUALITY_HIGH);
    wxBitmap StopBitmap(StopImage);

    wxImage RestartImage(path_Restart_Icon, wxBITMAP_TYPE_PNG);
    RestartImage = RestartImage.Scale(24, 24, wxIMAGE_QUALITY_HIGH);
    wxBitmap RestartBitmap(RestartImage);

    // Thêm các nút debug với wxBitmapBundle
    toolbar->AddTool(ID_DEBUG_STEP_INTO, "Step Into", wxBitmapBundle::FromBitmap(stepIntoBitmap), "Step into the next statement");
    toolbar->AddTool(ID_DEBUG_STEP_OVER, "Step Over", wxBitmapBundle::FromBitmap(stepOverBitmap), "Step over the next statement");
    toolbar->AddTool(ID_DEBUG_STEP_OUT, "Step Out", wxBitmapBundle::FromBitmap(stepOutBitmap), "Step out of the current function");
    toolbar->AddTool(ID_DEBUG_CONTINUE, "Continue", wxBitmapBundle::FromBitmap(wxArtProvider::GetBitmap(wxART_GO_FORWARD, wxART_TOOLBAR, wxSize(24, 24))), "Continue execution until the next breakpoint");
    toolbar->AddTool(ID_DEBUG_STOP, "Stop", wxBitmapBundle::FromBitmap(StopBitmap), "Stop code execution");
    toolbar->AddTool(ID_DEBUG_RESTART, "Restart", wxBitmapBundle::FromBitmap(RestartBitmap), "Restart the CPU");

    toolbar->Realize();

    // Layout
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);

    tree = new wxTreeCtrl(this, wxID_ANY);
    tree->SetMinSize(wxSize(200, -1));
    tree->SetMaxSize(wxSize(250, -1));
    hSizer->Add(tree, 0, wxEXPAND);

    editor = new wxStyledTextCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
    editor->SetMinSize(wxSize(400, 300));

    // Cấu hình margin số dòng
    editor->SetMarginType(0, wxSTC_MARGIN_NUMBER);
    editor->SetMarginWidth(0, 40);

    // Cấu hình margin đánh dấu breakpoint (margin 1)
    editor->SetMarginType(1, wxSTC_MARGIN_SYMBOL);
    editor->SetMarginMask(1, 0x1); // Chỉ cho phép 1 loại marker (bitmask 1)
    editor->SetMarginWidth(1, 20);
    editor->SetMarginSensitive(1, true); // margin này nhạy click

    // Định nghĩa marker dùng làm breakpoint - hình tròn đỏ
    editor->MarkerDefine(0, wxSTC_MARK_CIRCLE, *wxRED, *wxRED);
    editor->SetMinSize(wxSize(400, 300));
    hSizer->Add(editor, 1, wxEXPAND);

    mainSizer->Add(hSizer, 1, wxEXPAND);

    console = new wxStyledTextCtrl(this, wxID_ANY, wxDefaultPosition, wxSize(-1, 100), wxTE_MULTILINE | wxTE_READONLY);

    mainSizer->Add(console, 0, wxEXPAND);

    SetSizer(mainSizer);

    // Khởi tạo DirectoryTreeManager
    treeManager = new DirectoryTreeManager(tree, console);

    // Bind sự kiện cho wxTreeCtrl
    Bind(wxEVT_TREE_SEL_CHANGED, [this](wxTreeEvent &event)
         { treeManager->OnTreeSelect(event, editor, currentFilePath); }, tree->GetId());

    Bind(wxEVT_TOOL, &STM32IDE::OnRun, this, ID_RUN);
    Bind(wxEVT_TOOL, &STM32IDE::OnBuild, this, ID_BUILD);
    Bind(wxEVT_TOOL, &STM32IDE::OnConfigSystem, this, ID_CONFIG_SYSTEM);    // Bind sự kiện cho Config System
    Bind(wxEVT_TOOL, &STM32IDE::OnDebugStepInto, this, ID_DEBUG_STEP_INTO); // Bind sự kiện Debug
    Bind(wxEVT_TOOL, &STM32IDE::OnDebugStepOver, this, ID_DEBUG_STEP_OVER); // Bind sự kiện Debug Step Over
    Bind(wxEVT_TOOL, &STM32IDE::OnDebugStepOut, this, ID_DEBUG_STEP_OUT);   // Bind sự kiện Debug Step Out
    Bind(wxEVT_TOOL, &STM32IDE::OnDebugContinue, this, ID_DEBUG_CONTINUE);  // Bind sự kiện Debug Continue
    Bind(wxEVT_TOOL, &STM32IDE::OnDebugRestart, this, ID_DEBUG_RESTART);    // Bind sự kiện Debug Restart
    Bind(wxEVT_TOOL, &STM32IDE::OnDebugStop, this, ID_DEBUG_STOP);          // Bind sự kiện Debug Stop
    // Bind Events
    Bind(wxEVT_MENU, &STM32IDE::OnNewFile, this, wxID_NEW);
    Bind(wxEVT_MENU, &STM32IDE::OnOpenFile, this, wxID_OPEN);
    Bind(wxEVT_MENU, &STM32IDE::OnOpenProject, this, ID_OPEN_PROJECT);
    Bind(wxEVT_MENU, &STM32IDE::OnBuild, this, ID_BUILD);
    Bind(wxEVT_MENU, &STM32IDE::OnUpload, this, ID_UPLOAD);

    Bind(EVT_DEBUG_OUTPUT, &STM32IDE::OnGdbOutput, this); // Bind sự kiện debug output

    Bind(wxEVT_TOOL, &STM32IDE::OnDebug, this, ID_DEBUG);
    Bind(wxEVT_MENU, &STM32IDE::OnSave, this, wxID_SAVE); // Bind sự kiện Save

    Bind(wxEVT_MENU, &STM32IDE::OnViewMemory, this, ID_VIEW_MEMORY);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_VIEW_CORE_REGISTERS);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_ADC1);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_ADC2);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_ADC3);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_DMA1);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_DMA2);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_GPIOA);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_GPIOB);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_GPIOC);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_GPIOD);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_GPIOE);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_GPIOF);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_GPIOG);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_I2C1);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_I2C2);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_SPI1);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_SPI2);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_SPI3);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_TIM1);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_TIM2);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_TIM3);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_TIM4);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_TIM5);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_TIM6);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_TIM7);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_TIM8);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_TIM9);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_TIM10);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_TIM11);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_TIM12);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_TIM13);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_TIM14);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_USART1);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_USART2);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_USART3);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_UART4);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_UART5);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_RCC);
    Bind(wxEVT_MENU, &STM32IDE::OnViewRegisters, this, ID_PERIPH_FLASH);

    editor->Bind(wxEVT_STC_MARGINCLICK, &STM32IDE::OnMarginClick, this);
    editor->Bind(wxEVT_KEY_DOWN, &STM32IDE::OnKeyDown, this); // Bind sự kiện bàn phím

    wxDirDialog dlg(this, "Select Project Directory", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
    if (dlg.ShowModal() == wxID_OK)
    {
        projectPath = dlg.GetPath();
        treeManager->LoadDirectoryTree(projectPath);
    }
    else
    {
        console->AppendText("No project directory selected. Please select a project using File > Open Project.\n");
    }
}

void STM32IDE::OnNewFile(wxCommandEvent &event)
{
    if (projectPath.empty())
    {
        console->AppendText("Please select a project directory first using File > Open Project.\n");
        return;
    }
    wxFileDialog saveDlg(this, "New C File", projectPath, "", "C Files (*.c;*.h)|*.c;*.h", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (saveDlg.ShowModal() == wxID_OK)
    {
        wxString path = saveDlg.GetPath();
        wxFile file(path, wxFile::write);
        if (file.IsOpened())
        {
            file.Write("// New C File\n#include <stdint.h>\n\nint main(void) {\n    return 0;\n}\n");
            file.Close();
            currentFilePath = path;
            editor->SetValue("// New C File\n#include <stdint.h>\n\nint main(void) {\n    return 0;\n}\n");
            treeManager->LoadDirectoryTree(projectPath);
        }
        else
        {
            console->AppendText("Cannot create file: " + path + "\n");
        }
    }
}

void STM32IDE::OnOpenFile(wxCommandEvent &event)
{
    if (projectPath.empty())
    {
        console->AppendText("Please select a project directory first using File > Open Project.\n");
        return;
    }
    wxFileDialog openDlg(this, "Open C File", projectPath, "", "C Files (*.c;*.h)|*.c;*.h", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openDlg.ShowModal() == wxID_OK)
    {
        wxString path = openDlg.GetPath();
        wxFile file(path, wxFile::read);
        if (file.IsOpened())
        {
            wxString content;
            file.ReadAll(&content);
            editor->SetValue(content);
            currentFilePath = path;
            file.Close();
        }
        else
        {
            console->AppendText("Cannot open file: " + path + "\n");
        }
    }
}

void STM32IDE::OnOpenProject(wxCommandEvent &event)
{

    wxDirDialog dlg(this, "Select Project Directory", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
    if (dlg.ShowModal() == wxID_OK)
    {
        projectPath = dlg.GetPath();
        treeManager->LoadDirectoryTree(projectPath);
        console->AppendText(hexPath);
    }
}

void STM32IDE::OnBuild(wxCommandEvent &event)
{

    if (projectPath.IsEmpty())
    {
        console->AppendText("No project directory selected. Please open a project first.\n");
        return;
    }

    if (makefilePath.IsEmpty())
    {
        console->AppendText("Makefile not specified. Please configure the system first.\n");
        return;
    }

    if (linkerPath.IsEmpty() || startupPath.IsEmpty())
    {
        console->AppendText("Linker script or startup file not specified. Please configure the system first.\n");
        return;
    }

    console->AppendText("Building project...\n");

    wxTextFile configmakefile(configMakefile);
    if (configmakefile.Exists())
    {
        configmakefile.Open();
        configmakefile.Clear(); // Xóa nội dung cũ
    }
    else
    {
        configmakefile.Create();
    }

    wxString projectPathMask = projectPath;
    projectPathMask.Replace("\\", "/");
    wxString ProjecName = wxFileName(projectPathMask).GetFullName();
    configmakefile.AddLine(wxString::Format("PROJ_NAME := %s", ProjecName));
    configmakefile.AddLine(wxString::Format("PRO_DIR := %s", projectPathMask));
    configmakefile.AddLine(wxString::Format("LINKER_SCRIPT := %s", linkerPath));
    configmakefile.AddLine(wxString::Format("STARTUP_FILE := %s", startupPath));
    if (!libraryPath.IsEmpty())
    {
        libraryPath.Replace("\\", "/");
        configmakefile.AddLine(wxString::Format("LIB_DIR := %s", libraryPath));

        wxString savePath = projectPath + "/saveLibrary.txt"; // Nối đường dẫn đúng cú pháp

        wxFile fileSaveLib(savePath, wxFile::write);
        if (fileSaveLib.IsOpened())
        {
            wxString data = libraryPath;
            fileSaveLib.Write(data);
            fileSaveLib.Close(); // Phải viết hoa Close và gọi đúng
        }
        else
        {
            console->AppendText("Cannot open file for writing: " + savePath + "\n");
        }
    }

    configmakefile.Write();
    configmakefile.Close();

    wxString cleanCommand = wxString::Format(
        "make -C \"%s\" -f \"%s\" clean",
        projectPath, // Thư mục dự án
        makefilePath // Đường dẫn đến Makefile
    );

    wxArrayString output, errors;
    long result = wxExecute(cleanCommand, output, errors, wxEXEC_SYNC);

    wxString buildCommand = wxString::Format(
        "make -C \"%s\" -f \"%s\"",
        projectPath, // Thư mục dự án
        makefilePath // Đường dẫn đến Makefile
    );

    result = wxExecute(buildCommand, output, errors, wxEXEC_SYNC);

    // Hiển thị đầu ra lên console
    for (const wxString &line : output)
    {
        console->AppendText(line + "\n");
    }

    // Hiển thị lỗi (nếu có) lên console
    for (const wxString &error : errors)
    {
        console->AppendText("ERROR: " + error + "\n");
    }

    if (result == 0)
    {
        console->AppendText("Build completed successfully.\n");
    }
    else
    {
        console->AppendText(wxString::Format("Build failed with exit code %ld.\n", result));
    }
    console->SetSelection(console->GetLength(), console->GetLength());
    console->EnsureCaretVisible();
}

void STM32IDE::OnUpload(wxCommandEvent &event)
{
    console->Clear();
    console->AppendText("Uploading...\n");
    wxArrayString output, errors;
    wxString upLoadCommand = wxString::Format(
        "make -C \"%s\" -f \"%s\" run",
        projectPath, // Thư mục dự án
        makefilePath // Đường dẫn đến Makefile
    );
    long result = wxExecute(upLoadCommand, output, errors, wxEXEC_SYNC);
    for (const wxString &line : output)
    {
        console->AppendText(line + "\n");
    }
    console->SetSelection(console->GetLength(), console->GetLength());
    console->EnsureCaretVisible();
}

void STM32IDE::OnRun(wxCommandEvent &event)
{
    OnBuild(event);
    OnUpload(event);
}

void STM32IDE::OnSave(wxCommandEvent &event)
{
    if (currentFilePath.IsEmpty())
    {
        if (projectPath.IsEmpty())
        {
            console->AppendText("Please select a project directory first using File > Open Project.\n");
            return;
        }
        wxFileDialog saveDlg(this, "Save C File", projectPath, "", "C Files (*.c;*.h)|*.c;*.h", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
        if (saveDlg.ShowModal() == wxID_OK)
        {
            currentFilePath = saveDlg.GetPath();
            console->AppendText("Selected file to save: " + currentFilePath + "\n");
        }
        else
        {
            console->AppendText("Save canceled by user.\n");
            return; // Không lưu nếu người dùng hủy
        }
    }

    console->AppendText(currentFilePath);
    wxFile file(currentFilePath, wxFile::write);
    if (!file.IsOpened())
    {
        console->AppendText("Cannot open file for writing: " + currentFilePath + "\n");
        return;
    }

    wxString content = editor->GetValue();
    console->AppendText("Saving content length: " + std::to_string(content.Length()) + "\n");

    if (file.Write(content) == 0)
    {
        console->AppendText("Write operation failed.\n");
        file.Close();
        return;
    }

    file.Close();
    console->AppendText("Saved file: " + currentFilePath + "\n");
    console->SetSelection(console->GetLength(), console->GetLength());
    console->EnsureCaretVisible();

    treeManager->LoadDirectoryTree(projectPath); // Cập nhật cây thư mục
}

void STM32IDE::OnKeyDown(wxKeyEvent &event)
{
    if (event.GetKeyCode() == 'S' && event.ControlDown())
    {
        wxCommandEvent cmdEvent(wxEVT_MENU, wxID_SAVE);
        OnSave(cmdEvent);
    }
    else if (event.GetKeyCode() == 'O' && event.ControlDown())
    {
        wxCommandEvent cmdEvent(wxEVT_MENU, wxID_OPEN);
        OnOpenFile(cmdEvent);
    }
    else if (event.GetKeyCode() == 'N' && event.ControlDown())
    {
        wxCommandEvent cmdEvent(wxEVT_MENU, wxID_NEW);
        OnNewFile(cmdEvent);
    }
    else
    {
        event.Skip();
    }
}

void STM32IDE::OnDebug(wxCommandEvent &event)
{
    if (debugmanager == nullptr)
    {
        debugmanager = new DebugManager(this);
        return;
    }
    isDebugRunning = !isDebugRunning; // Đảo ngược trạng thái debug
    if (isDebugRunning)
    {
        debugmanager->StopDebugSession();                                                               // Dừng phiên debug hiện tại nếu có
        wxString elfPath = projectPath + "\\Output\\" + wxFileName(projectPath).GetFullName() + ".elf"; // Giả sử file ELF nằm trong thư mục build
        if (!wxFile::Exists(elfPath))
        {
            console->AppendText("ELF file does not exist: " + elfPath + "\n");
            isDebugRunning = false; // Đặt lại trạng thái nếu không tìm thấy file ELF
            return;
        }
        bool statusStart = debugmanager->StartDebugSession(elfPath, toolPath);
        if (!statusStart)
        {
            console->AppendText("Failed to start debug session. Please check your configuration.\n");
            isDebugRunning = false; // Đặt lại trạng thái nếu không thể bắt đầu phiên debug
            return;
        }
        console->AppendText("Debug session started.\n");
    }
    else
    {
        debugmanager->StopDebugSession(); // Dừng phiên debug
        console->AppendText("Debug session stopped.\n");
    }
}

void STM32IDE::OnConfigSystem(wxCommandEvent &event)
{
    wxString savePath = projectPath + "/saveLibrary.txt"; // Nối đường dẫn đúng cú pháp
    if (!wxFile::Exists(savePath))
    {
        wxFile(savePath, wxFile::write);
    }
    ConfigSystemDialog dialog(this, linkerPath, startupPath, libraryPath, currentWorkingDir, projectPath);
    dialog.ShowModal();
}

void STM32IDE::OnGdbOutput(wxCommandEvent &event)
{
    OutputGDB = event.GetString();
    if (!OutputGDB.IsEmpty())
    {
        console->AppendText(OutputGDB);

        // Cập nhật core registers
        debugmanager->FillValueCoreRegister(OutputGDB, _registerModel->GetGroups()[0]);

        // Cập nhật peripheral registers
        auto &groups = _registerModel->GetGroups();
        for (size_t i = 1; i < groups.size(); ++i)
        {
            debugmanager->FillValuePeripheralRegister(OutputGDB, groups[i]);
        }

        // Refresh tất cả các cửa sổ RegisterView đang mở
        for (auto &[id, viewPtr] : registerViews)
        {
            if (viewPtr && viewPtr->IsShown())
            {
                viewPtr->RefreshView();
            }
        }
        if (memoryView && memoryView->IsShown())
        {
            debugmanager->FillValueMemory(OutputGDB, memoryView->memoryData);
            memoryView->FillGridWithData32Bit(memoryView->memoryData, memoryView->addrStr);
        }

        console->SetSelection(console->GetLength(), console->GetLength());
        console->EnsureCaretVisible();
    }
}

void STM32IDE::OnMarginClick(wxStyledTextEvent &event)
{
    wxFileName fn(currentFilePath);
    wxString nameCurrentFile = fn.GetFullName(); // Lấy tên file cùng phần mở rộng
    if (debugmanager->IsRunning())
    {
        int pos = event.GetPosition();            // vị trí con trỏ
        int line = editor->LineFromPosition(pos); // lấy số dòng từ vị trí

        int markers = editor->MarkerGet(line);

        if (markers & (1 << 0))
        {
            editor->MarkerDelete(line, 0);
            debugmanager->RemoveBreakpoint(nameCurrentFile,line + 1); // Xóa breakpoint nếu đã có
            console->AppendText(wxString::Format("Removed breakpoint at line %d\n", line + 1));
        }

        else
        {
            editor->MarkerAdd(line, 0);
            debugmanager->AddBreakpoint(nameCurrentFile,line + 1); // Thêm breakpoint nếu chưa có
            console->AppendText(wxString::Format("Added breakpoint at line %d\n", line + 1));
        }
    }
    else
    {
        console->AppendText("Debug session is not running. Cannot toggle breakpoints.\n");
    }
}

void STM32IDE::OnViewMemory(wxCommandEvent &event)
{

    memoryView = new MemoryView(this, debugmanager);
    memoryView->Show();
    debugmanager->SendRequestMemory("0x08000000"); // Gửi yêu cầu lấy dữ liệu bộ nhớ
}

void STM32IDE::OnViewRegisters(wxCommandEvent &event)
{
    int id = event.GetId();

    // Map từ id menu đến index nhóm register trong _registerModel
    static const std::map<int, int> idToGroupIndex = {
        {ID_VIEW_CORE_REGISTERS, 0}, // Core registers - đứng đầu, index 0
        {ID_PERIPH_ADC1, 1},
        {ID_PERIPH_ADC2, 2},
        {ID_PERIPH_ADC3, 3},
        {ID_PERIPH_GPIOA, 4},
        {ID_PERIPH_GPIOB, 5},
        {ID_PERIPH_GPIOC, 6},
        {ID_PERIPH_GPIOD, 7},
        {ID_PERIPH_GPIOE, 8},
        {ID_PERIPH_GPIOF, 9},
        {ID_PERIPH_GPIOG, 10},
        {ID_PERIPH_I2C1, 11},
        {ID_PERIPH_I2C2, 12},
        {ID_PERIPH_SPI1, 13},
        {ID_PERIPH_SPI2, 14},
        {ID_PERIPH_SPI3, 15},
        {ID_PERIPH_DMA1, 16},
        {ID_PERIPH_DMA2, 17},
        {ID_PERIPH_TIM1, 18},
        {ID_PERIPH_TIM2, 19},
        {ID_PERIPH_TIM3, 20},
        {ID_PERIPH_TIM4, 21},
        {ID_PERIPH_TIM5, 22},
        {ID_PERIPH_TIM6, 23},
        {ID_PERIPH_TIM7, 24},
        {ID_PERIPH_TIM8, 25},
        {ID_PERIPH_TIM9, 26},
        {ID_PERIPH_TIM10, 27},
        {ID_PERIPH_TIM11, 28},
        {ID_PERIPH_TIM12, 29},
        {ID_PERIPH_TIM13, 30},
        {ID_PERIPH_TIM14, 31},
        {ID_PERIPH_USART1, 32},
        {ID_PERIPH_USART2, 33},
        {ID_PERIPH_USART3, 34},
        {ID_PERIPH_UART4, 35},
        {ID_PERIPH_UART5, 36},
        {ID_PERIPH_RCC, 37},
        {ID_PERIPH_FLASH, 38},
    };

    auto it = idToGroupIndex.find(id);
    if (it == idToGroupIndex.end())
    {
        // id không hợp lệ hoặc chưa xử lý
        return;
    }

    int groupIndex = it->second;

    // Tạo mới RegisterView nếu chưa có
    if (registerViews.find(id) == registerViews.end() || !registerViews[id])
    {
        registerViews[id] = std::make_unique<RegisterView>(this, &_registerModel->GetGroups()[groupIndex]);
    }

    registerViews[id]->Show();
    registerViews[id]->Raise();

    // Gửi yêu cầu lấy dữ liệu register
    if (groupIndex == 0)
    {
        debugmanager->SendRequestCoreRegister();
    }
    else
    {
        debugmanager->SendRequestPeripheralRegister(_registerModel->GetGroups()[groupIndex]);
    }
}

void STM32IDE::OnViewASM(wxCommandEvent &event){
    asmViewDialog = new AsmViewDialog(this);
    asmViewDialog->Show();
}

void STM32IDE::OnDebugStepInto(wxCommandEvent &event)
{
    debugmanager->SendStepIntoCommand(); // Gọi hàm StepInto trong DebugManager
}
void STM32IDE::OnDebugStepOver(wxCommandEvent &event)
{
    debugmanager->SendStepOverCommand(); // Gọi hàm StepOver trong DebugManager
}
void STM32IDE::OnDebugStepOut(wxCommandEvent &event)
{
    debugmanager->SendStepOutCommand(); // Gọi hàm StepOut trong DebugManager
}
void STM32IDE::OnDebugContinue(wxCommandEvent &event)
{
    debugmanager->SendContinueCommand(); // Gọi hàm Continue trong DebugManager
}
void STM32IDE::OnDebugStop(wxCommandEvent &event)
{
    debugmanager->SendStopCommand(); // Dừng phiên debug
}
void STM32IDE::OnDebugRestart(wxCommandEvent &event)
{
    debugmanager->SendResetCommand(); // Gọi hàm Restart trong DebugManager
}

