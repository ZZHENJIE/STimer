#include "core/httpclient.h"
#include <curl/curl.h>
#include <cstring>
#include <map>

struct RequestContext {
    int id;
    CURL* easy;
    std::string url;
    std::string method;
    std::string body;
    Callback callback;
    std::string response_body;
    long response_code;
    std::string error;
};

class HttpClient::Impl {
public:
    CURLM* multi;
    std::map<int, std::unique_ptr<RequestContext>> requests;
    int next_id;

    Impl() : multi(curl_multi_init()), next_id(1) {
        curl_multi_setopt(multi, CURLMOPT_PIPELINING, CURLPIPE_MULTIPLEX);
    }

    ~Impl() {
        for (auto& pair : requests) {
            curl_multi_remove_handle(multi, pair.second->easy);
            curl_easy_cleanup(pair.second->easy);
        }
        curl_multi_cleanup(multi);
    }
};

static size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata) {
    auto* ctx = static_cast<RequestContext*>(userdata);
    ctx->response_body.append(ptr, size * nmemb);
    return size * nmemb;
}

static CURL* setup_easy(CURL* easy, const std::string& url) {
    curl_easy_setopt(easy, CURLOPT_URL, url.c_str());
    curl_easy_setopt(easy, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(easy, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(easy, CURLOPT_TIMEOUT, 30L);
    curl_easy_setopt(easy, CURLOPT_CONNECTTIMEOUT, 10L);
    return easy;
}

Request HttpClient::get(const std::string& url, Callback callback) {
    Request req;
    req.id = pImpl->next_id++;
    req.user_data = nullptr;

    auto ctx = std::make_unique<RequestContext>();
    ctx->id = req.id;
    ctx->url = url;
    ctx->method = "GET";
    ctx->body = "";
    ctx->callback = std::move(callback);
    ctx->response_code = 0;

    ctx->easy = curl_easy_init();
    setup_easy(ctx->easy, url);
    curl_easy_setopt(ctx->easy, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(ctx->easy, CURLOPT_WRITEDATA, ctx.get());
    curl_easy_setopt(ctx->easy, CURLOPT_PRIVATE, ctx.get());

    curl_multi_add_handle(pImpl->multi, ctx->easy);
    pImpl->requests[ctx->id] = std::move(ctx);

    return req;
}

Request HttpClient::post(const std::string& url, const std::string& data, Callback callback) {
    Request req;
    req.id = pImpl->next_id++;
    req.user_data = nullptr;

    auto ctx = std::make_unique<RequestContext>();
    ctx->id = req.id;
    ctx->url = url;
    ctx->method = "POST";
    ctx->body = data;
    ctx->callback = std::move(callback);
    ctx->response_code = 0;

    ctx->easy = curl_easy_init();
    setup_easy(ctx->easy, url);
    curl_easy_setopt(ctx->easy, CURLOPT_POST, 1L);
    curl_easy_setopt(ctx->easy, CURLOPT_POSTFIELDS, ctx->body.c_str());
    curl_easy_setopt(ctx->easy, CURLOPT_WRITEDATA, ctx.get());
    curl_easy_setopt(ctx->easy, CURLOPT_PRIVATE, ctx.get());

    curl_multi_add_handle(pImpl->multi, ctx->easy);
    pImpl->requests[ctx->id] = std::move(ctx);

    return req;
}

Request HttpClient::put(const std::string& url, const std::string& data, Callback callback) {
    Request req;
    req.id = pImpl->next_id++;
    req.user_data = nullptr;

    auto ctx = std::make_unique<RequestContext>();
    ctx->id = req.id;
    ctx->url = url;
    ctx->method = "PUT";
    ctx->body = data;
    ctx->callback = std::move(callback);
    ctx->response_code = 0;

    ctx->easy = curl_easy_init();
    setup_easy(ctx->easy, url);
    curl_easy_setopt(ctx->easy, CURLOPT_CUSTOMREQUEST, "PUT");
    curl_easy_setopt(ctx->easy, CURLOPT_POSTFIELDS, ctx->body.c_str());
    curl_easy_setopt(ctx->easy, CURLOPT_WRITEDATA, ctx.get());
    curl_easy_setopt(ctx->easy, CURLOPT_PRIVATE, ctx.get());

    curl_multi_add_handle(pImpl->multi, ctx->easy);
    pImpl->requests[ctx->id] = std::move(ctx);

    return req;
}

Request HttpClient::del(const std::string& url, Callback callback) {
    Request req;
    req.id = pImpl->next_id++;
    req.user_data = nullptr;

    auto ctx = std::make_unique<RequestContext>();
    ctx->id = req.id;
    ctx->url = url;
    ctx->method = "DELETE";
    ctx->body = "";
    ctx->callback = std::move(callback);
    ctx->response_code = 0;

    ctx->easy = curl_easy_init();
    setup_easy(ctx->easy, url);
    curl_easy_setopt(ctx->easy, CURLOPT_CUSTOMREQUEST, "DELETE");
    curl_easy_setopt(ctx->easy, CURLOPT_WRITEDATA, ctx.get());
    curl_easy_setopt(ctx->easy, CURLOPT_PRIVATE, ctx.get());

    curl_multi_add_handle(pImpl->multi, ctx->easy);
    pImpl->requests[ctx->id] = std::move(ctx);

    return req;
}

Request HttpClient::patch(const std::string& url, const std::string& data, Callback callback) {
    Request req;
    req.id = pImpl->next_id++;
    req.user_data = nullptr;

    auto ctx = std::make_unique<RequestContext>();
    ctx->id = req.id;
    ctx->url = url;
    ctx->method = "PATCH";
    ctx->body = data;
    ctx->callback = std::move(callback);
    ctx->response_code = 0;

    ctx->easy = curl_easy_init();
    setup_easy(ctx->easy, url);
    curl_easy_setopt(ctx->easy, CURLOPT_CUSTOMREQUEST, "PATCH");
    curl_easy_setopt(ctx->easy, CURLOPT_POSTFIELDS, ctx->body.c_str());
    curl_easy_setopt(ctx->easy, CURLOPT_WRITEDATA, ctx.get());
    curl_easy_setopt(ctx->easy, CURLOPT_PRIVATE, ctx.get());

    curl_multi_add_handle(pImpl->multi, ctx->easy);
    pImpl->requests[ctx->id] = std::move(ctx);

    return req;
}

Request HttpClient::head(const std::string& url, Callback callback) {
    Request req;
    req.id = pImpl->next_id++;
    req.user_data = nullptr;

    auto ctx = std::make_unique<RequestContext>();
    ctx->id = req.id;
    ctx->url = url;
    ctx->method = "HEAD";
    ctx->body = "";
    ctx->callback = std::move(callback);
    ctx->response_code = 0;

    ctx->easy = curl_easy_init();
    setup_easy(ctx->easy, url);
    curl_easy_setopt(ctx->easy, CURLOPT_NOBODY, 1L);
    curl_easy_setopt(ctx->easy, CURLOPT_WRITEDATA, ctx.get());
    curl_easy_setopt(ctx->easy, CURLOPT_PRIVATE, ctx.get());

    curl_multi_add_handle(pImpl->multi, ctx->easy);
    pImpl->requests[ctx->id] = std::move(ctx);

    return req;
}

Request HttpClient::options(const std::string& url, Callback callback) {
    Request req;
    req.id = pImpl->next_id++;
    req.user_data = nullptr;

    auto ctx = std::make_unique<RequestContext>();
    ctx->id = req.id;
    ctx->url = url;
    ctx->method = "OPTIONS";
    ctx->body = "";
    ctx->callback = std::move(callback);
    ctx->response_code = 0;

    ctx->easy = curl_easy_init();
    setup_easy(ctx->easy, url);
    curl_easy_setopt(ctx->easy, CURLOPT_CUSTOMREQUEST, "OPTIONS");
    curl_easy_setopt(ctx->easy, CURLOPT_WRITEDATA, ctx.get());
    curl_easy_setopt(ctx->easy, CURLOPT_PRIVATE, ctx.get());

    curl_multi_add_handle(pImpl->multi, ctx->easy);
    pImpl->requests[ctx->id] = std::move(ctx);

    return req;
}

void HttpClient::remove(Request& req) {
    auto it = pImpl->requests.find(req.id);
    if (it != pImpl->requests.end()) {
        curl_multi_remove_handle(pImpl->multi, it->second->easy);
        curl_easy_cleanup(it->second->easy);
        pImpl->requests.erase(it);
    }
}

void HttpClient::poll() {
    int running = 0;
    CURLMcode rc = curl_multi_perform(pImpl->multi, &running);
    if (rc != CURLM_OK) {
        return;
    }

    int msgs_in_queue = 0;
    CURLMsg* msg = nullptr;
    while ((msg = curl_multi_info_read(pImpl->multi, &msgs_in_queue))) {
        if (msg->msg == CURLMSG_DONE) {
            CURL* easy = msg->easy_handle;
            RequestContext* ctx = nullptr;
            curl_easy_getinfo(easy, CURLINFO_PRIVATE, &ctx);

            if (ctx) {
                curl_easy_getinfo(easy, CURLINFO_RESPONSE_CODE, &ctx->response_code);

                Response res;
                res.id = ctx->id;
                res.code = static_cast<int>(ctx->response_code);
                res.body = std::move(ctx->response_body);
                res.error = (msg->data.result != CURLE_OK) ? curl_easy_strerror(msg->data.result) : "";

                if (ctx->callback) {
                    ctx->callback(res);
                }

                curl_multi_remove_handle(pImpl->multi, easy);
                pImpl->requests.erase(ctx->id);
            }
        }
    }
}

HttpClient::HttpClient() : pImpl(std::make_unique<Impl>()) {}

HttpClient::~HttpClient() = default;

int HttpClient::getActiveCount() {
    int running = 0;
    curl_multi_socket_action(pImpl->multi, CURL_SOCKET_TIMEOUT, 0, &running);
    return running;
}

HttpClient& HttpClient::instance() {
    static HttpClient client;
    return client;
}