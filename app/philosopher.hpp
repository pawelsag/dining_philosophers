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

        philosopher()= default;
        philosopher(table*, int);
        philosopher& operator=(philosopher&&);
        ~philosopher();

        void think();
        bool try_eat();
        void run();
        
        table *parent = nullptr; 
        const bool *fin_signal = &config::fin_signal;

        bool is_active = false;
        int ph_id = -1;
        size_t eatten_times = 0;
        fork_set assigned_forks;
        std::thread runner;

        bool active()
        {
            return is_active && !*fin_signal;
        }
    };
}


