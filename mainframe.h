#ifndef CMAINFRAME_H
#define CMAINFRAME_H

#include <wx/grid.h>
#include <wx/wx.h>

class CMainFrame : public wxFrame
{
private:
    enum { TIMER_ID = wxID_HIGHEST + 1 };

    wxTimer m_timer;
    wxTextCtrl* m_secDataTime;
    wxTextCtrl* m_dataTime;
    wxGrid* m_grid;
    wxTextCtrl* m_result;

    void OnTimerProcess(wxTimerEvent& event);
    void OnConvert(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()

public:
    CMainFrame(wxFrame* frame);
    ~CMainFrame();
};

#endif // CMAINFRAME_H
