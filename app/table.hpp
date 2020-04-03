#pragma once
#include"philosopher.hpp"
#include"fork.hpp"
#include"config.hpp"
#include<fmt/format.h>
namespace so2
{
    struct table
    {
        table()
        {
            int id = 0;
            for(auto &ph : phs)
            {
                ph =std::move(philosopher(this, id++));
            }
            for(auto &f: forks)
            {
                f.last_owner_id = -1;
            }
        }

        bool can_acquire(int ph_id, const fork_set& f_ids)
        {
            return forks[f_ids.first].can_acquire(ph_id) &&
                forks[f_ids.second].can_acquire(ph_id);
        }

        void mark_forks(int ph_id, const fork_set& f_ids)
        {
            forks[f_ids.first].last_owner_id = ph_id;
            forks[f_ids.second].last_owner_id = ph_id;
        }
        void show_forks()
        {
            for(auto &f: forks)
            {
                fmt::print("{} ", f.last_owner_id);
            }
            fmt::print("\n");
        }

        std::array<fork, config::ph_count> forks;
        std::array<philosopher, config::ph_count> phs;
    };
}
