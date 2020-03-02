#include "StringParser.h"
#include <sstream>
#include <iterator>
#include <cstring>
#include <algorithm>
#include "varTemplate.h"

static const std::map<std::string, int> Ones  = {{"zero", 0},{"one",1},{"two",2}, {"three",3}, {"four",4}, {"five",5}, {"six",6}, {"seven",7}, {"eight",8}, {"nine",9}};
static const std::map<std::string, int> Teens = {{"ten",10}, {"eleven",11}, {"twelve",12}, {"thirteen",13}, {"fourteen",14}, {"fifteen",15}, {"sixteen",16}, {"seventeen",17}, {"eighteen",18}, {"nineteen",19}};
static const std::map<std::string, int> Tens  = {{"twenty",20}, {"thirty",30}, {"forty",40}, {"fifty",50}, {"sixty",60}, {"seventy",70}, {"eighty",80}, {"ninety",90}};
static const std::map<std::string, int> Hundreds = {{"hundred",100}, {"thousand",1000}, {"million",1000000}};
static const std::string connectorAnd = "and";

const std::vector<std::string> allWordNumbersCombinations = {"zero", "one", "two","three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", 
                                                             "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen", "twenty", "thirty", "forty", "fifty", "sixty", 
                                                             "seventy", "eighty", "ninety","hundred", "thousand", "million"};


const std::map<std::string, int> *getMapPtr(wordType w)
{
    const std::map<std::string, int> *pMap = nullptr;
    switch (w)
    {
    case wordType::ONE:
        pMap = &Ones;
        break;
    case wordType::TEEN:
        pMap = &Teens;
        break;
    case wordType::TEN:
        pMap = &Tens;
        break;
    case wordType::HUNDRED:
        pMap = &Hundreds;
        break;
    default:
        pMap = nullptr;
        break;
    }
}

StringParser::StringParser(std::string str) : str_{str} 
{
   std::istringstream ss{str_};
   using StrIt = std::istream_iterator<std::string>;
   std::vector<std::string> v_str{StrIt{ss}, StrIt{}};
   for(auto &item : v_str)
   {
       std::string::size_type n;
       if((n= item.find("-")) != std::string::npos)
       {
           std::string tmp = item.substr(0, n);
           if(isANumber(tmp)) v_str_.push_back(tmp);
           
           tmp = item.substr(n+1, (item.size()- n));
           if(isANumber(tmp)) v_str_.push_back(tmp);
       }else
       {
           v_str_.push_back(item);
       }
       
   }
}

bool StringParser::hasANumber()
{
    bool isThereANumber = false;
    const char* subStr = NULL;
    std::string strLower = convertToLowerCase(str_);

    for(const std::string &word_number : allWordNumbersCombinations)
    {
        if( (subStr = std::strstr(strLower.c_str(), word_number.c_str())) != NULL)
        {
            isThereANumber = true;
            break;
        }
    }
    //TODO : Add a control to check if there are just "hundreds/thousands/millions" and no other numbers.
    return isThereANumber;
}

