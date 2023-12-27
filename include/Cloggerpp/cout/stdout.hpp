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
                const std::string& buffer,
                const std::string& format,
                const Clog::User& usr_,
                const Clog::Level& lvl
            );
        };
    };
};