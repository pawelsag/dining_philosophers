#include"table.hpp"

namespace so2
{
    constexpr int y_print_off = 10;
    constexpr int x_print_off = 10;

    table::table()
    {
        init_ncurses();
        last_ph_state.fill(0);

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

    bool table::can_acquire(int ph_id, const fork_set& f_ids)
    {
        return forks[f_ids.first].can_acquire(ph_id) &&
            forks[f_ids.second].can_acquire(ph_id);
    }

    void table::mark_forks(int ph_id, const fork_set& f_ids)
    {
        forks[f_ids.first].last_owner_id = ph_id;
        forks[f_ids.second].last_owner_id = ph_id;
    }

    void table::show_forks()
    {
        for(auto &f: forks)
        {
            fmt::print("{} ", f.last_owner_id);
        }
        fmt::print("\n");
    }
    
    void table::update_results()
    {
        print_green(y_print_off-1,x_print_off,"Type \'q\' to exit" );
        while(!config::fin_signal)
        {
            int off = 0;
            for(const auto& ph : phs)
            {
                const auto ph_id = ph.ph_id;
                const auto ph_eatten = ph.eatten_count();
                auto info = fmt::format("Ph {} have eatten {}",ph_id, ph_eatten);
                if(ph_state_changed(ph_id, ph_eatten))
                {
                    print_green(y_print_off+off, x_print_off, info);
                }
                else
                {
                    print_red(y_print_off+off, x_print_off, info);
                }
                off++;
            }
            std::this_thread::sleep_for(config::refresh_screen_interval);
        }
    }

    bool table::ph_state_changed(int id, size_t eatten)
    {
        auto cur_state = last_ph_state[id];
        last_ph_state[id] = eatten;
        return cur_state == last_ph_state[id];  
    }

    table::~table()
    {
        endwin();
    }

}
