#include <iostream>
#include <cstdlib>
#include "api_client.h"
#include "order_manager.h"

int main() {
    const char* client_id = std::getenv("DERIBIT_CLIENT_ID");
    const char* client_secret = std::getenv("DERIBIT_CLIENT_SECRET");

    if (!client_id || !client_secret) {
        std::cerr << "Error: API key or secret not set in environment variables." << std::endl;
        return 1;
    }
    ApiClient api_client(client_id, client_secret);
    OrderManager order_manager(api_client);

    //order_manager.PlaceOrder("ETH-PERPETUAL", 5000000, 160,OrderType::Buy);
    //order_manager.CancelOrder("ETH-14417143873");
    //order_manager.ModifyOrder("ETH-14417143873",4000,23000);
    //order_manager.GetOrderBook("BTC-PERPETUAL",10);
    //order_manager.ViewCurrentPositions();

    return 0;
}
