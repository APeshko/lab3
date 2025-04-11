#include <iostream>
#include <memory>

void noMemLeak() {
    for (int i = 0; i < 100; ++i) {
        auto ptr = std::make_unique<int[]>(10);
    }
}

int main() {
    noMemLeak();
    return 0;
}
