
#include <vgui_controls/Frame.h>
#include <vgui_controls/CodeEditor.h>
#include <convar.h>
#include <cdll_util.h>

using namespace vgui;

void vgui_test_code_editor(const CCommand& args)
{
	int scrh = ScreenHeight();
	int scrw = ScreenWidth();
	int panel_height = scrh / 2;
	int panel_width = scrw / 2;

	Frame* frame = new Frame(NULL, "test");
	frame->SetPos(scrw/2 - panel_width, scrh/2 - panel_height);
	frame->SetSize(panel_width, panel_height);
	frame->SetTitle("This is a test", true);
	frame->SetVisible(true);

	CodeEditor* editor = new CodeEditor(frame, "code_editor");
	editor->SetVisible(true);
	editor->SetWide(panel_width);
	editor->SetTall(panel_height);
	editor->cGutterBg = Color(0,0,0,255);
	editor->cGutterFg = Color(255,255,255,255);
	editor->SetBgColor(Color(0,0,0,255));
	editor->bDrawGutter = true;

}

ConCommand vgui_test_command("vgui_test_code_editor", vgui_test_code_editor);
