#pragma once
#include <queue>          // std::queue
#include <array>
#include "config.hpp"
#include "philosopher.hpp"

namespace so2
{
    using ph_view = std::queue<philosopher*>;
    
    struct waiter
    {
        ph_view next_ph_view;
        std::array<std::mutex, config::ph_count> forks;
        void verify(const philosopher& ph);
        bool request_forks(const philosopher& ph);
        void notify_philosophers();
        void register_ph(philosopher* ph);
    };

    void waiter::notify_philosophers()
    {
        philosopher::cv.notify_all(); 
    }

    void waiter::register_ph(philosopher* ph)
    {

    }

    bool waiter::request_forks(const philosopher& ph)
    {
        
    }
}
