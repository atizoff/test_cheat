#pragma once
#include "includes.h"
#include "cVar.h"
#include "cMenuTool.h"

ID3DXLine* pLine;
ID3DXFont* pFont;
ID3DXFont* pFonts;
bool			Install;
D3DVIEWPORT9	pViewport;
IDirect3DDevice9Ex* g_pDevice;
bool			SHOW = true;

bool			hExitThread;
int ScreenWidth = 0;
int ScreenHeight = 0;
int ScreenCenterX = 0;
int ScreenCenterY = 0;
D3DVIEWPORT9 Viewport;
#define CText (DT_CENTER|DT_NOCLIP)
#define LText (DT_LEFT|DT_NOCLIP) 
#define RText (DT_RIGHT|DT_NOCLIP)

enum gr_orientation { horizontal, vertical };

int x, y;
int CheckboxList[20] = { 0 }, CheckboxNumber = 0, CheckboxMax = 0;
struct D3DTLVERTEX {
	D3DTLVERTEX(FLOAT X, FLOAT Y, FLOAT Z, D3DCOLOR Color) :x(X), y(Y), z(Z), color(Color) {};
	D3DTLVERTEX() {};
	FLOAT x, y, z, rhw = 1.0f;
	D3DCOLOR color;

	static const DWORD FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
};
struct SD3DVertex
{
	float x, y, z, rhw;
	DWORD colour;
};









int kiriliza_kod[] =
{
	1040,//A

	1041,//Б

	1042,//В

	1043,//Г

	1044,//Д         

	1045,//Е

	1046,//Ж

	1047,//З

	1048,//И

	1049,//Й

	1050,//К

	1051,//Л

	1052,//М

	1053,//Н

	1054,//О

	1055,//П

	1056,//Р

	1057,//С

	1058,//Т

	1059,//У

	1060,//Ф

	1061,//Х

	1062,//Ц

	1063,//Ч

	1064,//Ш

	1065,//Щ

	1066,//Ъ

	1067,//Ы

	1068,//Ь

	1069,//Э

	1070,//Ю

	1071,//Я

	1072,//а

	1073,//б

	1074,//в

	1075,//г

	1076,//д

	1077,//е

	1078,//ж

	1079,//з

	1080,//и

	1081,//й

	1082,//к

	1083,//

	1084,//

	1085,//

	1086,//

	1087,//

	1088,//

	1089,//

	1090,//

	1091,//

	1092,//

	1093,//

	1094,//

	1095,//

	1096,//

	1097,//

	1098,//

	1099,//

	1100,//

	1101,//

	1102,//

	1103,//

	95,// _

	45,//-

	46,//.

	48,

	49,

	50,

	51,

	52,

	53,

	54,

	55,

	56,

	57,

	44
};

char *alf[] =
{
	"А",
	"Б",
	"В",
	"Г",
	"Д",
	"Е",
	"Ж",
	"З",
	"И",
	"Й",
	"К",
	"Л",
	"М",
	"Н",
	"О",
	"П",
	"Р",
	"С",
	"Т",
	"У",
	"Ф",
	"Х",
	"Ц",
	"Ч",
	"Ш",
	"Щ",
	"Ъ",
	"Ы",
	"Ь",
	"Э",
	"Ю",
	"Я",
	"а",
	"б",
	"в",
	"г",
	"д",
	"е",
	"ж",
	"з",
	"и",
	"й",
	"к",
	"л",
	"м",
	"н",
	"о",
	"п",
	"р",
	"с",
	"т",
	"у",
	"ф",
	"х",
	"ц",
	"ч",
	"ш",
	"щ",
	"ъ",
	"ы",
	"ь",
	"э",
	"ю",
	"я",
	"_",
	"-",
	".",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	","
};

enum EWstrToUTF8Constants
{
	eWTUC_MASKBITS = 0x3F,
	eWTUC_MASKBYTE = 0x80,
	eWTUC_MASK2BYTES = 0xC0,
	eWTUC_MASK3BYTES = 0xE0,

	eUTWC_MASKBYTE = 0x80,
	eUTWC_MASKBITS = 0x3F,
	eUTWC_MASKIDBITS = 0xE0,
	eUTWC_MASK2BYTES = 0xC0,
	eUTWC_MASK3BYTES = 0xE0,
};


