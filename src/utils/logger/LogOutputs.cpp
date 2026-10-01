//
//  LogOutputs.cpp
//  EPet
//
//  Created by marina porkhunova on 01.10.2026.
//

#include "LogOutputs.hpp"

#include <iostream>
#include <cerrno>
#include <system_error>

#include "GetPath.hpp"

void ILogOutput::Set(LogType type, bool isWriting)
{    
    _types[static_cast<size_t>(type)] = isWriting;
}

bool ILogOutput::Accepts(LogType type) const
{
    return _types[static_cast<size_t>(type)];
}

void ConsoleOutput::Write(const std::string& line)
{
    std::cout<<line<<std::endl;
}

FileOutput::FileOutput(const std::string& fileName, const std::string& prevFileName)
{
    auto path = GetSavePath() / fileName;
    auto prevPath = GetSavePath() / prevFileName;

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
}

void FileOutput::Write(const std::string& line)
{
    _file<<line<<std::endl;
}

FileOutput::~FileOutput()
{
    if (_file.is_open())
    {
        _file.close();
    }
}
