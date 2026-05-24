#include <iostream>

int main(){
    int a = 7;
    int b = 2;

    int sum = a+b;
    int diff = a-b;
    int prod = a*b;
    int div = a / b;
    int mod = a % b;

    std::cout << "sum = " << sum << "\n";
    std::cout << "diff = " << diff << "\n";
    std::cout << "prod = " << prod << "\n";
    std::cout << "div = " << div << "\n";
    std::cout << "mod = " << mod << "\n";
    return 0;
}