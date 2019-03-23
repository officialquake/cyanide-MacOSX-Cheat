#include "main.h"
#include "Config.h"

cdrawings* draw = new cdrawings();
cwindow* window = new cwindow();
Config cfg;

HFONT framefont, espfont, fontMenu, titleFont;
bool bWasPressed, bWasReleased;

typedef struct
{
	char    m_szDefinition[ 12 ];
	char    m_szShiftDefinition[ 12 ];
	char    m_szAltDefinition[ 12 ];
}KeyStroke_t;

Color ColorBasedOnFlags(IFlags& flag) {
	Color col = [&]() -> Color {
		if(flag == IFlags::IFLAG_DANGER)
			return Color(178, 13, 68, 255);
		else if(flag == IFlags::IFLAG_INFO)
			return Color(13, 159, 178, 255);
		else if(flag == IFlags::IFLAG_SUCCESS)
			return Color(25, 197, 151, 255);
		else if(flag == IFlags::IFLAG_WARNING)
			return Color(184, 186, 29, 255);
		else if(flag == IFlags::IFLAG_DEFAULT)
			return Color(160, 160, 160, 255);
	}();
	
	return col;
}

std::wstring StringToWstring(std::string str) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
	
	try
	{
		return converter.from_bytes(str);
	}
	catch (std::range_error)
	{
		std::wostringstream s;
		s << str.c_str();
		return s.str();
	}
}




int activeIndex = 0;

KeyStroke_t m_KeyStroke[MOUSE_COUNT + KEY_COUNT] = {
	{ "", "", "" },
	{ "0", "=", "}" },                      //KEY_0
	{ "1", "!", "" },                       //KEY_1
	{ "2", "'", "" },                       //KEY_2
	{ "3", "", "" },                        //KEY_3
	{ "4", "$", "" },                       //KEY_4
	{ "5", "%", "" },                       //KEY_5
	{ "6", "&", "" },                       //KEY_6
	{ "7", "/", "{" },                      //KEY_7
	{ "8", "(", "[" },                      //KEY_8
	{ "9", ")", "]" },                      //KEY_9
	{ "a", "A", "" },                       //KEY_A,
	{ "b", "B", "" },                       //KEY_B,
	{ "c", "C", "" },                       //KEY_C,
	{ "d", "D", "" },						//KEY_D,
	{ "e", "E", "" },						//KEY_E,
	{ "f", "F", "" },						//KEY_F,
	{ "g", "G", "" },						//KEY_G,
	{ "h", "H", "" },						//KEY_H,
	{ "i", "I", "" },						//KEY_I,
	{ "j", "J", "" },						//KEY_J,
	{ "k", "K", "" },						//KEY_K,
	{ "l", "L", "" },						//KEY_L,
	{ "m", "M", "" },						//KEY_M,
	{ "n", "N", "" },						//KEY_N,
	{ "o", "O", "" },						//KEY_O,
	{ "p", "P", "" },						//KEY_P,
	{ "q", "Q", "" },						//KEY_Q,
	{ "r", "R", "" },						//KEY_R,
	{ "s", "S", "" },						//KEY_S,
	{ "t", "T", "" },						//KEY_T,
	{ "u", "U", "" },						//KEY_U,
	{ "v", "V", "" },						//KEY_V,
	{ "w", "W", "" },						//KEY_W,
	{ "x", "X", "" },						//KEY_X,
	{ "y", "Y", "" },						//KEY_Y,
	{ "z", "Z", "" },						//KEY_Z,
	{ "0", "0", "" },						//KEY_PAD_0,
	{ "1", "1", "" },						//KEY_PAD_1,
	{ "2", "2", "" },						//KEY_PAD_2,
	{ "3", "3", "" },						//KEY_PAD_3,
	{ "4", "4", "" },						//KEY_PAD_4,
	{ "5", "5", "" },						//KEY_PAD_5,
	{ "6", "6", "" },						//KEY_PAD_6,
	{ "7", "7", "" },						//KEY_PAD_7,
	{ "8", "8", "" },						//KEY_PAD_8,
	{ "9", "9", "" },						//KEY_PAD_9,
	{ "/", "/", "" },						//KEY_PAD_DIVIDE,
	{ "*", "*", "" },						//KEY_PAD_MULTIPLY,
	{ "-", "-", "" },						//KEY_PAD_MINUS,
	{ "+", "+", "" },						//KEY_PAD_PLUS,
	{ "enter", "enter", "" },				//KEY_PAD_ENTER,
	{ ".", ">", "" },						//KEY_PAD_DECIMAL,
	{ "[", "{", "" },						//KEY_LBRACKET,
	{ "]", "}", "" },						//KEY_RBRACKET,
	{ ";", ":", "" },						//KEY_SEMICOLON,
	{ "'", "@", "" },						//KEY_APOSTROPHE,
	{ "`", "", "" },						//KEY_BACKQUOTE,
	{ ",", "<", "" },						//KEY_COMMA,
	{ ".", ">", "" },						//KEY_PERIOD,
	{ "/", "?", "" },						//KEY_SLASH,
	{ "\\", "|", "" },						//KEY_BACKSLASH,
	{ "-", "_", "" },						//KEY_MINUS,
	{ "=", "+", "" },						//KEY_EQUAL,
	{ "enter", "enter", "" },				//KEY_ENTER,
	{ "space", "space", "" },				//KEY_SPACE,
	{ "backspace", "backspace", "" },		//KEY_BACKSPACE,
	{ "tab", "tab", "" },					//KEY_TAB,
	{ "caps", "caps", "" },					//KEY_CAPSLOCK,
	{ "numlock", "numlock", "" },			//KEY_NUMLOCK,
	{ "escape", "escape", "" },				//KEY_ESCAPE,
	{ "scrlock", "scrlock", "" },			//KEY_SCROLLLOCK,
	{ "insert", "insert", "" },				//KEY_INSERT,
	{ "delete", "delete", "" },				//KEY_DELETE,
	{ "home", "home", "" },					//KEY_HOME,
	{ "end", "end", "" },					//KEY_END,
	{ "pageup", "pageup", "" },				//KEY_PAGEUP,
	{ "pagedown", "pagedown", "" },			//KEY_PAGEDOWN,
	{ "break", "break", "" },				//KEY_BREAK,
	{ "lshift", "lshift", "" },				//KEY_LSHIFT,
	{ "rshift", "rshift", "" },				//KEY_RSHIFT,
	{ "lalt", "lalt", "" },					//KEY_LALT,
	{ "ralt", "ralt", "" },					//KEY_RALT,
	{ "lctrl", "lctrl", "" },				//KEY_LCONTROL,
	{ "rctrl", "rctrl", "" },				//KEY_RCONTROL,
	{ "lwin", "lwin", "" },					//KEY_LWIN,
	{ "rwin", "rwin", "" },					//KEY_RWIN,
	{ "app", "app", "" },					//KEY_APP,
	{ "up", "up", "" },						//KEY_UP,
	{ "left", "left", "" },					//KEY_LEFT,
	{ "down", "down", "" },					//KEY_DOWN,
	{ "right", "right", "" },				//KEY_RIGHT,
	{ "f1", "f1", "" },						//KEY_F1,
	{ "f2", "f2", "" },						//KEY_F2,
	{ "f3", "f3", "" },						//KEY_F3,
	{ "f4", "f4", "" },						//KEY_F4,
	{ "f5", "f5", "" },						//KEY_F5,
	{ "f6", "f6", "" },						//KEY_F6,
	{ "f7", "f7", "" },						//KEY_F7,
	{ "f8", "f8", "" },						//KEY_F8,
	{ "f9", "f9", "" },						//KEY_F9,
	{ "f10", "f10", "" },					//KEY_F10,
	{ "f11", "f11", "" },					//KEY_F11,
	{ "f12", "f12", "" },					//KEY_F12,
	{ "caps", "capstoggle", "" },			//KEY_CAPSLOCKTOGGLE,
	{ "numlock", "numlock", "" },			//KEY_NUMLOCKTOGGLE,
	{ "scrlock", "scrlock", "" },			//KEY_SCROLLLOCKTOGGLE,
	
	// Mouse
	{ "mouse1", "mouse1", "" },				//MOUSE_LEFT = MOUSE_FIRST,
	{ "mouse2", "mouse2", "" },				//MOUSE_RIGHT,
	{ "mouse3", "mouse3", "" },				//MOUSE_MIDDLE,
	{ "mouse4", "mouse4", "" },				//MOUSE_4,
	{ "mouse5", "mouse5", "" },				//MOUSE_5,
	{ "mwheelup", "mwheelup", "" },			//MOUSE_WHEEL_UP, A fake button which is 'pressed' and 'released' when the wheel is moved up
	{ "mwheeldown", "mwheeldown", "" },		//MOUSE_WHEEL_DOWN, A fake button which is 'pressed' and 'released' when the wheel is moved down
};

