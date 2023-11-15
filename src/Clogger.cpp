#include "Cloggerpp/Clogger.hpp"

// -------------------------------- Clogger Impl -------------------------------- //
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
            }
        }

    // ---------------- NCURSES Handler ---------------- // 