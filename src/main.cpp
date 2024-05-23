#include <wx/wx.h>
#include <wx/filedlg.h>
#include <wx/progdlg.h>
#include <string>
#include "matrix/matrix.h"
#include "image/image.h"

// Главное окно приложения
class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title);

private:
    void OnOpen(wxCommandEvent& event);
    void OnApplyGaussianBlur(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);

    std::string inputPath;
    Image* image = nullptr;

    wxTextCtrl* ksizeInput;
    wxTextCtrl* sigmaInput;

wxDECLARE_EVENT_TABLE();
};

enum {
    ID_Open = 1,
    ID_ApplyGaussianBlur = 2,
    ID_Save = 3
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
                EVT_BUTTON(ID_Open, MyFrame::OnOpen)
                EVT_BUTTON(ID_ApplyGaussianBlur, MyFrame::OnApplyGaussianBlur)
                EVT_BUTTON(ID_Save, MyFrame::OnSave)
wxEND_EVENT_TABLE()

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame("Image Gaussian Blur Application");
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title)
        : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 300)) {
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);

    wxButton* btnOpen = new wxButton(panel, ID_Open, wxT("Open"));
    wxButton* btnApply = new wxButton(panel, ID_ApplyGaussianBlur, wxT("Apply Gaussian Blur"));
    wxButton* btnSave = new wxButton(panel, ID_Save, wxT("Save"));

    hbox->Add(btnOpen, 0, wxRIGHT, 5);
    hbox->Add(btnApply, 0, wxRIGHT, 5);
    hbox->Add(btnSave, 0, wxRIGHT, 5);

    wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText* ksizeLabel = new wxStaticText(panel, wxID_ANY, wxT("ksize:"));
    inputSizer->Add(ksizeLabel, 0, wxRIGHT, 5);
    ksizeInput = new wxTextCtrl(panel, wxID_ANY);
    inputSizer->Add(ksizeInput, 0, wxRIGHT, 10);

    wxStaticText* sigmaLabel = new wxStaticText(panel, wxID_ANY, wxT("sigma:"));
    inputSizer->Add(sigmaLabel, 0, wxRIGHT, 5);
    sigmaInput = new wxTextCtrl(panel, wxID_ANY);
    inputSizer->Add(sigmaInput, 0, wxRIGHT, 10);

    vbox->Add(inputSizer, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

    panel->SetSizer(vbox);

    // Создаем шрифт
    wxFont font(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Segoe UI");

    // Применяем шрифт к элементам управления
    ksizeLabel->SetFont(font);
    sigmaLabel->SetFont(font);
    ksizeInput->SetFont(font);
    sigmaInput->SetFont(font);
    btnOpen->SetFont(font);
    btnApply->SetFont(font);
    btnSave->SetFont(font);
}

void MyFrame::OnOpen(wxCommandEvent& event) {
    wxFileDialog openFileDialog(this, _("Open PGM file"), "", "", "PGM files (*.pgm)|*.pgm", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    inputPath = openFileDialog.GetPath().ToStdString();

    if (image) {
        delete image;
        image = nullptr;
    }

    image = new Image(5.0, 5, inputPath);
    wxLogMessage("Image loaded from '%s'.", inputPath);
}

void MyFrame::OnApplyGaussianBlur(wxCommandEvent& event) {
    if (!image) {
        wxLogError("No image loaded.");
        return;
    }

    long ksize;
    double sigma;
    if (!ksizeInput->GetValue().ToLong(&ksize) || !sigmaInput->GetValue().ToDouble(&sigma)) {
        wxLogError("Invalid ksize or sigma value.");
        return;
    }

    image->setKsize(ksize);
    image->setSigma(sigma);
    image->applyGaussianBlur();
    wxLogMessage("Gaussian Blur applied with ksize = %ld and sigma = %lf.", ksize, sigma);
}

void MyFrame::OnSave(wxCommandEvent& event) {
    if (!image) {
        wxLogError("No image to save.");
        return;
    }

    wxFileDialog saveFileDialog(this, _("Save PGM file"), "", "", "PGM files (*.pgm)|*.pgm", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxString outputPath = saveFileDialog.GetPath();

    wxProgressDialog progressDialog("Saving", "Saving the image, please wait...", 100, this, wxPD_APP_MODAL | wxPD_AUTO_HIDE);
    progressDialog.Pulse("Saving...");

    // Сохранение изображения
    image->saveToPGMFile(outputPath.ToStdString());

    progressDialog.Update(100);
    wxLogMessage("Image saved to '%s'.", outputPath);
}
