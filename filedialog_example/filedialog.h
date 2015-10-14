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
 
// RTDConfFrame handles the RTD configuration file editor,
// and contains the window and all objects in it.
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
	RTDCONFEDIT_New,
	RTDCONFEDIT_Open,
	RTDCONFEDIT_Close,
	RTDCONFEDIT_Save,
	RTDCONFEDIT_SaveAs,
	RTDCONFEDIT_Quit
};
 
BEGIN_EVENT_TABLE ( RTDConfFrame, wxFrame )
	EVT_MENU(RTDCONFEDIT_New, RTDConfFrame::NewFile)
	EVT_MENU(RTDCONFEDIT_Open, RTDConfFrame::OpenFile) 
	EVT_MENU(RTDCONFEDIT_Close, RTDConfFrame::CloseFile)
	EVT_MENU(RTDCONFEDIT_Save, RTDConfFrame::SaveFile)
	EVT_MENU(RTDCONFEDIT_SaveAs, RTDConfFrame::SaveFileAs)
	EVT_MENU(RTDCONFEDIT_Quit, RTDConfFrame::Quit)
END_EVENT_TABLE()