std::string StringParser::getStringWithNumbers()
{
    if(hasANumber())
    {
        //numbers in words can start by Ones, Teens or Tens but no Hundreds. So we position ourselves in the first "Number"
        auto it = v_str_.begin();
        auto firstPosition = it;
        auto lastPosition = it;
        std::vector<std::pair<std::vector<std::string>::iterator, wordType>> v_pWordAndWordType{};
        for(it; it < v_str_.end(); it++)
        {   
            bool numberis = isANumber(*it);
            if(isANumber(*it)) break;
        }
        
        if(it != v_str_.end())
        {
            firstPosition = it;
            
            bool connector = false;
            for(it = firstPosition; it < v_str_.end(); it++)
            {
                if(!isANumber(*it) && !isAHundred(*it) && !isAConnector(*it)) break;
                
                if(currentStringType_ != wordType::CONNECTOR) v_pWordAndWordType.push_back({it, currentStringType_});
                lastPosition = it;
            }
        }
        if(isAConnector(*lastPosition)) lastPosition = --lastPosition; //we go back one because that connector could mean other thing in the sentence
        std::vector<uint> numbers{}; //numbers once calculated will be pushed here. As there can be multiple numbers one after another this is a vector.
        uint numberToPush = 0;
        var<uint> numberAfterHundred{0};
        wordType prevWordType = wordType::NONE;

        auto prevPWordAndType = v_pWordAndWordType[0];
        for(auto pwordAndType : v_pWordAndWordType)
        {
            auto *pMap = getMapPtr(pwordAndType.second);
            std::string wordNumberInLowerCase = convertToLowerCase(*pwordAndType.first);
            if(prevWordType == wordType::NONE)
            {
                if(pMap != nullptr) numberToPush = (*pMap).at(convertToLowerCase(*pwordAndType.first));
            }else
            {
                if(prevWordType == wordType::ONE || prevWordType == wordType::TEEN)
                {
                    if(pwordAndType.second == wordType::ONE || pwordAndType.second == wordType::TEEN || pwordAndType.second == wordType::TEN)
                    {
                        if(numberAfterHundred.isSet())
                        {
                            numberToPush += numberAfterHundred.value();
                            numberAfterHundred.reset();
                        }
                        numbers.push_back(numberToPush);
                        numberToPush = (*pMap).at(convertToLowerCase(*pwordAndType.first));
                    }else //it is a hundred for sure
                    {
                        if(numberAfterHundred.isSet())
                        {
                            numberAfterHundred *= (*pMap).at(convertToLowerCase(*pwordAndType.first)); 
                            numberToPush += numberAfterHundred.value();
                            numberAfterHundred.reset();
                        }else
                        {                      
                            numberToPush *= (*pMap).at(convertToLowerCase(*pwordAndType.first));
                        }
                    }
                }else if(prevWordType == wordType::TEN)
                {
                    if(pwordAndType.second == wordType::ONE)
                    {
                        numberToPush += (*pMap).at(convertToLowerCase(*pwordAndType.first));
                    }else if(pwordAndType.second == wordType::HUNDRED)
                    {
                        if(numberAfterHundred.isSet())
                        {
                            numberAfterHundred *= (*pMap).at(convertToLowerCase(*pwordAndType.first)); 
                            numberToPush += numberAfterHundred.value();
                            numberAfterHundred.reset();
                        }else
                        {
                            numberToPush *= (*pMap).at(convertToLowerCase(*pwordAndType.first));
                        }
                    }else
                    {
                        numbers.push_back(numberToPush);
                        numberToPush = (*pMap).at(convertToLowerCase(*pwordAndType.first));
                    }
                }else //HUNDREDS
                {
                    if(pwordAndType.second == wordType::ONE || pwordAndType.second == wordType::TEEN || pwordAndType.second == wordType::TEN)
                    {
                        numberAfterHundred = (*pMap).at(convertToLowerCase(*pwordAndType.first));
                    }else
                    {
                        if(convertToLowerCase(*prevPWordAndType.first) == convertToLowerCase(*pwordAndType.first))
                        {
                            //we add the value to the number to push reset the numberAfterHundred and stop the execution due than concadenating hundreds can
                            //produce errors so we consider the rest of the number invalid
                            numberToPush += numberAfterHundred.value();
                            numberAfterHundred.reset();
                            
                            lastPosition = prevPWordAndType.first;
                            break;
                        }else
                        {
                            if(numberAfterHundred.isSet())
                            {
                                numberAfterHundred *= (*pMap).at(convertToLowerCase(*pwordAndType.first));
                            }else
                            {
                                numberToPush *= (*pMap).at(convertToLowerCase(*pwordAndType.first));
                            }
                        }
                        
                    }
                    
                }
                prevPWordAndType = pwordAndType;
            }
            
            prevWordType = pwordAndType.second; 
        }
        if(numberAfterHundred.isSet())
        {
            numberToPush += numberAfterHundred.value();
            numberAfterHundred.reset();
        }
        numbers.push_back(numberToPush);        

        str_.clear();
        for(auto itr = begin(v_str_); itr < end(v_str_) ; itr++)
        {
            if(itr == firstPosition)
            {
                
                for(auto num : numbers)
                {
                    str_ += std::to_string(num) + " ";
                }
                itr = ++lastPosition;
            }
            if(itr != end(v_str_)) str_ += *itr + " ";
        }
        str_.pop_back(); //delete last space
    }
    return str_;
}

std::string StringParser::convertToLowerCase(const std::string &s)
{
    std::string lowerCaseStr{};
    std::transform(s.begin(), s.end(), std::back_inserter(lowerCaseStr),
                   [](unsigned char c) -> unsigned char { return std::tolower(c); });
    
    return lowerCaseStr;
}

bool StringParser::isA(const std::string &s, const std::map<std::string, int> &map, wordType type)
{
    std::string lowercaseStr = StringParser::convertToLowerCase(s);
    bool isAKey = map.end() != map.find(lowercaseStr);
    if(isAKey)
    {
        currentStringType_ = type;
    }
    return isAKey;
}

bool StringParser::isAOne(const std::string &s)
{
    return isA(s, Ones, wordType::ONE);
}

bool StringParser::isATeen(const std::string &s)
{
    return isA(s, Teens, wordType::TEEN);
}

bool StringParser::isATen(const std::string &s)
{
    return isA(s, Tens, wordType::TEN);
}

bool StringParser::isAHundred(const std::string &s)
{
    currentStringType_ = wordType::NONE;
    return isA(s, Hundreds, wordType::HUNDRED);
}

bool StringParser::isAConnector(const std::string &s)
{
    bool isConnector = false;
    currentStringType_ = wordType::NONE;
    if((isConnector = (s == connectorAnd || s =="-")) == true)
    {
        currentStringType_ = wordType::CONNECTOR;
    }
    return isConnector;
}

bool StringParser::isANumber(const std::string& s)
{
    currentStringType_ = wordType::NONE;
    return (isAOne(s) || isATeen(s) || isATen(s));
}
