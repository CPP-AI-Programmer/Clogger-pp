// STD Includes
#include <iostream>
#include <string>
#include <vector>

// Local Includes
#include "Cloggerpp/Clogger.hpp"

namespace Clog {
    namespace Handler {
        class stdout : public Base {
        public:
            stdout();
            virtual void print(
                const std::vector<std::string>& buffer,
                std::string& format,
                Clog::Level& clvl,
                Clog::Level& olvl
            );
        };
    };
};