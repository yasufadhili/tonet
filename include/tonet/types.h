
#pragma once

#include <string>
#include <cstdint>

namespace tonet {
  struct DeviceInfo
  {
    std::string name;
    std::string ipv4;
    std::string ipv6;
    uint16_t port;
  };

  enum class ErrorCode {
    SUCCESS = 0,
    NETWORK_ERROR,
    FILE_ERROR,
    PERMISSION_ERROR
   };
  
}