#ifndef PRECOMP_HDR
#define PRECOMP_HDR

#include <utility>
#include <algorithm>
#include <functional>
#include <string>
#include <memory>

#include <iostream>
#include <sstream>

#include <vector>
#include <map>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <set>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "../Log.h"

#ifdef WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
#endif

#endif //PRECOMP_HDR