#include <vector>
#include <string>
#include <map>

enum class wordType
{
    ONE,
    TEEN,
    TEN,
    HUNDRED,
    CONNECTOR,
    NONE
};

class StringParser
{
public:
    StringParser(std::string str);
    //returns wether the string parsed have a number or not (it can have multiple numbers but this function will return true the first time it founds a number)
    bool hasANumber(); 
    std::string getStringWithNumbers();
    static std::string convertToLowerCase(const std::string &s);
private:
    bool isA(const std::string &s, const std::map<std::string, int> &map, wordType type = wordType::NONE);
    bool isANumber(const std::string& s);
    bool isAOne(const std::string &s);
    bool isATeen(const std::string &s);
    bool isATen(const std::string &s);
    bool isAHundred(const std::string &s);
    bool isAConnector(const std::string &s);

private:
    std::string str_;
    std::vector<std::string> v_str_{};
    wordType currentStringType_{wordType::NONE};
};