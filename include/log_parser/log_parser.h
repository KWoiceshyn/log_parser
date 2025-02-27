#ifndef LOG_PARSER_H
#define LOG_PARSER_H

#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class LogParser {

public:
  LogParser();

  void LoadLogFile(const string &log_file_path);

  vector<pair<string, int>> getWebserverAccessesByHost();

  vector<pair<string, int>> getSuccessfulAccessesByURI();

  void setStartTime(const string &start_time);
  void setEndTime(const string &end_time);

private:
  void processLine(const string &line);

  vector<pair<string, int>> sortByCount(const unordered_map<string, int> &data);

  string log_file_path_;
  const string code_OK_;
  const string target_request_;

  unordered_map<string, int> webserver_accesses_per_host_;
  unordered_map<string, int> successful_accesses_by_uri_;

  unique_ptr<chrono::system_clock::time_point> start_time_;
  unique_ptr<chrono::system_clock::time_point> end_time_;

  const string date_input_rgx_ = "\\d{2}:\\d{2}:\\d{2}:\\d{2}";
  const char *date_input_format_ = "%d:%H:%M:%S";
  const char *date_log_format_ = "[%d:%H:%M:%S]";
};
#endif // LOG_PARSER_H