#include "spdlog/sinks/stdout_color_sinks.h"

#include "Log.h"
#include "Core.h"

namespace Tempest
{
    std::shared_ptr<spdlog::logger> Log::_logger;

    void Log::init() 
    {
        _logger = spdlog::stdout_color_mt("Tempest");
        _logger->set_pattern("%^[%T] %n %l: %v%$");
        _logger->set_level(spdlog::level::trace);
    }
}