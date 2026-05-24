#include <iostream>

int main(){
    int total_minutes = 145;
    int hours = total_minutes / 60;
    int minutes = total_minutes % 60;

    std::cout<< total_minutes << " minutes = " << hours << " hours and " << minutes << " minutes";
    return 0;
}