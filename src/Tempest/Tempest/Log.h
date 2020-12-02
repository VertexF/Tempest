#ifndef LOG_HDR
#define LOG_HDR

#include "PreComp.h"

//This class sets up the logger to initalised to have the format we want.
namespace Tempest
{
    class Log
    {
    public:
        static void init();

        static inline std::shared_ptr<spdlog::logger>& getLogger() { return _logger; }

    private:
        static std::shared_ptr<spdlog::logger> _logger;
    };
}

//These defined used to run the logger at different level. While giving the 
//befinite of being able to be stripped on release builds.
#define TEMPEST_ERROR(...) ::Tempest::Log::getLogger()->error(__VA_ARGS__)
#define TEMPEST_WARN(...)  ::Tempest::Log::getLogger()->warn(__VA_ARGS__)
#define TEMPEST_INFO(...)  ::Tempest::Log::getLogger()->info(__VA_ARGS__)
#define TEMPEST_TRACE(...) ::Tempest::Log::getLogger()->trace(__VA_ARGS__)

#endif // !LOG_HDR
