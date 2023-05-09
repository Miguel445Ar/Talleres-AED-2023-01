#include <iostream>
#include <functional>
using namespace std;
int main() {
    function<void(int)> mostrar = [](int value) -> void {
        cout << value << "\n";
    };
    return 0;
}