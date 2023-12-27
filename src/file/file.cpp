#include "Cloggerpp/file/file.hpp"

// ---------------- File Handler ---------------- // 
    Clog::Handler::File::File(std::string& path) {
        this->file.open(path, std::ios::out);
    }
    Clog::Handler::File::~File() {
        this->file.close();
    }
    void Clog::Handler::File::print(
        const std::string& buffer,
        const std::string& format,
        const Clog::User& usr_,
        const Clog::Level& lvl
    ) {
        this->file << usr_.name << '-' << lvl.name << ": ";
        for (auto& text : buffer) {
            this->file << text;
        }
        this->file << '\n';
        this->file.flush();
    }