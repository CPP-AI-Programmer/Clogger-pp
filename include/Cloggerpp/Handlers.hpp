#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

namespace Clog {
    namespace Handler {
        class Base {
        public:
            virtual void print(
                const std::vector<std::string>& buffer,
                std::string& format,
                std::pair<int, std::string>& clvl,
                std::pair<int, std::string>& olvl
            ) = 0;
        };
        class stdout : public Base {
        public:
            stdout();
            virtual void print(
                const std::vector<std::string>& buffer,
                std::string& format,
                std::pair<int, std::string>& clvl,
                std::pair<int, std::string>& olvl
            );
        };
        class File : public Base {
        private:
            std::fstream file;
        public:
            File(std::string& path); // open file
            ~File(); // close file
            virtual void print(
                const std::vector<std::string>& buffer,
                std::string& format,
                std::pair<int, std::string>& clvl,
                std::pair<int, std::string>& olvl
            );

        };
        /*
        Comming soon...
        A Terminal Viewer like nano using ncurses;
        This as you can tell has endless possibilitys like allowing control over parts of your program through TUI,
         Although this should probably be its own repo i included it in here as i think it counts as logging,
         since this could be used for something as simple as help menus or dynamic logging after a critical error,
         and therefore deserves to be in this repo;
        */

        /*
        class TUI : public Base {
        public:
        
        };
        */
    };
};