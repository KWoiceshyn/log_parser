#include "log_parser/log_parser.h"


int main(int argc, char** argv){

    if(argc < 3){
        cerr << "Usage: " << argv[0] << "--file <file_path>" << endl;
        return 1;
    }

    LogParser log_parser;
    log_parser.LoadLogFile(string(argv[2]));
    cout << endl;
    log_parser.getWebserverAccessesByHost();
    cout << endl;
    log_parser.getSuccessfulAccessesByURI();

    return 0;
}