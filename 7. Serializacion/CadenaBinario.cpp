#include <iostream>

void cadenaABinario(const char* texto) {
    for (int i = 0; texto[i] != '\0'; i++) {
        char caracter = texto[i];
        for (int j = 7; j >= 0; j--) {
            if ((caracter >> j) & 1) {
                std::cout << "1";
            } else {
                std::cout << "0";
            }
        }
        std::cout << " ";
    }
    std::cout << std::endl;
}

int main() {
    char miTexto[] = "Hola soy Gabriela Orozco";
    
    std::cout << "Texto: " << miTexto << std::endl;
    std::cout << "Binario: ";
    cadenaABinario(miTexto);
    
    return 0;
}