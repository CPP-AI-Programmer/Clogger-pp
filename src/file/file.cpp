#include "Cloggerpp/file/file.hpp"

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
            this->file.flush();
        }
    }