/* Checks if button was pressed */
auto WasPressed (ButtonCode_t code) -> void {
	if (pInputSystem->IsButtonDown(code))
	{
		bWasPressed = true;
	}
	else if (!(pInputSystem->IsButtonDown(code)))
	{
		if (bWasPressed)
			bWasReleased = true;
			else
			{
				bWasReleased = false;
			}
		bWasPressed = false;
	}
}

void cwindow::setup(int x, int y, int w, int h) {
	this->x = x, this->y = y, this->w = w, this->h = h;
}

void cwindow::setname(const char *szName) {
	this->szName = szName;
}

const char* cwindow::getname() {
	return this->szName;
}

void cdrawings::drawbox(int x, int y, int w, int h, Color color) {
	pSurface->DrawSetColor(color);
	pSurface->DrawOutlinedRect(x, y, x + w, y + h);
}

void cdrawings::drawboxoutline(int x, int y, int w, int h, Color color) {
	this->drawbox(x, y, w, h, color);
	this->drawbox(x - 1, y - 1, w + 2, h + 2, Color(0, 0, 0, 180));
	this->drawbox(x + 1, y + 1, w - 2, h - 2, Color(0, 0, 0, 180));
}

void cdrawings::fillrgba(int x, int y, int w, int h, Color color) {
	pSurface->DrawSetColor(color);
	pSurface->DrawFilledRect(x, y, x + w, y + h);
}

void cdrawings::FilledRectangle(Vector2D start_pos, Vector2D end_pos, Color col) {
	fillrgba(start_pos.x, start_pos.y, end_pos.x, end_pos.y, col);
}

void cdrawings::drawline(int x, int y, int xx, int yy, Color color) {
	pSurface->DrawSetColor(color);
	pSurface->DrawLine(x, y, xx, yy);
}

void cdrawings::Line(Vector2D start_pos, Vector2D end_pos, Color col) {
	drawline(start_pos.x, start_pos.y, end_pos.x, end_pos.y, col);
}

void cdrawings::Circle(Vector2D position, float points, float radius, Color color)
{
	float step = (float)M_PI * 2.0f / points;
	
	for (float a = 0; a < (M_PI * 2.0f); a += step)
	{
		Vector2D start(radius * cosf(a) + position.x, radius * sinf(a) + position.y);
		Vector2D end(radius * cosf(a + step) + position.x, radius * sinf(a + step) + position.y);
		Line(start, end, color);
	}
}

//=====================================

void cdrawings::BorderBox(int x, int y, int w, int h, int thickness, Color color)
{
	this->fillrgba(x, y, w, thickness, color);
	this->fillrgba(x, y, thickness, h, color);
	this->fillrgba(x + w, y, thickness, h, color);
	this->fillrgba(x, y + h, w + thickness, thickness, color);
}


void cdrawings::RectOutlined(int x, int y, int w, int h, int thickness, Color color, Color outlined) {
	this->fillrgba(x, y, w, h, color);
	this->BorderBox(x - thickness, y - thickness, w + thickness, h + thickness, thickness, outlined);
}

int cdrawings::TweakColor(int c1, int c2, int variation)
{
	if (c1 == c2)
		return c1;
	else if (c1 < c2)
		c1 += variation;
	else
		c1 -= variation;
	return c1;
}

void cdrawings::GardientRect(int x, int y, int w, int h, Color color1, Color color2, int variation)
{
	int r1 = color1.r();
	int g1 = color1.g();
	int b1 = color1.b();
	int a1 = color1.a();
	
	int r2 = color2.r();
	int g2 = color2.g();
	int b2 = color2.b();
	int a2 = color2.a();
	
	for (int i = 0; i <= w; i++)
	{
		this->fillrgba(x + i, y, 1, h, Color(r1, g1, b1, a1));
		r1 = this->TweakColor(r1, r2, variation);
		g1 = this->TweakColor(g1, g2, variation);
		b1 = this->TweakColor(b1, b2, variation);
		a1 = this->TweakColor(a1, a2, variation);
	}
}


//=====================================

std::wstring cdrawings::wstringtostring(std::string str) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
	
	try {
		return converter.from_bytes(str);
	}
	catch (std::range_error) {
		std::wostringstream s;
		s << str.c_str();
		return s.str();
	}
}

HFONT cdrawings::createfont(HFONT font, const char *szFont, int tall, int flags) {
	font = pSurface->CreateFont();
	pSurface->SetFontGlyphSet(font, szFont, tall, 150, 0, 0, flags);
	return font;
}

ViVecMouse::ViVecMouse(void) {
	
}

ViVecMouse::ViVecMouse(int X, int Y) {
	x = X; y = Y;
}

ViVecMouse cdrawings::GetMouse() {
	int x, y;
	pInputSystem->GetCursorPosition(&x, &y);
	
	ViVecMouse pPosition = ViVecMouse(x, y);
	return pPosition;
}

int cdrawings::CalcPos(int x) { // Not really sure who made this...
	int iRealXStart = ((1920 / 2) - (1920 / 2)) + x;
	return GetMouse().x - iRealXStart;
}

