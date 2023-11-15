#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

#include <memory>

// linked
// #include <ncurses.h>

// TODO: 
//  Implement User Formatting


namespace Clog {
    // character escape sequences
    extern char exit;
    extern char nl;
    
    // this is a namespace for efficiency and convienience if new levels want to be added
    // using a std::string for safety, might be updated in the future:
    /*
    Example Code for std::string update
        // allocate memory for name member using new operator
        this->name = new char[strlen(name) + 1];
        // copy name argument to name member using strcpy function
        strcpy(this->name, name);
    
    */
    struct Level {
        int level;
        std::string name;
    };
    namespace lvl {
        extern Clog::Level UNKNOWN;
        extern Clog::Level DEBUG;
        extern Clog::Level INFO;
        extern Clog::Level NOTICE;
        extern Clog::Level WARNING;
        extern Clog::Level ERROR;
        extern Clog::Level CRITICAL;
    };
    
    namespace Handler {
        class Base {
        public:
            virtual void print(
                const std::vector<std::string>& buffer,
                std::string& format,
                Clog::Level& clvl,
                Clog::Level& olvl
            ) = 0;
        };
        class stdout : public Base {
        public:
            stdout();
            virtual void print(
                const std::vector<std::string>& buffer,
                std::string& format,
                Clog::Level& clvl,
                Clog::Level& olvl
            );
        };
        class File : public Base {
        private:
            std::fstream file;
        public:
            File(std::string& path); // open file
            ~File(); // close file
            virtual void print(
                const std::vector<std::string>& buffer,
                std::string& format,
                Clog::Level& clvl,
                Clog::Level& olvl
            );

        };
        /*
        Comming soon...
        A Terminal Viewer like nano using ncurses;
        This as you can tell has endless possibilitys like allowing control over parts of your program through TUI,
         Although this should probably be its own repo i included it in here as i think it counts as logging,
         since this could be used for something as simple as help menus or
         as complicated as dynamic logging after a critical error.
        */

        /*
        class TUI : public Base {
        public:
        
        };
        */
    };


    class Clogger {
    public:
    // Variables
    // these have to be public to be accessed by the operator<< functions
        // stores the level and current output level
        Clog::Level level = Clog::lvl::INFO;
        Clog::Level out_level = Clog::lvl::INFO;

        // stores the log format
        std::string format = "~L ~: ~T"; // ${Level(e.g. INFO)}: ${Text(e.g. Hello, World!)} // space is inserted automatically

        // logs to a user picked item (e.g. file, terminal, ...)
        std::shared_ptr<Clog::Handler::Base> handler;

        // stores user log
        std::vector<std::string> buffer;


    // Methods
        Clogger();
        Clogger(const Clog::Clogger& clog);
        Clogger(std::shared_ptr<Clog::Handler::Base> handl);

        void update_handler(std::shared_ptr<Clog::Handler::Base> handl);

        void set_level(Clog::Level& x);

        void set_format(std::string& _format);

        // AUX Methods for << use
        // Special Cases 
        friend Clogger& operator<<(Clogger& os, char text);
        friend Clogger& operator<<(Clogger& os, Clog::Level level);
        friend Clogger& operator<<(Clogger& os, char* text);
        friend Clogger& operator<<(Clogger& os, const char* text);
        friend Clogger& operator<<(Clogger& os, std::string text);
 
        // Default Cases
        template <typename T>
        friend Clog::Clogger& operator<<(Clog::Clogger& os, T text) {
            os.buffer.push_back(std::to_string(text));
            return os;
        }

        template <typename T>
        friend Clog::Clogger& operator<<(Clog::Clogger& os, T* text) {
            os.buffer.push_back(std::to_string(*text));
            return os;
        }
        
        template <typename T>
        friend Clog::Clogger& operator<<(Clog::Clogger& os, std::vector<T>& texts) {
            for (auto& text : texts) {
                os << text;
            }
            return os;
        }
    };
    /*
    Maybe Impl smth like this:
        Clogger& endl(Clogger& os) {
            os.buffer.push_back('\n');
            return os;
        }
    */
};
