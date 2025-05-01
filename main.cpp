#include <wx/wx.h>
#include <wx/treectrl.h>
#include <wx/dir.h>
#include <wx/file.h>
#include <wx/filename.h> // Thêm include này để dùng wxFileName
#include <wx/filedlg.h>
#include <wx/stdpaths.h>
#include <wx/artprov.h>

// Lớp dữ liệu cho wxTreeCtrl
class MyTreeItemData : public wxTreeItemData {
public:
    MyTreeItemData(const wxString& path) : m_path(path) {}
    const wxString& GetPath() const { return m_path; }

private:
    wxString m_path;
};

class STM32IDE : public wxFrame {
public:
    STM32IDE() : wxFrame(nullptr, wxID_ANY, "STM32 IDE Handmade", wxDefaultPosition, wxSize(800, 600)) {
        Maximize(); // Tối đa hóa cửa sổ

        // Menu Bar
        wxMenuBar* menubar = new wxMenuBar();
        wxMenu* fileMenu = new wxMenu();
        fileMenu->Append(wxID_NEW, "New File");
        fileMenu->Append(wxID_OPEN, "Open File");
        fileMenu->Append(ID_OPEN_PROJECT, "Open Project");
        menubar->Append(fileMenu, "File");
        wxMenu* buildMenu = new wxMenu();
        buildMenu->Append(ID_BUILD, "Build");
        buildMenu->Append(ID_UPLOAD, "Upload");
        menubar->Append(buildMenu, "Build");
        SetMenuBar(menubar);

        // Toolbar
        wxToolBar* toolbar = CreateToolBar();
        wxBitmap runBitmap = wxArtProvider::GetBitmap(wxART_EXECUTABLE_FILE, wxART_TOOLBAR);
        wxBitmap buildBitmap = wxArtProvider::GetBitmap(wxART_HARDDISK, wxART_TOOLBAR);
        toolbar->AddTool(ID_RUN, "Run", runBitmap, "Run");
        toolbar->AddTool(ID_BUILD, "Build", buildBitmap, "Build");
        toolbar->Realize();

        // Layout
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
        wxBoxSizer* hSizer = new wxBoxSizer(wxHORIZONTAL);

        // Directory Tree
        tree = new wxTreeCtrl(this, wxID_ANY);
        tree->SetMinSize(wxSize(200, -1));
        tree->SetMaxSize(wxSize(250, -1));
        hSizer->Add(tree, 0, wxEXPAND);

        // Code Editor
        editor = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
        editor->SetMinSize(wxSize(400, 300));
        hSizer->Add(editor, 1, wxEXPAND);

        mainSizer->Add(hSizer, 1, wxEXPAND);

        // Output Console
        console = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(-1, 100), wxTE_MULTILINE | wxTE_READONLY);
        mainSizer->Add(console, 0, wxEXPAND);

        SetSizer(mainSizer);

        // Bind Events
        Bind(wxEVT_MENU, &STM32IDE::OnNewFile, this, wxID_NEW);
        Bind(wxEVT_MENU, &STM32IDE::OnOpenFile, this, wxID_OPEN);
        Bind(wxEVT_MENU, &STM32IDE::OnOpenProject, this, ID_OPEN_PROJECT);
        Bind(wxEVT_MENU, &STM32IDE::OnBuild, this, ID_BUILD);
        Bind(wxEVT_MENU, &STM32IDE::OnUpload, this, ID_UPLOAD);
        Bind(wxEVT_TOOL, &STM32IDE::OnRun, this, ID_RUN);
        Bind(wxEVT_TOOL, &STM32IDE::OnBuild, this, ID_BUILD);
        Bind(wxEVT_TREE_SEL_CHANGED, &STM32IDE::OnTreeSelect, this, tree->GetId());

        // Tự động mở hộp thoại chọn project khi khởi động
        wxDirDialog dlg(this, "Select Project Directory", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
        if (dlg.ShowModal() == wxID_OK) {
            projectPath = dlg.GetPath();
            LoadDirectoryTree();
        } else {
            console->AppendText("No project directory selected. Please select a project using File > Open Project.\n");
        }
    }

private:
    enum {
        ID_BUILD = wxID_HIGHEST + 1,
        ID_UPLOAD,
        ID_RUN,
        ID_OPEN_PROJECT
    };

    wxTreeCtrl* tree;
    wxTextCtrl* editor;
    wxTextCtrl* console;
    wxString projectPath; // Lưu đường dẫn thư mục dự án

    void LoadDirectoryTree() {
        tree->DeleteAllItems();
        if (projectPath.empty()) return;

        // Hiển thị thư mục gốc của dự án
        wxFileName projectDir(projectPath);
        wxTreeItemId root = tree->AddRoot(projectDir.GetFullName());
        LoadDirectory(root, projectPath);
        tree->Expand(root);
    }