void cdrawings::addslider(int x, int y, int w, const char* szString, int& value, int index, int max, int min) {
	y += index * vars.buttonPadding;
	int h = 10;
	
	// int isCurrent = smoothValue * max - w + x; // DUM DUM VIKING, DUM DUM!
	int isCurrent = value * ((float)w / (float)(max));
	
	if (GetMouse().x > x - w / 2 && GetMouse().y > y - 2 && GetMouse().x < x + w + w / 2 && GetMouse().y < y + h + 2) {
		if (pInputSystem->IsButtonDown(MOUSE_LEFT)) {
			value = CalcPos(x) / ((float)w / (float)(max));
			if (value > max)
				value = max;
			if (value < min)
				value = min;
		}
	}
	std::string factor = std::to_string(value);
	std::string tostring = szString;
	
	std::string tofinal = tostring + ": " + factor;
	
	this->fillrgba(x, y, w, h, Color(34, 34, 34, 255));
	this->fillrgba(x + isCurrent, y - 1, 4, h + 2, Color(160, 160, 160, 255));
	this->drawbox(x, y, w, h, Color(160, 160, 160, 255));
	
	this->drawstring(x + w + 3, y - 4, Color(160, 160, 160, 255), framefont, tofinal.c_str());
}

void cdrawings::addslider(int x, int y, int w, const char* szString, float& value, int index, float max, float min) {
	y += index * vars.buttonPadding;
	int h = 10;
	
	// int isCurrent = smoothValue * max - w + x; // DUM DUM VIKING, DUM DUM!
	int isCurrent = value * ((float)w / (float)(max));
	
	if (GetMouse().x > x - w / 2 && GetMouse().y > y - 2 && GetMouse().x < x + w + w / 2 && GetMouse().y < y + h + 2) {
		if (pInputSystem->IsButtonDown(MOUSE_LEFT)) {
			value = CalcPos(x) / ((float)w / (float)(max));
			if (value > max)
				value = max;
			if (value < min)
				value = min;
		}
	}
	std::string factor = std::to_string(value);
	std::string tostring = szString;
	
	std::string tofinal = tostring + ": " + factor;
	
	this->fillrgba(x, y, w, h, Color(34, 34, 34, 255));
	this->fillrgba(x + isCurrent, y - 1, 4, h + 2, Color(160, 160, 160, 255));
	this->drawbox(x, y, w, h, Color(160, 160, 160, 255));
	
	this->drawstring(x + w + 3, y - 4, Color(160, 160, 160, 255), framefont, tofinal.c_str());
}


void cdrawings::drawstring(int x, int y, Color color, HFONT font, const char *szString, bool bCenter) {
	if(szString != NULL) {
		std::wstring wString = this->wstringtostring(szString);
		
		if(bCenter) {
			int wide, tall;
			pSurface->GetTextSize(font, wString.c_str(), wide, tall);
			x -= wide / 2;
			y -= tall / 2;
		}
		
		pSurface->DrawSetTextPos(x, y);
		pSurface->DrawSetTextFont(font);
		pSurface->DrawSetTextColor(color);
		pSurface->DrawPrintText(wString.c_str(), wcslen(wString.c_str()));
	}
}

void cdrawings::DrawBasicString(int x, int y, Color color, HFONT font, string szString) {
	std::wstring wString = StringToWstring(szString);
	pSurface->DrawSetTextPos(x, y);
	pSurface->DrawSetTextFont(font);
	pSurface->DrawSetTextColor(color);
	pSurface->DrawPrintText(wString.c_str(), wcslen(wString.c_str()));
}

void cdrawings::DrawBasicString(int x, int y, Color color, HFONT font, string szString, bool textsize) {
	std::wstring wString = StringToWstring(szString);
	
	if(textsize) {
		const wchar_t* cunt = wString.c_str();
		int w, t;
		pSurface->GetTextSize(font, cunt, w, t);
	}
	
	pSurface->DrawSetTextPos(x, y);
	pSurface->DrawSetTextFont(font);
	pSurface->DrawSetTextColor(color);
	pSurface->DrawPrintText(wString.c_str(), wcslen(wString.c_str()));
}

/*
 void fillrgbaINDEX(int x, int y, int w, int h, Color color, int index);
 void drawboxINDEX(int x, int y, int w, int h, Color color, int index);
 void drawstringINDEX(int x, int y, Color color, const char* szString, bool bCenter = false);
 */

void cdrawings::fillrgbaINDEX(int x, int y, int w, int h, Color color, int index) {
	y += index * vars.buttonPadding;
	
	fillrgba(x, y, w, h, color);
}

void cdrawings::drawboxINDEX(int x, int y, int w, int h, Color color, int index) {
	y += index * vars.buttonPadding;
	
	drawbox(x, y, w, h, color);
}

void cdrawings::drawstringINDEX(int x, int y, Color color, const char *szString, int index, bool bCenter, IFlags getFlag) {
	y += index * vars.buttonPadding;
	
	drawstring(x, y, ColorBasedOnFlags(getFlag), framefont, szString, bCenter);
}

bool cdrawings::inArea(int x, int y, int w, int h) {
	if(GetMouse().x > x && GetMouse().y > y && GetMouse().x < x + w && GetMouse().y < y + h) {
		return true;
	} else {
		return false;
	}
}



void cdrawings::addcolorslider(int x, int y, int w, const char* szString, int col[4], int index, int max, int min) {
	///this->addslider(x + 4, y + 50, redesignedWidth, "Fov", vars.aimbot.fov, 2);
	std::string adder = szString;
	
	std::string red = "R";
	std::string green = "G";
	std::string blue = "B";
	std::string alpha = "A";
	
	this->drawstringINDEX(x, y, Color(160, 160, 160, 255), szString, index);
	
	this->addslider(x, y, w, red.c_str(), col[0], index + 1, max, min);
	this->addslider(x, y, w, green.c_str(), col[1], index + 2, max, min);
	this->addslider(x, y, w, blue.c_str(), col[2], index + 3, max, min);
	this->addslider(x, y, w, alpha.c_str(), col[3], index + 4, max, min);
	
	this->fillrgbaINDEX(x, y, 20, 20, Color(col[0], col[1], col[2], col[3]), index + 5);
	this->drawboxINDEX(x, y, 20, 20, Color(160, 160, 160, 255), index + 5);
}

bool cdrawings::inArea2(int x, int y, int xx, int yy) {
	if(GetMouse().x > x && GetMouse().y > y && GetMouse().x < xx && GetMouse().y < yy) {
		return true;
	} else {
		return false;
	}
}

