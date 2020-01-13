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

    m_secDataTime = new wxTextCtrl(this, NewControlId(), wxT(""));
    m_dataTime = new wxTextCtrl(this, NewControlId(), wxT("0000-00-00 00:00:00"), wxDefaultPosition, wxSize(130, 10));

    wxButton* m_convert = new wxButton(this, NewControlId(), wxT("Convert"));
    m_result = new wxTextCtrl(this, NewControlId(), wxT(""));

    m_grid = new wxGrid(this, NewControlId());
    m_grid->CreateGrid(1, 6);
    m_grid->SetRowLabelSize(0);
    m_grid->SetColLabelValue(0, wxT("sec"));
    m_grid->SetColLabelValue(1, wxT("min"));
    m_grid->SetColLabelValue(2, wxT("hors"));
    m_grid->SetColLabelValue(3, wxT("day"));
    m_grid->SetColLabelValue(4, wxT("mounth"));
    m_grid->SetColLabelValue(5, wxT("yaer"));

    wxBoxSizer* main_box = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* h_box = nullptr;
    wxBoxSizer* v_box = nullptr;

    h_box = new wxBoxSizer(wxHORIZONTAL);
    h_box->Add(m_secDataTime, 1, wxEXPAND);
    h_box->Add(m_dataTime, 1, wxEXPAND);
    main_box->Add(h_box);

    v_box = new wxBoxSizer(wxVERTICAL);
    v_box->Add(m_convert);
    v_box->Add(m_result);

    h_box = new wxBoxSizer(wxHORIZONTAL);
    h_box->Add(m_grid);
    h_box->Add(v_box);

    main_box->Add(h_box);

    this->SetSizerAndFit(main_box);

    Bind(wxEVT_BUTTON, &CMainFrame::OnConvert, this, m_convert->GetId());

    m_timer.Start(1000);
}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::OnConvert(wxCommandEvent& event)
{
    uint8_t countCol = m_grid->GetNumberCols();
    wxString t_str[countCol];
    int t_int[countCol];
    for(int i = 0; i < countCol; i++) {
        t_str[i] = m_grid->GetCellValue(0, i);
        if(t_str[i].empty() == true)
            t_str[i] = wxT("1");
    }

    for(int i = 0; i < countCol; i++)
        t_int[i] = wxAtoi(t_str[i]);

    tDataTime dataTime{ (uint8_t)t_int[0], (uint8_t)t_int[1], (uint8_t)t_int[2], (uint8_t)t_int[3], (uint8_t)t_int[4],
        (uint16_t)t_int[5] };

    long res = CalculateTime(dataTime);
    t_str[0] = wxString::Format(wxT("%i"), res);

    m_result->SetValue(t_str[0]);
}

void CMainFrame::OnTimerProcess(wxTimerEvent& event)
{
    wxDateTime dt = wxDateTime::Now();

    tDataTime dataTime{ (uint8_t)dt.GetSecond(), (uint8_t)dt.GetMinute(), (uint8_t)dt.GetHour(), (uint8_t)dt.GetDay(),
        (uint8_t)dt.GetMonth(), (uint16_t)dt.GetYear() };

    long res = CalculateTime(dataTime);
    wxString t_string = wxString::Format(wxT("%i"), res);

    m_secDataTime->SetValue(t_string);
    m_dataTime->SetValue(dt.Format(wxT("%Y-%m-%d %H:%M:%S")));
}