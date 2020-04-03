#include <fmt/format.h>
#include "table.hpp"
#include <ncurses.h>

namespace config
{
    bool fin_signal = false;
}

int main ()
{
    so2::table inst;

    fd_set rfds;
    struct timeval tv;
    int retval = 0;

   /* Watch stdin (fd 0) to see when it has input. */
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);

   /* Wait up to 2 seconds. */
    tv.tv_sec = 2;
    tv.tv_usec = 0;

    fmt::print("Type \'q\' to exit:\n");
    
    while(retval != 'q')
    {
        retval = select(1, &rfds, NULL, NULL, &tv);
        inst.update_results();
        std::this_thread::sleep_for(config::refresh_screen_interval);
    }

    config::fin_signal = true;
}