void cdrawings::addbutton(int x, int y, const char* szValue, bool* var, int index, IFlags getFlag) {
	y += index * vars.buttonPadding;
	
	Color state;
	
	int w = 14;
	int h = 14;
	
	if(*var)
		this->fillrgba(x + 2, y + 2, w - 4, h - 4, Color(80, 80, 80, 255));
	
	if(inArea(x, y, w, h)) {
		if(bWasReleased) {
			*var = !*var;
		}
	}
	
	this->drawbox(x, y, w, h, Color(160, 160, 160, 255));
	
	this->drawstring(x + w + 8, y - 1, ColorBasedOnFlags(getFlag), framefont, szValue);
}

void cdrawings::drawgradient(int x, int y, int w, int h, Color col1, Color col2) {
	
	this->fillrgba(x, y, w, h, col1);
	Byte first = col2.r();
	Byte second = col2.g();
	Byte third = col2.b();
	for (int i = 0; i < h; i++)
	{
		float fi = i, fh = h;
		float a = fi / fh;
		int ia = a * 255;
		this->fillrgba(x, y + i, w, 1, Color(first, second, third, ia));
	}
	
}

void cdrawings::drawgradientw(int x, int y, int w, int h, Color col1, Color col2) {
	
	this->fillrgba(x, y, w, h, col1);
	Byte first = col2.r();
	Byte second = col2.g();
	Byte third = col2.b();
	for (int i = 0; i < w; i++)
	{
		float fi = i, fh = w;
		float a = fi / fh;
		int ia = a * 255;
		this->fillrgba(x, y + i, w, 1, Color(first, second, third, ia));
	}
	
}

void cdrawings::GradientH(int x, int y, int width, int height, Color color1, Color color2) {
	float flDifferenceR = (float)(color2.r() - color1.r()) / (float)width;
	float flDifferenceG = (float)(color2.g() - color1.g()) / (float)width;
	float flDifferenceB = (float)(color2.b() - color1.b()) / (float)width;
	
	for (float i = 0.f; i < width; i++) {
		Color colGradient = Color(color1.r() + (flDifferenceR * i), color1.g() + (flDifferenceG * i), color1.b() + (flDifferenceB * i), color1.a());
		draw->fillrgba(x + i, y, 1, height, colGradient);
	}
}

// Menu
const char* gettabs() {
	switch(vars.tabIndex) { // going to add more tabs? make sure to add them in a case section.
		case 0:
			return "Main";
			break;
			
		default:
			return "Main";
			break;
	}
}

enum tTabs {
	Main,
	Aimbot,
	Visuals,
	Chams,
	Misc,
	Playerlist,
	Colors
};

/* Draws menu */
void cdrawings::drawnavigation(int x, int y, int w, int h, const char* szString) {
	
	this->drawgradient(x, y, w, h, Color(33, 33, 33, 255), Color(26, 26, 26, 255));
	
	
	std::vector<std::string> getTabs;
	
	getTabs.push_back("Main");
	getTabs.push_back("Aimbot");
	getTabs.push_back("Visuals");
	getTabs.push_back("Misc");
	getTabs.push_back("Configs");
	getTabs.push_back("Playerlist");
	getTabs.push_back("Colors");
	
	
	for(int i = 0; i < getTabs.size(); i++) {
		this->addtabs(x, y, getTabs[i].c_str(), i, vars.tabIndex, getTabs.size());
	}
	
}

void cdrawings::addplayerlistbutton(int x, int y, int w, int h, int index, int& playercount, const char* szString, IFlags getFlag) {
	y += index * vars.buttonPadding;
	
	if(inArea(x, y, w, h)) {
		if(bWasReleased) {
			playercount = index;
		}
	}
	
	bool bHovering = inArea(x, y, w, h);
	this->drawgradient(x, y, w, h, bHovering ? Color(54, 54, 54, 255), Color(34, 34, 34, 255) : Color(44, 44, 44, 255), Color(24, 24, 24, 255));
	this->drawbox(x, y, w, h, Color::Black());
	
	this->drawstring(x + w / 2, y + h / 2, ColorBasedOnFlags(getFlag), framefont, szString, true);
}

void cdrawings::addtabs(int x, int y, const char* szTabs, int index, int& itab, int max) {
	int wScreen, hScreen;
	pEngine->GetScreenSize(wScreen, hScreen);
	
	int w = wScreen / max;
	x += index * w;
	int h = 30;
	
	if(inArea(x, y, w, h)) {
		if(bWasReleased) {
			itab = index;
		}
	}
	
	if(itab == index)
		this->drawgradient(x, y, w, h, Color(36, 123, 149, 255), Color(14, 102, 129, 255));
	
	if(itab == index)
		this->drawstring(x + w / 2, y + h / 2, Color(160, 160, 160, 255), framefont, szTabs, true);
	else
		this->drawstring(x + w / 2, y + h / 2, Color(88, 88, 88, 255), framefont, szTabs, true);
}

void cdrawings::drawpalettetabs(int x, int y, int w, const char* szString, int& itab, int index, int max) {
	w /= max;
	
	x += index * w;
	int h = 20;
	if(inArea(x, y, w, 20)) {
		if(bWasReleased) {
			itab = index;
		}
	}
	
	this->fillrgba(x, y, w, h, Color(64, 64, 64, 255));
	
	if(itab == index)
		this->drawgradient(x, y, w, h, Color(149, 36, 36, 255), Color(129, 13, 13, 255));
	
	if(itab == index)
		this->drawstring(x + w / 2, y + h / 2, Color(160, 160, 160, 255), framefont, szString, true);
	else
		this->drawstring(x + w / 2, y + h / 2, Color(88, 88, 88, 255), framefont, szString, true);
}

bool Janela[8][2];
ViVecMouse ClickPosicao;
bool cdrawings::MoveMenu(int & x, int & y, int w, int h, int index) {
	//Credits: Code64/CodeRed
	for (int i = 0; i < 8; i++)
		if (Janela[i][0] && i != index)
			return false;
	
	if (pInputSystem->IsButtonDown(MOUSE_LEFT))
	{
		/* GetMouse().x > x && GetMouse().x < x + w && GetMouse().y >(y - 3) && GetMouse().y < (y - 3) + h */
		if ((GetMouse().x > x && GetMouse().y > y && GetMouse().x < x + w && GetMouse().y < y + h) || Janela[index][0])
		{
			Janela[index][0] = true;
			
			if (!Janela[index][1])
			{
				ClickPosicao.x = GetMouse().x - x;
				ClickPosicao.y = GetMouse().y - y;
				Janela[index][1] = true;
				
			}
		}
		else
		{
			Janela[index][0] = false;
			Janela[index][1] = false;
		}
	}
	
	if (!(pInputSystem->IsButtonDown(MOUSE_LEFT)) && Janela[index][0])
	{
		Janela[index][0] = false;
		Janela[index][1] = false;
	}
	
	if (Janela[index][0])
	{
		x = GetMouse().x - ClickPosicao.x;
		y = GetMouse().y - ClickPosicao.y;
	}
	
	return true;
}

