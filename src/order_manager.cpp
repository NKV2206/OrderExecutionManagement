#include "order_manager.h"
#include <iostream>

OrderManager::OrderManager(ApiClient& api_client) : api_client_(api_client) {}
/**
 * @brief Makes a request to the Deribit API to Place Buy/Sell Orders
 * @param instrument_name Name of the instrument that is to be ordered
 * @param amount  Amount of the instrument to buy
 * @param price Price of the instrument to buy
 * @param order_type Type of the Order ie; Buy/Sell
 * @return Logs the result of the attempt to place an order
 */
void OrderManager::PlaceOrder(const std::string& instrument_name, double amount, double price,OrderType order_type) {
    std::string endpoint;
    if(order_type==OrderType::Buy){
        endpoint="/private/buy";
    }
    else{
        endpoint="/private/sell";
    }
    nlohmann::json order_data = {
        {"jsonrpc", "2.0"},
        {"id", 1},
        {"method", endpoint},
    };
    endpoint=endpoint + "?amount=" + std::to_string(amount)+"&instrument_name="+ instrument_name+"&price="+std::to_string(price)+"&label=market0000234&type=market";

    std::string result = api_client_.MakeRequest(endpoint, order_data);
    std::cout << "Order Response: " << result << std::endl;  //For Debugging
}

/**
 * @brief Makes a request to the Deribit API to Cancel Orders
 * @param order_id  Id of the order to be cancelled 
 * @return Logs the response for the attempt to cancel order with a given order id
 */
bool OrderManager::CancelOrder(const std::string& order_id){
    std::string endpoint="/private/cancel";
    nlohmann::json cancel_data = {
        {"jsonrpc", "2.0"},
        {"id", 1},
        {"method", endpoint},
    };
    endpoint=endpoint + "?order_id="+ order_id;
    std::string result = api_client_.MakeRequest(endpoint, cancel_data);
    nlohmann::json jsonData=nlohmann::json::parse(result);
    std::map<std::string, std::string> dataMap;
    for (auto& [key, value] : jsonData.items()) {
        dataMap[key] = value.dump();
    }
    std::cout << "Order Response: " << result << std::endl;  //For Debugging
    if(!dataMap["result"].empty()) return true;
    return false;
}
/**
 * @brief Makes a request to the Deribit API to Cancel Orders
 * @param order_id  Id of the order to be modified
 * @param new_price The new price for the instrument
 * @param amount The new amount for the order
 * @return Logs the response for the attempt to modify order with a given order id
 */
bool OrderManager::ModifyOrder(const std::string& order_id,double new_price,double amount){
    std::string endpoint="/private/edit";
    nlohmann::json modify_data = {
        {"jsonrpc", "2.0"},
        {"id", 1},
        {"method", endpoint},
    };
    endpoint=endpoint + "?advanced=implv&amount="+std::to_string(amount)+"&order_id="+ order_id+"&price="+std::to_string(new_price);
    std::string result = api_client_.MakeRequest(endpoint, modify_data);
    
    nlohmann::json jsonData=nlohmann::json::parse(result);
    std::map<std::string, std::string> dataMap;
    for (auto& [key, value] : jsonData.items()) {
        dataMap[key] = value.dump();
    }

    std::cout<<"Modify Response : "<<result<<std::endl;  // For Debugging

    if(dataMap.find("result")==dataMap.end()) return false;
    nlohmann::json order=nlohmann::json::parse(dataMap["result"]);
    for (auto& [key, value] : order.items()) {
        dataMap[key] = value.dump();
    }
    if(!dataMap["order"].empty()) return true;
    return false;
}
/**
 * @brief Makes a request to the Deribit API to view Order Books of different Instruments
 * @param instrument_name The name of the instrument whose order book has to be fetched 
 * @param depth The number of entries of the order book to list out 
 * @return Logs the order book response for the given instrument with a given depth 
 */
void OrderManager::GetOrderBook(const std::string& instrument_name,int depth){
    std::string endpoint="/public/get_order_book";
    nlohmann::json book_data = {
        {"jsonrpc", "2.0"},
        {"id", 1},
        {"method", endpoint},
    };
    endpoint=endpoint+"?depth="+std::to_string(depth)+"&instrument_name="+instrument_name;
    std::string result = api_client_.MakeRequest(endpoint, book_data);
    nlohmann::json jsonData=nlohmann::json::parse(result);
    std::map<std::string, std::string> dataMap;
    for (auto& [key, value] : jsonData.items()) {
        dataMap[key] = value.dump();
    }
    // std::cout<<result<<std::endl;    
   
    if(dataMap.find("result")!=dataMap.end()) std::cout<<dataMap["result"]<<std::endl;
    return;
}
/**
 * @brief Makes a request to the Deribit API to view Current Positions of the User 
 * @return Logs the Data Containing the current positions
 */
void OrderManager::ViewCurrentPositions(){
    std::string endpoint="/private/get_positions";
    nlohmann::json positions_data = {
        {"jsonrpc", "2.0"},
        {"id", 1},
        {"method", endpoint},
    };
    std::string result = api_client_.MakeRequest(endpoint, positions_data);
    nlohmann::json jsonData=nlohmann::json::parse(result);
    std::map<std::string, std::string> dataMap;
    for (auto& [key, value] : jsonData.items()) {
        dataMap[key] = value.dump();
    }
    std::cout<<dataMap["result"]<<std::endl;
    return;
}