#ifndef ORDER_EXECUTION_SYSTEM_API_CLIENT_H_
#define ORDER_EXECUTION_SYSTEM_API_CLIENT_H_

#include <string>
#include "nlohmann/json.hpp"
/**
 * @brief A client for interacting with the Deribit API.
 */
class ApiClient {
 public:
   ApiClient(const std::string& client_id, const std::string& client_secret);

   std::string MakeRequest(const std::string& endpoint, const nlohmann::json& data);

 private:
    std::string client_id_;
    std::string client_secret_;
    std::string base_url_;
    std::string access_token;
    void InitializeClient();
};

#endif  // ORDER_EXECUTION_SYSTEM_API_CLIENT_H_
