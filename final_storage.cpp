#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Supply {
    std::string name;
    int quantity;
    double cost, storageSpaceRequired;  // Storage space required in square feet
    std::string storageLocation;

    bool operator<(const Supply& other) const {
        return quantity < other.quantity;  // Sorting by quantity for optimization
    }
};

void displayStorage(const std::vector<Supply>& supplies) {
    std::cout << "\nCurrent Storage:\n";
    for (const auto& supply : supplies) {
        std::cout << "Item: " << supply.name << ", Qty: " << supply.quantity
                  << ", Cost: INR " << (supply.cost * 80) << ", Location: " << supply.storageLocation
                  << ", Space: " << supply.storageSpaceRequired << " ft^2\n";
    }
}

void optimizeStorage(std::vector<Supply>& supplies) {
    // Sorting supplies by quantity to optimize storage (greedy approach)
    std::sort(supplies.begin(), supplies.end());
    std::cout << "\nOptimized Storage (sorted by quantity):\n";
    displayStorage(supplies);
}

void checkStorageCapacity(const std::vector<Supply>& supplies, double totalCapacity) {
    double usedCapacity = 0;
    for (const auto& supply : supplies) {
        usedCapacity += supply.storageSpaceRequired;
    }
    std::cout << (usedCapacity > totalCapacity ? "Capacity exceeded!" : "Storage OK.")
              << " Used: " << usedCapacity << " ft^2\n";  // Feet squared
}

void addItem(std::vector<Supply>& storage) {
    Supply newItem;
    std::cout << "\nEnter item details:\n";
    std::cout << "Name: ";
    std::cin >> newItem.name;
    std::cout << "Quantity: ";
    std::cin >> newItem.quantity;
    std::cout << "Cost per unit: ";
    std::cin >> newItem.cost;
    std::cout << "Storage space required (in square feet): ";
    std::cin >> newItem.storageSpaceRequired;
    std::cout << "Storage location: ";
    std::cin >> newItem.storageLocation;

    storage.push_back(newItem);
    std::cout << "Item added successfully!\n";
}

void removeItem(std::vector<Supply>& storage) {
    std::string itemName;
    std::cout << "\nEnter the name of the item to remove: ";
    std::cin >> itemName;

    auto it = std::remove_if(storage.begin(), storage.end(), [&itemName](const Supply& supply) {
        return supply.name == itemName;
    });

    if (it != storage.end()) {
        storage.erase(it, storage.end());
        std::cout << "Item removed successfully!\n";
    } else {
        std::cout << "Item not found.\n";
    }
}

int main() {
    std::vector<Supply> storage = {
        {"Bandages", 50, 1.5, 5.0, "Shelf A1"},  // 5 ft^2 for Bandages
        {"Gloves", 200, 0.5, 4.0, "Shelf B2"},   // 4 ft^2 for Gloves
        {"Masks", 100, 2.0, 6.0, "Shelf C3"},    // 6 ft^2 for Masks
        {"Sanitizers", 80, 3.0, 5.5, "Shelf D4"} // 5.5 ft^2 for Sanitizers
    };

    int choice;
    double totalCapacity = 30.0;  // Total storage capacity available (in square feet)

    do {
        std::cout << "\n\nStorage Management System Menu:\n";
        std::cout << "1. Display Storage\n";
        std::cout << "2. Optimize Storage\n";
        std::cout << "3. Check Storage Capacity\n";
        std::cout << "4. Add Item\n";
        std::cout << "5. Remove Item\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                displayStorage(storage);
                break;
            case 2:
                optimizeStorage(storage);
                break;
            case 3:
                checkStorageCapacity(storage, totalCapacity);
                break;
            case 4:
                addItem(storage);
                break;
            case 5:
                removeItem(storage);
                break;
            case 6:
                std::cout << "Exiting program...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
