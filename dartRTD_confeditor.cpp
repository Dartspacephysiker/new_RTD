
#include <wx/wxprec.h>
 
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
 
#include "dartRTD_confeditor.h"
 
RTDConfFrame::RTDConfFrame(const wxString &title, const wxPoint &pos, const wxSize &size, DartRTDFrame *callingFrame )
: wxFrame((wxFrame*) NULL, -1, title, pos, size)
{
	CreateStatusBar(2);
 
	parentFrame = callingFrame;

	RTDConfMenu = new wxMenuBar();
	wxMenu *FileMenu = new wxMenu();
 
	FileMenu->Append(RTDCONFEDIT_Load,
		_("&Load RTD Config...\tCtrl-L"), _("Load the RTD configuration file that is currently open"));
 
	FileMenu->AppendSeparator();

	FileMenu->Append(RTDCONFEDIT_New,
		_("&New...\tCtrl-N"), _("Create a new RTD configuration file"));
 
	FileMenu->AppendSeparator();
	FileMenu->Append(RTDCONFEDIT_Open,
		_("&Open...\tCtrl-O"), _("Open an existing RTD configuration file"));
	FileMenu->Append(RTDCONFEDIT_Close,
		_("&Close...\tCtrl-W"), _("Close the current RTD configuration file"));
 
	FileMenu->AppendSeparator();
	FileMenu->Append(RTDCONFEDIT_Save,
		_("&Save...\tCtrl-S"), _("Save the current RTD configuration file"));
	FileMenu->Append(RTDCONFEDIT_SaveAs,
		_("Save &As...\tCtrl-Alt-S"), _("Save the current RTD configure with a different filename"));
 
	FileMenu->AppendSeparator();
	FileMenu->Append(RTDCONFEDIT_Quit,
		_("&Quit...\tCtrl-Q"), _("Close the RTD configuration editor window"));
 
	RTDConfMenu->Append(FileMenu, _("&File"));
	SetMenuBar(RTDConfMenu);
 
	RTDConfEditBox = new wxTextCtrl(
		this, TEXT_Main, _("Hi!"), wxDefaultPosition, wxDefaultSize, 
		wxTE_MULTILINE | wxTE_RICH , wxDefaultValidator, wxTextCtrlNameStr);
 
	boxRTDConfSizer = new wxBoxSizer(wxHORIZONTAL);
	boxRTDConfSizer->Add(RTDConfEditBox, 1, wxEXPAND | wxALL, 5);
	this->SetSizerAndFit(boxRTDConfSizer);
}
 
void RTDConfFrame::LoadConfFile(wxCommandEvent& WXUNUSED(event))
{
    parentFrame->SetRTDConfFile(sCurrentConfFile);
    parentFrame->LoadRTDConfFile(sCurrentConfFile);
}
 

void RTDConfFrame::NewConfFile(wxCommandEvent& WXUNUSED(event))
{
	// Clear the edit box
	RTDConfEditBox->Clear();
	// reset the path of our current open file
	CurrentDocPath = wxT("./");
	// Set the Title to reflect the file open
	SetTitle(_("RTD Configuration Editor - untitled.rtdconf *"));
}
 
void RTDConfFrame::OpenConfFile(wxCommandEvent& WXUNUSED(event))
{
	wxFileDialog *OpenDialog = new wxFileDialog(
		this, _("Choose an RTD configuration to open"), wxEmptyString, wxEmptyString,
		_("RTD Configuration file (*.rtdconf)|*.rtdconf"),
		wxFD_OPEN, wxDefaultPosition);
 
	// Creates a "open file" dialog with .rtdconf file type
	if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "cancel"
	{
		CurrentDocPath = OpenDialog->GetPath();
 
		// Sets our current RTD configuration file to the file the user selected
		RTDConfEditBox->LoadFile(CurrentDocPath); //Opens that file

		SetConfFilename(OpenDialog->GetFilename());

		// Set the Title to reflect the  file open
		SetTitle(wxString("RTD Configuration Editor - ") << OpenDialog->GetFilename()); 
	}
}
 
void RTDConfFrame::CloseConfFile(wxCommandEvent& WXUNUSED(event))
{
	// Clear the Text Box
	RTDConfEditBox->Clear();
	// Reset the current File being edited
	CurrentDocPath = wxT("./");
	// Set the Title to reflect the file open
	SetTitle(_("RTD Configuration Editor - untitled.rtdconf *"));
}
 
void RTDConfFrame::SaveConfFile(wxCommandEvent& WXUNUSED(event))
{
	// Save to the already-set path for the document
	RTDConfEditBox->SaveFile(CurrentDocPath);
}
 
void RTDConfFrame::SaveConfFileAs(wxCommandEvent& WXUNUSED(event))
{
	wxFileDialog *SaveDialog = new wxFileDialog(
		this, _("Save File As _?"), wxEmptyString, wxEmptyString,
		_("RTD Configuration file (*.rtdconf)|*.rtdconf"),
		wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);

	// Creates a Save Dialog
	if (SaveDialog->ShowModal() == wxID_OK) // If the user clicked "OK"
	{
		CurrentDocPath = SaveDialog->GetPath();
		// set the path of our current RTD configuration file to the file the user chose to save under
		RTDConfEditBox->SaveFile(CurrentDocPath); // Save the file to the selected path
		// Set the Title to reflect the file open
		SetTitle(wxString("RTD Configuration Editor - ") << SaveDialog->GetFilename());
	}
 
	// Clean up after ourselves
	SaveDialog->Destroy();
}

void RTDConfFrame::SetConfFilename( const wxString confFilename )
{
    sCurrentConfFile = confFilename.ToStdString();
}
 
void RTDConfFrame::Quit(wxCommandEvent& WXUNUSED(event))
{
	Close(TRUE); // Close the window
	//LoadNewRTDConfig();
}
