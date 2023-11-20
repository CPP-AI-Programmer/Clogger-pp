#include "Cloggerpp/Clogger.hpp"

// --- Variables Impl --- //
    char Clog::exit = '0';
    char Clog::nl = '\n';

    Clog::Level Clog::lvl::UNKNOWN =  {-1, "UNKNOWN"};
    Clog::Level Clog::lvl::DEBUG =    {0, "DEBUG"};
    Clog::Level Clog::lvl::INFO =     {1, "INFO"};
    Clog::Level Clog::lvl::NOTICE =   {2, "NOTICE"};
    Clog::Level Clog::lvl::WARNING =  {3, "WARNING"};
    Clog::Level Clog::lvl::ERROR =    {4, "ERROR"};
    Clog::Level Clog::lvl::CRITICAL = {5, "CRITICAL"};

// -------------------------------- Clogger Impl -------------------------------- //
    Clog::Clogger::Clogger() {}
    Clog::Clogger::Clogger(const Clog::Clogger& clog) {
        // copy over user defined variables
        this->out_level = clog.out_level;
        this->format = clog.format;
        this->handler = clog.handler;
    }
    Clog::Clogger::Clogger(std::shared_ptr<Clog::Handler::Base> handl) : handler(handl) {}

    void Clog::Clogger::update_handler(std::shared_ptr<Clog::Handler::Base> handl) {
        // this->handler.reset(); // reset value at handler
        // the line beneath decrease the reference to the handler by 1 apperantly and no need for the line aboe
        // testing REQUIRED
        this->handler = handl; // assign new value at handler according to new user handler
    }

    void Clog::Clogger::set_level(Clog::Level& x) {
        this->out_level = x;
    }

    void Clog::Clogger::set_format(std::string& _format) {
        this->format = _format;
    }

    // AUX Methods for << use
    // Special Cases 
    Clog::Clogger& Clog::operator<<(Clog::Clogger& os, char text) {
        // switch statment would 'probably'(untested) make this slower
        if (text = '0') {
            os.handler->print(os.buffer, os.format, os.level, os.out_level);
            os.level = Clog::lvl::INFO;
            os.buffer = {};
        } else {
            os.buffer.push_back(std::to_string(text));
        }
        return os;
    }

    Clog::Clogger& Clog::operator<<(Clog::Clogger& os, Clog::Level level) { 
        os.level = level;
        return os;
    }

    Clog::Clogger& Clog::operator<<(Clog::Clogger& os, char* text) { 
        os.buffer.push_back(text);
        return os;
    }
    Clog::Clogger& Clog::operator<<(Clog::Clogger& os, const char* text) {
        os.buffer.push_back(text);
        return os;
    }
    Clog::Clogger& Clog::operator<<(Clog::Clogger& os, std::string text) {
        os.buffer.push_back(text);
        return os;
    }

// -------------------------------- Handlers Impls --------------------------------//
    // ---------------- STD OUTPUT Handler ---------------- // 
        Clog::Handler::stdout::stdout() {}
        void Clog::Handler::stdout::print(
            const std::vector<std::string>& buffer,
            std::string& format,
            Clog::Level& clvl,
            Clog::Level& olvl
        ) {
            if (clvl.level >= olvl.level) {
                std::cout << clvl.name << ": ";
                for (auto& text : buffer) {
                    std::cout << text;
                }
                std::cout << std::endl;
            }
        }

    // ---------------- File Handler ---------------- // 
        Clog::Handler::File::File(std::string& path) {
            this->file.open(path, std::ios::out);
        }
        Clog::Handler::File::~File() {
            this->file.close();
        }
        void Clog::Handler::File::print(
            const std::vector<std::string>& buffer,
            std::string& format,
            Clog::Level& clvl,
            Clog::Level& olvl
        ) {
            if (clvl.level >= olvl.level) {
                this->file << clvl.name << ": ";
                for (auto& text : buffer) {
                    this->file << text;
                }
                this->file << '\n';
                this->file.flush();
            }

        }

    // ---------------- NCURSES Handler ---------------- // 
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

