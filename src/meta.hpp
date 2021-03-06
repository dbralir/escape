/*******************************************************************************
 * Inugami - An OpenGL framework designed for rapid game development
 * Version: 0.3.0
 * https://github.com/DBRalir/Inugami
 *
 * Copyright (c) 2012 Jeramy Harrison <dbralir@gmail.com>
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the
 * use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *  1. The origin of this software must not be misrepresented; you must not
 *     claim that you wrote the original software. If you use this software
 *     in a product, an acknowledgment in the product documentation would be
 *     appreciated but is not required.
 *
 *  2. Altered source versions must be plainly marked as such, and must not be
 *     misrepresented as being the original software.
 *
 *  3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#ifndef LOG_H
#define LOG_H

#include "inugami/logger.hpp"
#include "inugami/profiler.hpp"

#include <cstdint>

extern Inugami::Logger<>* logger;
extern Inugami::Profiler* profiler;

template <typename T>
std::ostream& print(std::ostream& os, T const& t)
{
    return (os << t);
}

template <typename T, typename... Ts>
std::ostream& print(std::ostream& os, T const& t, Ts const&... ts)
{
    os << t;
    return print(ts...);
}

template <typename... Ts>
std::string stringify(Ts&&... ts)
{
    std::stringstream ss;
    print(ss, ts...);
    return ss.str();
}

// Platform-specific Stuff

    #ifdef __MINGW32__
        #include <chrono>
        inline auto nd_rand()
        {
            auto now = std::chrono::high_resolution_clock::now();
            auto past = now.time_since_epoch();
            return past.count();
        }
    #else
        #include <random>
        inline auto nd_rand()
        {
            return std::random_device{}();
        }
    #endif // __MINGW32__

#endif // LOG_H
