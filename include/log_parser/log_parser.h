#ifndef LOG_PARSER_H
#define LOG_PARSER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std; 

class LogParser {

public:

LogParser();

void LoadLogFile(const string& log_file_path, const string& start_time="", const string& end_time="");

vector<pair<string, int>> getWebserverAccessesByHost();

vector<pair<string, int>> getSuccessfulAccessesByURI();


private:

void processLine(const string& line);

vector<pair<string, int>> sortByCount(const unordered_map<string, int>& data);

string log_file_path_;
const string code_OK_;
const string target_request_;

unordered_map<string, int> webserver_accesses_per_host_;
unordered_map<string, int> successful_accesses_by_uri_;


};
#endif // LOG_PARSER_H