#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Supplier {
public:
    string name;
    int cost;  // Cost in thousands of rupees
    int quality;  // Rating on a scale of 1 to 10 (1 = lowest quality, 10 = highest quality)
    int deliveryTime;  // Rating on a scale of 1 to 10 (1 = longest time, 10 = quickest time)

    Supplier(string name, int cost, int quality, int deliveryTime) {
        this->name = name;
        this->cost = cost;
        this->quality = quality;
        this->deliveryTime = deliveryTime;
    }

    double calculateScore() const {
        return quality * 0.6 + deliveryTime * 0.4;  // Weighted score
    }
};

int main() {
    vector<Supplier> suppliers = {
        Supplier("HealthEquip", 50, 9, 8),
        Supplier("MediTech", 60, 8, 7),
        Supplier("MedSupplyCo", 40, 7, 9),
        Supplier("PharmaSource", 70, 10, 6),
        Supplier("CareLogix", 30, 6, 10)
    };

    int budget;
    cout << "Enter the total budget (in thousands of rupees): ";
    cin >> budget;

    int n = suppliers.size();
    vector<vector<double>> dp(n + 1, vector<double>(budget + 1, 0));
    vector<vector<bool>> selected(n + 1, vector<bool>(budget + 1, false));

    // Knapsack DP algorithm
    for (int i = 1; i <= n; ++i) {
        for (int b = 1; b <= budget; ++b) {
            if (suppliers[i - 1].cost <= b) {
                double includeScore = dp[i - 1][b - suppliers[i - 1].cost] + suppliers[i - 1].calculateScore();
                double excludeScore = dp[i - 1][b];

                if (includeScore > excludeScore) {
                    dp[i][b] = includeScore;
                    selected[i][b] = true;
                } else {
                    dp[i][b] = excludeScore;
                }
            } else {
                dp[i][b] = dp[i - 1][b];
            }
        }
    }

    // Backtracking to find the selected suppliers
    vector<Supplier> selectedSuppliers;
    int remainingBudget = budget;
    double maxScore = dp[n][budget];

    for (int i = n; i > 0 && remainingBudget > 0; --i) {
        if (selected[i][remainingBudget]) {
            selectedSuppliers.push_back(suppliers[i - 1]);
            remainingBudget -= suppliers[i - 1].cost;
        }
    }

    // Output results
    cout << "\nMaximum Score Achieved: " << maxScore << "\n";
    cout << "Selected Suppliers:\n";
    for (const auto& supplier : selectedSuppliers) {
        cout << "Name: " << supplier.name
             << ", Cost: " << supplier.cost << "k"
             << ", Quality: " << supplier.quality
             << ", Delivery Time: " << supplier.deliveryTime << "\n";
    }

    return 0;
}
