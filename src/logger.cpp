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
    nlohmann::json jsonData;

    try {
        jsonData = nlohmann::json::parse(jsonResponse);
    } catch (const nlohmann::json::exception& e) {
        std::cerr << "Failed to parse JSON: " << e.what() << std::endl;
        return;
    }
    if (!jsonData.contains("result")) {
        std::cerr << "Error: 'result' key not found in JSON." << std::endl;
        return;
    }

    const auto& positions = jsonData["result"];

    for (const auto& position : positions) {
        std::cout << "Position Details:\n";
        std::cout << "  Instrument Name: " << position.value("instrument_name", "Unknown") << "\n";
        std::cout << "  Direction: " << position.value("direction", "Unknown") << "\n";
        std::cout << "  Size: " << position.value("size", 0.0) << "\n";
        std::cout << "  Average Price: " << position.value("average_price", 0.0) << "\n";
        std::cout << "  Index Price: " << position.value("index_price", 0.0) << "\n";
        std::cout << "  Mark Price: " << position.value("mark_price", 0.0) << "\n";
        std::cout << "  Settlement Price: " << position.value("settlement_price", 0.0) << "\n";
        std::cout << "  Maintenance Margin: " << position.value("maintenance_margin", 0.0) << "\n";
        std::cout << "  Initial Margin: " << position.value("initial_margin", 0.0) << "\n";
        std::cout << "  Floating Profit/Loss: " << position.value("floating_profit_loss", 0.0) << "\n";
        std::cout << "  Realized Profit/Loss: " << position.value("realized_profit_loss", 0.0) << "\n";
        std::cout << "  Total Profit/Loss: " << position.value("total_profit_loss", 0.0) << "\n";
        std::cout << "  Estimated Liquidation Price: " << position.value("estimated_liquidation_price", 0.0) << "\n";
        std::cout << "  Leverage: " << position.value("leverage", 1.0) << "\n";
        std::cout << "  Size Currency: " << position.value("size_currency", 0.0) << "\n";
        std::cout << "  Interest Value: " << position.value("interest_value", 0.0) << "\n";
        std::cout << "  Delta: " << position.value("delta", 0.0) << "\n";
        std::cout << "  Realized Funding: " << position.value("realized_funding", 0.0) << "\n";
        std::cout << "  Open Orders Margin: " << position.value("open_orders_margin", 0.0) << "\n";
        std::cout << "\n"; 
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
    nlohmann::json jsonData;

    try {
        jsonData = nlohmann::json::parse(jsonResponse);
    } catch (const nlohmann::json::exception& e) {
        std::cerr << "Failed to parse JSON: " << e.what() << std::endl;
        return;
    }

    if (!jsonData.contains("result")) {
        std::cerr << "Error: 'result' key not found in JSON." << std::endl;
        return;
    }

    const auto& result = jsonData["result"];

    std::cout << "Instrument Name: " << result.value("instrument_name", "Unknown") << "\n";
    std::cout << "Current State: " << result.value("state", "Unknown") << "\n";
    std::cout << "Timestamp: " << result.value("timestamp", 0) << "\n";
    std::cout << "Last Price: " << result.value("last_price", 0.0) << "\n";
    std::cout << "Best Bid Price: " << result.value("best_bid_price", 0.0) << " (Amount: " 
              << result.value("best_bid_amount", 0.0) << ")\n";
    std::cout << "Best Ask Price: " << result.value("best_ask_price", 0.0) << " (Amount: " 
              << result.value("best_ask_amount", 0.0) << ")\n";
    std::cout << "Index Price: " << result.value("index_price", 0.0) << "\n";
    std::cout << "Settlement Price: " << result.value("settlement_price", 0.0) << "\n";
    std::cout << "Open Interest: " << result.value("open_interest", 0.0) << "\n";
    std::cout << "Funding (8h): " << result.value("funding_8h", 0.0) << "\n";
    std::cout << "Change ID: " << result.value("change_id", 0) << "\n";
    

    const auto& stats = result.value("stats", nlohmann::json::object());
    std::cout << "Stats:\n";
    std::cout << "  High: " << stats.value("high", 0.0) << "\n";
    std::cout << "  Low: " << stats.value("low", 0.0) << "\n";
    std::cout << "  Price Change: " << stats.value("price_change", 0.0) << "\n";
    std::cout << "  Volume: " << stats.value("volume", 0.0) << "\n";
    std::cout << "  Volume USD: " << stats.value("volume_usd", 0.0) << "\n";
    std::cout << "  Volume Notional: " << stats.value("volume_notional", 0.0) << "\n";


    std::cout << "Bids:\n";
    if (result.contains("bids")) {
        for (const auto& bid : result["bids"]) {
            std::cout << "  Price: " << bid.at(0).get<double>() << ", Amount: " << bid.at(1).get<double>() << "\n";
        }
    } else {
        std::cout << "  No bids available.\n";
    }

    std::cout << "Asks:\n";
    if (result.contains("asks")) {
        for (const auto& ask : result["asks"]) {
            std::cout << "  Price: " << ask.at(0).get<double>() << ", Amount: " << ask.at(1).get<double>() << "\n";
        }
    } else {
        std::cout << "  No asks available.\n";
    }
}