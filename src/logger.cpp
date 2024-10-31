#include "logger.h"
#include <iostream>

void Logger::LogOrder(const std::string& jsonResponse){
    try 
    {
        std::cout<<"\n";
        auto json = nlohmann::json::parse(jsonResponse);

        auto order = json["result"]["order"];
        std::cout << "Order Details:\n";
        std::cout << "  Order ID: " << order["order_id"] << "\n";
        std::cout << "  Label: " << order["label"] << "\n";
        std::cout << "  Price: " << order["price"] << "\n";
        std::cout << "  Amount: " << order["amount"] << "\n";
        std::cout << "  Direction: " << order["direction"] << "\n";
        std::cout << "  State: " << order["order_state"] << "\n";
        std::cout << "  Creation Time: " << order["creation_timestamp"] << "\n";
        std::cout << "  Average Price: " << order["average_price"] << "\n";
        std::cout << "  Filled Amount: " << order["filled_amount"] << "\n";
        std::cout << "  Time In Force: " << order["time_in_force"] << "\n";
        std::cout<<"\n";
    } 
    catch (const nlohmann::json::parse_error& e) 
    {
        std::cerr << "JSON parse error: " << e.what() << "\n";
        std::cout<<"\n";
    } 
    catch (const std::exception& e) 
    {
        std::cerr << "Error: " << e.what() << "\n";
        std::cout<<"\n";
    }
}

void Logger::LogCancel(const std::string& jsonResponse){
    std::cout<<"\n";
    auto jsonData = nlohmann::json::parse(jsonResponse);
    if (jsonData.contains("error"))
    {
        std::cout << "Error: " << jsonData["error"]["message"] << " (Code: " 
                  << jsonData["error"]["code"] << ")\n";
        std::cout << "Testnet: " << (jsonData["testnet"] ? "true" : "false") << "\n";
        std::cout << "usIn: " << jsonData["usIn"] << "\n";
        std::cout << "usOut: " << jsonData["usOut"] << "\n";
        std::cout << "usDiff: " << jsonData["usDiff"] << "\n";
        std::cout<<"\n";
    }
    else
    {
        std::cout << "Success! Order ID: " << jsonData["result"]["order_id"] << "\n";
        std::cout << "Triggered: " << (jsonData["result"]["triggered"] ? "true" : "false") << "\n";
        std::cout << "Trigger: " << jsonData["result"]["trigger"] << "\n";
        std::cout << "Time in Force: " << jsonData["result"]["time_in_force"] << "\n";
        std::cout << "Trigger Price: " << jsonData["result"]["trigger_price"] << "\n";
        std::cout << "Order Type: " << jsonData["result"]["order_type"] << "\n";
        std::cout << "Order State: " << jsonData["result"]["order_state"] << "\n";
        std::cout << "Direction: " << jsonData["result"]["direction"] << "\n";
        std::cout << "Creation Timestamp: " << jsonData["result"]["creation_timestamp"] << "\n";
        std::cout << "Amount: " << jsonData["result"]["amount"] << "\n";
        std::cout<<"\n";
    } 
}
void Logger::LogCurrentPositions(const std::string& jsonResponse){
    auto jsonData = nlohmann::json::parse(jsonResponse);
    if (jsonData.is_array() && !jsonData.empty()) {
        std::cout << "Current Positions:\n";
        for (const auto& position : jsonData) {
            std::cout << "  Instrument Name: " << position["instrument_name"] << "\n";
            std::cout << "  Size: " << position["size"] << "\n";
            std::cout << "  Average Price: " << position["average_price"] << "\n";
            std::cout << "  Mark Price: " << position["mark_price"] << "\n";
            std::cout << "  Index Price: " << position["index_price"] << "\n";
            std::cout << "  Estimated Liquidation Price: " << position["estimated_liquidation_price"] << "\n";
            std::cout << "  Floating Profit/Loss: " << position["floating_profit_loss"] << "\n";
            std::cout << "  Realized Profit/Loss: " << position["realized_profit_loss"] << "\n";
            std::cout << "  Total Profit/Loss: " << position["total_profit_loss"] << "\n";
            std::cout << "  Direction: " << position["direction"] << "\n";
            std::cout << "  Leverage: " << position["leverage"] << "\n";
            std::cout << "  Initial Margin: " << position["initial_margin"] << "\n";
            std::cout << "  Maintenance Margin: " << position["maintenance_margin"] << "\n";
            std::cout<<"\n";
        }
    } else {
        std::cout << "No listings to show positions for.\n";
        std::cout<<"\n";
    }
}

