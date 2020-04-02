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
            int id = 0;
            for(auto &ph : phs)
            {
                ph =std::move(philosopher(this, &running, id++));
            }
        }

        bool can_acquire(int ph_id, const fork_set& f_ids)
        {
            return forks[f_ids.first].can_acquire(ph_id) &&
                forks[f_ids.second].can_acquire(ph_id);
        }

        void acquire_forks(int ph_id, const fork_set& f_ids)
        {
            forks[f_ids.first].last_owner_id = ph_id;
            forks[f_ids.second].last_owner_id = ph_id;
        }

        bool running=true;
        std::array<fork, config::ph_count> forks;
        std::array<philosopher, config::ph_count> phs;
    };
}
