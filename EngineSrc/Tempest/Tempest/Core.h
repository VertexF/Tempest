#ifndef CORE_HDR
#define CORE_HDR

#include <memory>

namespace Tempest 
{
    template<typename T>
    using scope = std::unique_ptr<T>;

    template<typename T>
    using ref = std::shared_ptr<T>;
}

#endif // !CORE_HDR
