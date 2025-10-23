#pragma once

#include <memory>

#include <spdlog/spdlog.h>

namespace Tazel {

  class Log {
  public:
    static void Init();

    inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
    inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
  private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;
  };

}

#define TZ_CORE_TRACE(...)    ::Tazel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TZ_CORE_INFO(...)     ::Tazel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TZ_CORE_WARN(...)     ::Tazel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TZ_CORE_ERROR(...)    ::Tazel::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TZ_CORE_FATAL(...)    ::Tazel::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define TZ_TRACE(...)	      ::Tazel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TZ_INFO(...)	      ::Tazel::Log::GetClientLogger()->info(__VA_ARGS__)
#define TZ_WARN(...)	      ::Tazel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TZ_ERROR(...)	      ::Tazel::Log::GetClientLogger()->error(__VA_ARGS__)
#define TZ_FATAL(...)	      ::Tazel::Log::GetClientLogger()->fatal(__VA_ARGS__)
