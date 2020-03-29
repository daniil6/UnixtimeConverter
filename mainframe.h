#ifndef CMAINFRAME_H
#define CMAINFRAME_H

//#include "RBKLib.h"
#include <convert_string_double.h>
#include <wtime.h>

#include <wx/grid.h>
#include <wx/wx.h>

class CMainFrame : public wxFrame
{
private:
    enum { TIMER_ID = wxID_HIGHEST + 1 };

    wxTimer m_timer;
    wxTextCtrl* m_secDataTime;
    wxTextCtrl* m_dataTime;
    wxGrid* m_gridIn;
    wxGrid* m_gridOut;
    wxTextCtrl* m_txtSecOut;
    wxTextCtrl* m_txtSecIn;

    void SetDefaultValue(tDateTime dateTime, wxString t_string);
    void SetDateAndTime();

    void OnTimerProcess(wxTimerEvent& event);
    void OnConvertSecondToDateTime(wxCommandEvent& event);
    void OnConvertDateTimeToSecond(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()

public:
    CMainFrame(wxFrame* frame);
    ~CMainFrame();
};

#endif // CMAINFRAME_H
