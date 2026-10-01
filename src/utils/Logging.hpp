//
//  logging.hpp
//  EPet
//
//  Created by marina porkhunova on 03.01.2025.
//

#ifndef Logging_hpp
#define Logging_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Singleton.hpp"

#define LOG_WRITE(type, text)                                               \
    do {                                                                    \
        std::ostringstream logStream_;                                      \
        logStream_ << text;                                                 \
        Logger::Instance().Write(type, __FILE_NAME__, __LINE__, __func__, logStream_.str().c_str()); \
    } while (0)

#define LOG_MESSAGE(text) LOG_WRITE(LogType::Message, text)
#define LOG_WARNING(text) LOG_WRITE(LogType::Warning, text)
#define LOG_ERROR(text)   LOG_WRITE(LogType::Error, text)

enum class LogType
{
    Message,
    Warning,
    Error
};

class Logger: public Singleton<Logger>
{
    Logger();
    ~Logger();

    void CreateTerminalOutput();
    void CreateFileOutput();

    static const char* GetTypeString(LogType type);
    /// local time, "HH:MM:SS.mmm"
    static std::string GetTimeString();
    
public:
    void Initialize();
    void Write(LogType type, const char* file, int line, const char* func, const char* text);

private:

    bool _initialize = false;
    std::vector<std::ostream*> _outputs;
    std::ofstream _file;

    const std::string _fileName = "last_session.log";
    const std::string _prevFileName = "prev_session.log";

    friend class Singleton<Logger>;
};

#endif /* logging_hpp */
