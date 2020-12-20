#ifndef CORE_HDR
#define CORE_HDR

#include <memory>

#ifdef TEMPEST_DEBUG
    #define TEMPEST_CORE_ASSERT(x, ...) { if(!(x)) { TEMPEST_CRITICAL("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define TEMPEST_CORE_ASSERT(x, ...)
#endif

namespace Tempest 
{
    template<typename T>
    using scope = std::unique_ptr<T>;

    template<typename T>
    using ref = std::shared_ptr<T>;
}

#endif // !CORE_HDR
