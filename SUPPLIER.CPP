#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Supplier {
public:
    string name;
    int cost;  // Rating on a scale of 1 to 10 (1 = highest cost, 10 = lowest cost)
    int quality;  // Rating on a scale of 1 to 10 (1 = lowest quality, 10 = highest quality)
    int deliveryTime;  // Rating on a scale of 1 to 10 (1 = longest time, 10 = quickest time)

    Supplier(string name, int cost, int quality, int deliveryTime) {
        this->name = name;
        this->cost = cost;
        this->quality = quality;
        this->deliveryTime = deliveryTime;
    }

    // Make this method const since it doesn't modify the object state
    double calculateScore(double costWeight, double qualityWeight, double deliveryWeight) const {
        return (cost * costWeight) + (quality * qualityWeight) + (deliveryTime * deliveryWeight);
    }
};

int main() {
    vector<Supplier> suppliers;

    // Input data for suppliers: name, cost, quality, delivery time
    suppliers.push_back(Supplier("HealthEquip", 8, 9, 7)); // Example values for HealthEquip
    suppliers.push_back(Supplier("MedSupplyCo", 7, 8, 6)); // Example values for MedSupplyCo
    suppliers.push_back(Supplier("MediTech", 6, 7, 5)); // Example values for MediTech

    // Weights for cost, quality, and delivery time
    double costWeight = 0.5;
    double qualityWeight = 0.3;
    double deliveryWeight = 0.2;

    // Display header
    cout << "Supplier Selection Results:\n";
    cout << "------------------------------------\n";

    // Calculate and display scores for each supplier
    for (const auto& supplier : suppliers) {
        double score = supplier.calculateScore(costWeight, qualityWeight, deliveryWeight);
        cout << supplier.name << " Score: " << score << "\n";
    }

    // Find the best supplier
    Supplier bestSupplier = suppliers[0];
    double bestScore = bestSupplier.calculateScore(costWeight, qualityWeight, deliveryWeight);

    for (const auto& supplier : suppliers) {
        double score = supplier.calculateScore(costWeight, qualityWeight, deliveryWeight);
        if (score > bestScore) {
            bestScore = score;
            bestSupplier = supplier;
        }
    }

    cout << "\nBest Supplier: " << bestSupplier.name << " with a score of " << bestScore << "\n";

    return 0;
}
