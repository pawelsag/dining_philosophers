#pragma once
#include <list> 
#include <array>
#include "config.hpp"
#include "philosopher.hpp"

namespace so2
{
    struct fork
    {
        int last_owner_id;
        std::mutex fork_;
        bool can_acquire(int ph_id)
        {
            return ph_id == last_owner_id;
        }
    };
}
