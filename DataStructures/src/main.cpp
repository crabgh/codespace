#include <iostream>
#include "AVLMap.hpp"

int main() {
    AVLMap<int, std::string> bt(1, "A");
    bt[2] = "B";
    bt[5] = "E";
    bt[3] = "C";
    bt[7] = "G";
    bt[4] = "D";
    bt[6] = "F";
    std::cout << bt.erase(4) << " was erased\n";
    bt.inOrderTraversal();
}