#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;

struct Item {
    string name;
    int quantity;
    int criticalLevel;
    int expiryDays; // Days until expiration

    bool operator<(const Item& other) const {
        return expiryDays > other.expiryDays; // Min-heap for expiration
    }
};

class InventoryManagement {
private:
    vector<Item> inventory;
    priority_queue<Item> expirationQueue; // Min-heap for managing expirations

    // Binary search for item lookup
    int findItemIndex(const string& name) const {
        int low = 0, high = inventory.size() - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (inventory[mid].name == name) return mid;
            else if (inventory[mid].name < name) low = mid + 1;
            else high = mid - 1;
        }
        return -1; // Not found
    }

public:
    void addItem(const string& name, int quantity, int criticalLevel, int expiryDays) {
        Item newItem = {name, quantity, criticalLevel, expiryDays};
        inventory.push_back(newItem);
        expirationQueue.push(newItem);
        sort(inventory.begin(), inventory.end(), [](const Item& a, const Item& b) {
            return a.name < b.name; // Maintain alphabetical order for binary search
        });
    }

    void checkItemStatus(const string& name) const {
        int index = findItemIndex(name);
        if (index == -1) {
            cout << "Item not found in inventory.\n";
            return;
        }

        const Item& item = inventory[index];
        cout << "Name: " << item.name
             << ", Quantity: " << item.quantity
             << ", Critical Level: " << item.criticalLevel
             << ", Expiry Days: " << item.expiryDays << "\n";
    }

    void displayDepletedStock() {
        vector<Item> depleted;
        for (const auto& item : inventory) {
            if (item.quantity < item.criticalLevel) {
                depleted.push_back(item);
            }
        }

        // Sort by most critical first (greedy approach)
        sort(depleted.begin(), depleted.end(), [](const Item& a, const Item& b) {
            return (a.criticalLevel - a.quantity) > (b.criticalLevel - b.quantity);
        });

        cout << "\nDepleted Stock Items (prioritized):\n";
        for (const auto& item : depleted) {
            cout << "Name: " << item.name
                 << ", Quantity: " << item.quantity
                 << ", Critical Level: " << item.criticalLevel
                 << ", Shortage: " << (item.criticalLevel - item.quantity) << "\n";
        }
    }

    void handleExpirations() {
        cout << "\nItems near expiration:\n";
        while (!expirationQueue.empty() && expirationQueue.top().expiryDays <= 7) {
            const Item& item = expirationQueue.top();
            cout << "Name: " << item.name
                 << ", Quantity: " << item.quantity
                 << ", Expiry Days: " << item.expiryDays << "\n";
            expirationQueue.pop();
        }
    }

    void manageInventory() {
        int choice;
        do {
            cout << "\nInventory Management Menu:\n";
            cout << "1. Add Item\n";
            cout << "2. Check Item Status\n";
            cout << "3. Display Depleted Stock\n";
            cout << "4. Handle Expirations\n";
            cout << "5. Exit Inventory Management\n";
            cout << "Enter your choice: ";
            cin >> choice;

            string name;
            int quantity, criticalLevel, expiryDays;
            switch (choice) {
                case 1:
                    cout << "Enter item name: ";
                    cin >> name;
                    cout << "Enter quantity: ";
                    cin >> quantity;
                    cout << "Enter critical level: ";
                    cin >> criticalLevel;
                    cout << "Enter expiry days: ";
                    cin >> expiryDays;
                    addItem(name, quantity, criticalLevel, expiryDays);
                    cout << "Item added successfully.\n";
                    break;
                case 2:
                    cout << "Enter item name to check status: ";
                    cin >> name;
                    checkItemStatus(name);
                    break;
                case 3:
                    displayDepletedStock();
                    break;
                case 4:
                    handleExpirations();
                    break;
                case 5:
                    cout << "Exiting Inventory Management...\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 5);
    }
};

// Function to call Inventory Management within a larger menu
void menuDrivenProgram() {
    InventoryManagement inventory;
    inventory.addItem("Paracetamol", 100, 50, 10);
    inventory.addItem("Aspirin", 30, 40, 5);
    inventory.addItem("Ibuprofen", 10, 20, 2);
    inventory.addItem("Amoxicillin", 5, 10, 15);




                inventory.manageInventory();

}

int main() {
    menuDrivenProgram();
    return 0;
}
