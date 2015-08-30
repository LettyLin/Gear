#include "Formater.h"
#include "GameUtile.h"

std::string Formater::getString(const std::string &text){
    std::string result;
    result = text.substr(1, text.length() - 2);

    return result;
}

std::string Formater::getString(const std::wstring &text){
    std::string result;
    std::string _text;
    GameUtile::WStringToString(text, _text);

    result = getString(_text);

    return result;
}

int Formater::getInt(const std::string &text){
    int result;
    result = atoi(text.c_str());

    return result;
}

int Formater::getInt(const std::wstring &text){
    int result;
    std::string _text;
    GameUtile::WStringToString(text, _text);

    result = getInt(_text);

    return result;
}

bool Formater::getBool(const std::string &text){
    bool result;
    result = (text == "true" || text == "True") ? true : false;

    return result;
}

Point Formater::getPoint(const std::string &text){
    Point result;
    int sign = text.find(",");

    result.x = atof(text.substr(1, sign - 1).c_str());
    result.y = atof(text.substr(sign + 1, text.length() - 2).c_str());

    return result;
}

std::string Formater::StringToString(const std::string &content){
    std::string result;
    result = String::createWithFormat("\"%s\"", content)->getCString();

    return result;
}

std::string Formater::IntToString(const int content){
    std::string result;
    result = String::createWithFormat("%d", content)->getCString();

    return result;
}

std::string Formater::BoolToString(const bool content){
    std::string result;
    result = content ? "true" : "false";

    return result;
}

std::string Formater::PointToString(const Point content){
    std::string result;
    result = String::createWithFormat("(%f,%f)", content.x, content.y)->getCString();

    return result;
}