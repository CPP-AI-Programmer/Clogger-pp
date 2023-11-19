#include <Cloggerpp/Clogger.hpp>

int main() {
    initscr();
    refresh();
    WINDOW* win = newwin(LINES, COLS, 0, 0);
    box(win, 0, 0);
    wrefresh(win);

    // if you want you can use the default initalize but this will limit options and this should be used purly as a log window in your application
    std::shared_ptr<Clog::Handler::Base> handler = std::make_shared<Clog::Handler::Tui>(win);
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

