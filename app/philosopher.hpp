#pragma once
#include <condition_variable>
#include <atomic>
#include <mutex>
namespace so2
{
    struct waiter;

    struct philosopher
    {
        void think();
        void try_eat();
        bool forks_ready();

        static inline std::mutex t_mutex = {};
        static inline std::condition_variable cv = {};
        static inline int next_ph = 0;
        
        int curent_ph = next_ph++;
        std::atomic<bool> forks_accessible;
        //const waiter& w;
    };

    void philosopher::think()
    {
       std::unique_lock<std::mutex> lk(t_mutex);
       //there will be some kind of ncurses view 
       forks_accessible = false; 
       cv.wait(lk, [&]{return forks_accessible.load();});
    }

    bool philosopher::forks_ready()
    {
       if(forks_accessible == true)
           return false;

       forks_accessible = true;
       return true;
    }
}