void cdrawings::drawcolorpicker(int x, int y, const char *szString, Color &col, int index) {
	y += index * vars.buttonPadding;
	int oner = 6;
	float flRnbw = 0.0005f;
	int currPosX, currPosY;
	for(int i = 0 ; i < 21; i++) {
		flRnbw += 0.045f;
		
		Color col1 = Color::GetFromHSB(flRnbw, 1.0f, 1.0f);
		Color col2 = Color::GetFromHSB(flRnbw, 0.90f, 0.90f);
		Color col3 = Color::GetFromHSB(flRnbw, 0.80f, 0.80f);
		Color col4 = Color::GetFromHSB(flRnbw, 0.70f, 0.70f);
		Color col5 = Color::GetFromHSB(flRnbw, 0.60f, 0.60f);
		Color col6 = Color::GetFromHSB(flRnbw, 0.50f, 0.50f);
		Color col7 = Color::GetFromHSB(flRnbw, 0.40f, 0.40f);
		Color col8 = Color::GetFromHSB(flRnbw, 0.30f, 0.30f);
		Color col9 = Color::GetFromHSB(flRnbw, 0.20f, 0.20f);
		Color col10 = Color::GetFromHSB(flRnbw, 0.15f, 0.15f);
		Color col11 = Color::GetFromHSB(flRnbw, 0.10f, 0.10f);
		
		this->fillrgba(x + i * oner, y, oner, oner, Color(col1.r(), col1.g(), col1.b(), 255));
		this->fillrgba(x + i * oner, y + oner * 1, oner, oner, Color(col2.r(), col2.g(), col2.b(), 255));
		this->fillrgba(x + i * oner, y + oner * 2, oner, oner, Color(col3.r(), col3.g(), col3.b(), 255));
		this->fillrgba(x + i * oner, y + oner * 3, oner, oner, Color(col4.r(), col4.g(), col4.b(), 255));
		this->fillrgba(x + i * oner, y + oner * 4, oner, oner, Color(col5.r(), col5.g(), col5.b(), 255));
		this->fillrgba(x + i * oner, y + oner * 5, oner, oner, Color(col6.r(), col6.g(), col6.b(), 255));
		this->fillrgba(x + i * oner, y + oner * 6, oner, oner, Color(col7.r(), col7.g(), col7.b(), 255));
		this->fillrgba(x + i * oner, y + oner * 7, oner, oner, Color(col8.r(), col8.g(), col8.b(), 255));
		this->fillrgba(x + i * oner, y + oner * 8, oner, oner, Color(col9.r(), col9.g(), col9.b(), 255));
		this->fillrgba(x + i * oner, y + oner * 9, oner, oner, Color(col10.r(), col10.g(), col10.b(), 255));
		this->fillrgba(x + i * oner, y + oner * 10, oner, oner, Color(col11.r(), col11.g(), col11.b(), 255));
		
		int x1 = x + i * oner;
		int y2 = y + oner * 1;
		int y3 = y + oner * 2;
		int y4 = y + oner * 3;
		int y5 = y + oner * 4;
		int y6 = y + oner * 5;
		int y7 = y + oner * 6;
		int y8 = y + oner * 7;
		int y9 = y + oner * 8;
		int y10 = y + oner * 9;
		int y11 = y + oner * 10;
		
		if(inArea(x1, y, oner, oner)) {
			if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
				col = col1;
				this->drawbox(x1, y, oner, oner, Color::Black());
				currPosX = x1;
				currPosY = y;
			}
		} else if(inArea(x1, y2, oner, oner)) {
			if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
				col = col2;
				this->drawbox(x1, y2, oner, oner, Color::Black());
				currPosX = x1;
				currPosY = y2;
			}
		} else if(inArea(x1, y3, oner, oner)) {
			if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
				col = col3;
				this->drawbox(x1, y3, oner, oner, Color::Black());
				currPosX = x1;
				currPosY = y3;
			}
		} else if(inArea(x1, y4, oner, oner)) {
			if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
				col = col4;
				this->drawbox(x1, y4, oner, oner, Color::Black());
				currPosX = x1;
				currPosY = y4;
			}
		} else if(inArea(x1, y5, oner, oner)) {
			if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
				col = col5;
				this->drawbox(x1, y5, oner, oner, Color::Black());
				currPosX = x1;
				currPosY = y5;
			}
		} else if(inArea(x1, y6, oner, oner)) {
			if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
				col = col6;
				this->drawbox(x1, y6, oner, oner, Color::Black());
				currPosX = x1;
				currPosY = y6;
			}
		}
		else if(inArea(x1, y7, oner, oner)) {
			if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
				col = col7;
				this->drawbox(x1, y7, oner, oner, Color::Black());
				currPosX = x1;
				currPosY = y7;
			}
		}
		else if(inArea(x1, y8, oner, oner)) {
			if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
				col = col8;
				this->drawbox(x1, y8, oner, oner, Color::Black());
				currPosX = x1;
				currPosY = y8;
			}
		}
		else if(inArea(x1, y9, oner, oner)) {
			if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
				col = col9;
				this->drawbox(x1, y9, oner, oner, Color::Black());
				currPosX = x1;
				currPosY = y9;
			}
		}
		else if(inArea(x1, y10, oner, oner)) {
			if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
				col = col10;
				this->drawbox(x1, y10, oner, oner, Color::Black());
				currPosX = x1;
				currPosY = y10;
			}
		}
		else if(inArea(x1, y11, oner, oner)) {
			if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
				col = col11;
				this->drawbox(x1, y11, oner, oner, Color::Black());
				currPosX = x1;
				currPosY = y11;
			}
		}
	}
	
	this->fillrgba(x, y + 78, 90, 20, Color(col.r(), col.g(), col.b(), 255));
	this->drawbox(x, y + 78, 90, 20, Color::Black());
	
	// this->drawbox(currPosX, currPosY, oner, oner, Color::Black());
	
	//char tostrcolpalette[308];
	//sprintf(tostrcolpalette, "%s R: %i, G: %i, B: %i", szString, col.r(), col.g(), col.b());
	
	std::string strPalette = szString;
	strPalette.append(" R: ");
	strPalette.append(std::to_string(col.r()));
	
	strPalette.append(" G: ");
	strPalette.append(std::to_string(col.g()));
	
	strPalette.append(" B: ");
	strPalette.append(std::to_string(col.b()));
	
	
	this->drawstring(x, y + 110, Color::White(), framefont, strPalette.c_str());
}

void cdrawings::addcombo(int x, int y, int w, const char* szString, std::vector<std::string> szValue, int& currValue, bool* bOpend, int index) {
	y += index * vars.buttonPadding;
	int h = 15;
	
	if(inArea(x, y, w, h)) {
		if(bWasReleased) {
			*bOpend = !*bOpend;
		}
	}
	
	if(*bOpend) {
		for(int i = 0; i < szValue.size(); i++) {
			int yy = y + h + i * h;
			
			this->fillrgba(x, yy, w, h, Color(34, 34, 34, 255));
			//this->drawbox(x, yy, w, h, Color(134, 134, 134, 255));
			this->drawstring(x + 2, yy - 1, Color(160, 160, 160, 255), framefont, szValue[i].c_str());
			
			if(inArea2(x, yy, x + w, yy + h)) {
				if(bWasReleased) {
					currValue = i;
					*bOpend = false;
				}
			}
		}
	}
	
	this->fillrgba(x, y, w, h, Color(34, 34, 34, 255));
	this->drawbox(x, y, w, h, Color(160, 160, 160, 255));
	this->drawstring(x + 2, y - 1, Color(160, 160, 160, 255), framefont, szValue[currValue].c_str());
	this->drawstring(x + w + 3, y - 1, Color(160, 160, 160, 255), framefont, szString);
}

