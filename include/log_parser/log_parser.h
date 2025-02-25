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

void getWebserverAccessesByHost();

void getSuccessfulAccessesByURI();


private:

void sortByCountAndPrint(const unordered_map<string, int>& data);

string log_file_path_;
const string code_OK = "200";

unordered_map<string, int> webserver_accesses_per_host_;
unordered_map<string, int> successful_accesses_by_uri_;


};