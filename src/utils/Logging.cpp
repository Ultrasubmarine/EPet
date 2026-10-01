//
//  Logging.cpp
//  EPet
//
//  Created by marina porkhunova on 01.10.2026.
//

#include "Logging.hpp"

#include <cerrno>
#include <system_error>
#include <chrono>
#include <ctime>
#include <iomanip>

#include "GetPath.hpp"

Logger::Logger()
{
    CreateTerminalOutput();
}

Logger::~Logger()
{
    if (_file.is_open())
    {
        _file.close();
    }
}

void Logger::Initialize()
{
    if(_initialize) {
        return;
    }

   // CreateTerminalOutput();
    CreateFileOutput();

    _initialize = true;
}

void Logger::CreateTerminalOutput()
{
    _outputs.push_back(&std::cout);
}

void Logger::CreateFileOutput()
{
    auto path = GetSavePath() / _fileName;
    auto prevPath = GetSavePath() / _prevFileName;

    if (fs::exists(path)) {
        std::error_code error;
      fs::rename(path, prevPath, error);
      if (error) {
          LOG_ERROR("couldn't rename old log: " << error.message());
      }
    }

    _file.open(path, std::ios::out | std::ios::trunc);
    if (!_file.is_open()) {
        LOG_ERROR("couldn't open file. error: " <<std::system_category().message(errno)<<" path: "<<path);
        return;
    }

    _outputs.push_back(&_file);
}

void Logger::Write(LogType type, const char* file, int line, const char* func, const char* text)
{
    std::ostringstream message;
    message<<"[" <<GetTimeString()<<"]"<<GetTypeString(type)<<"["<<file<<':'<<line<<' '<<func<<"]" <<'\t'<<text;

    std::string message_str = message.str();
    for(auto& o: _outputs)
    {
        *o<< message_str <<std::endl;
    }
}

const char* Logger::GetTypeString(LogType type)
{
    switch (type)
    {
        case LogType::Message: return "[LOG]    ";
        case LogType::Warning: return "[WARNING]";
        case LogType::Error:   return "[ERROR]  ";
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
