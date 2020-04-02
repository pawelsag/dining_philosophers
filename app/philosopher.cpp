#include"philosopher.hpp"
#include"table.hpp"
#include<fmt/format.h>
namespace so2
{
    philosopher::philosopher(table*t, bool *a, int p_id)
    : parent(t), is_active(a), ph_id(p_id)
    {
        fmt::print("Creating ph with id {}\n", ph_id);
        runner = std::thread(&philosopher::run, this);
    }

    philosopher& philosopher::operator=(philosopher&& p)
    {
       ph_id = p.ph_id;
       runner = std::move(p.runner);
       parent = p.parent;
       p.parent = nullptr;
       is_active = p.is_active;
       return *this;
    }

    void philosopher::think()
    {
       std::unique_lock<std::mutex> lk(t_mutex);
       try
       {
           cv.wait(lk, [&]{return parent->can_acquire(ph_id,assigned_forks);});
       }catch(...)
       {
         fmt::print("Exception occured");
       }
    }

    bool philosopher::try_eat()
    {
        if(std::try_lock(parent->forks[assigned_forks.first].fork_,
                parent->forks[assigned_forks.second].fork_)!= false)
        {
            parent->acquire_forks(ph_id, assigned_forks);
            fmt::print("PH {} is eating", ph_id);
            std::this_thread::sleep_for(config::eating_time);
            return true;
        }
        return false;
    }

    void philosopher::run()
    {
        while(*is_active)
        {
            if(try_eat() == false)
            {
                cv.notify_all();
                think();
            }
            cv.notify_all();
        }
    }

    philosopher::~philosopher()
    {
        // ph has been moved
        // do nothing here
        if(parent == nullptr)
            return;
        // elsewhere terminate ph
        bool is_active_ = false;
        bool *old_ref = is_active; 
        is_active = &is_active_;

        if(runner.joinable())
            runner.join();
        is_active = old_ref; 
    }
}

