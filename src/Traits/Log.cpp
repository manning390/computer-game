#include "Log.hpp"

std::shared_ptr<spdlog::logger> Log::s_logger;

void Log::init() {
  spdlog::set_pattern("%^[%T] %n: %v%$");

  s_logger = spdlog::stdout_color_mt("APP");
  s_logger->set_level(spdlog::level::trace);

  LOG_TRACE("Logging initialized");
}

