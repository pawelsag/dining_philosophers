#include <fmt/format.h>
#include <iostream>       // std::cin, std::cout
#include <queue>          // std::queue
#include "table.hpp"
#include <ncurses.h>

namespace config
{
    bool fin_signal = false;
}

int main ()
{
    so2::table inst;
    std::thread display(&so2::table::update_results, &inst);
    
    char c = '\0';
    while(c != 'q')
    {
        std::cin >> c;
    }
    config::fin_signal = true;
    display.join();
}
