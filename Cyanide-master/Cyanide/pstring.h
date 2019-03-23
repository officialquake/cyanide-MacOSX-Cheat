#include <string>
#include <sstream>

using namespace std;

class pstring : public string
{
public:
    pstring(): string() {}
    
    template<typename T>
    pstring(const T v): string(v) {}
    
    template<typename T>
    pstring& operator<<(const T s)
    {
        stringstream stream;
        stream << *this;
        stream << s;
        *this = stream.str();
        return *this;
    }
    
    pstring& operator+(const unsigned int i)
    {
        stringstream stream;
        stream << *this;
        stream << i;
        *this = stream.str();
        return *this;
    }
};