void Logger::LogEdit(const std::string& jsonResponse){
    auto jsonData = nlohmann::json::parse(jsonResponse);
    if (jsonData.contains("error")) 
    {
        std::cout << "Error: " << jsonData["error"]["message"] << " (Code: " 
                  << jsonData["error"]["code"] << ")\n";
        std::cout << "Testnet: " << (jsonData["testnet"] ? "true" : "false") << "\n";
        std::cout << "usIn: " << jsonData["usIn"] << "\n";
        std::cout << "usOut: " << jsonData["usOut"] << "\n";
        std::cout << "usDiff: " << jsonData["usDiff"] << "\n";
        std::cout<<"\n";
    }
    else
    {
        const auto& order = jsonData["result"]["order"];
        std::cout << "Success! Order ID: " << order["order_id"] << "\n";
        std::cout << "Time in Force: " << order["time_in_force"] << "\n";
        std::cout << "Price: " << order["price"] << "\n";
        std::cout << "Order Type: " << order["order_type"] << "\n";
        std::cout << "Order State: " << order["order_state"] << "\n";
        std::cout << "Direction: " << order["direction"] << "\n";
        std::cout << "Amount: " << order["amount"] << "\n";
        std::cout << "Filled Amount: " << order["filled_amount"] << "\n";
        std::cout << "Average Price: " << order["average_price"] << "\n";
        std::cout << "Creation Timestamp: " << order["creation_timestamp"] << "\n";
        std::cout << "Last Update Timestamp: " << order["last_update_timestamp"] << "\n";
        std::cout << "Instrument Name: " << order["instrument_name"] << "\n";
        std::cout << "Advanced: " << order["advanced"] << "\n";
        std::cout<<"\n";
    } 
}

void Logger::LogOrderbook(const std::string& jsonResponse){
    auto jsonData = nlohmann::json::parse(jsonResponse);

    std::cout << "Instrument Name: " << jsonData["instrument_name"] << "\n";
    std::cout << "Current State: " << jsonData["state"] << "\n";
    std::cout << "Timestamp: " << jsonData["timestamp"] << "\n";
    std::cout << "Last Price: " << jsonData["last_price"] << "\n";
    std::cout << "Best Bid Price: " << jsonData["best_bid_price"] << " (Amount: " 
              << jsonData["best_bid_amount"] << ")\n";
    std::cout << "Best Ask Price: " << jsonData["best_ask_price"] << " (Amount: " 
              << jsonData["best_ask_amount"] << ")\n";
    std::cout << "Index Price: " << jsonData["index_price"] << "\n";
    std::cout << "Estimated Delivery Price: " << jsonData["estimated_delivery_price"] << "\n";
    std::cout << "Open Interest: " << jsonData["open_interest"] << "\n";
    std::cout << "Funding (8h): " << jsonData["funding_8h"] << "\n";
    std::cout << "Change ID: " << jsonData["change_id"] << "\n";
    
    
    // Display stats
    const auto& stats = jsonData["stats"];
    std::cout << "Stats:\n";
    std::cout << "  High: " << stats["high"] << "\n";
    std::cout << "  Low: " << stats["low"] << "\n";
    std::cout << "  Price Change: " << stats["price_change"] << "\n";
    std::cout << "  Volume: " << stats["volume"] << "\n";
    std::cout << "  Volume Notional: " << stats["volume_notional"] << "\n";
    std::cout << "  Volume USD: " << stats["volume_usd"] << "\n";

    std::cout << "Bids:\n";
    std::cout<<"\n";
    for (const auto& bid : jsonData["bids"]) {
        std::cout << "  Price: " << bid[0] << ", Amount: " << bid[1] << "\n";
        std::cout<<"\n";
    }
    std::cout << "Asks:\n";
    for (const auto& ask : jsonData["asks"]) {
        std::cout << "  Price: " << ask[0] << ", Amount: " << ask[1] << "\n";
        std::cout<<"\n";
    }
}