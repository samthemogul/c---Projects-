#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Utility
{
    vector<string> split(string str, char separator)
    {
        vector<string> result;
        string temp = "";
        for (int i = 0; i < str.size(); i++)
        {
            if (str[i] == separator)
            {
                result.push_back(temp);
                temp = "";
            }
            else
            {
                temp += str[i];
            }
        }
        result.push_back(temp);

        return result;
    }
};

struct Product
{
    string productName;
    int productPrice;
    int productQuantity;
};

struct Order
{
    string customerName;
    string orderName;
    int quantityOrdered;
};

class Shopping
{
private:
    int wallet;
    int amountToPay;
    Product myProduct;
    Order myOrder;
    Utility u;

public:
    Shopping(int walletValue)
    {
        wallet = walletValue;
    }

public:
    void readFromFile(string productName)
    {
        ifstream stockFile("Stock.txt", ios::in);
        if (!stockFile.is_open())
        {
            cerr << "Error: Unable to open Stock.txt" << endl;
            return;
        }
        string line;
        while (getline(stockFile, line))
        {
            vector<string> productDetails = u.split(line, ',');
            string currentProductName = productDetails[0];
            if (currentProductName == productName)
            {
                myProduct.productPrice = stoi(productDetails[1]);
                myProduct.productQuantity = stoi(productDetails[2]);
                myProduct.productName = currentProductName;
                break;
            }
        }
        stockFile.close();

        return;
    }

    bool calcOrders(string nameOfProduct, int quantity)
    {
        readFromFile(nameOfProduct);
        if (nameOfProduct == myProduct.productName)
        {
            if (quantity < myProduct.productQuantity)
            {
                myOrder.quantityOrdered = quantity;
                myOrder.orderName = nameOfProduct;
                amountToPay = myProduct.productPrice * quantity;
                if (wallet > amountToPay)
                {
                    wallet -= amountToPay;
                    return true;
                }
                else
                {
                    cerr << "Error: Insufficient funds" << endl;
                    return false;
                }
            }
            else
            {
                cerr << "Error: Quantity ordered is more than available stock" << endl;
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    void printSlip(bool status)
    {
        if (status)
        {
            cout << "Enter your name: ";
            cin >> myOrder.customerName;
            cout << "Customer Name: " << myOrder.customerName << endl;
            cout << "Product Name: " << myOrder.orderName << endl;
            cout << "Quantity: " << myOrder.quantityOrdered << endl;
        }
    }

    void saveToFile(bool status)
    {
        if (status)
        {
            ofstream purchaseHistory("PurchaseHistory.txt", ios::app);
            if (!purchaseHistory.is_open())
            {
                cerr << "Error: Unable to open PurchaseHistory.txt" << endl;
                return;
            }
            purchaseHistory << "Customer's Name: " << myOrder.customerName << ", Quantity Ordered: " << myOrder.quantityOrdered << ", Name of Product: " << myOrder.orderName << endl;
            purchaseHistory.close();
            return;
        }
        return;
    }
};

int main()
{
    Shopping myShopping(1000);
    bool status = myShopping.calcOrders("Pineapples", 5);
    myShopping.printSlip(status);
    myShopping.saveToFile(status);

    return 0;
}