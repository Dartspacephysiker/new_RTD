//dartRTD.h

#ifndef __DART_RTD_H_INCLUDED__   
#define __DART_RTD_H_INCLUDED__   


#include <fstream>

const int ID_PLUS = 101;
const int ID_MINUS = 102;

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

/*The panel that holds the spectrograms*/
class SpectrogramPanel : public wxPanel
{
public:
    SpectrogramPanel(wxPanel *parent);

    void OnPlus(wxCommandEvent & event);
    void OnMinus(wxCommandEvent & event);

    wxButton *m_plus;
    wxButton *m_minus;
    wxPanel *m_parent;
    int count;

};

/*The panel that holds the list of available spectrograms*/
class SpectrListPanel : public wxPanel
{
public:
    SpectrListPanel(wxPanel *parent);

    void OnSetText(wxCommandEvent & event);

    wxStaticText *m_text;

};

class DartRTDFrame: public wxFrame
{
    wxMenu             * menuFile;
    wxMenu             * menuView;
    wxMenu             * menuHelp;
		       
    wxMenuBar          * menuBar;

public:
    DartRTDFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    SpectrogramPanel   * m_lp;
    SpectrListPanel    * m_rp;
    wxPanel            * m_parent;

private:
    void OnHello(wxCommandEvent& event);
    void OnLoadRTDConf(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};

#endif //end #define __DART_RTD_H_INCLUDED__   
