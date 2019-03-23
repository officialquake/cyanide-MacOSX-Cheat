/* Credits to : wÊs aka  aKalisch */


struct MemoryModule
{
    off_t       length;
    uint64_t    address;
    char*       path;
    std::string fullpath;
    Byte*       buffer = nullptr;
};

struct MatchPathSeparator
{
    bool operator()( char ch ) const
    {
        return ch == '\\' || ch == '/';
    }
};

class CPatternScanner {
public:
    static CPatternScanner* Instance() {
        if(!instance) {
            instance = new CPatternScanner();
        }
        
        return instance;
    }
    CPatternScanner();
    std::string Basename(std::string const& pathname);
    bool Compare(const unsigned char* pData, const unsigned char* bMask, const char* szMask);
    uintptr_t FindPattern(uintptr_t dwAddress, off_t dwLen, unsigned char* bMask, const char* szMask, uintptr_t offset = 0x0);
    uintptr_t GetPointer(std::string imageName, unsigned char* bMask, const char* szMask, uint32_t start);
    uintptr_t GetProcedure(std::string imageName, unsigned char* bMask, const char* szMask, uintptr_t offset = 0x0);
    std::string GetModulePath(std::string imageName);
    uintptr_t GetBaseAddress(std::string imageName);
private:
    void LoadModules();
    std::map<std::string, MemoryModule> loaded_modules;
    static CPatternScanner* instance;
};
