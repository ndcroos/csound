// generated by Fast Light User Interface Designer (fluid) version 1.0106

#ifndef installer_h
#define installer_h
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Output.H>
extern Fl_Output *bintype;
#include <FL/Fl_Check_Button.H>
extern void set_system(Fl_Check_Button*, void*);
extern Fl_Check_Button *systemp;
#include <FL/Fl_File_Input.H>
extern Fl_File_Input *bindir;
extern Fl_File_Input *opcdir;
extern Fl_File_Input *doc;
extern Fl_File_Input *libdir;
#include <FL/Fl_Group.H>
#include <FL/Fl_Light_Button.H>
extern Fl_Light_Button *profile;
#include <FL/Fl_Round_Button.H>
extern Fl_Round_Button *shell;
extern Fl_Round_Button *cshell;
#include <FL/Fl_Progress.H>
extern Fl_Progress *progress;
#include <FL/Fl_Button.H>
Fl_Double_Window* make_window(char* type);
extern Fl_Output *err_text;
#include <FL/Fl_Return_Button.H>
Fl_Double_Window* make_alert();
#endif
