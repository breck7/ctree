#include <iostream>
#include "CTree.h"

int main() {
    auto tree = new CTree("none", "Yo world", NULL);
    std::cout << tree->toString() << std::endl;
    tree->setLine("BAM");
    std::cout << tree->toString() << std::endl;
    return 0;
}