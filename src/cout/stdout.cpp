#include "Cloggerpp/cout/stdout.hpp"

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