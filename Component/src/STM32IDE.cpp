// src/STM32IDE.cpp
#include "../include/STM32IDE.h"

const char *path_Debug_Icon = "D:/Simple_STM32xx_IDE/Component/Assets/DebugIcon.png";
const char *path_System_Icon = "D:/Simple_STM32xx_IDE/Component/Assets/System.png";
const char *path_Run_Icon = "D:/Simple_STM32xx_IDE/Component/Assets/RunIcon.png";
const char *path_Build_Icon = "D:/Simple_STM32xx_IDE/Component/Assets/BuildIcon.png";

STM32IDE::STM32IDE() : wxFrame(nullptr, wxID_ANY, "STM32 IDE Handmade", wxDefaultPosition, wxSize(800, 600))
{
    Maximize();

    currentWorkingDir = wxGetCwd(); // Biến mới để lưu đường dẫn hiện tại
    // Menu Bar
    wxMenuBar *menubar = new wxMenuBar();
    wxMenu *fileMenu = new wxMenu();
    fileMenu->Append(wxID_NEW, "New File");
    fileMenu->Append(wxID_OPEN, "Open File");
    fileMenu->Append(ID_NEW_FOLDER, "New Folder");
    fileMenu->Append(ID_OPEN_PROJECT, "Open Project");
    menubar->Append(fileMenu, "File");

    wxMenu *buildMenu = new wxMenu();
    buildMenu->Append(ID_BUILD, "Build");
    buildMenu->Append(ID_UPLOAD, "Upload");
    menubar->Append(buildMenu, "Build");

    wxMenu *PeripheralsMenu = new wxMenu();
    wxMenu *systemViewerMenu = new wxMenu();

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

    PeripheralsMenu->AppendSubMenu(systemViewerMenu, "System Viewer");
    PeripheralsMenu->Append(ID_CORE_PERIPHERALS, "Core Peripherals");
    menubar->Append(PeripheralsMenu, "Peripherals");
    SetMenuBar(menubar);

    // Toolbar
    wxToolBar *toolbar = CreateToolBar();
    wxBitmap runBitmap = wxArtProvider::GetBitmap(wxART_EXECUTABLE_FILE, wxART_TOOLBAR);
    // wxBitmap buildBitmap = wxArtProvider::GetBitmap(wxART_HARDDISK, wxART_TOOLBAR);

    // wxBitmap runBitmap(path_Run_Icon,wxBITMAP_TYPE_PNG);
    // wxImage runImage = runBitmap.ConvertToImage();
    // runImage = runImage.Scale(36,36);
    // runBitmap = wxBitmap(runImage);

    wxBitmap buildBitmap(path_Build_Icon, wxBITMAP_TYPE_PNG);
    wxImage BuildImage = buildBitmap.ConvertToImage();
    BuildImage = BuildImage.Scale(36, 36);
    buildBitmap = wxBitmap(BuildImage);

    wxBitmap configSystemBitmap(path_System_Icon, wxBITMAP_TYPE_PNG);
    wxImage configSystemImage = configSystemBitmap.ConvertToImage();
    configSystemImage = configSystemImage.Scale(36, 36);
    configSystemBitmap = wxBitmap(configSystemImage);

    wxBitmap debugBitmap(path_Debug_Icon, wxBITMAP_TYPE_PNG);
    wxImage debugImage = debugBitmap.ConvertToImage();
    debugImage = debugImage.Scale(36, 36);
    debugBitmap = wxBitmap(debugImage);

    toolbar->AddTool(ID_RUN, "Run", runBitmap, "Run");
    toolbar->AddTool(ID_BUILD, "Build", buildBitmap, "Build");
    toolbar->AddTool(ID_DEBUG, "Debug", debugBitmap, "Debug");
    toolbar->AddTool(ID_CONFIG_SYSTEM, "Config System", configSystemBitmap, "Config System");
    toolbar->Realize();

    // Layout
    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);

    tree = new wxTreeCtrl(this, wxID_ANY);
    tree->SetMinSize(wxSize(200, -1));
    tree->SetMaxSize(wxSize(250, -1));
    hSizer->Add(tree, 0, wxEXPAND);

    editor = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    editor->SetMinSize(wxSize(400, 300));
    hSizer->Add(editor, 1, wxEXPAND);

    mainSizer->Add(hSizer, 1, wxEXPAND);

    console = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(-1, 100), wxTE_MULTILINE | wxTE_READONLY);
    mainSizer->Add(console, 0, wxEXPAND);

    SetSizer(mainSizer);

    // Khởi tạo DirectoryTreeManager
    treeManager = new DirectoryTreeManager(tree, console);

    // Bind sự kiện cho wxTreeCtrl
    Bind(wxEVT_TREE_SEL_CHANGED, [this](wxTreeEvent &event)
         { treeManager->OnTreeSelect(event, editor); }, tree->GetId());

    // Bind Events
    Bind(wxEVT_MENU, &STM32IDE::OnNewFile, this, wxID_NEW);
    Bind(wxEVT_MENU, &STM32IDE::OnOpenFile, this, wxID_OPEN);
    Bind(wxEVT_MENU, &STM32IDE::OnOpenProject, this, ID_OPEN_PROJECT);
    Bind(wxEVT_MENU, &STM32IDE::OnBuild, this, ID_BUILD);
    Bind(wxEVT_MENU, &STM32IDE::OnUpload, this, ID_UPLOAD);
    Bind(wxEVT_TOOL, &STM32IDE::OnRun, this, ID_RUN);
    Bind(wxEVT_TOOL, &STM32IDE::OnBuild, this, ID_BUILD);
    Bind(wxEVT_TOOL, &STM32IDE::OnConfigSystem, this, ID_CONFIG_SYSTEM); // Bind sự kiện cho Config System
    
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
    }
}

void STM32IDE::OnBuild(wxCommandEvent &event)
{
    console->Clear();
    console->AppendText("Building...\n");
    wxArrayString output, errors;
    long result = wxExecute("arm-none-eabi-gcc -v", output, errors, wxEXEC_SYNC);
    for (const auto &line : output)
    {
        console->AppendText(line + "\n");
    }
    for (const auto &line : errors)
    {
        console->AppendText(line + "\n");
    }
    if (result != 0)
    {
        console->AppendText("Build failed with exit code: " + wxString::Format("%ld", result) + "\n");
    }
}

void STM32IDE::OnUpload(wxCommandEvent &event)
{
    console->Clear();
    console->AppendText("Uploading...\n");
    wxArrayString output, errors;
    long result = wxExecute("openocd --version", output, errors, wxEXEC_SYNC);
    for (const auto &line : output)
    {
        console->AppendText(line + "\n");
    }
    for (const auto &line : errors)
    {
        console->AppendText(line + "\n");
    }
    if (result != 0)
    {
        console->AppendText("Upload failed with exit code: " + wxString::Format("%ld", result) + "\n");
    }
}

void STM32IDE::OnRun(wxCommandEvent &event)
{
    OnBuild(event);
    OnUpload(event);
}

void STM32IDE::OnConfigSystem(wxCommandEvent &event)
{
    ConfigSystemDialog dialog(this, linkerPath, startupPath, makefilePath, currentWorkingDir);
    dialog.ShowModal();
}