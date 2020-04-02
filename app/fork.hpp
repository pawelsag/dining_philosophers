#pragma once
#include <list> 
#include <array>
#include "config.hpp"
#include "philosopher.hpp"

namespace so2
{
    using fork_set = std::pair<int,int>;
    struct fork
    {
        int last_owner_id = -1;
        std::mutex fork_;
        bool can_acquire(int ph_id)
        {
            return ph_id != last_owner_id;
        }
    };
}
