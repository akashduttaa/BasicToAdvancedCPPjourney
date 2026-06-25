#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

// Class representing a product in the shop inventory
class Product {
public:
    int id;
    string name;
    double price;
    int stock;

    Product(int i, string n, double p, int s) : id(i), name(n), price(p), stock(s) {}

    // Converts product fields into a comma-separated format for file storage
    string toFileData() const {
        return to_string(id) + "," + name + "," + to_string(price) + "," + to_string(stock);
    }
};

// Class representing an item inside the customer's shopping cart
class CartItem {
public:
    int id;
    string name;
    double price;
    int quantity;

    CartItem(int i, string n, double p, int q) : id(i), name(n), price(p), quantity(q) {}
};

// Main system controller managing inventory, cart sessions, authentication, and files
class BillingSystem {
private:
    vector<Product> inventory;
    vector<CartItem> cart;
    const string inventoryFile = "inventory.txt";

    // Internal helper to parse database file on app startup
    void loadInventory() {
        inventory.clear();
        ifstream file(inventoryFile);
        if (!file.is_open()) return; 

        string line;
        while (getline(file, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t pos3 = line.find(',', pos2 + 1);

            if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
                int id = stoi(line.substr(0, pos1));
                string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
                double price = stod(line.substr(pos2 + 1, pos3 - pos2 - 1));
                int stock = stoi(line.substr(pos3 + 1));
                inventory.push_back(Product(id, name, price, stock));
            }
        }
        file.close();
    }

    // Internal helper to commit changes back to data file
    void saveInventory() {
        ofstream file(inventoryFile);
        for (const auto& prod : inventory) {
            file << prod.toFileData() << "\n";
        }
        file.close();
    }

public:
    BillingSystem() {
        loadInventory();
    }

    // Admin Verification System
    bool authenticateAdmin() {
        string username, password;
        cout << "\n================= ADMIN LOGIN =================\n";
        cout << "Enter Admin Username: ";
        cin >> username;
        cout << "Enter Admin Password: ";
        cin >> password;

        if (username == "admin" && password == "admin123") {
            cout << " Access Granted! Welcome back, Admin.\n";
            return true;
        } else {
            cout << " Invalid Credentials! Access Denied.\n";
            return false;
        }
    }

    // ADMIN MODE: Stock Registration
    void addNewProduct() {
        int id, stock;
        string name;
        double price;

        cout << "\nEnter Product ID: ";
        cin >> id;
        
        for (const auto& prod : inventory) {
            if (prod.id == id) {
                cout << " Error: Product ID already exists!\n";
                return;
            }
        }

        cout << "Enter Product Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Price: Rs. ";
        cin >> price;
        cout << "Enter Initial Stock Quantity: ";
        cin >> stock;

        inventory.push_back(Product(id, name, price, stock));
        saveInventory();
        cout << " Product successfully recorded in inventory!\n";
    }

    // CUSTOMER & ADMIN MODE: Display Live Catalog
    void viewInventory() {
        if (inventory.empty()) {
            cout << "\n Store catalogs are empty right now.\n";
            return;
        }

        cout << "\n================ AVAILABLE PRODUCTS ================\n";
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Price (Rs.)" << setw(10) << "Stock" << "\n";
        cout << "----------------------------------------------------\n";
        for (const auto& prod : inventory) {
            cout << left << setw(10) << prod.id 
                 << setw(20) << prod.name 
                 << "Rs. " << setw(11) << fixed << setprecision(2) << prod.price 
                 << setw(10) << prod.stock << "\n";
        }
        cout << "====================================================\n";
    }

    // CUSTOMER MODE: Add products into dynamic session vector
    void addToCart() {
        if (inventory.empty()) {
            cout << "\n No items available to buy!\n";
            return;
        }

        int id, qty;
        cout << "\nEnter Product ID to add: ";
        cin >> id;

        for (auto& prod : inventory) {
            if (prod.id == id) {
                cout << "Enter Quantity: ";
                cin >> qty;

                if (qty < 0 || qty == 0) {
                    cout << " Invalid quantity value!\n";
                    return;
                }
                if (qty > prod.stock) {
                    cout << " Insufficient stock allocation! Only " << prod.stock << " remaining.\n";
                    return;
                }

                prod.stock -= qty;
                
                bool foundInCart = false;
                for (auto& item : cart) {
                    if (item.id == id) {
                        item.quantity += qty;
                        foundInCart = true;
                        break;
                    }
                }
                if (!foundInCart) {
                    cart.push_back(CartItem(prod.id, prod.name, prod.price, qty));
                }

                saveInventory(); 
                cout << "🛒 Successfully added " << qty << " units of " << prod.name << " to cart!\n";
                return;
            }
        }
        cout << " Requested Product ID not found!\n";
    }

