//dartRTD.h

#ifndef __DART_RTD_H_INCLUDED__   
#define __DART_RTD_H_INCLUDED__   


#include <fstream>

class DARTRTD_Measurement { 

  private:
    std::string        sName;
    std::string        sAbbrev;
    std::string        sUser;

    std::string        sRTDDataFile;
    std::ifstream      fsRTDDataFile;

    std::string        sRTDDataOut;
    std::ofstream      fsRTDDataOut;

    std::string        sDataType;
    unsigned short     uDataType;

    long int           lSPS;
};

class DartRTDApp: public wxApp
{
public:
    virtual bool OnInit();
};

class DartRTDFrame: public wxFrame
{
public:
    DartRTDFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
    void OnHello(wxCommandEvent& event);
    void OnLoadRTDConf(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};

#endif //end #define __DART_RTD_H_INCLUDED__   
