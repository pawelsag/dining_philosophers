#pragma once
#include"philosopher.hpp"
#include"fork.hpp"
#include"config.hpp"
#include<fmt/format.h>
#include"display.hpp"

namespace so2
{
    struct table
    {
        table();
        ~table();
        
        bool can_acquire(int ph_id, const fork_set& f_ids);

        void mark_forks(int ph_id, const fork_set& f_ids);

        void show_forks();
        
        void update_results();
        
        std::array<fork, config::ph_count> forks;
        std::array<philosopher, config::ph_count> phs;
    private:
        bool ph_state_changed(int, size_t);
        
        std::array<size_t,config::ph_count> last_ph_state;
    };
}
