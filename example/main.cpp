#include "Cloggerpp/Clogger.hpp" // <- called Cloggerpp because Clogger probably exsists and if it dosen't i will recreate this in pure C

// Pronounced: Clog - er - p - p
// or: Clog - er - plus - plus

int main() {
    // Simple Logger Tests

    // Create Handlers
    auto stdout_handl = std::make_shared<Clog::Handler::stdout>(); // stdout
    std::string file_path = "app.log";
    auto file_handl = std::make_shared<Clog::Handler::File>(file_path); // file

    // Create Logger
    auto logger = Clog::Clogger(stdout_handl);

    // define defaults
    // NOTICE: exit has to be a 'char' otherwise won't work
    // NOTICE: if the exit character is left out it wont print (This might change in the future)
    const char* test = "Hello, World!";
    logger << "Hello, World!" << defstr::nl << defstr::exit; // '0' = termination character 
    logger << Clog::level::NOTICE << " Notice Text" << defstr::exit;

    return 0;
}
