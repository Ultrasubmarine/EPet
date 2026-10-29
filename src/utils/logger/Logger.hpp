//
//  Logger.hpp
//  EPet
//
//  Created by marina porkhunova on 03.01.2025.
//

#ifndef Logger_hpp
#define Logger_hpp

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <source_location>

#include "Singleton.hpp"


#define LOG_WRITE(type, text, ...)                                          \
    do {                                                                    \
        std::ostringstream logStream_;                                      \
        logStream_ << text;                                                 \
        Logger::Instance().Write(type, logStream_.str().c_str() __VA_OPT__(,) __VA_ARGS__); \
    } while (0)

#define LOG_MESSAGE(text) LOG_WRITE(LogType::Message, text)
#define LOG_WARNING(text) LOG_WRITE(LogType::Warning, text)
#define LOG_ERROR(text)   LOG_WRITE(LogType::Error, text)

// Bests logs for templates. To checking reall code position.
#define LOG_MESSAGE_AT(loc, text) LOG_WRITE(LogType::Message, text, loc)
#define LOG_WARNING_AT(loc, text) LOG_WRITE(LogType::Warning, text, loc)
#define LOG_ERROR_AT(loc, text)   LOG_WRITE(LogType::Error, text, loc)

enum class LogType
{
    Message = 0,
    Warning = 1,
    Error = 2,
    Count
};

class ILogOutput;

class Logger: public Singleton<Logger>
{
    Logger();
    ~Logger();

    void CreateTerminalOutput(const std::vector<LogType>& acceptionTypes);
    void CreateFileOutput(const std::vector<LogType>& acceptionTypes, const std::string& fileName, const std::string& prevFileName);

    static const char* GetTypeString(LogType type);
    /// local time, "HH:MM:SS.mmm"
    static std::string GetTimeString();
    
public:
    void Init();
    void Write(LogType type, const char* text, std::source_location loc = std::source_location::current());

    static std::string_view GetShortFileName(std::source_location loc);
    static std::string_view GetShortFunctionName(std::source_location loc);
    
private:
    bool _initialize = false;
    std::vector<std::unique_ptr<ILogOutput>> _outputs;

    friend class Singleton<Logger>;
};

#endif /* Logger_hpp */
