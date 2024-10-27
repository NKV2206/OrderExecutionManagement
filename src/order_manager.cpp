#include "order_manager.h"
#include <iostream>

OrderManager::OrderManager(ApiClient& api_client) : api_client_(api_client) {}

void OrderManager::PlaceOrder(const std::string& instrument_name, double amount, double price, const std::string& type) {
    nlohmann::json order_data = {
        {"jsonrpc", "2.0"},
        {"id", 1},
        {"method", "private/buy"},
        {"params", {
            {"instrument_name", instrument_name},
            {"amount", amount},
            {"price", price},
            {"type", type}
        }}
    };

    std::string result = api_client_.MakeRequest("/private/buy", order_data);
    std::cout << "Order Response: " << result << std::endl;
}
