#include "gtest/gtest.h"
#include "log_parser/log_parser.h"

class LogParserTests : public ::testing::Test {
protected:
    LogParser log_parser;
    void SetUp() override {
        log_parser.LoadLogFile("../test/test_log.txt");
    }
};

TEST_F(LogParserTests, shouldContainCorrectNumberOfWebserverCount) {
    auto webserver_accesses = log_parser.getWebserverAccessesByHost();
    string host1 = "host1";
    int host1_count = 2;
    EXPECT_EQ(webserver_accesses[0].first, host1);
    EXPECT_EQ(webserver_accesses[0].second, host1_count);
}

TEST_F(LogParserTests, shouldContainCorrectNumberOfURICount){
    auto uri_accesses = log_parser.getSuccessfulAccessesByURI();
    string uri1 = "/uri3";
    int uri1_count = 3;
    EXPECT_EQ(uri_accesses[0].first, uri1);
    EXPECT_EQ(uri_accesses[0].second, uri1_count);
}

TEST_F(LogParserTests, shouldNotContainPOSTRequests){
    auto uri_accesses = log_parser.getSuccessfulAccessesByURI();
    string uri1 = "/uri2";
    for (const auto& [name, count] : uri_accesses) {
        EXPECT_NE(name, uri1);
    }
}

TEST_F(LogParserTests, shouldNotContainUnsuccessful){
    auto uri_accesses = log_parser.getSuccessfulAccessesByURI();
    string uri1 = "/uri1";
    for (const auto& [name, count] : uri_accesses) {
        EXPECT_NE(name, uri1);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}