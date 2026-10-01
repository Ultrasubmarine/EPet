//
//  LogOutputs.hpp
//  EPet
//
//  Created by marina porkhunova on 01.10.2026.
//

#ifndef LogOutputs_hpp
#define LogOutputs_hpp

#include <string>
#include <fstream>
#include <array>

#include "Logger.hpp"

class ILogOutput
{
public:
    ILogOutput()= default;
    virtual ~ILogOutput() = default;

    void Set(LogType type, bool isWriting);
    bool Accepts(LogType type) const;
    virtual void Write(const std::string& line) = 0; /// must not use LOG_* inside

protected:
    std::array<bool, static_cast<size_t>(LogType::Count)> _types{false};
};


class ConsoleOutput : public ILogOutput
{
public:
    virtual void Write(const std::string& line) override;
};


class FileOutput : public ILogOutput
{
public:
    FileOutput(const std::string& fileName, const std::string& prevFileName);
    ~FileOutput();
    
    bool IsOpen() const { return _file.is_open(); }

    virtual void Write(const std::string& line) override;

private:
    std::ofstream _file;
};

#endif /* LogOutputs_hpp */