void cdrawings::textbox(int x, int y, int w, const char* szString, std::string szValue[100], int inputIndex, int index, bool* var) {
	y += index * vars.buttonPadding;
	int h = 15;
	
	if(inArea(x, y, w, h)) {
		*var = true;
		activeIndex = inputIndex;
	} else {
		*var = false;
	}
	
	this->fillrgba(x, y, w, h, Color(34, 34, 34, 255));
	if(inArea(x, y, w, h)) {
		this->drawbox(x, y, w, h, Color::Black());
	} else {
		this->drawbox(x, y, w, h, Color(160, 160, 160, 255));
	}
	this->drawstring(x + 2, y - 1, Color(160, 160, 160, 255), framefont, ">");
	
	if(szValue[inputIndex].length() > 32) {
		std::size_t getLength = szValue[inputIndex].length();
		szValue[inputIndex].erase(getLength - 1);
		m_nCurrentPos[inputIndex]--;
	}
	
	if(szValue[inputIndex].length() > 0) {
		this->drawstring(x + 15, y - 1, Color(160, 160, 160, 255), framefont, szValue[inputIndex].c_str());
	}
	
	
	
	this->drawstring(x + w + 3, y - 1, Color(160, 160, 160, 255), framefont, szString);
	
	
}

void cdrawings::handleinput(int eventcode, string arr[100]) {
	if (IsKeyPressed(eventcode, KEY_BACKSPACE))
	{
		size_t nLength = arr[activeIndex].length();
		if (nLength > 0)
		{
			arr[activeIndex].erase(nLength - 1);
			m_nCurrentPos[activeIndex]--;
			return;
		}
	}
	
	if(IsKeyPressed(eventcode, KEY_ENTER)) {
		m_szChangedValue[activeIndex] = arr[activeIndex];
		return;
	}
	
	if (IsKeyPressed(eventcode, KEY_SPACE))
	{
		arr[activeIndex].append(" ");
		return;
	}
	
	if (eventcode >= KEY_0
		&& eventcode <= KEY_EQUAL
		&& arr[activeIndex].length() <= 114)
	{
		if (pInputSystem->IsButtonDown(KEY_LSHIFT) || pInputSystem->IsButtonDown(KEY_RSHIFT))
		{
			arr[activeIndex].append(m_KeyStroke[eventcode].m_szShiftDefinition);
			m_nCurrentPos[activeIndex]++;
		}
		else
		{
			arr[activeIndex].append(m_KeyStroke[eventcode].m_szDefinition);
			m_nCurrentPos[activeIndex]++;
		}
	}
}

void cdrawings::renderButton(int x, int y, int w, int h, const char* szString, bool* var) { //Color col1, Color col2
	
	if(draw->inArea(x, y, w, h)) {
		if(bWasPressed) {
			*var = true;
			draw->drawbox(x, y, w, h, Color(149, 36, 36, 255));
			draw->fillrgba(x, y, w, h, Color(149, 36, 36, 255));
		}
	} else {
		*var = false;
	}
	
	
	//bool bHovering = draw->inArea(x, y, w, h);
	
	//draw->drawgradient(x, y, w, h, col1, col2);
	//draw->drawbox(x, y, w, h, Color(255, 137, 0, 255)); //border1 60 60 60
	draw->fillrgba(x, y, w, h, Color(64, 64, 64, 255));
	draw->drawstring(x + w / 2, y + 9, Color(255, 255, 255, 255), framefont, szString, true); //y + h / 2
	
}

void cdrawings::renderCombo(int x, int y, int w, int h, const char* szString, vector<string> szValue, int& currValue, bool* bOpend)
{
	
	int Y = y + h;
	
	if(draw->inArea(x, y, w, h)) {
		if(bWasReleased) {
			*bOpend = !*bOpend;
		}
	}
	
	if (*bOpend) {
		for ( int i = 0; i < szValue.size(); i++ ) {
			
			//auto bHover = draw->inArea(x, Y + 2 + (i * h), w, 18);
			draw->fillrgba(x, Y + (i * h), w, h, Color(64, 64, 64, 180));
			//draw->drawbox(x, Y + (i * h), w, h, Color(0, 170, 255, 255));
			draw->drawstring(x + 10, Y + 3 + (i * h), Color(175, 175, 175, 255), framefont, szValue[i].c_str());
			
			
			if (draw->inArea(x, Y + 2 + ( i * h ), w, 18)) {
				if(bWasPressed){
					currValue = i;
					*bOpend = false;
				}
			}
		}
	}
	
	if(currValue == 0)
		szString = szString;
	else
		szString = szValue[currValue].c_str();
	
	// Draws the box
	draw->fillrgba(x, y, w, h, Color(64, 64, 64, 55));
	draw->drawstring(x + 10, y + (h / 2) - 7, Color(175, 175, 175, 255), framefont, szString);
	
	
	if (!*bOpend)
	{
		// draw arrow pointing down
		draw->fillrgba( ( x + w - h + 113 - 107 ), ( y + 8 ), 1, 1, Color( 255, 255, 255, 255 ) );
		draw->fillrgba( ( x + w - h + 114 - 107 ), ( y + 8 ), 1, 2, Color( 255, 255, 255, 255 ) );
		draw->fillrgba( ( x + w - h + 115 - 107 ), ( y + 8 ), 1, 3, Color( 255, 255, 255, 255 ) );
		draw->fillrgba( ( x + w - h + 116 - 107 ), ( y + 8 ), 1, 4, Color( 255, 255, 255, 255 ) );
		draw->fillrgba( ( x + w - h + 117 - 107 ), ( y + 8 ), 1, 3, Color( 255, 255, 255, 255 ) );
		draw->fillrgba( ( x + w - h + 118 - 107 ), ( y + 8 ), 1, 2, Color( 255, 255, 255, 255 ) );
		draw->fillrgba( ( x + w - h + 119 - 107 ), ( y + 8 ), 1, 1, Color( 255, 255, 255, 255 ) );
	}
	else
	{
		// draw arrow pointing up
		draw->fillrgba( ( x + w - h + 113 - 107 ), ( y + 11 ), 1, 1, Color( 255, 255, 255, 255 ) );
		draw->fillrgba( ( x + w - h + 114 - 107 ), ( y + 10 ), 1, 2, Color( 255, 255, 255, 255 ) );
		draw->fillrgba( ( x + w - h + 115 - 107 ), ( y + 9 ), 1, 3, Color( 255, 255, 255, 255 ) );
		draw->fillrgba( ( x + w - h + 116 - 107 ), ( y + 8 ), 1, 4, Color( 255, 255, 255, 255 ) );
		draw->fillrgba( ( x + w - h + 117 - 107 ), ( y + 9 ), 1, 3, Color( 255, 255, 255, 255 ) );
		draw->fillrgba( ( x + w - h + 118 - 107 ), ( y + 10 ), 1, 2, Color( 255, 255, 255, 255 ) );
		draw->fillrgba( ( x + w - h + 119 - 107 ), ( y + 11 ), 1, 1, Color( 255, 255, 255, 255 ) );
	}
}

