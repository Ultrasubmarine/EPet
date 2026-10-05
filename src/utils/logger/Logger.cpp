//
//  Logger.cpp
//  EPet
//
//  Created by marina porkhunova on 01.10.2026.
//

#include "Logger.hpp"

#include <cerrno>
#include <system_error>
#include <chrono>
#include <ctime>
#include <iomanip>

#include "GetPath.hpp"
#include "LogOutputs.hpp"

Logger::Logger()
{
    CreateTerminalOutput({LogType::Error,LogType::Warning});
    //CreateTerminalOutput({LogType::Error, LogType::Warning, LogType::Message});
}

Logger::~Logger() = default;

void Logger::Init()
{
    if(_initialize) {
        return;
    }

    CreateFileOutput({LogType::Error, LogType::Warning, LogType::Message}, "last_session.log", "prev_session.log");
    CreateFileOutput({LogType::Error}, "errors.log", "errors_prev_session.log");
    _initialize = true;
}

void Logger::CreateTerminalOutput(const std::vector<LogType>& acceptionTypes)
{
    auto output = std::make_unique<ConsoleOutput>();
    for(auto t: acceptionTypes)
    {
        output->Set(t, true);
    }
    _outputs.push_back(std::move(output));
    
}

void Logger::CreateFileOutput(const std::vector<LogType>& acceptionTypes, const std::string& fileName, const std::string& prevFileName)
{
    auto output = std::make_unique<FileOutput>(fileName, prevFileName);
    if(!output->IsOpen())
    {
        LOG_ERROR("couldn't create logging file ["<<fileName<<"]");
        return;
    }
    for(auto t: acceptionTypes)
    {
        output->Set(t, true);
    }
    _outputs.push_back(std::move(output));
}

void Logger::Write(LogType type, const char* file, int line, const char* func, const char* text)
{
    std::ostringstream message;
    message<<"[" <<GetTimeString()<<"]"<<GetTypeString(type)<<"["<<file<<':'<<line<<' '<<func<<"]" <<'\t'<<text;

    std::string message_str = message.str();
    for(auto& o: _outputs)
    {
        if(o->Accepts(type))
        {
            o->Write(message_str);
        }
    }
}

const char* Logger::GetTypeString(LogType type)
{
    switch (type)
    {
        case LogType::Message: return "[LOG]    ";
        case LogType::Warning: return "[WARNING]";
        case LogType::Error:   return "[ERROR]  ";
        case LogType::Count:   break;
    }
    return "[?]      ";
}

std::string Logger::GetTimeString()
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
