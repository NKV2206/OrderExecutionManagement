#include "order_manager.h"
#include <iostream>

OrderManager::OrderManager(ApiClient& api_client) : api_client_(api_client) {}

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