    void LoadDirectory(wxTreeItemId parent, const wxString& path) {
        wxDir dir;
        if (!dir.Open(path)) {
            console->AppendText("Cannot access directory: " + path + "\n");
            return;
        }

        // Chỉ liệt kê các tệp và thư mục con trực tiếp (không đệ quy)
        wxString filename;
        bool cont = dir.GetFirst(&filename);
        while (cont) {
            wxString filepath = path + wxFILE_SEP_PATH + filename;
            wxTreeItemId child = tree->AppendItem(parent, filename);
            tree->SetItemData(child, new MyTreeItemData(filepath));
            cont = dir.GetNext(&filename);
        }
    }

    void OnTreeSelect(wxTreeEvent& event) {
        wxTreeItemId item = event.GetItem();
        if (!item.IsOk()) return;

        MyTreeItemData* data = dynamic_cast<MyTreeItemData*>(tree->GetItemData(item));
        if (data) {
            wxString filepath = data->GetPath();
            if (filepath.EndsWith(".c") || filepath.EndsWith(".h")) {
                wxFile file(filepath, wxFile::read);
                if (file.IsOpened()) {
                    wxString content;
                    file.ReadAll(&content);
                    editor->SetValue(content);
                    file.Close();
                } else {
                    console->AppendText("Cannot open file: " + filepath + "\n");
                }
            }
        }
    }

    void OnNewFile(wxCommandEvent& event) {
        if (projectPath.empty()) {
            console->AppendText("Please select a project directory first using File > Open Project.\n");
            return;
        }

        wxFileDialog saveDlg(this, "New C File", projectPath, "", "C Files (*.c;*.h)|*.c;*.h", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
        if (saveDlg.ShowModal() == wxID_OK) {
            wxString path = saveDlg.GetPath();
            wxFile file(path, wxFile::write);
            if (file.IsOpened()) {
                file.Write("// New C File\n#include <stdint.h>\n\nint main(void) {\n    return 0;\n}\n");
                file.Close();
                editor->SetValue("// New C File\n#include <stdint.h>\n\nint main(void) {\n    return 0;\n}\n");
                LoadDirectoryTree();
            } else {
                console->AppendText("Cannot create file: " + path + "\n");
            }
        }
    }

    void OnOpenFile(wxCommandEvent& event) {
        if (projectPath.empty()) {
            console->AppendText("Please select a project directory first using File > Open Project.\n");
            return;
        }

        wxFileDialog openDlg(this, "Open C File", projectPath, "", "C Files (*.c;*.h)|*.c;*.h", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
        if (openDlg.ShowModal() == wxID_OK) {
            wxString path = openDlg.GetPath();
            wxFile file(path, wxFile::read);
            if (file.IsOpened()) {
                wxString content;
                file.ReadAll(&content);
                editor->SetValue(content);
                file.Close();
            } else {
                console->AppendText("Cannot open file: " + path + "\n");
            }
        }
    }

    void OnOpenProject(wxCommandEvent& event) {
        wxDirDialog dlg(this, "Select Project Directory", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
        if (dlg.ShowModal() == wxID_OK) {
            projectPath = dlg.GetPath();
            LoadDirectoryTree();
        }
    }

    void OnBuild(wxCommandEvent& event) {
        console->Clear();
        console->AppendText("Building...\n");
        wxArrayString output, errors;
        long result = wxExecute("arm-none-eabi-gcc -v", output, errors, wxEXEC_SYNC);
        for (const auto& line : output) {
            console->AppendText(line + "\n");
        }
        for (const auto& line : errors) {
            console->AppendText(line + "\n");
        }
        if (result != 0) {
            console->AppendText("Build failed with exit code: " + wxString::Format("%ld", result) + "\n");
        }
    }

    void OnUpload(wxCommandEvent& event) {
        console->Clear();
        console->AppendText("Uploading...\n");
        wxArrayString output, errors;
        long result = wxExecute("openocd --version", output, errors, wxEXEC_SYNC);
        for (const auto& line : output) {
            console->AppendText(line + "\n");
        }
        for (const auto& line : errors) {
            console->AppendText(line + "\n");
        }
        if (result != 0) {
            console->AppendText("Upload failed with exit code: " + wxString::Format("%ld", result) + "\n");
        }
    }

    void OnRun(wxCommandEvent& event) {
        OnBuild(event);
        OnUpload(event);
    }
};

class MyApp : public wxApp {
public:
    bool OnInit() override {
        STM32IDE* frame = new STM32IDE();
        frame->Show();
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);