#include "PreComp.h"

#include "Log.h"
#include "Core.h"

namespace Tempest
{
    //Static shared_ptr needs to be defined or we get linker errors.
    std::shared_ptr<spdlog::logger> Log::_logger;

    void Log::init() 
    {
        //Allocates the shared pointer with the Tempests name.
        _logger = spdlog::stdout_color_mt("Tempest");
        //This set the pattern we will be using.
        _logger->set_pattern("%^[%T] %n %l: %v%$");
        //This means it will print everythings of important.
        _logger->set_level(spdlog::level::trace);
    }
}