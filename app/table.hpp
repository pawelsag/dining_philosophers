#pragma once
#include"philosopher.hpp"
#include"fork.hpp"
#include"config.hpp"

namespace so2
{
    struct table
    {
        table()
        {
            for(auto &ph : phs)
            {
                ph = philosopher(this, &running);
            }
        }

        bool running=true;
        std::array<fork, config::ph_count> forks;
        std::array<philosopher, config::ph_count> phs;
    };
}
