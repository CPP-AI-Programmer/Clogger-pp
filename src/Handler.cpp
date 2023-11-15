#include "Cloggerpp/Handlers.hpp"
// ---------------- STD OUTPUT Handler ---------------- // 
    Clog::Handler::stdout::stdout() {}
    void Clog::Handler::stdout::print(
        const std::vector<std::string>& buffer,
        std::string& format,
        std::pair<int, std::string>& clvl,
        std::pair<int, std::string>& olvl
    ) {
        if (clvl.first >= olvl.first) {
            std::cout << clvl.second << ": ";
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
        std::pair<int, std::string>& clvl,
        std::pair<int, std::string>& olvl
    ) {
        if (clvl.first >= olvl.first) {
            this->file << clvl.second << ": ";
            for (auto& text : buffer) {
                this->file << text;
            }
            this->file << '\n';
        }
    }

// ---------------- NCURSES Handler ---------------- // 
    