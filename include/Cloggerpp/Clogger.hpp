#pragma once
// STD Includes
#include <vector>
#include <string>
// #include <utility>
#include <memory>

// TODO: 
//  Implement User Formatting
//  Implement USER naming

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
        extern Clog::Level UNKNOWN;     // Level -1
        extern Clog::Level DEBUG;       // Level 0
        extern Clog::Level INFO;        // Level 1
        extern Clog::Level NOTICE;      // Level 2
        extern Clog::Level WARNING;     // Level 3
        extern Clog::Level ERROR;       // Level 4
        extern Clog::Level CRITICAL;    // Level 5
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
    };

    struct User {
        std::string name = "ROOT";
        // in case it will be used for something like a webserver (which will flood the .log file with loads of connections),
        //  this way you can have multiple handlers for one clog object
        bool custom_handl = false; // to stop any seg faults this will set weather to use Clogger handl or the users handl
        std::shared_ptr<Clog::Handler::Base> handl = nullptr; 
    };
    namespace usr {
        extern Clog::User ROOT;
    };

    // Consider Changing shared_ptr to unique_ptr
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
        Clogger& operator<<(char text);
        Clogger& operator<<(Clog::Level level);
        Clogger& operator<<(Clog::User usr); // TODO: Implement This
        Clogger& operator<<(char* text);
        Clogger& operator<<(const char* text);
        Clogger& operator<<(std::string text);
 
        // Default Cases
        template <typename T>
        Clog::Clogger& operator<<(T text) {
            this->buffer.push_back(std::to_string(text));
            return *this;
        }
        template <typename T>
        Clog::Clogger& operator<<(T* text) {
            this << text;
            return *this;
        }
        template <typename T>
        Clog::Clogger& operator<<(std::vector<T>& texts) {
            for (auto& text : texts) {
                this << text;
            }
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
