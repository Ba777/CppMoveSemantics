#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Timer.hpp"
#include "Email.cpp"

Email newEmail() {
    static int id = 0;
    return Email("User" + std::to_string(++id) + "@mydomain.com");
}

int main(int argc, char** argv) {
    int numElems = argc > 1 ? std::atoi(argv[1]) : 100000;
    Timer tmr;
    double t = tmr.elapsed();
    std::cout << t << std::endl;

    // init the collection with email addresses.

    std::vector<Email> cell;
    for (int i = 0; i < numElems; ++i) {
        cell.push_back(newEmail());
    }

    double after_init = tmr.elapsed();
    std::cout << "after init time taken: " << after_init*1000 << "milli sec" << std::endl;

    //sort the vector

    std::sort(cell.begin(), cell.end(),
              [](const Email& lhs, const Email& rhs) {
                return lhs.getValue() < rhs.getValue();
              });
    double after_sort = tmr.elapsed();
    std::cout << "sorting operation time taken: " << ((after_sort*1000) - (after_init*1000)) << "milli sec" << std::endl;

    for (char c : newEmail().getValue()) {
        auto x = Email{"bala@gmail.com"};
        std::cout << c << " ";
    }
    std::cout << "\n";

    //Email e1{"ddd"};

    Email e{std::move(cell[2])};
    for (const auto& e1: cell) {
        //std::cout << e.getValue() << std::endl;
        if(e1.getDomain() != "@mydomain.com") {
            std::cout << "other domain: " << e1.getDomain() << "\n";
        }
    }
}
