#include "Cloggerpp/Clogger.hpp" // <- called Cloggerpp because Clogger probably exsists and if it dosen't i will recreate this in pure C

// Pronounced: Clog - er - plus - plus
// or: Clog - er - p - p

int main() {
    // ------------ Logger Init ------------ //
        // Create Handlers
        auto stdout_handl = std::make_shared<Clog::Handler::stdout>(); // stdout
        std::string file_path = "app.log";
        auto file_handl = std::make_shared<Clog::Handler::File>(file_path); // file

        // Create Logger
        auto logger = Clog::Clogger(stdout_handl);

    // ------------ Logging ------------ //
        // define defaults
        // NOTICE: exit has to be a 'char' otherwise won't work
        // NOTICE: if the exit character is left out it wont print (This might change in the future)

        // '0' = termination character | '\n' = new line character
        // Default log level is INFO
        logger << "Hello, World!" << Clog::nl << Clog::nl << Clog::exit; 
        /*
        Output:
        INFO: Hello, World!
        INFO: 
        INFO:
        */
        
        logger << Clog::lvl::NOTICE << "Notice Text" << Clog::exit;
        /*
        Output:
        NOTICE: Notice Text
        */

        logger << Clog::lvl::INFO << "INFO TEXT"; 
        logger << ", More Info Text";
        logger << Clog::exit;
        /*
        Output:
        INFO: INFO TEXT, More Info Text
        */

    // ------------ Logger Settings ------------ //
        // format is not available yet...
        std::string new_format = "FORMAT COMMING SOON...";
        logger.set_format(new_format);
    
        
        // Creating a Custom Level
        Clog::Level custom_level = {0, "CUSTOM_LEVEL"};
        logger.set_level(custom_level);

        // Showing Printing Levels
        // INFO: according to the int level with the (out_level < level ? print)
        logger << Clog::lvl::DEBUG << "Debug Message" << Clog::exit;
        // No Output
        logger.set_level(Clog::lvl::DEBUG);
        logger << Clog::lvl::DEBUG << "Debug Message" << Clog::exit;
        /*
        Output:
        DEBUG: Debug Message
        */

    return 0;
}
