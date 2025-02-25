#include "log_parser/log_parser.h"

LogParser::LogParser() : log_file_path_(""), code_OK_("200"), target_request_("GET") {
}

void LogParser::LoadLogFile(const string& log_file_path, const string& start_time, const string& end_time) {
    log_file_path_ = log_file_path;
    webserver_accesses_per_host_.clear();
    successful_accesses_by_uri_.clear();
    ifstream log_file_stream(log_file_path_);
    string line;
    while (getline(log_file_stream, line)) {
        processLine(line);
    }
}

void LogParser::processLine(const string& line) {
    istringstream iss(line);
    string host;
    string date_time;
    string request;
    string uri;
    string proto;
    string status;
    string bytes;
    iss >> host >> date_time >> request >> uri >> proto >> status >> bytes;
    if(host.empty()){
        cerr << "Invalid host name." << endl;
        return;
    }
    // Remove quotes from request
    size_t pos = -1;
    while ((pos = request.rfind('\"')) != string::npos) {
        request.erase(pos, 1);
    }
    //cout << host << " " << date_time << " " << request << " " << uri << " " << proto << " " << status << " " << bytes << endl;
    if (false) {
        //TODO check time range
    } else {
        webserver_accesses_per_host_[host]++;
        if (request == target_request_ and status == code_OK_) {
            if(uri.empty()){
                cerr << "Invalid URI." << endl;
                return;
            }
            successful_accesses_by_uri_[uri]++;
        }
    }
}

vector<pair<string, int>>  LogParser::sortByCount(const unordered_map<string, int>& data) {
    // Copy to vector to sort by counts
    vector<pair<string, int>> data_sorted(data.begin(), data.end());
    sort(data_sorted.begin(), data_sorted.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });
    return data_sorted;
}

void LogParser::getWebserverAccessesByHost() {
    auto data = sortByCount(webserver_accesses_per_host_);
    // TODO write output to file ?
    for (const auto& [name, count] : data) {
        cout << name << " " << count << endl;
    }
}

void LogParser::getSuccessfulAccessesByURI() {
    auto data = sortByCount(successful_accesses_by_uri_);
    for (const auto& [name, count] : data) {
        cout << name << " " << count << endl;
    }
}