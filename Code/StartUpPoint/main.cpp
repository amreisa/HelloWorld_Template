// wxWidgets "Hello world" Program
#include "main.hpp"

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame {
public:
    MyFrame( const wxString &title, const wxPoint &pos, const wxSize &size );

private:
    void OnHello( wxCommandEvent &event );
    void OnExit( wxCommandEvent &event );
    void OnAbout( wxCommandEvent &event );
    wxDECLARE_EVENT_TABLE();
};

enum { ID_Hello = 1 };

wxBEGIN_EVENT_TABLE( MyFrame, wxFrame )
EVT_MENU( ID_Hello, MyFrame::OnHello )
EVT_MENU( wxID_EXIT, MyFrame::OnExit )
EVT_MENU( wxID_ABOUT, MyFrame::OnAbout )
wxEND_EVENT_TABLE()
wxIMPLEMENT_APP( MyApp );

bool MyApp::OnInit() {
    MyFrame *frame = new MyFrame( _( "Hello World" ), wxPoint( 50, 50 ), wxSize( 450, 340 ) );
    frame->Show( true );
    return true;
}

MyFrame::MyFrame( const wxString &title, const wxPoint &pos, const wxSize &size ) : wxFrame( NULL, wxID_ANY, title, pos, size ) {
    wxMenu *menuFile = new wxMenu;
    // menuFile->Append( ID_Hello, _( "&Hello...\tCtrl-H" ), _( "Help string shown in status bar for this menu item" ) );
    menuFile->AppendSeparator();
    menuFile->Append( wxID_EXIT );
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append( wxID_ABOUT );
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, _( "&File" ) );
    menuBar->Append( menuHelp, _( "&Help" ) );
    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText( _( "Welcome to wxWidgets!" ) );
}

void MyFrame::OnExit( wxCommandEvent &event ) {
    Close( true );
}

void MyFrame::OnAbout( wxCommandEvent &event ) {
    wxMessageBox( _( "This is a wxWidgets' Hello world sample" ), _( "About Hello World" ), wxOK | wxICON_INFORMATION );
}

void MyFrame::OnHello( wxCommandEvent &event ) {
    wxLogMessage( _( "Hello world from wxWidgets!" ) );
}
