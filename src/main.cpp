#include "log_parser/log_parser.h"


int main(int argc, char** argv){

    if(argc < 3){
        cerr << "Usage: " << argv[0] << "--file <file_path>" << endl;
        return 1;
    }

    LogParser log_parser;
    log_parser.LoadLogFile(string(argv[2]));
    auto webserver_accesses = log_parser.getWebserverAccessesByHost();
    auto uri_accesses = log_parser.getSuccessfulAccessesByURI();

    // TODO write output to file ?
    for (const auto& [name, count] : webserver_accesses) {
        cout << name << " " << count << endl;
    }
    cout << endl;
    
    for (const auto& [name, count] : uri_accesses) {
        cout << name << " " << count << endl;
    }
    

    return 0;
}