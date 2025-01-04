#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

// Structure for supply items
struct Supply {
    std::string name;
    int quantity;
    int priority; // Higher values indicate higher priority
    double cost;  // Cost per unit of the supply in USD

    bool operator<(const Supply& other) const {
        return priority < other.priority; // Sorting by priority in descending order
    }
};

// Function to display supply items
void displaySupplies(const std::vector<Supply>& supplies) {
    std::cout << "\nCurrent Supplies:\n";
    for (const auto& supply : supplies) {
        std::cout << "Item: " << supply.name
                  << ", Quantity: " << supply.quantity
                  << ", Priority: " << supply.priority
                  << ", Cost (in INR): " << (supply.cost * 80) << "\n"; // Convert cost to INR
    }
}

// Function to process requests using priority queue and update storage
void processRequests(std::priority_queue<Supply>& pq, std::vector<Supply>& supplies) {
    double totalCostUSD = 0.0;
    while (!pq.empty()) {
        Supply current = pq.top();
        pq.pop();

        // Search for the item in the available supplies
        bool found = false;
        for (auto& supply : supplies) {
            if (supply.name == current.name) {
                found = true;
                if (supply.quantity >= current.quantity) {
                    supply.quantity -= current.quantity;
                    totalCostUSD += current.quantity * supply.cost;  // Calculate total cost in USD
                    std::cout << "Request for " << current.name << " processed. "
                              << current.quantity << " units provided.\n";
                } else {
                    totalCostUSD += supply.quantity * supply.cost;  // Only charge for available units
                    std::cout << "Not enough " << current.name << " in storage. "
                              << "Only " << supply.quantity << " units available.\n";
                    supply.quantity = 0; // Deplete the stock
                }
                break;
            }
        }

        if (!found) {
            std::cout << "Item " << current.name << " not found in storage.\n";
        }
    }

    // Convert the total cost from USD to INR
    double totalCostINR = totalCostUSD * 80;
    std::cout << "Total cost for the processed requests: " << totalCostINR << "\n";
}

// Main function
int main() {
    std::vector<Supply> supplies = {
        {"Bandages", 50, 3, 1.5},      // $1.5 per bandage
        {"Gloves", 200, 2, 0.5},       // $0.5 per pair of gloves
        {"Masks", 100, 5, 2.0},        // $2.0 per mask
        {"Sanitizers", 80, 4, 3.0}     // $3.0 per sanitizer bottle
    };

    std::cout << "Initial Storage Management:\n";
    displaySupplies(supplies);

    // Sort supplies by priority
    std::sort(supplies.begin(), supplies.end(), [](const Supply& a, const Supply& b) {
        return a.priority > b.priority; // Descending order
    });
    std::cout << "\nSupplies After Sorting by Priority:\n";
    displaySupplies(supplies);

    // Create a priority queue
    std::priority_queue<Supply> pq;

    // Display available supplies before taking user input
    std::cout << "\nAvailable Supplies for Request:\n";
    displaySupplies(supplies);

    // Simulating user input
    std::string itemName;
    int itemQuantity;
    std::cout << "\nEnter the item name for the supply request: ";
    std::cin >> itemName;
    std::cout << "Enter the quantity needed: ";
    std::cin >> itemQuantity;

    // Add user input to priority queue with default priority
    int defaultPriority = 3; // Default priority for simplicity
    pq.push({itemName, itemQuantity, defaultPriority, 0.0}); // Cost will be updated during processing

    std::cout << "\nProcessing Requests in Priority Order:\n";
    processRequests(pq, supplies);

    // Display remaining supplies after processing the request
    std::cout << "\nRemaining Storage After Request:\n";
    displaySupplies(supplies);

    return 0;
}
