
#include <wx/wxprec.h>
 
#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif
 
#include "filedialog.h"
 
IMPLEMENT_APP(RTDConfApp) // Initializes the RTDConfApp class...
 
// .. and tells our program to run it
bool RTDConfApp::OnInit()
{
	// Create an instance of our frame, or window
	RTDConfFrame *RTDConfWin = new RTDConfFrame(
		_("Edit"), wxPoint(1, 1), wxSize(300, 200));
	RTDConfWin->Show(TRUE); // show the window
	SetTopWindow(RTDConfWin); // and finally, set it as the main window
	return TRUE;
}
 
RTDConfFrame::RTDConfFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
: wxFrame((wxFrame*) NULL, -1, title, pos, size)
{
	CreateStatusBar(2);
 
	RTDConfMenu = new wxMenuBar();
	wxMenu *FileMenu = new wxMenu();
 
	FileMenu->Append(RTDCONFEDIT_New,
		_("&New"), _("Create a new RTD configuration file"));
 
	FileMenu->AppendSeparator();
	FileMenu->Append(RTDCONFEDIT_Open,
		_("&Open"), _("Open an existing RTD configuration file"));
	FileMenu->Append(RTDCONFEDIT_Close,
		_("&Close"), _("Close the current RTD configuration file"));
 
	FileMenu->AppendSeparator();
	FileMenu->Append(RTDCONFEDIT_Save,
		_("&Save"), _("Save the current RTD configuration file"));
	FileMenu->Append(RTDCONFEDIT_SaveAs,
		_("Save &As"), _("Save the current RTD configure with a different filename"));
 
	FileMenu->AppendSeparator();
	FileMenu->Append(RTDCONFEDIT_Quit,
		_("&Quit"), _("Close the RTD configuration editor window"));
 
	RTDConfMenu->Append(FileMenu, _("&File"));
	SetMenuBar(RTDConfMenu);
 
	RTDConfEditBox = new wxTextCtrl(
		this, TEXT_Main, _("Hi!"), wxDefaultPosition, wxDefaultSize, 
		wxTE_MULTILINE | wxTE_RICH , wxDefaultValidator, wxTextCtrlNameStr);
 
	Maximize(); // Maximize the window
}
 
void RTDConfFrame::NewFile(wxCommandEvent& WXUNUSED(event))
{
	// Clear the edit box
	RTDConfEditBox->Clear();
	// reset the path of our current open file
	CurrentDocPath = wxT("./");
	// Set the Title to reflect the file open
	SetTitle(_("Edit - untitled *"));
}
 
void RTDConfFrame::OpenFile(wxCommandEvent& WXUNUSED(event))
{
	// wxFileDialog *OpenDialog = new wxFileDialog(
	// 	this, _("Choose an RTD configuration to open"), wxEmptyString, wxEmptyString,
	// 	_("Text files (*.txt)|*.txt|C++ Source Files (*.cpp, *.cxx)|*.cpp;*.cxx|C Source files (*.c)|*.c|C header files (*.h)|*.h"),
	// 	wxFD_OPEN, wxDefaultPosition);

	wxFileDialog *OpenDialog = new wxFileDialog(
		this, _("Choose an RTD configuration to open"), wxEmptyString, wxEmptyString,
		_("RTD Configuration file (*.rtdconf)|*.rtdconf"),
		wxFD_OPEN, wxDefaultPosition);
 
	// Creates a "open file" dialog with 4 file types
	if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "cancel"
	{
		CurrentDocPath = OpenDialog->GetPath();
 
		// Sets our current RTD configuration file to the file the user selected
		RTDConfEditBox->LoadFile(CurrentDocPath); //Opens that file
		// Set the Title to reflect the  file open
		SetTitle(wxString("Edit - ") << OpenDialog->GetFilename());
	}
}
 
void RTDConfFrame::CloseFile(wxCommandEvent& WXUNUSED(event))
{
	// Clear the Text Box
	RTDConfEditBox->Clear();
	// Reset the current File being edited
	CurrentDocPath = wxT("C:/");
	// Set the Title to reflect the file open
	SetTitle(_("Edit - untitled *"));
}
 
void RTDConfFrame::SaveFile(wxCommandEvent& WXUNUSED(event))
{
	// Save to the already-set path for the document
	RTDConfEditBox->SaveFile(CurrentDocPath);
}
 
void RTDConfFrame::SaveFileAs(wxCommandEvent& WXUNUSED(event))
{
	// wxFileDialog *SaveDialog = new wxFileDialog(
	// 	this, _("Save File As _?"), wxEmptyString, wxEmptyString,
	// 	_("Text files (*.txt)|*.txt|C++ Source Files (*.cpp)|*.cpp|C Source files (*.c)|*.c|C header files (*.h)|*.h"),
	// 	wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);
	wxFileDialog *SaveDialog = new wxFileDialog(
		this, _("Save File As _?"), wxEmptyString, wxEmptyString,
		_("RTD Configuration file (*.rtdconf)|*.rtdconf"),
		wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);

	// Creates a Save Dialog with 4 file types
	if (SaveDialog->ShowModal() == wxID_OK) // If the user clicked "OK"
	{
		CurrentDocPath = SaveDialog->GetPath();
		// set the path of our current RTD configuration file to the file the user chose to save under
		RTDConfEditBox->SaveFile(CurrentDocPath); // Save the file to the selected path
		// Set the Title to reflect the file open
		SetTitle(wxString("Edit - ") << SaveDialog->GetFilename());
	}
 
	// Clean up after ourselves
	SaveDialog->Destroy();
}
 
void RTDConfFrame::Quit(wxCommandEvent& WXUNUSED(event))
{
	Close(TRUE); // Close the window
}
