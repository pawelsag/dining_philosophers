#include"philosopher.hpp"
#include"table.hpp"
#include"reflect.hpp"
namespace so2
{
    philosopher::philosopher(table*t, bool *a)
    : parent(t), is_active(a)
    {}
    void philosopher::think()
    {
       //std::unique_lock<std::mutex> lk(t_mutex);
       //there will be some kind of ncurses view 
       //cv.wait(lk, [&]{return forks_accessible.load();});
    }

    bool philosopher::try_eat()
    {
        if(parent->forks[ph_id].can_acquire(ph_id)&&
            std::try_lock(parent->forks[assigned_forks.first].fork_,
                parent->forks[assigned_forks.second].fork_)!= -1)
        {
            std::this_thread::sleep_for(config::eating_time);
            return true;
        }
        return false;
    }

    void philosopher::run()
    {
        while(is_active)
        {
            if(try_eat() == false)
                think();
        }
    }
}

