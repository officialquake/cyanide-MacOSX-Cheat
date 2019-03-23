#include "main.h"

extern HFONT framefont, espfont, fontMenu, titleFont;

class cwindow {
public:
    void setup(int x, int y, int w, int h);
    void setname(const char* szName);
    const char* getname();
public:
    int x, y, w, h;
    const char* szName;
};

typedef int ViVec_t;

class ViVecMouse {
public:
    ViVec_t x, y;
    ViVecMouse(void);
    ViVecMouse(ViVec_t X, ViVec_t Y);
};

enum class IFlags {
    IFLAG_DEFAULT = 0x1337,
    IFLAG_DANGER = 0x100,
    IFLAG_WARNING = 0x200,
    IFLAG_SUCCESS = 0x300,
    IFLAG_INFO = 0x400
};

class cdrawings {
public:
    void drawbox(int x, int y, int w, int h, Color color);
    void drawboxoutline(int x, int y, int w, int h, Color color);
    void fillrgba(int x, int y, int w, int h, Color color);
     void renderButton(int x, int y, int w, int h, const char* szString, bool* var);
     void renderCombo(int x, int y, int w, int h, const char* szString, vector<string> szValue, int& currValue, bool* bOpend);
    void drawline(int x, int y, int xx, int yy, Color color);
    void Circle(Vector2D position, float points, float radius, Color color);
    std::wstring wstringtostring(std::string str);
    HFONT createfont(HFONT font, const char* szFont, int tall, int flags);
    void drawstring(int x, int y, Color color, HFONT font, const char* szString, bool bCenter = false);
    void fillrgbaINDEX(int x, int y, int w, int h, Color color, int index);
    void drawboxINDEX(int x, int y, int w, int h, Color color, int index);
    void drawstringINDEX(int x, int y, Color color, const char *szString, int index, bool bCenter = false, IFlags getFlag = IFlags::IFLAG_DEFAULT);
    int CalcPos(int x);
    void addbutton(int x, int y, const char* szValue, bool* var, int index, IFlags getFlag = IFlags::IFLAG_DEFAULT);
    void addtabs(int x, int y, const char* szTabs, int index, int& itab, int max);
    void addslider(int x, int y, int w, const char* szString, int& value, int index, int max = 180, int min = 0);
    void addslider(int x, int y, int w, const char* szString, float& value, int index, float max, float min);
    void addcolorslider(int x, int y, int w, const char* szString, int col[4], int index, int max = 255, int min = 0);
    void addcombo(int x, int y, int w, const char* szString, std::vector<std::string> szValue, int& currValue, bool* bOpend, int index);
    void handleinput(int eventcode, string arr[100]);
    //void handleinput(int eventcode);
    void textbox(int x, int y, int w, const char* szString, std::string szValue[100], int inputIndex, int index, bool* var);
    void drawnavigation(int x, int y, int w, int h, const char* szString);
    void drawgradient(int x, int y, int w, int h, Color col1, Color col2);
    void drawcolorpicker(int x, int y, const char* szString, Color& col, int index);
    void drawpalettetabs(int x, int y, int w, const char* szString, int& itab, int index, int max);
    bool MoveMenu(int & x, int & y, int w, int h, int index);
    void addplayerlistbutton(int x, int y, int w, int h, int index, int& playercount, const char* szString, IFlags getFlag = IFlags::IFLAG_DEFAULT);
    void drawmenu();
    ViVecMouse GetMouse();
    void drawmouse();
    bool inArea(int x, int y, int w, int h);
    bool inArea2(int x, int y, int xx, int yy);
    // Edit
    void DrawBasicString(int x, int y, Color color, HFONT font, string szString);
    void FilledRectangle(Vector2D start_pos, Vector2D end_pos, Color col);
    void Line(Vector2D start_pos, Vector2D end_pos, Color col);
    void DrawTabs(int x, int y, const char* szString, int& itab, int index, int max);
    void Checkbox(int x, int y, const char* szValue, bool* var);
    void Slider(int x, int y, int w, const char* szString, int& value, int max, int min);
    void Slider(int x, int y, int w, const char* szString, float& value, int max, int min);
    void GradientH(int x, int y, int width, int height, Color color1, Color color2);
    void RenderComboBox(int x, int y, int w, int h, const char* szString, vector<string> szValue, int& currValue, bool* bOpend);
    // Menu
    void RectOutlined(int x, int y, int w, int h, int thickness, Color color, Color outlined);
    void BorderBox(int x, int y, int w, int h, int thickness, Color color);
    void DrawBasicString(int x, int y, Color color, HFONT font, string szString, bool textsize);
    void GardientRect(int x, int y, int w, int h, Color color1, Color color2, int variation);
    int TweakColor(int c1, int c2, int variation);
    void drawgradientw(int x, int y, int w, int h, Color col1, Color col2);
    void renderConfigs(int x, int y);

    
public:
    std::size_t m_nCurrentPos[100]; /* Credit's to reactiioN @ uc. */
    std::string m_szCurrentString[100];
    
    std::string m_szChangedValue[100];
    
    bool IsKeyPressed(int eventCode, ButtonCode_t keyCode)
    {
        return (eventCode == keyCode) ? true : false;
    }
};

void setupConfig();

extern cdrawings* draw;
extern cwindow* window;


template<class T>
const T& clamp(const T& x, const T& upper, const T& lower) {
    return min(upper, max(x, lower));
}



