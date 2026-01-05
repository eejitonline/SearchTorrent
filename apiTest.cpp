#include <curl/curl.h>
#include <iostream>
#include <string>

CURLcode searchshow(std::string searchparam){
    std::string url = "https://api.themoviedb.org/3/search/tv?query="+searchparam+"&include_adult=false&language=en-US&page=1";

    CURL *hnd = curl_easy_init();

    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(hnd, CURLOPT_WRITEDATA, stdout);
    curl_easy_setopt(hnd, CURLOPT_URL, url.c_str());

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "accept: application/json");
    headers = curl_slist_append(headers, "Authorization: Bearer");
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

    CURLcode ret = curl_easy_perform(hnd);

    return ret;
}

int main(void){
    std::cout << searchshow("community");
}

