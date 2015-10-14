#ifndef __DART_RTD_CONFEDIT_H_INCLUDED__   
#define __DART_RTD_CONFEDIT_H_INCLUDED__   

#include <wx/string.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
 
#include "dartRTD.h"

// RTDConfFrame handles the RTD configuration file editor
class RTDConfFrame: public wxFrame
{
public:
    RTDConfFrame( const wxString &title, const wxPoint &pos, const wxSize &size, DartRTDFrame *callingFrame );
    
    void Quit( wxCommandEvent& event );
    void LoadConfFile( wxCommandEvent& event );
    void NewConfFile( wxCommandEvent& event );
    void OpenConfFile( wxCommandEvent& event );
    void SaveConfFile( wxCommandEvent& event );
    void SaveConfFileAs( wxCommandEvent& event );
    void CloseConfFile( wxCommandEvent& event );
    
    void SetConfFilename( const wxString confFilename );
    std::string          sCurrentConfFile;

    DartRTDFrame       * parentFrame;
    
    wxBoxSizer         * boxRTDConfSizer;
    
    wxTextCtrl         * RTDConfEditBox;
    wxMenuBar          * RTDConfMenu;
    
    // The Path to the file we have open
    wxString             CurrentDocPath;
    
    DECLARE_EVENT_TABLE()
};
 
enum
{
	// declares an id which will be used to call our button
	TEXT_Main = wxID_HIGHEST + 1,
	RTDCONFEDIT_Load,
	RTDCONFEDIT_New,
	RTDCONFEDIT_Open,
	RTDCONFEDIT_Close,
	RTDCONFEDIT_Save,
	RTDCONFEDIT_SaveAs,
	RTDCONFEDIT_Quit
};
 
#endif //end #define __DART_RTD_CONFEDIT_H_INCLUDED__   
