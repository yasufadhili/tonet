#include "console.h"


void cli::Console::displayStartUpText(){
  std::cout << CYAN << R"(
    ╔═════════════════════════════════════════════════════════════╗
    ║                                                             ║
    ║        ████████╗  ██████╗  ███╗   ██╗ ███████╗ ████████╗    ║
    ║        ╚══██╔══╝ ██╔═══██╗ ████╗  ██║ ██╔════╝ ╚══██╔══╝    ║
    ║           ██║    ██║   ██║ ██╔██╗ ██║ █████╗      ██║       ║
    ║           ██║    ██║   ██║ ██║╚██╗██║ ██╔══╝      ██║       ║
    ║           ██║    ╚██████╔╝ ██║ ╚████║ ███████╗    ██║       ║
    ║           ╚═╝     ╚═════╝  ╚═╝  ╚═══╝ ╚══════╝    ╚═╝       ║
    ║                                                             ║
    ║        Version : 1.0.0                                      ║
    ║        Author: Yasu Fadhili                                 ║
    ║        Email: fadhili@gmail.com                             ║
    ║        Website: yasufadhili.github.io                       ║
    ║                                                             ║
    ╚═════════════════════════════════════════════════════════════╝
  )"<< RESET;
  std::cout<< " " <<std::endl;
}

void cli::Console::handleStartCommand(const std::vector<std::string>& args){
  std::cout << "Start command" << std::endl;
  for(auto arg : args)
  {
    std::cout << arg << std::endl;
  }
}

void cli::Console::handleStopCommand(const std::vector<std::string>& args){
  std::cout << "Stop command" << std::endl;
  for(auto arg : args)
  {
    std::cout << arg << std::endl;
  }
}

void cli::Console::handleHelpCommand(const std::vector<std::string>& args) {
  std::cout << "Available commands: \n";
  for (const auto& [command, _] : commands) {
    std::cout << " - " << command << "\n";
  }
}

void cli::Console::handleCommand(const std::string& command){
  std::vector<std::string> args = parseCommand(command);
  if (args.empty())
  {
    return;
  }

  std::string commandName = args[0];
  args.erase(args.begin());

  if (commands.find(commandName) != commands.end()) {
    commands[commandName](args);
  } else {
    std::cout << RED << "Unknown command: " << commandName << RESET << std::endl;
  }
}

std::vector<std::string> cli::Console::parseCommand(const std::string& command) {
  std::vector<std::string> args;
  std::string currentArg;
  
  for (char c : command) {
      if (c == ' ') {
          if (!currentArg.empty()) {
              args.push_back(currentArg);
              currentArg.clear();
          }
      } else {
          currentArg += c;
      }
  }
  
  if (!currentArg.empty()) {
      args.push_back(currentArg);
  }
  
  return args;
}

void cli::Console::handleShareCommand(const std::vector<std::string>& args){
  for(auto arg : args)
  {
    std::cout << arg << std::endl;
  }
}

void cli::Console::handleCopyCommand(const std::vector<std::string>& args){
  
  for(auto arg : args)
  {
    std::cout << arg << std::endl;
  }
}

void cli::Console::registerCommands(){
  commands["start"] =  [this](const std::vector<std::string>& args) {handleStartCommand(args); } ;
  commands["stop"] =  [this](const std::vector<std::string>& args) {handleStopCommand(args); } ;
  commands["help"] =  [this](const std::vector<std::string>& args) {handleHelpCommand(args); } ;
  commands["share"] =  [this](const std::vector<std::string>& args) {handleShareCommand(args); } ;
  commands["copy"] =  [this](const std::vector<std::string>& args) {handleCopyCommand(args); } ;
}

void cli::Console::startConsole(){
  std::string command;
  while (true)
  {
    std::cout << BLUE << "tonet > " << RESET;
    std::getline(std::cin, command);
    if (command == "stop")
    {
      std::cout << "Exiting tonet" << std::endl;
      break;
    }
    handleCommand(command);
  }
  
}

cli::Console::Console(){
  registerCommands();
  displayStartUpText();
  startConsole();
}
cli::Console::~Console(){}