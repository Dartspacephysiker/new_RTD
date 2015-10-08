#include <wx/string.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
 
// RTDConfApp is the class for our application, it just acts
// as a container for the window or frame in RTDConfFrame.
class RTDConfApp: public wxApp
{
public:
	virtual bool OnInit();
};
 
// RTDConfFrame is the class for our window, it
// contains the window and all objects in it.
class RTDConfFrame: public wxFrame
{
public:
	RTDConfFrame( const wxString &title, const wxPoint &pos, const wxSize &size );
 
	void Quit( wxCommandEvent& event );
	void NewFile( wxCommandEvent& event );
	void OpenFile( wxCommandEvent& event );
	void SaveFile( wxCommandEvent& event );
	void SaveFileAs( wxCommandEvent& event );
	void CloseFile( wxCommandEvent& event );
 
	wxTextCtrl *RTDConfEditBox;
	wxMenuBar *RTDConfMenu;
	// The Path to the file we have open
	wxString CurrentDocPath;
 
	DECLARE_EVENT_TABLE()
};
 
enum
{
	// declares an id which will be used to call our button
	TEXT_Main = wxID_HIGHEST + 1,
	MENU_New,
	MENU_Open,
	MENU_Close,
	MENU_Save,
	MENU_SaveAs,
	MENU_Quit
};
 
BEGIN_EVENT_TABLE ( RTDConfFrame, wxFrame )
	EVT_MENU(MENU_New, RTDConfFrame::NewFile)
	EVT_MENU(MENU_Open, RTDConfFrame::OpenFile) 
	EVT_MENU(MENU_Close, RTDConfFrame::CloseFile)
	EVT_MENU(MENU_Save, RTDConfFrame::SaveFile)
	EVT_MENU(MENU_SaveAs, RTDConfFrame::SaveFileAs)
	EVT_MENU(MENU_Quit, RTDConfFrame::Quit)
END_EVENT_TABLE()
