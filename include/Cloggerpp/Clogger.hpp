#pragma once
// STD Includes
#include <string> // try to remove this include when possible

// TODO: 
//  Implement User Formatting
//  Implement USER naming

/*
In the future this class will branch off to a C style class (using a struct with function pointers)
 and then to a collection of C Functions with static variables for the buffer, usr, lvl, format and so on
*/

namespace Clog {
    // Forward Declarations
    namespace Handler {
        class Base;
    }


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
    struct User {
        std::string name = "ROOT";
        // in case it will be used for something like a webserver (which will flood the .log file with loads of connections),
        //  this way you can have multiple handlers for one clog object
        bool custom_handl = false; // to stop any seg faults this will set weather to use Clogger handl or the users handl
        Clog::Handler::Base* handl = nullptr; 
    };
    
    /* Seperate these into defaults */
    namespace lvl {
        extern Clog::Level UNKNOWN;     // Level -1
        extern Clog::Level DEBUG;       // Level 0
        extern Clog::Level INFO;        // Level 1
        extern Clog::Level NOTICE;      // Level 2
        extern Clog::Level WARNING;     // Level 3
        extern Clog::Level ERROR;       // Level 4
        extern Clog::Level CRITICAL;    // Level 5
    };
    namespace usr {
        extern Clog::User ROOT;
    };
    
    namespace Handler {
        class Base {
        public:
            virtual void print(
                const std::string& buffer,
                const std::string& format,
                const Clog::User& usr_,
                const Clog::Level& lvl
            ) = 0;
        };
    };

    // Consider Changing shared_ptr to unique_ptr
    class Clogger {
    private:
        // stores the level and current output level
        Clog::Level level = Clog::lvl::INFO;
        Clog::Level out_level = Clog::lvl::INFO;
        Clog::User usr = Clog::usr::ROOT;

        // stores the log format
        std::string format = "~L/:~T"; // ${Level(e.g. INFO)}: ${Text(e.g. Hello, World!)} // space is inserted automatically

        // logs to a user picked item (e.g. file, terminal, ...)
        Clog::Handler::Base* handler;

        // stores user log
        std::string buffer; // TOOD: benchmark a stringstream against a std::string and char[]
    public:
        Clogger();
        Clogger(Clog::Clogger&& clog);
        Clogger(Clog::Handler::Base* handl);

        void update_handler(Clog::Handler::Base* handl);

        void set_level(Clog::Level& x);

        void set_format(std::string& _format);

        // AUX Methods for << use
        // Special Cases 
        Clog::Clogger& operator<<(char text);
        Clog::Clogger& operator<<(const Clog::User& usr);
        Clog::Clogger& operator<<(const Clog::Level& level);
        Clog::Clogger& operator<<(char* text);
        Clog::Clogger& operator<<(const char* text);
        Clog::Clogger& operator<<(std::string text);
 
        // seperate these into advancedCXX
        // Default Cases
        template <typename T>
        Clog::Clogger& operator<<(T text) {
            this->buffer += std::to_string(text);
            return *this;
        }
        template <typename T>
        Clog::Clogger& operator<<(T* text) {
            this << *text;
            return *this;
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
