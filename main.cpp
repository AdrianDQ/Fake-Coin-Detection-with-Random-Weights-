#include <iostream>
#include <cstdlib>
#include <limits> 
#include <ctime>
using namespace std;

// ANSI color codes
#define RESET "\033[0m"    // Resets to default text
#define RED "\033[1;31m"   // Red text 
#define GREEN "\033[1;32m" // Green text for step no.
#define YELLOW "\033[1;33m"// Yellow text for border
#define CYAN "\033[1;36m"  // Cyan text for header

// Function to find the fake coin
int findFakeCoin(int coins[], int left, int right) {
    int iteration = 1;
    
    while (left < right) {
        int n = right - left + 1;
        int groupSize;

        // Determine the number of groups
        if (n % 2 == 0) {
            groupSize = 2; // Divide into 2 groups if even
        } else if (n % 3 == 0) {
            groupSize = 3; // Divide into 3 groups if divisible by 3
        } else {
            // If neither, increase the number of groups until the coins can be evenly divided
            groupSize = 2;
            while (n % groupSize != 0) {
                groupSize++;
            }
        }

        int groupLength = n / groupSize;
        int* groupSums = new int[groupSize](); // Array to store sums of each group

        // Calculate the sum for each group
        for (int i = 0; i < groupSize; i++) {
            int start = left + i * groupLength;
            int end = start + groupLength - 1;
            for (int j = start; j <= end; j++) {
                groupSums[i] += coins[j];
            }
        }

        // Output per iteration
        cout << CYAN << "\nIteration " << iteration << ":" << RESET << endl;
        cout << YELLOW << "----------------------------------------------------\n" << RESET;
        
        for (int i = 0; i < groupSize; i++) {
            int start = left + i * groupLength;
            int end = start + groupLength - 1;
            cout << "Group " << i + 1 << RESET << " (coins [" << start << " to " << end << "]): ";
            for (int j = start; j <= end; j++) {
                cout << coins[j] << (j < end ? ", " : "");
            }
            cout << endl;
        }

        cout << GREEN << "\nStep 2: Compare the sum of the groups.\n" << RESET;
        for (int i = 0; i < groupSize; i++) {
            cout << "Group " << i + 1 << " sum: " << groupSums[i] << endl;
        }

        // Find the group with the fake coin
        int minSum = groupSums[0];
        int minIndex = 0;
        for (int i = 1; i < groupSize; i++) {
            if (groupSums[i] < minSum) {
                minSum = groupSums[i];
                minIndex = i;
            }
        }

        // Narrow down the search to the group with the fake coin
        left = left + minIndex * groupLength;
        right = left + groupLength - 1;

        cout << RED << "\nFake coin is in Group " << minIndex + 1 << ". Narrowing search to this group.\n" << RESET;
        cout << YELLOW << "----------------------------------------------------\n" << RESET;

        iteration++;
        delete[] groupSums;
    }

    // Output the fake coin
    cout << RED << "\nFake coin found at index " << left << " with weight " << coins[left] << RESET << endl;
    return left;
}

//--------------------------------------------------------------------------------------------------------

bool isValidInteger(const string& input) {
    if (input.empty()) return false; // Rejects empty strings
    for (char c : input) {
        if (!isdigit(c)) return false; 
    }
    return true;
}

//--------------------------------------------------------------------------------------------------------

int main() {
    srand(time(0));
    int N;
    string input;
    int choice;
    
    while (true) {
        cout << YELLOW << "============================================================\n";
        cout << YELLOW << "           CHOOSE A MODE FOR FAKE COIN DETECTION:\n";
        cout << YELLOW << "------------------------------------------------------------\n";
        cout << YELLOW << "1. Ensure one coin is lighter than the rest\n";
        cout << YELLOW << "2. Handle exception where all coins may have the same weight\n";
        cout << YELLOW << "============================================================\n";        
        cout << RESET << "Enter choice (1 or 2): ";
        getline(cin, input);

        if (isValidInteger(input)) {
            choice = stoi(input);
            if (choice == 1 || choice == 2) break;
        }
        cout << "Invalid choice! Please enter 1 or 2.\n";
    }
    
    // Keep asking for input until a valid number of coins is entered
    while (true) {
        cout << "Enter number of coins (N): " << RESET;
        getline(cin, input); 

        if (!isValidInteger(input)) {
            cout << RED << "Invalid input! Please enter a valid integer greater than 1.\n" << RESET;
            continue;
        }

        N = stoi(input); // Convert valid string to an integer
        if (N > 1) break;

        cout << RED << "Number must be greater than 1.\n" << RESET;
    }

    // Generate random weights for N coins
    int coins[N];
    int fakeIndex = rand() % N;
    int normalWeight = rand() % 11 + 10; // Random weight for normal coins (between 10 and 20)
    int fakeWeight; 
       

    if (choice == 1) {
        do {// case 1
            fakeWeight = rand() % 11 + 10; // Random weight for fake coins (10-20)
        } while (fakeWeight >= normalWeight); // Ensuring fake coin is lighter

    } else if (choice == 2) {
        do {// case 2
            fakeWeight = rand() % 11 + 10; 
        } while (fakeWeight > normalWeight); // Can be equal or lighter

        if (fakeWeight == normalWeight) {
            cout << "\nAll coins have the same weight (" << normalWeight << "). No fake coin exists.\n";
            return 0;
        }
    }
    for (int i = 0; i < N; i++) {
        if (i == fakeIndex) {
            coins[i] = fakeWeight;
        } else {
            coins[i] = normalWeight;
        }
    }

    cout << CYAN << "\nFake Coin Problem Simulation" << RESET << endl;
    cout << "Coins: " << RESET;
    for (int i = 0; i < N; i++) cout << coins[i] << " ";
    cout << endl << endl;

    cout << "Step-by-Step Process of Identifying the Fake Coin:" << RESET << endl;
    
    int fakeCoinIndex = findFakeCoin(coins, 0, N - 1);

    if (fakeCoinIndex != -1) {
        cout << GREEN << "\nThe fake coin is at index " << fakeCoinIndex << RESET << endl;
    } else {
        cout << RED << "\nNo fake coin found." << RESET << endl;
    }

    return 0;
}
