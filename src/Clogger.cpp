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

    Clog::User Clog::usr::ROOT = {};
// --- END (Variables Impl) --- //

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
    Clog::Clogger& Clog::Clogger::operator<<(char text) {
        // switch statment would 'probably'(untested) make this slower
        if (text = '0') {
            this->handler->print(this->buffer, this->format, this->level, this->out_level);
            this->level = Clog::lvl::INFO;
            this->buffer = {};
        } else {
            this->buffer.push_back(std::to_string(text));
        }
        return *this;
    }
    Clog::Clogger& Clog::Clogger::operator<<(Clog::User usr) {
        /* Needs to update handler before this serves any purpose */
        return *this;
    }

    Clog::Clogger& Clog::Clogger::operator<<(Clog::Level level) { 
        this->level = level;
        return *this;
    }

    Clog::Clogger& Clog::Clogger::operator<<(char* text) { 
        this->buffer.push_back(text);
        return *this;
    }
    Clog::Clogger& Clog::Clogger::operator<<(const char* text) {
        this->buffer.push_back(text);
        return *this;
    }
    Clog::Clogger& Clog::Clogger::operator<<(std::string text) {
        this->buffer.push_back(text);
        return *this;
    }
// -------------------------------- END (Clogger Impl) -------------------------------- //
