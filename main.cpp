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
    char c = '\0';
    fmt::print("Type \'q\' to exit:\n");
    while(c != 'q')
    {
        std::cin >> c;
    }
    config::fin_signal = true;
}
