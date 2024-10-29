#include "api_client.h"
#include <curl/curl.h>
#include<iostream>

ApiClient::ApiClient(const std::string& client_id, const std::string& client_secret)
    : client_id_(client_id), client_secret_(client_secret), base_url_("https://test.deribit.com/api/v2") {
        InitializeClient();
    }


size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    size_t totalSize = size * nmemb;
    userp->append((char*)contents, totalSize); 
    return totalSize;

}

/**
 * @brief Makes a request to the Deribit API.
 * @param endpoint The API endpoint to call.
 * @param data The JSON data to send in the request.
 * @return The response from the API.
 */

std::string ApiClient::MakeRequest(const std::string& endpoint, const nlohmann::json& data) {
    CURL* curl;
    CURLcode res;
    std::string response;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, (base_url_ + endpoint).c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.dump().c_str());
        
        //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);  //For debugging

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        std::string auth_header;
        if(!access_token.empty()) auth_header="Bearer "+ access_token;
        if(!access_token.empty()) headers = curl_slist_append(headers, ("Authorization: "+ auth_header).c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }
    return response;
}

void ApiClient::InitializeClient(){
    std::string endpoint="/public/auth?client_id=" + client_id_ + "&client_secret=" + client_secret_ + "&grant_type=client_credentials";
    nlohmann::json auth_data = {
        {"jsonrpc", "2.0"},
        {"id", 1},
    };
    //std::cout << "Request JSON: " << auth_data.dump(4) << std::endl;
    std::string response=MakeRequest(endpoint,auth_data);
    //std::cout<<response<<std::endl;  //for debugging
    nlohmann::json jsonData = nlohmann::json::parse(response);
    std::map<std::string, std::string> dataMap;
    for (auto& [key, value] : jsonData.items()) {
        dataMap[key] = value.dump();
    }
    nlohmann::json result=nlohmann::json::parse(dataMap["result"]);
    for (auto& [key, value] : result.items()) {
        dataMap[key] = value.dump();
    }
    std::string temp=dataMap["access_token"];
    auto len=temp.length();
    this->access_token=temp.substr(1,len-2);
    //std::cout<<access_token<<std::endl;  //for debugging
}