    // CUSTOMER MODE: Print console bill + write customized persistent text file
    void generateFinalBill() {
        if (cart.empty()) {
            cout << "\n🛒 Processing halted: Shopping cart is empty!\n";
            return;
        }

        double subtotal = 0.0;
        
        // Dynamic, unique timestamp creation for independent receipt files
        time_t now = time(0);
        string receiptFileName = "Receipt_" + to_string(now) + ".txt";
        
        ofstream receipt(receiptFileName);

        // Header definitions for console stream
        cout << "\n=================== FINAL INVOICE ===================\n";
        cout << left << setw(20) << "Item Name" << setw(12) << "Price" << setw(10) << "Qty" << setw(12) << "Total" << "\n";
        cout << "-----------------------------------------------------\n";

        // Header definitions for active output file stream
        receipt << "=================== TRANSACTION RECEIPT ===================\n";
        receipt << "Timestamp ID: " << now << "\n";
        receipt << "-----------------------------------------------------------\n";
        receipt << left << setw(20) << "Item Name" << setw(12) << "Price" << setw(10) << "Qty" << setw(12) << "Total" << "\n";
        receipt << "-----------------------------------------------------------\n";

        for (const auto& item : cart) {
            double itemTotal = item.price * item.quantity;
            subtotal += itemTotal;

            // Output data stream running side by side
            cout << left << setw(20) << item.name << "Rs. " << setw(8) << fixed << setprecision(2) << item.price << setw(10) << item.quantity << "Rs. " << itemTotal << "\n";
            receipt << left << setw(20) << item.name << "Rs. " << setw(8) << fixed << setprecision(2) << item.price << setw(10) << item.quantity << "Rs. " << itemTotal << "\n";
        }

        // Tiered Discount calculations
        double discountPercent = 0.0;
        if (subtotal > 5000) discountPercent = 15.0;      
        else if (subtotal > 2000) discountPercent = 10.0; 
        else if (subtotal > 1000) discountPercent = 5.0;  

        double discountAmount = subtotal * (discountPercent / 100.0);
        double finalBill = subtotal - discountAmount;

        // Terminal Block output
        cout << "-----------------------------------------------------\n";
        cout << left << setw(42) << "Subtotal:" << "Rs. " << subtotal << "\n";
        cout << left << setw(42) << ("Discount (" + to_string((int)discountPercent) + "%):") << "-Rs. " << discountAmount << "\n";
        cout << "=====================================================\n";
        cout << left << setw(42) << "GRAND TOTAL TO PAY:" << "Rs. " << finalBill << "\n";
        cout << "=====================================================\n";
        cout << "✨ Bill settled. Receipt written to disk as: " << receiptFileName << "\n\n";

        // File generation summary block
        receipt << "-----------------------------------------------------------\n";
        receipt << left << setw(42) << "Subtotal:" << "Rs. " << subtotal << "\n";
        receipt << left << setw(42) << ("Discount (" + to_string((int)discountPercent) + "%):") << "-Rs. " << discountAmount << "\n";
        receipt << "===========================================================\n";
        receipt << left << setw(42) << "GRAND TOTAL PAID:" << "Rs. " << finalBill << "\n";
        receipt << "===========================================================\n";
        receipt << "         ✨ Thank you for choosing our store! ✨\n";

        receipt.close();
        cart.clear(); // Session flush
    }
};

int main() {
    BillingSystem shop;
    int systemChoice;

    while (true) {
        cout << "\n==============================================\n";
        cout << "      WELCOME TO THE E-COMMERCE GATEWAY       \n";
        cout << "==============================================\n";
        cout << "1. Login as Administrator\n";
        cout << "2. Enter as Customer\n";
        cout << "3. Shut Down System\n";
        cout << "Select Access Profile (1-3): ";
        cin >> systemChoice;
        if (systemChoice == 3) 
        {cout << "Terminating services cleanly. Goodbye!\n";
            break;}
        // Admin Workflow Branch
        if (systemChoice == 1) 
        {if (shop.authenticateAdmin()) {
            int adminChoice;
            do {cout << "\n--- ADMIN OPERATIONS CONTROL PANEL ---\n";
                cout << "1. Register New Product/Stock\n";
                cout << "2. Inspect Live Inventory Logs\n";
                cout << "3. Logout\n";
                cout << "Enter command: ";
                cin >> adminChoice;
                switch (adminChoice) {
                    case 1: shop.addNewProduct(); break;
                    case 2: shop.viewInventory(); break;
                    case 3: cout << "Logging out from session admin...\n"; break;
                    default: cout << " Unknown command code.\n";}}
                     while (adminChoice != 3);}}
                     // Customer Workflow Branch
                     else if (systemChoice == 2) {int customerChoice;
                        do {cout << "\n--- CUSTOMER DIGITAL SELF-SERVICE HUB ---\n";
                            cout << "1. View Store Catalog\n";
                            cout << "2. Put Item in Shopping Cart\n";
                            cout << "3. Finalize Bill & Run Invoice\n";
                            cout << "4. Exit Shopping Deck\n";
                            cout << "Enter command: ";
                            cin >> customerChoice;
                            switch (customerChoice) {
                                case 1: shop.viewInventory(); break;
                                case 2: shop.addToCart(); break;
                                case 3: shop.generateFinalBill(); break;
                                case 4: cout << "Clearing temporary visual decks. Goodbye!\n"; break;
                                default: cout << " Option invalid. Pick from menu items.\n";}} 
                                while (customerChoice != 4);
                            }else {cout << " Top level routing out of index boundaries.\n";
                            }
                        }
                        return 0;
                    }