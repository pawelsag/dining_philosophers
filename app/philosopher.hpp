#pragma once
#include <condition_variable>
namespace so2
{
    class philosopher
    {
        std::condition_variable cv;
        std::mutex t_mutex;

    public:
        void think();
        void try_eat();
        void notify();
    };

    void philosopher::think()
    {
        //there will be some kind of ncurses view     
    }

    void philosopher::notify()
    {
             
    }
}