bool bCheckState() {
	if(pEngine->IsInGame() && pEngine->IsConnected()) {
		return true;
	} else {
		return false;
	}
}

enum cColorTabs {
	CTChams		= 0,
	TChams		= 1,
	CTBoxes		= 2,
	TBoxes		= 3,
	HANDChams	= 4,
	World		= 5
};

enum cMainTabs{ // Tabs
	
	AimbotTab		= 0,
	//VisualsTab		= 1,
	//MiscTab			= 2,
	//ConfigsTab		= 3,
	ColorsTab		= 1,
	//PlayerlistTab	= 5
};

void cdrawings::drawmouse() { // Draws mouse
	int mouse_x = this->GetMouse().x;
	int mouse_y = this->GetMouse().y;
	
	this->fillrgba(mouse_x + 1, mouse_y, 1, 17, Color(0, 0, 0, 255));
	
	// Mouse outline - Color(51, 51, 51, 255) - Original colour
	for(int i = 0; i < 11; i++)
		this->fillrgba(mouse_x + 2 + i, mouse_y + 1 + i, 1, 1, Color(0, 0, 0, 255)); // (0, 0, 0, 255)
	this->fillrgba(mouse_x + 7, mouse_y + 12, 6, 1, Color(0, 0, 0, 255));
	this->fillrgba(mouse_x + 6, mouse_y + 12, 1, 1, Color(0, 0, 0, 255));
	this->fillrgba(mouse_x + 5, mouse_y + 13, 1, 1, Color(0, 0, 0, 255));
	this->fillrgba(mouse_x + 4, mouse_y + 14, 1, 1, Color(0, 0, 0, 255));
	this->fillrgba(mouse_x + 3, mouse_y + 15, 1, 1, Color(0, 0, 0, 255));
	this->fillrgba(mouse_x + 2, mouse_y + 16, 1, 1, Color(0, 0, 0, 255));
	
	// Mouse body - Color(81, 81, 81, 255) - Original colour
	for(int i = 0; i < 4; i++)
		this->fillrgba(mouse_x + 2 + i, mouse_y + 2 + i, 1, 14 - (i * 2), Color(150, 20, 20, 230));
	this->fillrgba(mouse_x + 6, mouse_y + 6, 1, 6, Color(150, 20, 20, 230));
	this->fillrgba(mouse_x + 7, mouse_y + 7, 1, 5, Color(150, 20, 20, 230));
	this->fillrgba(mouse_x + 8, mouse_y + 8, 1, 4, Color(150, 20, 20, 230));
	this->fillrgba(mouse_x + 9, mouse_y + 9, 1, 3, Color(150, 20, 20, 230));
	this->fillrgba(mouse_x + 10, mouse_y + 10, 1, 2, Color(150, 20, 20, 230));
	this->fillrgba(mouse_x + 11, mouse_y + 11, 1, 1, Color(150, 20, 20, 230));
}

