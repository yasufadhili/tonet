
#include "core/utils/logger.h"
#include <iostream>

int main(){

  try {
    utils::Logger::getInstance().init("tonet.log", utils::LogLevel::DEBUG);
    utils::LOG_INFO("Tonet application starting...");
        
    // ....
        
  } catch (const std::exception& e) {
    std::cerr << "Failed to initialise logger: " << e.what() << std::endl;
    return 1;
  }
  
}