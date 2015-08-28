#include "Formater.h"

std::string Formater::getString(const std::string &text){
    std::string result;
    result = text.substr(1, text.length() - 2);

    return result;
}

int Formater::getInt(const std::string &text){
    int result;
    result = atoi(text.c_str());

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

std::string StringToString(const std::string &content){
    std::string result;
    result = String::createWithFormat("\"%s\"", content)->getCString();

    return result;
}

std::string IntToString(const int content){
    std::string result;
    result = String::createWithFormat("%d", content)->getCString();

    return result;
}

std::string BoolToString(const bool content){
    std::string result;
    result = content ? "true" : "false";

    return result;
}

std::string PointToString(const Point content){
    std::string result;
    result = String::createWithFormat("(%f,%f)", content.x, content.y)->getCString();

    return result;
}