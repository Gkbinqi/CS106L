#include <iostream>
#include "src/StanfordID.cpp"

int main() {
    StanfordID jacob{ "Jacob Roberts-Baca", "jtrb", 12345678 };
    StanfordID fabio{ "Fabio Ibanez", "fabioi", 87654321 };
    if (jacob < fabio) {
        std::cout << jacob.getName() << " has a lower ID number than " << fabio.getName() << std::endl;
    } else {
        std::cout << fabio.getName() << " has a lower ID number than " << jacob.getName() << std::endl;
    }

    std::cout << jacob << fabio;
    return 0;
}