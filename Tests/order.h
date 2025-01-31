//code
#include <string>
class Order{
    char ID;
    std::string name;
    std::string order;
    double price;
    char special;
    public:

    Order(char ID, std::string name, std::string order, double price, char special);
    void print();
    double updatePrice(double newPrice);

};