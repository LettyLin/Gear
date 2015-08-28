#ifndef _H_FORMATER_
#define _H_FORMATER_

#include <cocos2d.h>
USING_NS_CC;

class Formater{
public:
    static std::string getString(const std::string &text);
    static int getInt(const std::string &text);
    static bool getBool(const std::string &text);
    static Point getPoint(const std::string &text);

    static std::string StringToString(const std::string &content);
    static std::string IntToString(const int content);
    static std::string BoolToString(const bool content);
    static std::string PointToString(const Point content);
};

#endif