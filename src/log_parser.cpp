#include "log_parser/log_parser.h"

LogParser::LogParser() {
    log_file_path_ = "";
}

void LogParser::LoadLogFile(const string& log_file_path, const string& start_time, const string& end_time) {
    log_file_path_ = log_file_path;
    webserver_accesses_per_host_.clear();
    successful_accesses_by_uri_.clear();
    ifstream log_file_stream(log_file_path_);
    string line;
    while (getline(log_file_stream, line)) {
        istringstream iss(line);
        string host;
        string date_time;
        string request;
        string uri;
        string proto;
        string status;
        string bytes;
        iss >> host >> date_time >> request >> uri >> proto >> status >> bytes;
        //cout << host << " " << date_time << " " << request << " " << uri << " " << proto << " " << status << " " << bytes << endl;
        if (false) {
            //TODO check time range
        } else {
            webserver_accesses_per_host_[host]++;
            if (request == "\"GET" and status == code_OK) {
                successful_accesses_by_uri_[uri]++;
            }
        }
    }
}

void LogParser::sortByCountAndPrint(const unordered_map<string, int>& data) {
    // Copy to vector to sort by counts
    vector<pair<string, int>> data_sorted(data.begin(), data.end());
    sort(data_sorted.begin(), data_sorted.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });
    // TODO write output to file
    for (const auto& [name, count] : data_sorted) {
        cout << name << " " << count << endl;
    }
}

void LogParser::getWebserverAccessesByHost() {
    sortByCountAndPrint(webserver_accesses_per_host_);
}

void LogParser::getSuccessfulAccessesByURI() {
    sortByCountAndPrint(successful_accesses_by_uri_);
}