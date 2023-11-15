#pragma once

#include <string>
#include <vector>
#include <map>
#include <utility>

#include <memory>

// linked
// #include <ncurses.h>

// local
#include "Handlers.hpp"

// TODO: 
//  Implement User Formatting


namespace defstr {
    char exit = '0';
    char nl = '\n';
};

namespace Clog {    
    // this is a namespace for efficiency and convienience if new levels want to be added
    namespace level {
        std::pair<int, std::string> UNKNOWN =  std::pair<int, std::string>(-1, "UNKNOWN");
        std::pair<int, std::string> DEBUG =    std::pair<int, std::string>(0, "DEBUG");
        std::pair<int, std::string> INFO =     std::pair<int, std::string>(1, "INFO");
        std::pair<int, std::string> NOTICE =   std::pair<int, std::string>(2, "NOTICE");
        std::pair<int, std::string> WARNING =  std::pair<int, std::string>(3, "WARNING");
        std::pair<int, std::string> ERROR =    std::pair<int, std::string>(4, "ERROR");
        std::pair<int, std::string> CRITICAL = std::pair<int, std::string>(5, "CRITICAL");
    };

    class Clogger {
    public:
    // Variables
    // these have to be public to be accessed by the operator<< functions
        // stores the level and current output level
        std::pair<int, std::string> level = Clog::level::INFO;
        std::pair<int, std::string> out_level = Clog::level::DEBUG;

        // stores the log format
        std::string format = "~L ~: ~T"; // ${Level(e.g. INFO)}: ${Text(e.g. Hello, World!)} // space is inserted automatically

        // logs to a user picked item (e.g. file, terminal, ...)
        std::shared_ptr<Clog::Handler::Base> handler;

        // stores user log
        std::vector<std::string> buffer;


    // Methods
        Clogger(std::shared_ptr<Clog::Handler::Base> handl);

        void update_handler(std::shared_ptr<Clog::Handler::Base> handl);

        void set_level(std::pair<int, std::string>& x);

        void set_format(std::string _format);

        // AUX Methods for << use
        // Special Cases 
        friend Clogger& operator<<(Clogger& os, char text);
        
        friend Clogger& operator<<(Clogger& os, std::pair<int, std::string> level);

        friend Clogger& operator<<(Clogger& os, char* text);
        friend Clogger& operator<<(Clogger& os, const char* text);

        // Impl in Clogger.tpp
        template <typename T>
        friend Clogger& operator<<(Clogger& os, std::vector<T>& texts);

        // Default Cases
        template <typename T>
        friend Clogger& operator<<(Clogger& os, T text);
        template <typename T>
        friend Clogger& operator<<(Clogger& os, T* text);

    };
};

#include "Clogger.tpp"