void cdrawings::drawmenu() { // Draws menu
	
	int wScreen, hScreen;
	pEngine->GetScreenSize(wScreen, hScreen);
	
	
	
	int w = 600;
	int h = 400;
	int hh = 22;
	
	
	static int y = 80;
	static int rewidth = 130;
	
	
	// Menu
	this->fillrgba(rewidth, y, w, h, Color(30, 30, 30, 255));
	this->drawbox(rewidth, y, w, h, Color(58, 58, 58, 255));
	//this->drawstring(rewidth + 6, y + 4, Color(160, 160, 160, 255), framefont, "Cyanide"); // Window title
	
	this->drawline(rewidth, y + 22, rewidth + w, y + 22, Color(58, 58, 58, 255));
	
	
	
	/* Aimbot, Visuals, Misc, Playerlist, Colors */
	
	if(vars.tabIndex == tTabs::Main) {
		std::vector<std::string> MainTabs;
		
		MainTabs.push_back("Cyanide");
		//MainTabs.push_back("Visuals");
		//MainTabs.push_back("Misc");
		//MainTabs.push_back("Configs");
		MainTabs.push_back("Colors");
		
		
		
		
		for(int i = 0; i < MainTabs.size(); i++) { // Draws main tabs
			this->drawpalettetabs(rewidth, y + 20, w, MainTabs[i].c_str(), vars.main.tab, i, MainTabs.size());
		}
		
		
		
		
		if(vars.main.tab == cMainTabs::AimbotTab) {
			this->addbutton(rewidth + 12, y + 50, "Aimbot", &vars.aimbot.enabled, 0);
			this->addbutton(rewidth + 12, y + 50, "Silent Aim", &vars.aimbot.silent, 1);
			this->addslider(rewidth + 12, y + 50, 50, "FOV", vars.aimbot.fov, 2, 5, 0); // 180 and 0... 180 Are the maximum value and 0 is the minimum.
			this->addbutton(rewidth + 12, y + 50, "Smooth", &vars.aimbot.smooth, 3);
			this->addslider(rewidth + 12, y + 50, 50, "", vars.aimbot.smoothf, 4, 1.f, 0.f); // Smothing amount
			this->addslider(rewidth + 12, y + 50, 50, "Hitbox", vars.aimbot.bone, 5, 17, 0); // 180 and 0... 180 Are the maximum value and 0 is the minimum.
			this->addbutton(rewidth + 12, y + 50, "RCS", &vars.aimbot.rcs, 6);
			this->addslider(rewidth + 12, y + 50, 50, "", vars.aimbot.rcsf, 7, 25.f, 0.f);
			
			this->addbutton(rewidth + 12 + 170, y + 50, "Trigger", &vars.aimbot.trigger, 0);
			
			
			std::vector<std::string> chamsvector;
			
			chamsvector.push_back("Lit");
			chamsvector.push_back("Texture");
			
			
			this->addbutton(rewidth + 12 + 290, y + 50, "Chams", &vars.visuals.chams, 0);
			this->addbutton(rewidth + 12 + 290, y + 50, "Wallhack", &vars.visuals.wallhack, 1);
			
			this->addcombo(rewidth + 12 + 410, y + 50, 70, "Type", chamsvector, vars.visuals.playersType, &vars.players_opend, 0);
			
			this->addbutton(rewidth + 12 + 290, y + 50, "Bunny hop", &vars.misc.bhop, 3);
			this->addbutton(rewidth + 12 + 290, y + 50, "Skinchanger", &vars.visuals.skinc, 4);
			
			this->addbutton(rewidth + 12 + 290, y + 50, "No Recoil", &vars.misc.norecoil, 5);
			this->addbutton(rewidth + 12 + 290, y + 50, "No Visual Recoil", &vars.misc.novisualrecoil, 6);
			
			this->addbutton(rewidth + 12 + 290, y + 50, "Show Real angle (see if you are spinning)", &vars.misc.thirdpersonmode, 7);
			
			
			vector<string> configvec;
			
			configvec.push_back("Settings");
			
			this->renderCombo(rewidth + 80 + 40, y + 300, 80, 20, "Settings", configvec, cfg.cfgcombo, &vars.cfg_opend);
			this->renderButton(rewidth + 80 + 125, y + 300, 80, 20, "Load", &cfg.loadconfig);
			this->renderButton(rewidth + 80 + 210, y + 300, 80, 20, "Save", &cfg.saveconfig);
			
		}/*
		  if(vars.main.tab == cMainTabs::VisualsTab) {
		  this->addbutton(rewidth + 12, y + 50, "Enabled", &vars.visuals.enabled, 0);
		  this->addbutton(rewidth + 12, y + 50, "Enemy Only", &vars.visuals.enemyonly, 1);
		  this->addbutton(rewidth + 12, y + 50, "Box", &vars.visuals.box, 2);
		  this->addbutton(rewidth + 12, y + 50, "Name", &vars.visuals.name, 3);
		  this->addbutton(rewidth + 12, y + 50, "Health Text", &vars.visuals.healthtext, 4);
		  this->addbutton(rewidth + 12, y + 50, "Armour Text", &vars.visuals.armourtext, 5);
		  this->addbutton(rewidth + 12 + 170, y + 50, "No Flash", &vars.misc.noflash, 0);
		  this->addslider(rewidth + 12 + 170, y +50, 105, "Flash Alpha", vars.misc.flashalpha, 1, 255, 0);// 255 and 0... 255 maximum value and 0 is the minimum.
		  this->addbutton(rewidth + 12 + 170, y + 50, "Scoped ESP", &vars.visuals.Scoped, 2);
		  this->addbutton(rewidth + 12 + 170, y + 50, "Rescuing(Hostage) ESP", &vars.visuals.Rescuing, 3);
		  this->addbutton(rewidth + 12 + 170, y + 50, "Cash ESP", &vars.visuals.cash, 4);
		  this->addbutton(rewidth + 12 + 170, y + 50, "Defusing ESP", &vars.visuals.Defusing, 5);
		  
		  
		  std::vector<std::string> chamsvector;
		  
		  chamsvector.push_back("Lit");
		  chamsvector.push_back("Texture");
		  
		  
		  
		  this->addbutton(rewidth + 12 + 290, y + 50, "Player Chams", &vars.visuals.chams, 0);
		  this->addbutton(rewidth + 12 + 290, y + 50, "Cham Wallhack", &vars.visuals.wallhack, 3);
		  
		  this->addcombo(rewidth + 12 + 410, y + 50, 90, "Players", chamsvector, vars.visuals.playersType, &vars.players_opend, 0);
		  
		  
		  
		  }
		  
		  if(vars.main.tab == cMainTabs::MiscTab) {
		  
		  this->addbutton(rewidth + 12, y + 50, "Enabled", &vars.misc.enabled, 0);
		  this->addbutton(rewidth + 12, y + 50, "Bunny hop", &vars.misc.bhop, 1);
		  this->addbutton(rewidth + 12, y + 50, "No Recoil", &vars.misc.norecoil, 8);
		  this->addbutton(rewidth + 12, y + 50, "No Visual Recoil", &vars.misc.novisualrecoil, 9);
		  
		  }
		  
		  if(vars.main.tab == cMainTabs::ConfigsTab) {
		  
		  vector<string> configvec;
		  
		  configvec.push_back("Settings");
		  configvec.push_back("Settings 2");
		  
		  this->renderCombo(rewidth + 80 + 40, y + 300, 80, 20, "Settings", configvec, cfg.cfgcombo, &vars.cfg_opend);
		  this->renderButton(rewidth + 80 + 125, y + 300, 80, 20, "Load", &cfg.loadconfig);
		  this->renderButton(rewidth + 80 + 210, y + 300, 80, 20, "Save", &cfg.saveconfig);
		  }
		  */
		
		if(vars.main.tab == cMainTabs::ColorsTab) {
			
			
			std::vector<std::string> ColorTabs;
			
			ColorTabs.push_back("CT Chams");
			ColorTabs.push_back("T Chams");
			ColorTabs.push_back("CT Box");
			ColorTabs.push_back("T Box");
			
			for(int i = 0; i < ColorTabs.size(); i++) { // Draws color tabs
				this->drawpalettetabs(rewidth, y + 40 + 1, w, ColorTabs[i].c_str(), vars.colors.tab, i, ColorTabs.size());
			}
			
			
			
			if(vars.colors.tab == cColorTabs::CTChams) {
				this->drawcolorpicker(rewidth + 12, y + 70, "CT Chams", vars.colors.ctchams, 0);
				this->drawcolorpicker(rewidth + 12 + 300, y + 70, "CT Chams Ignore", vars.colors.ctchams_ign, 0);
			}
			
			if(vars.colors.tab == cColorTabs::TChams) {
				this->drawcolorpicker(rewidth + 12, y + 70, "T Chams", vars.colors.tchams, 0);
				this->drawcolorpicker(rewidth + 12 + 300, y + 70, "T Chams Ignore", vars.colors.tchams_ign, 0);
			}
			
			if(vars.colors.tab == cColorTabs::CTBoxes) {
				this->drawcolorpicker(rewidth + 12, y + 70, "CT Box", vars.colors.ctbox, 0);
				this->drawcolorpicker(rewidth + 12 + 300, y + 70, "CT Box Wall", vars.colors.ctbox_ign, 0);
			}
			
			if(vars.colors.tab == cColorTabs::TBoxes) {
				this->drawcolorpicker(rewidth + 12, y + 70, "T Box", vars.colors.tbox, 0);
				this->drawcolorpicker(rewidth + 12 + 300, y + 70, "T Box Wall", vars.colors.tbox_ign, 0);
			}
		}
	}
	
	//this->renderConfigs(x + 25, y + h - 56);
	
	config->getConfig(cfg.cfgcombo);
	
	if(!vars.cfgInit) {
		config->LoadConfig();
		config->InitSkins();
		config->LoadSkins();
		vars.cfgInit = true;
	}
	
	if(cfg.loadconfig) {
		config->LoadConfig();
	}
	
	if(cfg.saveconfig) {
		config->SaveConfig();
	}
	
	this->MoveMenu(rewidth, y, w, hh, 0);
	
	WasPressed(MOUSE_LEFT);
	
}
