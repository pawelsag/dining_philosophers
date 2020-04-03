#include <ncurses.h>
#include<string>

namespace so2
{
    enum COLOR_DESCRIPTOR
    {
        RED = 1,
        GREEN =2
    };
    void init_ncurses();
    void print_red(int y, int x, const std::string& text);
    void print_green(int y, int x, const std::string& text);
}
