#ifndef ORDER_EXECUTION_SYSTEM_ORDER_MANAGER_H_
#define ORDER_EXECUTION_SYSTEM_ORDER_MANAGER_H_

#include <string>
#include "api_client.h"
#include <nlohmann/json.hpp>

class OrderManager {
 public:
    OrderManager(ApiClient& api_client);
    
    void PlaceOrder(const std::string& instrument_name, double amount, double price, const std::string& type);

 private:
    ApiClient& api_client_;
};

#endif  // ORDER_EXECUTION_SYSTEM_ORDER_MANAGER_H_