class cDraw
{
public:
	void FilledBox(int x, int y, int width, int height, D3DCOLOR colour, LPDIRECT3DDEVICE9 pDevice)
	{
		SD3DVertex pVertex[4] = { { x, y + height, 0.0f, 1.0f, colour },{ x, y, 0.0f, 1.0f, colour },{ x + width, y + height, 0.0f, 1.0f, colour },{ x + width, y, 0.0f, 1.0f, colour } };
		pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, pVertex, sizeof(SD3DVertex));
	}

	void FilledBorder(int x, int y, int w, int h, int s, DWORD color, LPDIRECT3DDEVICE9 pDevice)
	{
		FilledBox(x, y, w, s, color, pDevice);
		FilledBox(x, y, s, h, color, pDevice);
		FilledBox(x, y + h - s, w, s, color, pDevice);
		FilledBox(x + w - s, y, s, h, color, pDevice);
	}

	void FillRGB(int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9 * pDevice)
	{
		D3DRECT rec = { x, y, x + w, y + h };
		pDevice->Clear(1, &rec, D3DCLEAR_TARGET, color, 0, 0);
	}

	void Line(float x, float y, float x2, float y2, float width, DWORD color)
	{
		D3DXVECTOR2 vLine[2];
		pLine->SetWidth(width);
		pLine->SetAntialias(false);
		pLine->SetGLLines(true);
		vLine[0].x = x;
		vLine[0].y = y;
		vLine[1].x = x2;
		vLine[1].y = y2;
		pLine->Begin();
		pLine->Draw(vLine, 2, color);
		pLine->End();

		return;
	}

	void Circle(int X, int Y, int radius, int numSides, DWORD Color)
	{
		D3DXVECTOR2 Line[128];
		float Step = (float)(D3DX_PI * 2.0 / numSides);
		int Count = 0;
		for (float a = 0; a < D3DX_PI * 2.0; a += Step)
		{
			float X1 = radius * cos(a) + X;
			float Y1 = radius * sin(a) + Y;
			float X2 = radius * cos(a + Step) + X;
			float Y2 = radius * sin(a + Step) + Y;
			Line[Count].x = X1;
			Line[Count].y = Y1;
			Line[Count + 1].x = X2;
			Line[Count + 1].y = Y2;
			Count += 2;
		}
		pLine->Begin();
		pLine->Draw(Line, Count, Color);
		pLine->End();
	}

	void DrawString(float x, float y, D3DCOLOR color, DWORD Flag, const char* fmt, ...)
	{
		char buf[1024] = { '\0' };
		va_list va_alist;
		va_start(va_alist, fmt);
		vsprintf_s(buf, fmt, va_alist);
		va_end(va_alist);
		RECT rect;
		SetRect(&rect, x, y, x, y);
		pFont->DrawTextA(NULL, buf, -1, &rect, Flag, color);
	}

	void StringBroder(int x, int y, DWORD Color, DWORD Style, const char* Format, ...)
	{
		RECT FontPos = { x, y, x, y };
		RECT FontPos1 = { x - 1, y, x - 1, y };
		RECT FontPos2 = { x + 1, y, x + 1, y };
		RECT FontPos3 = { x, y - 1, x, y - 1 };
		RECT FontPos4 = { x, y + 1, x, y + 1 };
		char Buffer[1024] = { '\0' };
		va_list va_alist;

		va_start(va_alist, Format);
		vsprintf_s(Buffer, Format, va_alist);
		va_end(va_alist);

		pFont->DrawTextA(NULL, Buffer, -1, &FontPos1, Style, BLACK);
		pFont->DrawTextA(NULL, Buffer, -1, &FontPos2, Style, BLACK);
		pFont->DrawTextA(NULL, Buffer, -1, &FontPos3, Style, BLACK);
		pFont->DrawTextA(NULL, Buffer, -1, &FontPos4, Style, BLACK);
		pFont->DrawTextA(NULL, Buffer, -1, &FontPos, Style, Color);
		return;
	}

	void StringBroderU(int x, int y, DWORD Color, DWORD BkColor, DWORD Style, const char* Format, ...)
	{
		RECT FontPos = { x, y, x, y };
		RECT FontPos1 = { x - 1, y, x - 1, y };
		RECT FontPos2 = { x + 1, y, x + 1, y };
		RECT FontPos3 = { x, y - 1, x, y - 1 };
		RECT FontPos4 = { x, y + 1, x, y + 1 };
		char Buffer[1024] = { '\0' };
		va_list va_alist;

		va_start(va_alist, Format);
		vsprintf_s(Buffer, Format, va_alist);
		va_end(va_alist);

		pFont->DrawTextA(NULL, Buffer, -1, &FontPos1, Style, BkColor);
		pFont->DrawTextA(NULL, Buffer, -1, &FontPos2, Style, BkColor);
		pFont->DrawTextA(NULL, Buffer, -1, &FontPos3, Style, BkColor);
		pFont->DrawTextA(NULL, Buffer, -1, &FontPos4, Style, BkColor);
		pFont->DrawTextA(NULL, Buffer, -1, &FontPos, Style, Color);
		return;
	}

	BOOL IsInBox(int x, int y, int w, int h)
	{
		POINT MousePosition;
		GetCursorPos(&MousePosition);
		ScreenToClient(GetForegroundWindow(), &MousePosition);
		return(MousePosition.x >= x && MousePosition.x <= x + w && MousePosition.y >= y && MousePosition.y <= y + h);
	}

	void Cursor(LPDIRECT3DDEVICE9 pDevice)
	{
		D3DCOLOR Color = YELLOW;
		POINT mpos;
		GetCursorPos(&mpos);
		ScreenToClient(GetForegroundWindow(), &mpos);
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			Color = D3DCOLOR_ARGB(255,255,0,0);
		}
		else
		{
			Color = YELLOW;
		}

		StringBroder(500, 500, Color, LText, "x: %i || y: %i", mpos.x, mpos.y);
	}

	void Draw_GradientBox(float x, float y, float width, float height, DWORD startCol, DWORD endCol, gr_orientation orientation, IDirect3DDevice9 * mDevice)
	{
		static struct D3DVERTEX
		{
			float x,
				y,
				z,
				rhw;
			DWORD color;
		}
		vertices[4] = {
			{ 0, 0, 0, 1.0f, 0 },
			{ 0, 0, 0, 1.0f, 0 },
			{ 0, 0, 0, 1.0f, 0 },
			{ 0, 0, 0, 1.0f, 0 } };


		vertices[0].x = x;
		vertices[0].y = y;
		vertices[0].color = startCol;

		vertices[1].x = x + width;
		vertices[1].y = y;
		vertices[1].color = orientation == horizontal ? endCol : startCol;

		vertices[2].x = x;
		vertices[2].y = y + height;
		vertices[2].color = orientation == horizontal ? startCol : endCol;

		vertices[3].x = x + width;
		vertices[3].y = y + height;
		vertices[3].color = endCol;


		mDevice->SetTexture(0, NULL);
		mDevice->SetPixelShader(0);
		mDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
		mDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		mDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		mDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
		mDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		mDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(D3DVERTEX));
	}

	void Button(int x, int y, const char* text, IDirect3DDevice9 * pDevice)
	{
		int w = 120, height = 20;
		DWORD color = KingRed, Text = KingRed;
		if (IsInBox(x + 1, y + 4, w + 20, height))
		{
			FilledBox(x + 140, y + 4, 2, 20, Krasnui, pDevice);
			FilledBox(x, y + 4, 2, 20, Krasnui, pDevice);

			if (sTools->KeyPressed(VK_LBUTTON, 5000))
			{
				if (CheckboxList[CheckboxNumber] != 1)
					CheckboxList[CheckboxNumber] = 1;
				else if (CheckboxList[CheckboxNumber] != 0)
					CheckboxList[CheckboxNumber] = 0;
			}
		}
		if (CheckboxList[CheckboxNumber])
		{
			FilledBox(x + 140, y + 4, 2, 20, KingRed, pDevice);
			FilledBox(x, y + 4, 2, 20, KingRed, pDevice);
			Text = KingRed;
			for (int i = 0; i < 20; i++)
				if (i != CheckboxNumber)
					CheckboxList[i] = 0;
		}
		FilledBox(x + 1, y + 4, w + 20, height, ЕsoneBlackBox, pDevice);
		StringBroder(x + 70, y + 6, Text, DT_CENTER | DT_NOCLIP, text);
		y + 1,
			CheckboxNumber = CheckboxNumber + 1;
		if (CheckboxMax < CheckboxNumber)
			CheckboxMax = CheckboxNumber;
	}
	void DrawBox(int x, int y, int w, int h, D3DCOLOR Color, IDirect3DDevice9 * mDevice)
	{
		D3DRECT rec;
		rec.x1 = x;
		rec.x2 = x + w;
		rec.y1 = y;
		rec.y2 = y + h;
		mDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
		mDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		mDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		mDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, D3DPT_TRIANGLESTRIP);
		mDevice->Clear(1, &rec, D3DCLEAR_TARGET, Color, 1, 1);
	}
	void DrawCheckBox(FLOAT x, FLOAT y, FLOAT w, FLOAT h, INT index) {
		DrawBox(x, y, w, h, 0x0000FF, g_pDevice);

	}
	void CheckBox(int x, int y, int& var, const char* text, LPDIRECT3DDEVICE9 pDevice) {
		FilledBox(x + 10, y + 2, 345, 19, EsoneBlackBorder, pDevice);
		if (IsInBox(x + 10, y + 2, 345, 19) && sTools->KeyPressed(VK_LBUTTON, 130)) {
			var = !var;
		}
		if (var)StringBroder(x + 285, y + 3, GREENDSIFD, LText, " Вкл");
		if (!var)StringBroder(x + 285, y + 3, GREENDSIFD, LText, "Выкл");
		StringBroder(x + 15, y + 3, WHITE, LText, text);

	}
	VOID D3DirectD3_DrawStripLine(__in int count, __in D3DTLVERTEX * vertex) {
		g_pDevice->SetFVF(D3DTLVERTEX::FVF);
		g_pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, count, vertex, sizeof(D3DTLVERTEX));
	}
	template<typename cData> void DrawScroolBox(FLOAT x, FLOAT y, FLOAT w, FLOAT h, cData min, cData max, cData * Value) {
		w -= 50.0f;
		POINT CursorPos;
		GetCursorPos(&CursorPos);
		ScreenToClient(GetForegroundWindow(), &CursorPos);

		if (*(cData*)Value > max)* (cData*)Value = max;
		if (*(cData*)Value < min)* (cData*)Value = min;
		w -= h;
		FLOAT valueX = x + ((*(cData*)Value - min) * w / (max + min));
		if ((CursorPos.x >= x && CursorPos.x <= x + w && CursorPos.y >= y && CursorPos.y <= y + h) && GetKeyState(VK_LBUTTON) < 0) {
			*(cData*)Value = (cData)((CursorPos.x - x) * (max + min) / w);
		}
		w += h;
		FilledBox(x, y, w, h, 0xFF020136);
		FilledBox(valueX, y, h, h, 0xFF001aff);
		FilledBorder(x, y, w, h, 1, 0xFF080b45);
		if (typeid(cData).name() == typeid(FLOAT).name()) StringBroder(x + w + 5, y + h / 2, 0xFFfffcfc, LText, "[%0.3f]", *(cData*)Value);
		if (typeid(cData).name() == typeid(INT).name()) StringBroder(x + w + 5, y + h / 2, 0xFFfffcfc, LText, "[%d]", *(cData*)Value);
	}

	void CornerBox(int x, int y, int w, int h, D3DCOLOR Draw)
	{
		int bWidth = w;
		int bHeight = h;
		Line(x, y, x, y + (bHeight / 5), 1, Draw);
		Line(x, y, x + (bWidth / 5), y, 1, Draw);
		Line(x + bWidth, y, x + bWidth - (bWidth / 5), y, 1, Draw);
		Line(x + bWidth, y, x + bWidth, y + (bHeight / 5), 1, Draw);
		Line(x, y + bHeight, x + (bWidth / 5), y + bHeight, 1, Draw);
		Line(x, y + bHeight, x, y + bHeight - (bHeight / 5), 1, Draw);
		Line(x + bWidth, y + bHeight, x + bWidth - (bWidth / 5), y + bHeight, 1, Draw);
		Line(x + bWidth, y + bHeight, x + bWidth, y + bHeight - (bHeight / 5), 1, Draw);
	}

	void EdgedOutline(int x, int y, int w, int h, D3DCOLOR Draw)
	{
		CornerBox(x - 1, y - 1, w + 2, h + 2, D3DCOLOR_ARGB(0, 0, 0, 255));
		CornerBox(x, y, w, h, Draw);
	}

	void Scroll(int x, int y, int& Var, const char** typ, int max, const char* text, LPDIRECT3DDEVICE9 pDevice)
	{
		int color = D3DCOLOR_ARGB(255, 190, 190, 190);
		D3DCOLOR c = D3DCOLOR_ARGB(255, 255, 0, 0);;

		StringBroder(x + 260-130, y + 1, WHITE, LText, "<");
		StringBroder(x + 335-130, y + 1, WHITE, LText, ">");

		if (IsInBox(x + 260 - 130, y + 3, 10, 10))//
		{
			if (sTools->KeyPressed(VK_LBUTTON, 130))
			{
				if (Var != 0)
				{
					Var--;
				}
			}
		}
		if (IsInBox(x + 335 - 130, y + 3, 10, 10))
		{
			if (sTools->KeyPressed(VK_LBUTTON, 130))
			{
				if (Var >= 0 && Var < max)
				{
					Var++;
				}
			}
		}

		StringBroder(x + 303 - 130, y, D3DCOLOR_ARGB(255, 190, 190, 190), DT_CENTER | DT_NOCLIP, typ[Var]);
		Text((LPSTR)text, x + 24, y, D3DCOLOR_ARGB(255, 190, 190, 190), DT_LEFT | DT_NOCLIP);
	}

	void Scrollinfo(int x, int y, int& Var, const char** typ, int max, const char* text, LPDIRECT3DDEVICE9 pDevice)
	{
		int color = KingGray;
		FilledBox(x + 10, y + 2, 345, 19, ЕsoneBlackBox, pDevice);
		if (IsInBox(x + 10, y + 2, 345, 19))
		{
			color = KingWhite;
			FilledBox(x + 10, y + 2, 345, 19, ЕsoneBlackBox, pDevice);
		}

		StringBroder(x + 303, y + 3, color, DT_CENTER | DT_NOCLIP, typ[Var]);
		StringBroder(x + 15, y + 3, color, LText, text);
	}

	void AIMScroll(int x, int y, int& Var, const char** typ, int max, const char* text, LPDIRECT3DDEVICE9 pDevice)
	{
		int color = GREEN;
		FilledBox(x + 10, y + 2, 345, 19, KingDark, pDevice);
		if (IsInBox(x + 10, y + 2, 345, 19))
		{
			color = GREEN;
			FilledBox(x + 10, y + 2, 345, 19, KingDark2, pDevice);
		}

		//----Рисуем кнопку "<<"(OFF)-----
		StringBroder(x + 260, y + 3, YELLOW, LText, "<<");
		//----Рисуем кнопку ">>"(ON)-----
		StringBroder(x + 335, y + 3, YELLOW, LText, ">>");

		if (IsInBox(x + 260, y + 3, 10, 10))//
		{
			StringBroder(x + 260, y + 3, GREEN, LText, "<<");
			if (sTools->KeyPressed(VK_LBUTTON, 100))
			{
				if (Var != 0)
				{
					Var--;
				}
			}
		}
		if (IsInBox(x + 335, y + 3, 10, 10))
		{
			StringBroder(x + 335, y + 3, YELLOW, LText, ">>");
			if (sTools->KeyPressed(VK_LBUTTON, 100))
			{
				if (Var >= 0 && Var < max)
				{
					//Fun.AimBot = Fun.FastAim = Fun.AimAssit = 0;
					Var = 1;
				}
			}
		}

		StringBroder(x + 303, y + 3, color, DT_CENTER | DT_NOCLIP, typ[Var]);
		StringBroder(x + 15, y + 3, color, LText, text);
	}

	void LineTreug(int x, int y, DWORD Color, LPDIRECT3DDEVICE9 pDevice) // by KANKOSHEV
	{
		Line(x + 17, y, x, y + 31, 2, Color);
		Line(x + 17, y, x + 40, y + 31, 2, Color);
		Line(x, y + 31, x + 40, y + 30, 2, Color);
	}











	void  Box(int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pD3D9)
	{
		struct Vertex
		{
			float x, y, z, ht;
			DWORD Color;
		}
		V[4] = { { x, y + h, 0.0f, 0.0f, Color },{ x, y, 0.0f, 0.0f, Color },{ x + w, y + h, 0.0f, 0.0f, Color },{ x + w, y, 0.0f, 0.0f, Color } };

		pD3D9->SetTexture(0, NULL);
		pD3D9->SetPixelShader(0);
		pD3D9->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
		pD3D9->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		pD3D9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		pD3D9->SetRenderState(D3DRS_ZENABLE, FALSE);
		pD3D9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		pD3D9->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, V, sizeof(Vertex));
		return;
	}


	void Border(int x, int y, int w, int h, int s, D3DCOLOR Color, LPDIRECT3DDEVICE9 pD3D9)
	{
		Box(x - s, y, s, h, Color, pD3D9);
		Box(x - s, y + h, w + s * 2, s, Color, pD3D9);
		Box(x - s, y - s, w + s * 2, s, Color, pD3D9);
		Box(x + w, y, s, h + s, Color, pD3D9);
	}


