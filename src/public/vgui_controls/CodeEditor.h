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
	class CodeEditor : public Panel
	{
	private:
		DECLARE_CLASS_SIMPLE(CodeEditor, TextEntry);

	public:
		CodeEditor(Panel *parent, const char *panelname);

		virtual ~CodeEditor();


		/* Events */
		void OnKeyCodePressed(KeyCode code) override;
		void OnKeyCodeReleased(KeyCode code) override;

		void Paint() override;
		void PaintBackground() override;

		virtual void DrawAllText(int startx, int starty, int line, HFont font);

	public:

		struct line_t
		{
			char* str;
			int len;
			int alloclen;
		};

		CUtlVector<CUtlString> lines;

		Color FgColor;
		Color BgColor;

		/* Colors for syntax highlighting */
		Color cOperatorColor;
		Color cStringColor;
		Color cIntColor;
		Color cFloatColor;
		Color cFunctionColor;
		Color cKeywordColor;
		Color cCommentColor;
		Color cEscapeCharColor;
		Color cGutterBg;
		Color cGutterFg;

		/* Keyboard states */
		bool pKeyStates[BUTTON_CODE_COUNT];
		bool pKeyRepeats[BUTTON_CODE_COUNT];
		float pKeyTimes[BUTTON_CODE_COUNT];

		bool bViMode;
		bool bDrawStatusBar;
		bool bDrawGutter;
		float fInitialRepeatDelay;
		float fRepeatDelay;
		int nLines;
		int nColumns;
		int nStartLine;
		int nGutterWidth;
		int nLineSpacing;
		int nMargin;

		/* Cursor positions */
		int nLine, nCol;

		enum {
			INSERT,
			NORMAL,
			VISUAL
		} mode;

		enum {
			LUA,
			C,
			CPP,
			JAVA,
			PYTHON,
			KV,
		} nHighlightMode;
	};
}