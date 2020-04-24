/*
 *
 * CodeEditor.cpp
 *
 * Code editor widget for vgui2
 *
 */

#include "vgui_controls/CodeEditor.h"
#include "vgui_controls/Frame.h"
#include "vgui/ISurface.h"


using namespace vgui;

CodeEditor::CodeEditor(Panel* parent, const char* panelname) :
	Panel(parent, panelname),
	nStartLine(1),
	nLine(1),
	nLines(1),
	nCol(1)
{
}

CodeEditor::~CodeEditor()
{

}

void CodeEditor::OnKeyCodePressed(KeyCode code)
{

}

void CodeEditor::OnKeyCodeReleased(KeyCode code)
{

}

void CodeEditor::Paint()
{
	int x, y, w, h, scrw, scrh;
	int gutter_width;
	int max_font_height, unused;

	this->GetPos(x,y);
	this->GetSize(w,h);
	surface()->GetScreenSize(scrw, scrh);

	IScheme* pScheme = scheme()->GetIScheme(GetScheme());
	HFont hFont = pScheme->GetFont("DefaultSmall");
	surface()->DrawSetTextFont(hFont);

	/* Fill in some basic info about the panel */
	surface()->GetTextSize(hFont, L"|", max_font_height, unused);

	/* Draw background */
	surface()->DrawSetColor(this->GetBgColor());
	surface()->DrawFilledRect(x,y, x+w, y+h);

	/* Draw the gutter */
	if(bDrawGutter)
	{
		surface()->DrawSetColor(this->cGutterBg);
		surface()->DrawSetTextColor(this->cGutterFg);
		surface()->GetTextSize(hFont, L"9999", gutter_width, unused);
		surface()->DrawFilledRect(x, y, x + gutter_width, y + h);
	}

	/* Draw all lines */
	for(int i = nStartLine; i <= nLines; i++)
	{
		this->DrawAllText(this->nMargin + gutter_width + x, i * max_font_height + y + nLineSpacing, i, hFont);
	}
}

void CodeEditor::PaintBackground()
{

}

void CodeEditor::DrawAllText(int startx, int starty, int line, HFont font)
{
	static union {
		struct {

		} lua_ctx;

		struct {

		} c_ctx;

		struct {

		} cpp_ctx;

		struct {

		} kv_ctx;

		struct {

		} default_ctx;
	} context;

	switch(this->nHighlightMode)
	{
		case LUA:
			break;
		case C:
			break;
		case CPP:
			break;
		case JAVA:
			break;
		case KV:
			break;
		default:
			break;
	}
}