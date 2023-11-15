// ---------------- Clogger ---------------- //
    template <typename T>
    Clog::Clogger& operator<<(Clog::Clogger& os, std::vector<T>& texts) {
        for (auto& text : texts) {
            os << text;
        }
        return os;
    }

    // Default Cases
    template <typename T>
    Clog::Clogger& operator<<(Clog::Clogger& os, T text) {
        os.buffer.push_back(std::to_string(text));
        return os;
    }

    template <typename T>
    Clog::Clogger& operator<<(Clog::Clogger& os, T* text) {
        os.buffer.push_back(std::to_string(*text));
        return os;
    }