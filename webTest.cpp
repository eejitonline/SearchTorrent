#include "includes/httplib.h"
#include <curl/curl.h>
#include <iostream>
#include <string>

static size_t writeMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    std::string& response = *reinterpret_cast<std::string*>(userp);
    size_t totalBytes = size * nmemb;
    response.append(static_cast<const char*>(contents), totalBytes);
    return totalBytes;
}

std::string searchshow(std::string searchparam){
    std::string url = "https://api.themoviedb.org/3/search/tv?query="+searchparam+"&include_adult=false&language=en-US&page=1";

    CURL *hnd = curl_easy_init();

    std::string response;

    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, writeMemoryCallback);
    curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(hnd, CURLOPT_URL, url.c_str());

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "accept: application/json");
    headers = curl_slist_append(headers, "Authorization: Bearer ");
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

    CURLcode ret = curl_easy_perform(hnd);

    return response;
}

int main() {
    using namespace httplib;

    Server svr;

    svr.Get("/:search", [](const Request& req, Response& res){
        auto search = req.path_params.at("search");
        std::string searchRes = searchshow(search);
        std::cout << "recieved";
        std::cout << searchRes;
        
        res.set_content(searchRes, "text/html");
    });
    svr.listen("0.0.0.0", 8080);
}