#ifndef LOGGER_H_
#define LOGGER_H_
#include<string>
#include "nlohmann/json.hpp"

class Logger{
    public:
        void LogOrder(const std::string& jsonResponse);
        void LogEdit(const std::string& jsonResponse);
        void LogCancel(const std::string& jsonResponse);
        void LogOrderbook(const std::string& jsonResponse);
        void LogCurrentPositions(const std::string& jsonResponse);
};
#endif  //LOGGER_H_
