/*
 *
 * CodeEditor.h
 *
 * Code editor for vgui2
 *
 */
#pragma once

#include <vgui_controls/Panel.h>
#include <vgui_controls/TextEntry.h>

namespace vgui
{
	class CodeEditor : public TextEntry
	{
	private:
		DECLARE_CLASS_SIMPLE(CodeEditor, TextEntry);

	public:
		CodeEditor(Panel *parent, const char *panelname);

		virtual ~CodeEditor();


	};
}