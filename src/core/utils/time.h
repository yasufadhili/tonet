/*
 * Filename: time.h
 * Path: /tonet/src/core/utils
 * Created Date: Monday 11th November, 2024, 20:44:14 EAT
 * Author: Yasu Fadhili
 * 
 * Credits -> Building Low Latency Applications in C++ book
 */

#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace utils {

  typedef int64_t Nanos;

  constexpr Nanos NANOS_TO_MICROS = 1000;
  constexpr Nanos MICROS_TO_MILLIS = 1000;
  constexpr Nanos MILLIS_TO_SECS = 1000;
  constexpr Nanos NANOS_TO_MILLIS = NANOS_TO_MICROS * MICROS_TO_MILLIS;
  constexpr Nanos NANOS_TO_SECS = NANOS_TO_MILLIS * MILLIS_TO_SECS;

  inline auto getCurrentNanos() noexcept {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
  }

  inline auto& getCurrentTimeStr(std::string* time_str) {
    const auto now = std::chrono::system_clock::now();
    const auto time = std::chrono::system_clock::to_time_t(now);

    // Convert `time_t` to `tm` structure for further manipulation
    std::tm tm_info;
    localtime_r(&time, &tm_info);

    // Format time in the "Day DD Month YYYY HH:MM:SS" format
    std::ostringstream oss;
    oss << std::put_time(&tm_info, "%a %d %b %Y %H:%M:%S");
    time_str->assign(oss.str());

    return *time_str;
  }

} // namespace utils