#define BLACKFULL   D3DCOLOR_ARGB(200,0,0,0)
#define BLUEZZ    D3DCOLOR_ARGB(255,30 ,144 ,255)
	void FullHack(LPDIRECT3DDEVICE9 pD3D9)
	{
#define FullBlack   D3DCOLOR_ARGB(255,26,26,26)
		Box(x + 55, y + 50, 110, 200, BLACKFULL, pD3D9);
		Border(x + 55, y + 50, 110, 200, 1, BLUEZZ, pD3D9);
	}

	void FullHack2(LPDIRECT3DDEVICE9 pD3D9)
	{
#define FullBlack   D3DCOLOR_ARGB(255,0,0,0)
		Box(x + 170, y + 50, 240, 200, BLACKFULL, pD3D9);
		Border(x + 170, y + 50, 240, 200, 1, BLUEZZ, pD3D9);
	}


#define New          D3DCOLOR_ARGB(255, 26, 26, 26) 

	void normal(bool stabl, LPDIRECT3DDEVICE9 pD3D9)
	{
		Box(x + 1150, y + 50, 0, 1, D3DCOLOR_ARGB(0,0,0,0), pD3D9);//
	}
	void DrawMenu(LPDIRECT3DDEVICE9 pD3D9)
	{
		FilledBox(x + 50, y + 50, 500, 200 + 100, New, pD3D9);
		FilledBorder(x - 1 + 50, y - 1 + 50, 500, 200 + 100, 3, D3DCOLOR_ARGB(255, 43, 43, 43), pD3D9);
		FilledBorder(x - 2 + 50, y - 2 + 50, 500 + 2, 200 + 1 + 100, 3, D3DCOLOR_ARGB(255, 105, 105, 105), pD3D9);
		StringBroder(x + 212.5 + 52, y + 60, WHITE, DT_NOCLIP, "UNKNW CHEAT");
		Line(x + 60, y + 80, x + 535, y + 80, 3, D3DCOLOR_ARGB(255, 71, 71, 71));
	}
	void DrawMenu2(LPDIRECT3DDEVICE9 pD3D9)
	{
		Box(x + 60, y + 130, 120 + 100, 100 + 100, D3DCOLOR_ARGB(225, 36, 36, 36), pD3D9);
		Border(x + 60, y + 130, 120 + 100, 100 + 100, 1, D3DCOLOR_ARGB(255, 43, 43, 43), pD3D9);
		Border(x + 60, y + 130, 120 + 100, 100 + 100, 1, D3DCOLOR_ARGB(255, 105, 105, 105), pD3D9);

		Box(x + 317, y + 130, 120 + 100, 100 + 100, D3DCOLOR_ARGB(225, 36, 36, 36), pD3D9);
		Border(x + 317, y + 130, 120 + 100, 100 + 100, 1, D3DCOLOR_ARGB(255, 43, 43, 43), pD3D9);
		Border(x + 317, y + 130, 120 + 100, 100 + 100, 1, D3DCOLOR_ARGB(255, 105, 105, 105), pD3D9);
	}

	void  Text(LPSTR text, int x, int y, DWORD color, DWORD ST)
	{
		RECT rect, rect2;
		SetRect(&rect, x, y, x, y);
		SetRect(&rect2, x - 0.1, y + 0.2, x - 0.1, y + 0.);
		pFont->DrawTextA(NULL, text, -1, &rect2, ST, 0x00000000);
		pFont->DrawTextA(NULL, text, -1, &rect, ST, color);
	}

	void  TextMy(int x, int y, DWORD color, DWORD ST, LPSTR text, ...)
	{
		RECT rect, rect2;
		SetRect(&rect, x, y, x, y);
		SetRect(&rect2, x - 0.1, y + 0.2, x - 0.1, y + 0.);
		pFont->DrawTextA(NULL, text, -1, &rect2, ST, 0x00000000);
		pFont->DrawTextA(NULL, text, -1, &rect, ST, color);
	}

	void ButtonJ(int x, int y, char* BText, bool& Var, LPDIRECT3DDEVICE9 pD3D9)
	{

		D3DCOLOR Bord_text = D3DCOLOR_ARGB(255, 255, 255, 255);
		D3DCOLOR text_Activ = D3DCOLOR_ARGB(255, 0, 207, 230);
		if (IsInBox(x, y, 156, 20))
		{
			Line(x + 30, y + 20, x + 123, y + 20, 3, D3DCOLOR_ARGB(255, 204, 37, 37));
			if (GetAsyncKeyState(VK_LBUTTON) & 1)
			{
				Menu_Weapon = Menu_ESP = Menu_AIMS = Menu_Player = 0;
				Var = !Var;
			}
		}
		if (Var)
		{
			Line(x + 30, y + 20, x + 123, y + 20, 3, D3DCOLOR_ARGB(255, 0, 207, 230));
		}
		else
		{
			Line(x + 30, y + 20, x + 123, y + 20, 3, D3DCOLOR_ARGB(255, 71, 71, 71));
		}
		StringBroder(x + (156 / 2), y, Bord_text, DT_CENTER | DT_NOCLIP, BText);
	}

	void CheckJ(int x, int y, char *BText, int &Var, LPDIRECT3DDEVICE9 pD3D9)
	{

		D3DCOLOR Back = D3DCOLOR_ARGB(255, 31, 31, 31);
		D3DCOLOR Back2 = D3DCOLOR_ARGB(255, 58, 58, 58);
		D3DCOLOR c = D3DCOLOR_ARGB(255, 255, 0, 0);;
		//Box(x + 5, y + 10, 1, 1, c, pD3D9);

		if (IsInBox(x - 12, y, 15, 15))
		{
			Back = D3DCOLOR_ARGB(255, 62, 132, 140);
			if (GetAsyncKeyState(VK_LBUTTON) & 1)
			{
				Var = !Var;
			}

		}
		if (Var) Back = D3DCOLOR_ARGB(230, 0, 207, 230);
		Box(x - 10, y + 3, 10, 10, Back, pD3D9);
		Text(BText, x + 10, y + 2, D3DCOLOR_ARGB(255, 190, 190, 190), DT_LEFT | DT_NOCLIP);

	}

	template <typename T>
	void Scroll(int x, int y, int w, int h, T min, T max, T& value, LPSTR text, LPSTR text2, LPDIRECT3DDEVICE9 Device)
	{
		POINT CursorPos;
		GetCursorPos(&CursorPos);
		ScreenToClient(GetForegroundWindow(), &CursorPos);
		Box(x, y, w, h, New, Device);

		if (value > max) value = max;
		if (value < min) value = min;

		T valueW = ((value - min) * w / (max - min));
		if ((CursorPos.x >= x && CursorPos.x <= x + w && CursorPos.y >= y && CursorPos.y <= y + 19) && GetKeyState(VK_LBUTTON) < 0)
			value = (CursorPos.x - x) * (max - min) / w + 1;
		Box(x, y, valueW, h, D3DCOLOR_ARGB(230, 0, 207, 230), Device);
		Border(x + 1, y, w - 2, h - 2, 2, D3DCOLOR_ARGB(255, 43, 43, 43), Device);

		String((value - min) * w / (max - min) + 150, y + 4, D3DCOLOR_ARGB(255, 190, 190, 190), DT_CENTER | DT_NOCLIP, "%s%d%s", text, value, text2);
	}

	template <typename T>
	void Scroll2Tab(int x, int y, int w, int h, T min, T max, T& value, LPSTR text, LPSTR text2, LPDIRECT3DDEVICE9 Device)
	{
		POINT CursorPos;
		GetCursorPos(&CursorPos);
		ScreenToClient(GetForegroundWindow(), &CursorPos);
		Box(x, y, w, h, New, Device);

		if (value > max) value = max;
		if (value < min) value = min;

		T valueW = ((value - min) * w / (max - min));
		if ((CursorPos.x >= x && CursorPos.x <= x + w && CursorPos.y >= y && CursorPos.y <= y + 19) && GetKeyState(VK_LBUTTON) < 0)
			value = (CursorPos.x - x) * (max - min) / w + 1;
		Box(x, y, valueW, h, D3DCOLOR_ARGB(230, 0, 207, 230), Device);
		Border(x + 1, y, w - 2, h - 2, 2, D3DCOLOR_ARGB(255, 43, 43, 43), Device);

		String((value - min) * w / (max - min) + 415, y + 4, D3DCOLOR_ARGB(255, 190, 190, 190), DT_CENTER | DT_NOCLIP, "%s%d%s", text, value, text2);
	}

	void String(int x, int y, DWORD Color, DWORD style, const char* Format, ...)
	{
		RECT FontPos = { x, y, x, y };
		RECT FontPos1 = { x - 1, y, x - 1, y };
		RECT FontPos2 = { x + 1, y, x + 1, y };
		RECT FontPos3 = { x, y - 1, x, y - 1 };
		RECT FontPos4 = { x, y + 1, x, y + 1 };
		char Buffer[1024] = { '\0' };
		va_list va_alist;

		va_start(va_alist, Format);
		vsprintf_s(Buffer, Format, va_alist);
		va_end(va_alist);

		pFont->DrawTextA(NULL, Buffer, -1, &FontPos1, style, 0x00000000);
		pFont->DrawTextA(NULL, Buffer, -1, &FontPos2, style, 0x00000000);
		pFont->DrawTextA(NULL, Buffer, -1, &FontPos3, style, 0x00000000);
		pFont->DrawTextA(NULL, Buffer, -1, &FontPos4, style, 0x00000000);
		pFont->DrawTextA(NULL, Buffer, -1, &FontPos, style, Color);
	}

	void __fastcall UTF8ToWStr(const char* str, WStr& dstr)
	{
		WStr tmp;

		const size_t length = strlen(str);
		tmp.resize(length);  // this preallocation is enough in simple cases (in complex cases append() will re-allocate)
		tmp.clear();

		const unsigned char* const src = (unsigned char*)str;

		for (size_t i = 0; i < length; )
		{
			if (src[i] < 0x80) // < 128
			{
				tmp.append(1, (wchar_t)src[i]);
				++i;
			}
			else if ((src[i] & eUTWC_MASKIDBITS) == eUTWC_MASK2BYTES)
			{
				wchar_t d = (wchar_t)(src[i] & ~eUTWC_MASKIDBITS) << 6;
				wchar_t e = (wchar_t)(src[i + 1] & eUTWC_MASKBITS);
				wchar_t f = d | e;
				tmp.append(1, f);
				i += 2;
			}
			else
			{
				wchar_t d = (wchar_t)(src[i] & ~eUTWC_MASKIDBITS) << 12;
				wchar_t e = (wchar_t)(src[i + 1] & eUTWC_MASKBITS) << 6;
				wchar_t f = (wchar_t)(src[i + 2] & eUTWC_MASKBITS);
				wchar_t g = d | e | f;
				tmp.append(1, g);
				i += 3;
			}
		}

		dstr.assign(tmp.data(), tmp.length());
	}


	int GetTextLen(LPCTSTR szString)
	{
		RECT rect = { 0, 0, 0, 0 };
		pFont->DrawText(NULL, szString, -1, &rect, DT_CALCRECT, 0);
		return rect.right;
	}


	void StringS(int x, int y, int w, int h, DWORD Color, DWORD Style, const char *Format, ...)
	{
		RECT FontPos = { x, y, x + w, y + h };
		char Buffer[1024] = { '\0' };
		va_list va_alist;
		va_start(va_alist, Format);
		vsprintf_s(Buffer, Format, va_alist);
		va_end(va_alist);
		pFont->DrawTextA(NULL, Buffer, -1, &FontPos, Style, Color);
		return;
	}

	void ESPString(int x, int y, DWORD Color, DWORD Style, const char *Format, ...)
	{
		char Buffer[1024] = { '\0' };
		va_list va_alist;
		va_start(va_alist, Format);
		vsprintf_s(Buffer, Format, va_alist);
		va_end(va_alist);

		StringS(x - 15, y, GetTextLen(Buffer), 16, Color, Style, Buffer);
		StringS(x - 16, y, GetTextLen(Buffer), 16, BLACK, Style, Buffer);
		StringS(x - 14, y, GetTextLen(Buffer), 16, BLACK, Style, Buffer);
		StringS(x - 15, y - 1, GetTextLen(Buffer), 16, BLACK, Style, Buffer);
		StringS(x - 15, y + 1, GetTextLen(Buffer), 16, BLACK, Style, Buffer);
		StringS(x - 15, y, GetTextLen(Buffer), 16, Color, Style, Buffer);
	}

	void Names2(const char *name, float X, float Y, DWORD style, DWORD Color)
	{
		WStr huita;
		char* herota[40];
		int size = strlen(name);
		UTF8ToWStr(name, huita);// 410 = 1040  A 
		for (size_t i = 0; i < huita.length(); i++)
		{
			int fuck = huita[i];
			for (int w = 0; w < 76; w++)
			{
				if (fuck == kiriliza_kod[w])
				{
					herota[i] = alf[w];
					ESPString((X)+7 * i, Y, Color, style, "%s", herota[i]);
				}
			}
		}
	}

}*sDraw;



