#include "api_client.h"
#include <curl/curl.h>
#include<iostream>

ApiClient::ApiClient(const std::string& api_key, const std::string& api_secret)
    : api_key_(api_key), api_secret_(api_secret), base_url_("https://test.deribit.com/api/v2") {}

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
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.dump().c_str());
        // Handle response setup here...

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return response;
}
