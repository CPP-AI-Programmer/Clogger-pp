// STD Includes
#include <fstream>
#include <string>
#include <vector>

// Local Includes
#include "Cloggerpp/Clogger.hpp"

namespace Clog {
    namespace Handler {
        class File : public Base {
        private:
            std::fstream file;
        public:
            File(std::string& path); // open file
            ~File(); // close file
            virtual void print(
                const std::vector<std::string>& buffer,
                std::string& format,
                Clog::Level& clvl,
                Clog::Level& olvl
            );
        };
    };
};