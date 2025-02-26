#include "log_parser/log_parser.h"

char* getCmdArg(char** begin, char** end, const string& arg){
    char** itr = find(begin, end, arg);
    if(itr != end && ++itr != end){
        return *itr;
    }
    return 0;
}


int main(int argc, char** argv){

    if(argc < 3){
        cerr << "Usage: " << argv[0] << "-f <file_path> [-s <start_time DD:HH:MM:SS> ] [-e <end_time DD:HH:MM:SS>]" << endl;
        return 1;
    }

    LogParser log_parser;

    char* start_time = getCmdArg(argv, argv + argc, "-s");
    if(start_time){
        log_parser.setStartTime(string(start_time));
    }

    char* end_time = getCmdArg(argv, argv + argc, "-e");
    if(end_time){
        log_parser.setEndTime(string(end_time));
    }

    //log_parser.setStartTime("[29:23:55:46]");
    //log_parser.setEndTime("[29:23:57:05]");

    char* file_path = getCmdArg(argv, argv + argc, "-f");
    if(file_path){
        log_parser.LoadLogFile(string(file_path));
    } else {
        cerr << "Invalid file path." << endl;
        return 1;
    }
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