#include "DebugManager.h"

wxDEFINE_EVENT(EVT_DEBUG_OUTPUT, wxCommandEvent);

DebugManager::DebugManager(wxWindow *parent)
    : m_parent(parent),
      m_gdbServerProcess(nullptr),
      m_gdbClientProcess(nullptr),
      m_outputTimer(nullptr),
      m_isRunning(false)
{
    m_gdbServerProcess = new ProcessHandle(m_parent);
    m_gdbClientProcess = new ProcessHandle(m_parent);
    m_outputTimer = new wxTimer(this);
    Bind(wxEVT_TIMER, &DebugManager::OnGdbOutput, this, m_outputTimer->GetId());
    Bind(wxEVT_END_PROCESS, &DebugManager::OnProcessTerminated, this);
}

DebugManager::~DebugManager()
{
    StopDebugSession();
    delete m_gdbServerProcess;
    delete m_gdbClientProcess;
    delete m_outputTimer;
}

bool DebugManager::StartDebugSession(const wxString &elfPath, const wxString &toolDirPath)
{
    if (m_isRunning)
        return false;

    // 1. Start GDB Server
    wxString gdbServerCmd = toolDirPath + "/Debug_GDB/bin/st-util.exe";
    long pidServer = m_gdbServerProcess->RunProcess(gdbServerCmd, false);
    if (pidServer <= 0)
        return false;

    // 2. Start GDB Client with elf file
    wxString gdbClientCmd = wxString::Format("%s/GNU_Toolchain/GCC_NEW/bin/arm-none-eabi-gdb.exe %s", toolDirPath, elfPath);
    //m_gdbWinProcess.Start(gdbClientCmd);
    
    long pidClient = m_gdbClientProcess->RunProcess(gdbClientCmd, true);

    if (pidClient <= 0)
    {
        m_gdbServerProcess->KillProcess();
        return false;
    }

    m_isRunning = true;
    wxString connectCmd = wxString::Format("target remote localhost:%d\n", 4242);
    //m_gdbWinProcess.WriteToStdin(connectCmd);
    m_gdbClientProcess->SendCommand("target remote localhost:4242\n");
    m_outputTimer->Start(100);
    return true;
}

void DebugManager::StopDebugSession()
{
    if (!m_isRunning)
        return;
    m_outputTimer->Stop();

    if (m_gdbClientProcess->IsRunning())
        m_gdbClientProcess->KillProcess();
    if (m_gdbServerProcess->IsRunning())
        m_gdbServerProcess->KillProcess();

    m_isRunning = false;
}

void DebugManager::SendCommand(const wxString &cmd)
{
    if (m_isRunning && m_gdbClientProcess->IsRunning())
    {
        m_gdbClientProcess->SendCommand(cmd);
    }
}

void DebugManager::AddBreakpoint(wxString currentlyFile,int line)
{
    wxString cmd = wxString::Format("break %s:%d",currentlyFile, line);
    SendCommand(cmd);
}

void DebugManager::RemoveBreakpoint(wxString currentlyFile,int line)
{
    wxString cmd = wxString::Format("clear %s:%d",currentlyFile, line);
    SendCommand(cmd);
}

void DebugManager::OnGdbOutput(wxTimerEvent &event)
{
    if (!m_gdbClientProcess->IsRunning())
    {
        m_outputTimer->Stop();
        m_isRunning = false;
        return;
    }

    wxInputStream *outStream = m_gdbClientProcess->GetOutputStream();
    if (outStream && outStream->CanRead())
    {
        wxString output;
        while (outStream->CanRead())
        {
            char buf[1024];
            size_t bytesRead = outStream->Read(buf, sizeof(buf)).LastRead();
            if (bytesRead == 0)
                break;
            output.Append(wxString::From8BitData(buf, bytesRead));
        }

        if (!output.IsEmpty())
        {
            wxCommandEvent evt(EVT_DEBUG_OUTPUT);
            evt.SetString(output);
            m_parent->GetEventHandler()->AddPendingEvent(evt);
        }
    }
}

void DebugManager::OnProcessTerminated(wxProcessEvent &event)
{
    if (event.GetPid() == m_gdbClientProcess->GetPID() || event.GetPid() == m_gdbServerProcess->GetPID())
    {
        StopDebugSession();
        // Có thể notify UI rằng debug đã kết thúc
    }
}

void DebugManager::SendRequestPeripheralRegister(RegisterGroup registerGroup)
{
    for (auto reg : registerGroup.GetRegisters())
    {
        wxString cmd = wxString::Format("x/wx 0x%08X", reg.GetAddress());
        DebugManager::SendCommand(cmd);
    }
}

void DebugManager::SendRequestCoreRegister()
{
    wxString cmd = "i r";
    DebugManager::SendCommand(cmd);
}

