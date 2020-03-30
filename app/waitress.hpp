#pragma once
#include <queue>          // std::queue
#include <array>
#include "config.hpp"
#include "philosopher.hpp"

namespace so2
{
    using ph_view = std::queue<philosopher*>;
    
    class waitress
    {
        ph_view next_ph_view;
        std::array<std::mutex, config::ph_count> forks;
        void verify(const philosopher& ph);

    public:
        bool get_forks(const philosopher& ph);
    };
}
