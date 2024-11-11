
#include "core/utils/logger.h"
#include "core/utils/thread.h"
#include "cli/console.h"
#include <iostream>
#include "core/network/socket.h"


int main(){

  std::string name {"yasu"};

  utils::Logger logger("logging_example.log");

  logger.log("Welcome \n");
  logger.log("Name % :", name);

  std::cout << "main exiting." << std::endl;
  
}

