#include <wx/string.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
 
#ifndef __DART_RTD_CONFEDIT_H_INCLUDED__   
#define __DART_RTD_CONFEDIT_H_INCLUDED__   

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
 
	wxBoxSizer         * boxRTDConfSizer;

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
 
#endif //end #define __DART_RTD_CONFEDIT_H_INCLUDED__   
