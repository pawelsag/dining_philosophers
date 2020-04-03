#pragma once
#include <stdint.h>
#include <chrono>
namespace config
{
    using ms = std::chrono::milliseconds;
    constexpr int  ph_count = 5;
    constexpr int  forks_count = ph_count;
    // minimal interval between lunch'es
    constexpr auto eating_time = ms(10); 
    constexpr auto refresh_screen_interval = ms(500);
    // this value is used as a limit for each
    // philosopher. Philosoper will take his lunch
    // eatting_goal times, than it will rest forever
    constexpr auto eatting_goal = 1000;

    extern bool fin_signal;
}