void DebugManager::FillValuePeripheralRegister(wxString output, RegisterGroup &registerGroup)
{
    std::istringstream stream(std::string(output.mb_str()));
    std::string line;

    while (std::getline(stream, line))
    {
        // Loại bỏ prefix "(gdb) " nếu có
        const std::string prefix = "(gdb)";
        size_t prefix_pos = line.find(prefix);
        if (prefix_pos != std::string::npos)
        {
            line = line.substr(prefix_pos + prefix.length());
        }

        // Tìm vị trí dấu ':'
        auto pos = line.find(':');
        if (pos == std::string::npos)
            continue;

        std::string addrStr = line.substr(0, pos);
        std::string valStr = line.substr(pos + 1);

        // Loại bỏ khoảng trắng 2 đầu
        addrStr.erase(0, addrStr.find_first_not_of(" \t"));
        addrStr.erase(addrStr.find_last_not_of(" \t") + 1);
        valStr.erase(0, valStr.find_first_not_of(" \t"));
        valStr.erase(valStr.find_last_not_of(" \t") + 1);

        // Chuyển hex string thành số
        uint32_t addr = 0, value = 0;
        try
        {
            addr = std::stoul(addrStr, nullptr, 16);
            value = std::stoul(valStr, nullptr, 16);
        }
        catch (...)
        {
            continue;
        }

        // Cập nhật giá trị cho register đúng địa chỉ
        auto &regs = registerGroup.GetRegisters(); // Cần đảm bảo GetRegisters trả về non-const để có thể sửa
        for (auto &reg : regs)
        {
            if (reg.GetAddress() == addr)
            {
                reg.SetValue(value);
                break;
            }
        }
    }
}

void DebugManager::FillValueCoreRegister(wxString output, RegisterGroup &_registerGroupCore)
{
    std::istringstream stream(std::string(output.mb_str()));
    std::string line;

    auto &coreRegs = _registerGroupCore.GetRegisters(); // Ví dụ biến lưu core registers

    while (std::getline(stream, line))
    {
        std::istringstream linestream(line);
        std::string regName;
        std::string valHex;

        if (!(linestream >> regName >> valHex))
            continue;

        // valHex có thể ở dạng "0x..." hoặc decimal, ta chỉ parse hex
        uint32_t value = 0;
        try
        {
            if (valHex.find("0x") == 0 || valHex.find("0X") == 0)
                value = std::stoul(valHex, nullptr, 16);
            else
                value = std::stoul(valHex);
        }
        catch (...)
        {
            continue;
        }

        // Tìm register có tên regName và set value
        for (auto &reg : coreRegs)
        {
            if (reg.GetName() == regName)
            {
                reg.SetValue(value);
                break;
            }
        }
    }
}

void DebugManager::SendRequestMemory(const wxString &startAddr)
{
    wxString cmd = wxString::Format("x/64wx %s", startAddr);
    wxLogMessage("Sending memory request: %s", cmd);
    SendCommand(cmd);
}

void DebugManager::FillValueMemory(wxString output, std::vector<uint32_t> &memoryData)
{
    std::istringstream stream(std::string(output.mb_str()));
    std::string line;

    memoryData.clear(); // Xóa dữ liệu cũ

    while (std::getline(stream, line))
    {
        // Kiểm tra dòng có chứa "<vectors" không
        if (line.find("<") == std::string::npos)
            continue; // Không phải dòng dữ liệu memory cần lấy

        // Tìm dấu ':' để tách phần địa chỉ và phần dữ liệu
        size_t colonPos = line.find(':');
        if (colonPos == std::string::npos)
            continue;

        std::string valuesStr = line.substr(colonPos + 1);
        std::istringstream valuesStream(valuesStr);
        std::string valueToken;

        while (valuesStream >> valueToken)
        {
            try
            {
                // Chuyển chuỗi hex sang số uint32_t
                uint32_t val = std::stoul(valueToken, nullptr, 16);
                memoryData.push_back(val);
            }
            catch (...)
            {
                // Bỏ qua nếu không chuyển được
                continue;
            }
        }
    }
}

void DebugManager::SendStepIntoCommandASM(){
    wxString cmd = "stepi";
    DebugManager::SendCommand(cmd);
}

void DebugManager::SendStepIntoCommand()
{
    wxString cmd = "step";
    SendCommand(cmd);
}
void DebugManager::SendStepOverCommand()
{
    wxString cmd = "next";
    SendCommand(cmd);
}
void DebugManager::SendStepOutCommand()
{
    wxString cmd = "finish";
    SendCommand(cmd);
}
void DebugManager::SendContinueCommand()
{
    wxString cmd = "continue";
    SendCommand(cmd);
}
void DebugManager::SendStopCommand()
{
    // wxString cmd = "kill";
    // SendCommand(cmd);
    m_gdbWinProcess.Interrupt();
}
void DebugManager::SendResetCommand()
{
    wxString cmd = "monitor reset";
    SendCommand(cmd);
}