#ifndef ORDER_EXECUTION_SYSTEM_ORDER_MANAGER_H_
#define ORDER_EXECUTION_SYSTEM_ORDER_MANAGER_H_

#include <string>
#include "api_client.h"
#include "nlohmann/json.hpp"

enum class OrderType {
    Buy,
    Sell
};


class OrderManager {
 public:
    OrderManager(ApiClient& api_client);
    void PlaceOrder(const std::string& instrument_name, double amount, double price,OrderType order_type);
    bool CancelOrder(const std::string& order_id);
    bool ModifyOrder(const std::string& order_id, double new_price,double amount);
    void GetOrderBook(const std::string& instrument_name,int depth);
    void ViewCurrentPositions();

 private:
    ApiClient& api_client_;
};

#endif  // ORDER_EXECUTION_SYSTEM_ORDER_MANAGER_H_
