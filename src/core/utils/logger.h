#pragma once

#include <string>
#include <fstream>
#include <mutex>
#include <filesystem>

namespace utils {

enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

class Logger {
public:
    static Logger& getInstance();
    
    void init(const std::string& logFile = "tonet.log", LogLevel minLevel = LogLevel::INFO);
    
    // Log messages with different severity levels
    template<typename... Args>
    void debug(const std::string& file, int line, const std::string& message);
    
    template<typename... Args>
    void info(const std::string& file, int line, const std::string& message);
    
    template<typename... Args>
    void warning(const std::string& file, int line, const std::string& message);
    
    template<typename... Args>
    void error(const std::string& file, int line, const std::string& message);
    
    template<typename... Args>
    void critical(const std::string& file, int line, const std::string& message);
    
    void setLogLevel(LogLevel level);

private:
    Logger() = default;
    
    void log(LogLevel level, const std::string& file, int line, const std::string& message);
    std::string levelToString(LogLevel level);
    std::string getTimestamp();
    std::string getFileName(const std::string& filepath);
    
    std::ofstream logFile_;
    LogLevel minLevel_ = LogLevel::INFO;
    std::mutex mutex_;
};

template<typename... Args>
void Logger::debug(const std::string& file, int line, const std::string& message) {
    log(LogLevel::DEBUG, file, line, message);
}

template<typename... Args>
void Logger::info(const std::string& file, int line, const std::string& message) {
    log(LogLevel::INFO, file, line, message);
}

template<typename... Args>
void Logger::warning(const std::string& file, int line, const std::string& message) {
    log(LogLevel::WARNING, file, line, message);
}

template<typename... Args>
void Logger::error(const std::string& file, int line, const std::string& message) {
    log(LogLevel::ERROR, file, line, message);
}

template<typename... Args>
void Logger::critical(const std::string& file, int line, const std::string& message) {
    log(LogLevel::CRITICAL, file, line, message);
}

// Convenience macros for logging
#define LOG_DEBUG(msg)    Logger::getInstance().debug(__FILE__, __LINE__, msg)
#define LOG_INFO(msg)     Logger::getInstance().info(__FILE__, __LINE__, msg)
#define LOG_WARNING(msg)  Logger::getInstance().warning(__FILE__, __LINE__, msg)
#define LOG_ERROR(msg)    Logger::getInstance().error(__FILE__, __LINE__, msg)
#define LOG_CRITICAL(msg) Logger::getInstance().critical(__FILE__, __LINE__, msg)

} // namespace utils