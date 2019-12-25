#include "mainframe.h"

class wxMiniApp : public wxApp
{
public:
    virtual bool OnInit();
};

IMPLEMENT_APP(wxMiniApp);

bool wxMiniApp::OnInit()
{
    CMainFrame* mainFrame = new CMainFrame(NULL);
    mainFrame->Show();
    return true;
}
