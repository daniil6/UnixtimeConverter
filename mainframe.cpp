#include "RBKLib.h"
#include "mainframe.h"

// 00:00 1 января 1970

BEGIN_EVENT_TABLE(CMainFrame, wxFrame)
EVT_TIMER(TIMER_ID, CMainFrame::OnTimerProcess)
END_EVENT_TABLE()

CMainFrame::CMainFrame(wxFrame* frame)
    : wxFrame(frame, wxID_ANY, wxT("UnixtimeConverter"))
    , m_timer(this, TIMER_ID)
{
    wxBoxSizer* main_sizer = new wxBoxSizer(wxHORIZONTAL);
    m_secDataTime = new wxTextCtrl(this, NewControlId(), wxT(""));
    m_dataTime = new wxTextCtrl(this, NewControlId(), wxT("0000-00-00 00:00:00"), wxDefaultPosition, wxSize(130, 10));
    main_sizer->Add(m_secDataTime, 1, wxEXPAND);
    main_sizer->Add(m_dataTime, 1, wxEXPAND);
    this->SetSizerAndFit(main_sizer);

    m_timer.Start(1000);
}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::OnTimerProcess(wxTimerEvent& event)
{
    wxDateTime dt = wxDateTime::Now();

    tDataTime dataTime{ (uint8_t)dt.GetSecond(), (uint8_t)dt.GetMinute(), (uint8_t)(dt.GetHour() + 3),
        (uint8_t)dt.GetDay(), (uint8_t)dt.GetMonth(), (uint16_t)dt.GetYear() };
    long res = CalculateTime(dataTime);
    wxString t_string = wxString::Format(wxT("%i"), res);

    m_secDataTime->SetValue(t_string);
    m_dataTime->SetValue(dt.Format(wxT("%Y-%m-%d %H:%M:%S")));
}