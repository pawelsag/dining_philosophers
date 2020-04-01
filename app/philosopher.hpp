#pragma once
#include <condition_variable>
#include <atomic>
#include <mutex>
#include <utility>
#include <thread>
#include "fork.hpp"

namespace so2
{
    constexpr std::pair<int,int> calc_forks_ids(int id)
    {
       return {id-1<0?config::forks_count-1:id-1, id}; 
    }
    struct table;

    struct philosopher
    {
        static inline std::mutex t_mutex = {};
        static inline std::condition_variable cv = {};
        static inline int next_ph = 0;
        philosopher() = default;
        philosopher(table*, bool* is_active);
        void think();
        bool try_eat();
        void run();
        

        int ph_id = next_ph++;
        std::pair<int,int> assigned_forks=calc_forks_ids(ph_id);
        
        table* parent; 
        bool *is_active;
    };

}


