#include <iostream>

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    printArray(new int[]{1, 2, 3, 4, 5}, 5);

    return 0;
}