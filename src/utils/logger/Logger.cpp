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
#include <string_view>

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
        LOG_ERROR("Failed to create log file [" << fileName << "]");
        return;
    }
    for(auto t: acceptionTypes)
    {
        output->Set(t, true);
    }
    _outputs.push_back(std::move(output));
}

void Logger::Write(LogType type, const char* text, std::source_location loc)
{
    std::ostringstream message;
    message<<"[" 
        <<GetTimeString()<<"]"<<GetTypeString(type)<<"["
        <<GetShortFileName(loc)
        <<':'<<loc.line()
        <<' '<<GetShortFunctionName(loc)<<"()"
        <<"]" <<'\t'<<text;

    std::string message_str = message.str();
    for(auto& o: _outputs)
    {
        if(o->Accepts(type))
        {
            o->Write(message_str);
        }
    }
}

std::string_view Logger::GetShortFileName(std::source_location loc)
{
    std::string_view view = loc.file_name();
    if( auto p = view.find_last_of('/'); p != view.npos)
    {
        return view.substr(p + 1);
    }
    return view;
}

std::string_view Logger::GetShortFunctionName(std::source_location loc)
{
    std::string_view view = loc.function_name();
    
    auto fin_pos = view.find_first_of('(');
    if(fin_pos != view.npos)
    {
        view.remove_suffix(view.size() - fin_pos);
    }
    
    auto start_pos = view.find_last_of(" *&");
    if(start_pos != view.npos)
    {
        view.remove_prefix(start_pos + 1);
    }
    
    return view;
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
