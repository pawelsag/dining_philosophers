#pragma once
#include <stdint.h>
#include <chrono>
namespace config
{
    using ms = std::chrono::milliseconds;
    constexpr int  ph_count = 5;
    constexpr int  forks_count = ph_count;
    constexpr auto eating_time = ms(10); 
    constexpr auto refresh_screen_interval = ms(500);

    extern bool fin_signal;
}
