#pragma once
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
namespace fs = std::filesystem;

namespace unspag {
    class Configuration {
        fs::path path;
        auto EvalAndImplode(ostream &out) -> int {
            int result = this->Eval(out);
            delete this;
            return result;
        }
        auto RunCommand(string command, ostream &out) -> int {
            while(command[0] == '\n') command.erase(0, 1);
            if(command[0] == '%') return 0;
            if(command.length() == 0) return 0;
            
            auto firstSpace = command.find_first_of(' ');
            auto commandName = command.substr(0, firstSpace);
            auto param = command.substr(firstSpace + 1);

            if(commandName == "set") {
                out << "export " << param << endl;
            } else if(commandName == "use") {
                fs::path newPath = path;
                newPath.replace_filename(param);
                return (new Configuration(newPath))->EvalAndImplode(out);
            } else if(commandName == "eval") {
                return system(param.c_str());
            } else {
                cerr << "Unknown instruction: " << commandName << endl;
                return 1;
            }
            return 0;
        }

    public:
        Configuration(fs::path path) : path(path) {
            if(!fs::exists(path)) {
                cerr << "Configuration file does not exist: " << path << endl
                     << "Please run `unspag init` to create it." << endl;
                throw 1;
            }
        }

        auto Eval(ostream &out) -> int {
            ifstream stream(this->path);

            string buf;
            
            do {
                getline(stream, buf);

                int result = RunCommand(buf, out);
                if(result != 0) return result;                
            } while(!stream.eof());
            return 0;
        }
    };
}