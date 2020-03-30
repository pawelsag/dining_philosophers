#pragma once
#include <stdint.h>
#include <chrono>
namespace config
{
    using ms = std::chrono::milliseconds;
    constexpr int ph_count = 5;
    constexpr int forks_count = ph_count;
    constexpr auto eating_time = ms(1000); 
    constexpr auto thinking_time = ms(1000);
}
