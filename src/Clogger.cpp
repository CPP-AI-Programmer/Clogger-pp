#include "Cloggerpp/Clogger.hpp"

Clog::Clogger::Clogger(std::shared_ptr<Clog::Handler::Base> handl) : handler(handl) {}

void Clog::Clogger::update_handler(std::shared_ptr<Clog::Handler::Base> handl) {
    // this->handler.reset(); // reset value at handler
    // the line beneath decrease the reference to the handler by 1 apperantly and no need for the line aboe
    // testing REQUIRED
    this->handler = handl; // assign new value at handler according to new user handler
}

void Clog::Clogger::set_level(std::pair<int, std::string>& x) {
    this->out_level = x;
}

void Clog::Clogger::set_format(std::string _format) {
    this->format = _format;
}

// AUX Methods for << use
// Special Cases 
Clog::Clogger& operator<<(Clog::Clogger& os, char text) {
    // switch statment would 'probably'(untested) make this slower
    if (text = '0') {
        os.handler->print(os.buffer, os.format, os.level, os.out_level);
        os.buffer = {};
    } else {
        os.buffer.push_back(std::to_string(text));
    }
    return os;
}
 
Clog::Clogger& operator<<(Clog::Clogger& os, std::pair<int, std::string> level) { 
    os.level = level;
    return os;
}

Clog::Clogger& operator<<(Clog::Clogger& os, char* text) { 
    os.buffer.push_back(text);
    return os;
}
Clog::Clogger& operator<<(Clog::Clogger& os, const char* text) {
    os.buffer.push_back(text);
    return os;
}
