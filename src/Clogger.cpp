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
    Clog::Clogger::Clogger(Clog::Clogger&& clog) {
        // copy over user defined variables
        this->out_level = std::move(clog.out_level);
        this->format = std::move(clog.format);
        this->handler = std::move(clog.handler);
    }
    Clog::Clogger::Clogger(Clog::Handler::Base* handl) : handler(std::move(handl)) {}

    void Clog::Clogger::update_handler(Clog::Handler::Base* handl) {
        // this->handler.reset(); // reset value at handler
        // the line beneath decrease the reference to the handler by 1 apperantly and no need for the line aboe
        // testing REQUIRED
        this->handler = std::move(handl); // assign new value at handler according to new user handler
    }

    void Clog::Clogger::set_level(Clog::Level& x) {
        this->out_level = std::move(x);
    }

    void Clog::Clogger::set_format(std::string& _format) {
        this->format = std::move(_format);
    }

    // AUX Methods for << use
    // Special Cases 
    Clog::Clogger& Clog::Clogger::operator<<(char text) {
        // switch statment would 'probably'(untested) make this slower
        if (text = '0') {
            if (this->level.level >= this->out_level.level) {
                if (this->usr.custom_handl) {
                    this->usr.handl->print(this->buffer, this->format, this->usr, this->level);
                } else {
                    this->handler->print(this->buffer, this->format, this->usr, this->level);
                }
            }
            this->usr = Clog::usr::ROOT;
            this->level = Clog::lvl::INFO;
            this->buffer.clear();
        } else {
            this->buffer += text;
        }
        return *this;
    }
    Clog::Clogger& Clog::Clogger::operator<<(const Clog::User& usr) {
        this->usr = usr;
        return *this;
    }

    Clog::Clogger& Clog::Clogger::operator<<(const Clog::Level& level) { 
        this->level = level;
        return *this;
    }

    Clog::Clogger& Clog::Clogger::operator<<(char* text) { 
        this->buffer += text;
        return *this;
    }
    Clog::Clogger& Clog::Clogger::operator<<(const char* text) {
        this->buffer += text;
        return *this;
    }
    Clog::Clogger& Clog::Clogger::operator<<(std::string text) {
        this->buffer += text;
        return *this;
    }
// -------------------------------- END (Clogger Impl) -------------------------------- //
