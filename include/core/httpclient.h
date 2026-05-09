#pragma once

#include <string>
#include <functional>
#include <memory>

struct Response {
    int id;
    int code;
    std::string body;
    std::string error;
};

using Callback = std::function<void(Response)>;

struct Request {
    int id;
    void* user_data;
};

class HttpClient {
private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;

    HttpClient();
    ~HttpClient();

public:

    Request get(const std::string& url, Callback callback);
    Request post(const std::string& url, const std::string& data, Callback callback);
    Request put(const std::string& url, const std::string& data, Callback callback);
    Request del(const std::string& url, Callback callback);
    Request patch(const std::string& url, const std::string& data, Callback callback);
    Request head(const std::string& url, Callback callback);
    Request options(const std::string& url, Callback callback);
    void remove(Request& req);
    void poll();

    int getActiveCount();

    static HttpClient& instance();
};