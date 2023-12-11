// STD Includes
#include <string>

// Linked Includes
#include <ncurses.h>

// Local Includes
#include "Cloggerpp/Clogger.hpp"

/*
WARNING:
    Be careful using this header as ncurses has terrible compatibility with other packages.
    There will other more viable options in the future...
*/

namespace Clog {
    namespace Handler {
        class NC_Tui : public Base {
	    private:
            WINDOW* _win;
	    public:
	        NC_Tui(); // initscr
            NC_Tui(WINDOW* win);
            NC_Tui(int x_size, int y_size, int x_pos, int y_pos); // initscr
	        ~NC_Tui(); // endwin
	        virtual void print(
	    	    const std::vector<std::string>& buffer,
	    	    std::string& format,
	    	    Clog::Level& clvl,
	    	    Clog::Level& olvl
	        );
	    };
    };
};