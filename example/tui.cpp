#include <Cloggerpp/Clogger.hpp>
#include <Cloggerpp/tui/ncurses.hpp>
#include <ncurses.h>

int main() {
    initscr();
    refresh();
    WINDOW* win = newwin(LINES, COLS, 0, 0);
    box(win, 0, 0);
    wrefresh(win);

    std::shared_ptr<Clog::Handler::Base> handler = std::make_shared<Clog::Handler::NC_Tui>(win);
    auto logger = Clog::Clogger(handler);

    logger << Clog::lvl::INFO << "Hello, World!" << Clog::exit;
    getch();

    logger << Clog::lvl::WARNING << "Second Test" << Clog::exit;
    getch();

    char usrin[20];
    logger << "What would you like to print: " << Clog::exit;
    move(1, 37);
    getstr(usrin);
    wclear(win);
    logger << "You Printed: " << usrin << Clog::exit;
    
    getch();

    return 0;
}
