#pragma once
#include <condition_variable>
#include <atomic>
#include <mutex>
#include <utility>
#include <thread>
#include "fork.hpp"

namespace so2
{
    constexpr fork_set calc_forks_ids(int id)
    {
       return {id-1<0?config::forks_count-1:id-1, id}; 
    }
    struct table;

    struct philosopher
    {
        static inline std::mutex t_mutex = {};
        static inline std::condition_variable cv = {};
        static inline bool dummy_active = false;

        philosopher()= default;
        philosopher(table*, bool* is_active, int id);
        philosopher& operator=(philosopher&&);
        ~philosopher();
        void think();
        bool try_eat();
        void run();
        
        fork_set assigned_forks = calc_forks_ids(ph_id);

        table *parent = nullptr; 
        bool *is_active = &dummy_active ;
        int ph_id = -1;

        std::thread runner; 
    };
}


