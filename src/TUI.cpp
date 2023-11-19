#include "Cloggerpp/Clogger.hpp"

Clog::Handler::Tui::Tui() {
    initscr();
    refresh();
    this->_win = newwin(LINES, COLS, 0, 0);
    box(this->_win, 0, 0);
    wrefresh(this->_win);
}
Clog::Handler::Tui::Tui(WINDOW* win) {
    this->_win = win;
    wrefresh(this->_win);
}
Clog::Handler::Tui::Tui(int x_size, int y_size, int x_pos, int y_pos) {
    initscr();
    refresh();
    this->_win = newwin(x_size, y_size, x_pos, x_size);
    box(this->_win, 0, 0);
    wrefresh(this->_win);
}
Clog::Handler::Tui::~Tui() {
    delwin(this->_win);
    endwin();
}

void Clog::Handler::Tui::print(
    const std::vector<std::string>& buffer,
    std::string& format,
    Clog::Level& clvl,
    Clog::Level& olvl
) {
    if (clvl.level >= olvl.level) {
        int x_pos = 1;
        int y_pos = 1;
        if (format != "") {
            int x_pos = std::stoi(std::to_string(format[0]));
            int y_pos = std::stoi(std::to_string(format[1]));
        }
        std::string final_text = clvl.name + ": ";
	    for (auto& text : buffer) {
	        final_text += text;
	    }
	    mvwprintw(this->_win, x_pos, y_pos, "%s", final_text.c_str());
	    wrefresh(this->_win);
    }
}
