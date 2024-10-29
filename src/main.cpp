#include <iostream>
#include <cstdlib>
#include "api_client.h"
#include "order_manager.h"

void DisplayMenu() {
    std::cout << "Order Execution and Management System\n";
    std::cout << "1. Place Order\n";
    std::cout << "2. Cancel Order\n";
    std::cout << "3. Modify Order\n";
    std::cout << "4. Get Order Book\n";
    std::cout << "5. View Current Positions\n";
    std::cout << "0. Exit\n";
    std::cout << "Select an option: ";
}

int main() {
    const char* client_id = std::getenv("DERIBIT_CLIENT_ID");
    const char* client_secret = std::getenv("DERIBIT_CLIENT_SECRET");

    if (!client_id || !client_secret) {
        std::cerr << "Error: API key or secret not set in environment variables." << std::endl;
        return 1;
    }
    ApiClient api_client(client_id, client_secret);
    OrderManager order_manager(api_client);
    
    int choice;
    while (true) {
        DisplayMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                std::string instrument;
                double price;
                double amount;
                std::cout << "Enter instrument (e.g., ETH-PERPETUAL): ";
                std::cin >> instrument;
                std::cout << "Enter amount: ";
                std::cin >> amount;
                std::cout << "Enter price: ";
                std::cin >> price;
                order_manager.PlaceOrder(instrument, amount, price, OrderType::Buy);
                break;
            }
            case 2: {
                std::string order_id;
                std::cout << "Enter order ID to cancel: ";
                std::cin >> order_id;
                order_manager.CancelOrder(order_id);
                break;
            }
            case 3: {
                std::string order_id;
                double new_amount, new_price;
                std::cout << "Enter order ID to modify: ";
                std::cin >> order_id;
                std::cout << "Enter new amount: ";
                std::cin >> new_amount;
                std::cout << "Enter new price: ";
                std::cin >> new_price;
                order_manager.ModifyOrder(order_id, new_amount, new_price);
                break;
            }
            case 4: {
                std::string instrument;
                int depth;
                std::cout << "Enter instrument (e.g., BTC-PERPETUAL): ";
                std::cin >> instrument;
                std::cout << "Enter depth: ";
                std::cin >> depth;
                order_manager.GetOrderBook(instrument, depth);
                break;
            }
            case 5: {
                order_manager.ViewCurrentPositions();
                break;
            }
            case 0:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please select a valid option.\n";
        }
    }

    return 0;
}
