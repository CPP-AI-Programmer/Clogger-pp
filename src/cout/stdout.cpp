#include "Cloggerpp/cout/stdout.hpp"

// ---------------- STD OUTPUT Handler ---------------- // 
    Clog::Handler::stdout::stdout() {}
    void Clog::Handler::stdout::print(
        const std::string& buffer,
        const std::string& format,
        const Clog::User& usr_,
        const Clog::Level& lvl
    ) {
        std::cout << usr_.name << '-' << lvl.name << ": ";
        for (auto& text : buffer) {
            std::cout << text;
        }
        std::cout << std::endl;
    }