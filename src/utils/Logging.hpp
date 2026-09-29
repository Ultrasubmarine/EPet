//
//  logging.hpp
//  EPet
//
//  Created by marina porkhunova on 03.01.2025.
//

#ifndef utils_hpp
#define utils_hpp

#include <stdio.h>
#include <iostream>
#include <cerrno>
#include <system_error>
#include <fstream>
#include <sstream>

#include <chrono>
#include <ctime>
#include <iomanip>

#include "Singleton.hpp"
#include "GetPath.hpp"

#define LOG_WRITE(type, text)                                               \
    do {                                                                    \
        std::ostringstream logStream_;                                      \
        logStream_ << text;                                                 \
        Logger::Instance().Write(type, __func__, logStream_.str().c_str()); \
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
public:
    Logger()
    {
        CreateTerminalOutput();
        CreateFileOutput();
    }
    
    ~Logger()
    {
        if (_file.is_open())
        {
            _file.close();
        }
    }
 
private:
    void CreateTerminalOutput()
    {
        _outputs.push_back(&std::cout);
    }
    
    void CreateFileOutput()
    {
        auto path = GetSavePath() / _fileName;
        auto prevPath = GetSavePath() / _prevFileName;
        
        if (fs::exists(path)) {
            std::error_code error;
          fs::rename(path, prevPath, error);
          if (error) {
              std::cout << "[ERROR] can't rename old log: " << error.message() << std::endl;
          }
        }
        
        _file.open(path, std::ios::out | std::ios::trunc);
        if (!_file.is_open()) {
            std::cout << "couldn't open file. error: " <<std::system_category().message(errno)<<"\n path:"<<path;
            return;
        }
        
        _outputs.push_back(&_file);
    }

public:
    void Write(LogType type, const char* func, const char* text)
    {
        std::ostringstream message;
        message<<"[" <<GetTimeString()<<"]"<<GetTypeString(type)<<"["<<func<<"]" <<'\t'<<text;
        
        std::string message_str = message.str();
        for(auto& o: _outputs)
        {
            *o<< message_str <<std::endl;
        }
    }

private:
    static const char* GetTypeString(LogType type)
    {
        switch (type)
        {
            case LogType::Message: return "[LOG]    ";
            case LogType::Warning: return "[WARNING]";
            case LogType::Error:   return "[ERROR]  ";
        }
        return "[?]      ";
    }

    /// local time, "HH:MM:SS.mmm"
    static std::string GetTimeString()
    {
        const auto now = std::chrono::system_clock::now();
        const std::time_t t = std::chrono::system_clock::to_time_t(now);

        std::tm local{};
        localtime_r(&t, &local);

        const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000;

        std::ostringstream result;
        result << std::put_time(&local, "%H:%M:%S") << '.' << std::setfill('0') << std::setw(3) << ms;
        return result.str();
    }

    std::vector<std::ostream*> _outputs;
    std::ofstream _file;
    
    
    const std::string _fileName = "last_session.log";
    const std::string _prevFileName = "prev_session.log";
};

#endif /* logging_hpp */
