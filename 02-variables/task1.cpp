#include <iostream>

int main(){
    double pi = 3.14159;
    double radius = 5.0;
    double area = pi * (radius * radius);
    std::cout << "Circle area for r = " << radius << " : " << area << "\n";
    return 0;
}