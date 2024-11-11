/*
 * Filename: console.h
 * Path: tonet/src/cli
 * Created Date: Monday 11th November, 2024, 4:03:21 pm
 * Author: Yasu Fadhili
 * 
 * Copyright (c) 2024 Yasu Fadhili
 */


#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <functional>


namespace cli
{
  class Console
  {
  private:
    // ANSI colour codes
    const std::string RESET = "\033[0m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string ORANGE = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string CYAN = "\033[36m";
    std::map<std::string, std::function<void(std::vector<std::string>&)>> commands;
  public:
    void registerCommands();
    void displayStartUpText();
    void startConsole();
    void handleCommand(const std::string& command);
    std::vector<std::string> parseCommand(const std::string& command);
    void handleStartCommand(const std::vector<std::string>& args);
    void handleStopCommand(const std::vector<std::string>& args);
    void handleHelpCommand(const std::vector<std::string>& args);
    void handleShareCommand(const std::vector<std::string>& args);
    void handleCopyCommand(const std::vector<std::string>& args);
    Console(/* args */);
    ~Console();
  };

} // namespace cli
