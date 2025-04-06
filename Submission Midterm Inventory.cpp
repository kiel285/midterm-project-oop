#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;
//created by Kiel E. Biscocho IT2A
class Items {
private:
    int Product_id;
    string name;
    int quantity;
    float price;
public:
    Items(int Product_id, string name, int quantity, float price) {
        this->Product_id = Product_id;
        this->name = name;
        this->quantity = quantity;
        this->price = price;
    }

    int getID() { return Product_id; }
    string getName() { return name; }
    int getQuantity() { return quantity; }
    float getPrice() { return price; }

    void setName(string name) { this->name = name; }
    void setQuantity(int quantity) { this->quantity = quantity; }
    void setPrice(float price) { this->price = price; }

    void displayAll() {
        cout << "     " << getID() << "       " << getName() << "         " << getQuantity() << "        ₱" << getPrice() << endl;
    }
};
bool isDigits(string& str) {
    if (str.empty()) return false;
    for (char ch : str) {
        if (!isdigit(ch)) {
            return false;
        }
    }
    return true;
}
bool isPositiveNumber(string& str) {
    if (str.empty()) return false;
    for (char ch : str) {
        if (!isdigit(ch) && ch != '.') {
            return false;
        }
    }
    return true;
}
string _input(string x){
    while(!isDigits(x)){
        cout<<"Error: Wrong Input Syntax"<<endl;
        cout<<"Input: ";
        getline(cin,x);
    }
    return x;
}
string _inputFloat(string x){
    while(!isPositiveNumber(x)){
        cout<<"Error: Please enter a valid positive number"<<endl;
        cout<<"Input: ";
        getline(cin,x);
    }
    return x;
}
void displayMenu() {
    cout << "-----------------------------" << endl;
    cout << "Inventory Management System" << endl;
    cout << "-----------------------------" << endl;
    cout << "1 - Add Item" << endl;
    cout << "2 - Update Item" << endl;
    cout << "3 - Remove Item" << endl;
    cout << "4 - Display All Items" << endl;
    cout << "5 - Search Item" << endl;
    cout << "6 - Sort Items" << endl;
    cout << "7 - Low Stock Items" << endl;
    cout << "8 - Exit" << endl;
    cout << "-----------------------------" << endl;
    cout << "Choose: ";
}
void addItem(vector<Items>& inventory, int& counter) {
    string Name;
    int tQuantity;
    float tPrice;

    cout<<"Adding Item: "<<counter<<endl;
    cout<<"-----------------------------"<<endl;
    cout<<"Item Name: ";
    cin.ignore();
    getline(cin, Name);
    cout << "Item Quantity: ";
    string x;
    getline(cin,x);
    tQuantity = stoi(_input(x));

   
    if(tQuantity <= 0) {
        cout<<"Error: Quantity must be a positive integer."<<endl;
        return;
    }

    cout<<"Item Price: ";
    getline(cin,x);
    tPrice = stof(_inputFloat(x));

    
    if(tPrice <= 0) {
        cout<<"Error: Price must be a positive number."<<endl;
        return;
    }

    inventory.push_back(Items(counter, Name, tQuantity, tPrice));
    cout<<"-----------------------------"<<endl;
    cout<<"Item added successfully!"<<endl;
    counter++;
}
void updateItem(vector<Items>& inventory) {
    string x;
    if (inventory.empty()) {
        cout << "There are no items to update" << endl;
        return;
    }

    int selector;
    cout<<"Enter Product ID to update: ";
    cin>>selector;

    bool found = false;
    for (int i = 0; i < inventory.size(); i++) {
        if (inventory[i].getID() == selector) {
            found = true;
            string Name = inventory[i].getName();
            int hQuantity = inventory[i].getQuantity();
            float hPrice = inventory[i].getPrice();
            cout<< "Product found! Choose to update:"<<endl;
            cout<< "1 - Update Quantity"<<endl;
            cout<< "2 - Update Price"<<endl;
            cout<< "3 - Cancel"<<endl;
            cout<< "-----------------------------"<<endl;
            cout<<"choose";
            int update;
            cin >> update;

            int tQuantity;
            float tPrice;
            switch (update) {
                case 1:
                    cout << "Enter new quantity: ";
                    cin.ignore();
                    getline(cin, x);
                    tQuantity = stoi(_input(x));
                    if(tQuantity <= 0) {
                        cout << "Error: Quantity must be positive." << endl;
                        return;
                    }
                    inventory[i].setQuantity(tQuantity);
                    cout << "Quantity updated!" << endl;
                    cout<<"Quantity of "<<Name<<" updated from "<<hQuantity<<" to "<<inventory[i].getQuantity()<<endl;
                    cout<<"Returning to menu"<<endl;
                    break;
                case 2:
                    cout << "Enter new price: ";
                    getline(cin, x);
                    tPrice = stof(_inputFloat(x));
                    if(tPrice <= 0) {
                        cout << "Error: Price must be positive." << endl;
                        return;
                    }
                    inventory[i].setPrice(tPrice);
                    cout << "Price updated!" << endl;
                    cout<<"Price of "<<Name<<" updated from ₱"<<hPrice<<" to ₱"<<inventory[i].getPrice()<<endl;
                    cout<<"Returning to menu"<<endl;
                    break;
                case 3:
                    cout << "Update Terminated" << endl;
                    break;
                default:
                    cout << "Invalid option!" << endl;
            }
            break;
        }
    }

    if (!found) {
        cout << "Item not found!" << endl;
    }
}
void removeItem(vector<Items>& inventory) {
    if (inventory.empty()) {
        cout<<"There are no items to remove."<<endl;
        return;
    }

    int selector;
    cout<<"Enter Product ID to remove: ";
    cin>>selector;

    bool found = false;
    for (int i = 0; i < inventory.size(); i++) {
        if (inventory[i].getID() == selector) {
            found = true;
            inventory.erase(inventory.begin() + i);
            cout<<"Item removed!"<<endl;
            break;
        }
    }

    if (!found) {
        cout<<"Item not found!"<<endl;
    }
}
void displayAllItems(vector<Items>& inventory) {
    if (inventory.empty()) {
        cout<<"No items to display!"<<endl;
        return;
    }

    cout<<"Product ID || Name || Quantity || Price"<<endl;
    for (int i = 0; i < inventory.size(); i++) {
        inventory[i].displayAll();
    }
}
void searchItem(vector<Items>& inventory) {
    int input;
    cout<<"Enter Product ID to search: ";
    cin>>input;

    bool found = false;
    for (int i = 0; i < inventory.size(); i++) {
        if (inventory[i].getID() == input) {
            cout<<"Product ID || Name || Quantity || Price"<<endl;
            inventory[i].displayAll();
            found = true;
            break;
        }
    }

    if (!found) {
        cout<<"Item not found!"<<endl;
    }
}
void sortByPrice(vector<Items>& inventory, int orderOption) {
    if (orderOption == 1) {  
        sort(inventory.begin(), inventory.end(), [](Items& a, Items& b) {
            return a.getPrice() < b.getPrice();
        });
    } else if (orderOption == 2) {  
        sort(inventory.begin(), inventory.end(), [](Items& a, Items& b) {
            return a.getPrice() > b.getPrice();
        });
    } else {
        cout<<"Invalid order option for price!"<<endl;
    }
}
void sortByQuantity(vector<Items>& inventory, int orderOption) {
    if (orderOption == 1) {
        sort(inventory.begin(), inventory.end(), [](Items& a, Items& b) {
            return a.getQuantity() < b.getQuantity();
        });
    } else if (orderOption == 2) {
        sort(inventory.begin(), inventory.end(), [](Items& a, Items& b) {
            return a.getQuantity() > b.getQuantity();
        });
    } else {
        cout<<"Invalid order option for quantity!"<<endl;
    }
}
void sortItems(vector<Items>& inventory) {
    int sortOption, orderOption;

    cout<<"Sort by:"<<endl;
    cout<<"1 - Price"<<endl;
    cout<<"2 - Quantity"<<endl;
    cout<<"Choose: ";
    cin>>sortOption;

    cout<<"Order:"<<endl;
    cout<<"1 - Increasing"<<endl;
    cout<<"2 - Decreasing"<<endl;
    cout<<"Choose: ";
    cin>>orderOption;
    
    
    if (sortOption == 1) {
        sortByPrice(inventory, orderOption);
        cout<<"Items sorted successfully!"<<endl;
    } else if (sortOption == 2) {
        sortByQuantity(inventory, orderOption);
        cout<<"Items sorted successfully!"<<endl;
    } else {
        cout<<"Invalid sort option!"<<endl;
    }
    
}
void displayLowStockItems(vector<Items>& inventory, int lowStock) {
    bool lwfound = false;
    for (int i = 0; i < inventory.size(); i++) {
        if (inventory[i].getQuantity() <= lowStock) {
            if (!lwfound) {
                cout<<"Product ID || Name || Quantity || Price"<<endl;
                lwfound = true;
            }
            inventory[i].displayAll();
        }
    }

    if (!lwfound) {
        cout << "No low stock items!" << endl;
    }
}
int main() {
    int counter = 1;
    int choose;
    vector<Items> inventory;
    int lowStock = 5;
    string x;

    while (true) {
        displayMenu();
        getline(cin, x);
        choose = stoi(_input(x));

        if (choose >= 1 && choose <= 8) {
            switch (choose) {
                case 1: addItem(inventory, counter); break;
                case 2: updateItem(inventory); break;
                case 3: removeItem(inventory); break;
                case 4: displayAllItems(inventory); break;
                case 5: searchItem(inventory); break;
                case 6: sortItems(inventory); break;
                case 7: displayLowStockItems(inventory, lowStock); break;
                case 8: cout<<"Terminating Inventory"<<endl; return 0;
                default: cout<<"Invalid choice. Please try again"<<endl;
            }
        } else {
            cout<<"Invalid input, Input valid choices in the menu"<<endl;
        }
    }
}
