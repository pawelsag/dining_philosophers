#include"philosopher.hpp"
#include"table.hpp"
#include<fmt/format.h>
namespace so2
{
    philosopher::philosopher(table *t, int id)
    : parent(t), ph_id(id)
    {
        assigned_forks = calc_forks_ids(ph_id);
        is_active = true;
        runner = std::thread(&philosopher::run, this);
    }

    philosopher& philosopher::operator=(philosopher&& p)
    {
       ph_id = p.ph_id;
       parent = p.parent;
       assigned_forks = std::move(p.assigned_forks);
       is_active = p.is_active;

       p.is_active = false;
       cv.notify_all();
       p.runner.join();
       p.parent = nullptr;

       runner = std::thread(&philosopher::run, this);
       return *this;
    }

    void philosopher::think()
    {
       std::unique_lock<std::mutex> lk(t_mutex);
       try
       {
           cv.wait(lk, [&]{return parent->can_acquire(ph_id,assigned_forks) || !active();});
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
            parent->mark_forks(ph_id, assigned_forks);
            eatten_times++;
            std::this_thread::sleep_for(config::eating_time);
            parent->forks[assigned_forks.first].fork_.unlock();
            parent->forks[assigned_forks.second].fork_.unlock();
            return true;
        }
        return false;
    }

    void philosopher::run()
    {
        while(active())
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

        is_active = false; 
        cv.notify_all();
       
        if(runner.joinable())
            runner.join();
    }
}

