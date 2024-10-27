#include <iostream>
#include <cstdlib>
#include "api_client.h"
#include "order_manager.h"

int main() {
    const char* api_key = std::getenv("DERIBIT_API_KEY");
    const char* api_secret = std::getenv("DERIBIT_API_SECRET");

    if (!api_key || !api_secret) {
        std::cerr << "Error: API key or secret not set in environment variables." << std::endl;
        return 1;

    ApiClient api_client(api_key, api_secret);
    OrderManager order_manager(api_client);

    order_manager.PlaceOrder("BTC-PERPETUAL", 1, 30000, "limit");

    return 0;
}
