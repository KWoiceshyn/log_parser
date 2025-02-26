#include "log_parser/log_parser.h"

LogParser::LogParser() : log_file_path_(""), code_OK_("200"), target_request_("GET") {
}

void LogParser::LoadLogFile(const string& log_file_path) {
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

    if(start_time_){
        tm tm = {};
        stringstream ss(date_time);
        ss >> get_time(&tm, date_log_format_);
        chrono::system_clock::time_point line_time = chrono::system_clock::from_time_t(mktime(&tm));
        if(line_time < *start_time_){
            return;
        }
    }

    if(end_time_){
        tm tm = {};
        stringstream ss(date_time);
        ss >> get_time(&tm, date_log_format_);
        chrono::system_clock::time_point line_time = chrono::system_clock::from_time_t(mktime(&tm));
        if(line_time > *end_time_){
            return;
        }
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

void LogParser::setStartTime(const string& start_time) {
    if(!regex_match(start_time, regex(date_input_rgx_))){
        cerr << "Invalid start time." << endl;
        return;
    }
    tm tm = {};
    stringstream ss(start_time);
    ss >> get_time(&tm, date_input_format_);
    start_time_ = make_unique<chrono::system_clock::time_point>(chrono::system_clock::from_time_t(mktime(&tm)));
}

void LogParser::setEndTime(const string& end_time) {
    if(!regex_match(end_time, regex(date_input_rgx_))){
        cerr << "Invalid end time." << endl;
        return;
    }
    tm tm = {};
    stringstream ss(end_time);
    ss >> get_time(&tm, date_input_format_);
    end_time_ = make_unique<chrono::system_clock::time_point>(chrono::system_clock::from_time_t(mktime(&tm)));
}

vector<pair<string, int>>  LogParser::sortByCount(const unordered_map<string, int>& data) {
    // Copy to vector to sort by counts
    vector<pair<string, int>> data_sorted(data.begin(), data.end());
    sort(data_sorted.begin(), data_sorted.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });
    return data_sorted;
}

vector<pair<string, int>>  LogParser::getWebserverAccessesByHost() {
    return sortByCount(webserver_accesses_per_host_);

}

vector<pair<string, int>> LogParser::getSuccessfulAccessesByURI() {
    return sortByCount(successful_accesses_by_uri_);
}