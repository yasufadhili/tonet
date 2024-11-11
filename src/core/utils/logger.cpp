#include "logger.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <iostream>

namespace utils {

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::init(const std::string& logFilePath, LogLevel minLevel) {
    std::lock_guard<std::mutex> lock(mutex_);
    logFile_.open(logFilePath, std::ios::app);
    minLevel_ = minLevel;
    
    if (!logFile_.is_open()) {
        throw std::runtime_error("Failed to open log file: " + logFilePath);
    }
    
    info(__FILE__, __LINE__, "Logger initialized");
}

void Logger::log(LogLevel level, const std::string& file, int line, const std::string& message) {
    if (level < minLevel_) return;
    
    std::lock_guard<std::mutex> lock(mutex_);
    
    // Format: [TIMESTAMP] [LEVEL] [FILE:LINE] Message
    std::stringstream logMessage;
    logMessage << "[" << getTimestamp() << "] "
               << "[" << levelToString(level) << "] "
               << "[" << getFileName(file) << ":" << line << "] "
               << message << std::endl;
    
    // Write to file
    logFile_ << logMessage.str();
    logFile_.flush();
    
    // Also print to console for ERROR and CRITICAL
    if (level >= LogLevel::ERROR) {
        std::cerr << logMessage.str();
    }
}

void Logger::setLogLevel(LogLevel level) {
    std::lock_guard<std::mutex> lock(mutex_);
    minLevel_ = level;
    info(__FILE__, __LINE__, "Log level changed to: " + levelToString(level));
}

std::string Logger::levelToString(LogLevel level) {
    switch (level) {
        case LogLevel::DEBUG:    return "DEBUG";
        case LogLevel::INFO:     return "INFO";
        case LogLevel::WARNING:  return "WARNING";
        case LogLevel::ERROR:    return "ERROR";
        case LogLevel::CRITICAL: return "CRITICAL";
        default:                 return "UNKNOWN";
    }
}

std::string Logger::getTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S")
       << '.' << std::setfill('0') << std::setw(3) << ms.count();
    return ss.str();
}

std::string Logger::getFileName(const std::string& filepath) {
    return std::filesystem::path(filepath).filename().string();
}

} // namespace utils