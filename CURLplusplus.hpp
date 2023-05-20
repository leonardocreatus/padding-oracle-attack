/*
    Based on https://stackoverflow.com/questions/1011339/how-do-you-make-a-http-request-with-c
*/

#ifndef CURLPLUSPLUS_HPP
#define CURLPLUSPLUS_HPP

#include <curl/curl.h>
#include <string>
#include <sstream>

class CURLplusplus
{
private:
    CURL *curl;
    std::stringstream ss;
    long http_code;

public:
    CURLplusplus();
    ~CURLplusplus();
    std::string Get(const std::string &url);
    long GetHttpCode();

private:
    static size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp);
    size_t Write(void *buffer, size_t size, size_t nmemb);
};

#endif // CURLPLUSPLUS_HPP