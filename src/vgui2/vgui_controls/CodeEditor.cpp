/*
 *
 * CodeEditor.cpp
 *
 * Code editor widget for vgui2
 *
 */

#include "vgui_controls/CodeEditor.h"

using namespace vgui;

CodeEditor::CodeEditor(Panel* parent, const char* panelname) :
	TextEntry(parent, panelname)
{

}

CodeEditor::~CodeEditor()
{

}

void vgui_test_code_editor()
{

}

ConCommand vgui_code_edit_test_command("vgui_test_code_editor", vgui_test_code_editor);