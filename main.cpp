#include <iostream>
#include <type_traits>
#include <concepts>

template <typename T>
concept PuntoMobile = std::is_floating_point_v<T>;

template<FloatingPoint T>
class numero_complesso {
private:
    T reale;
    T immaginario;
public:
    // Costruttore di default che inizializza a zero
    numero_complesso() : reale(0), immaginario(0) {}

    // Costruttore user-defined che inizializza la parte reale ed immaginaria
    numero_complesso(T r, T i) : reale(r), immaginario(i) {}

    // Metodo che restituisce la parte reale
    T getReale() const {
        return reale;
    }

    // Metodo che restituisce la parte immaginaria
    T getImmaginario() const {
        return immaginario;
    }

    // Metodo che restituisce il coniugato del numero complesso
    numero_complesso coniugato() const {
        return numero_complesso(reale, -immaginario);
    }

    // Overload dell'operatore += per l'addizione di due numeri complessi
    numero_complesso& operator+=(const numero_complesso& altro) {
        reale += altro.reale;
        immaginario += altro.immaginario;
        return *this;
    }

    // Overload dell'operatore *= 
    numero_complesso& operator*=(const numero_complesso& altro) {
        T nuovo_reale = reale * altro.reale - immaginario * altro.immaginario;
        T nuovo_immaginario = reale * altro.immaginario + immaginario * altro.reale;
        reale = nuovo_reale;
        immaginario = nuovo_immaginario;
        return *this;
    }

    // Overload dell'operatore << per la stampa 
    friend std::ostream& operator<<(std::ostream& os, const numero_complesso& n) {
        os << n.reale;
        if(n.immaginario >= 0)
            os << "+" << n.immaginario << "i";
        else
            os << n.immaginario << "i";
        return os;
    }
};

// Overload non-membro dell'operatore + per l'addizione di due numeri complessi
template<FloatingPoint T>
numero_complesso<T> operator+(numero_complesso<T> sinistro, const numero_complesso<T>& destro) {
    sinistro += destro;
    return sinistro;
}

// Overload non-membro dell'operatore * per la moltiplicazione di due numeri complessi
template<FloatingPoint T>
numero_complesso<T> operator*(numero_complesso<T> sinistro, const numero_complesso<T>& destro) {
    sinistro *= destro;
    return sinistro;
}

// Overload per operazioni miste con un numero reale (di tipo T)
template<FloatingPoint T>
numero_complesso<T> operator+(const numero_complesso<T>& sinistro, T destro) {
    return sinistro + numero_complesso<T>(destro, 0);
}

template<FloatingPoint T>
numero_complesso<T> operator+(T sinistro, const numero_complesso<T>& destro) {
    return numero_complesso<T>(sinistro, 0) + destro;
}

template<FloatingPoint T>
numero_complesso<T> operator*(const numero_complesso<T>& sinistro, T destro) {
    return sinistro * numero_complesso<T>(destro, 0);
}

template<FloatingPoint T>
numero_complesso<T> operator*(T sinistro, const numero_complesso<T>& destro) {
    return numero_complesso<T>(sinistro, 0) * destro;
}

int main() {
    double parteReale1, parteImmaginaria1;
    std::cout << "Inserisci la parte reale del primo numero complesso: ";
    std::cin >> parteReale1;
    std::cout << "Inserisci la parte immaginaria del primo numero complesso: ";
    std::cin >> parteImmaginaria1;
    numero_complesso<double> numeroA(parteReale1, parteImmaginaria1);
  
    double parteReale2, parteImmaginaria2;
    std::cout << "Inserisci la parte reale del secondo numero complesso: ";
    std::cin >> parteReale2;
    std::cout << "Inserisci la parte immaginaria del secondo numero complesso: ";
    std::cin >> parteImmaginaria2;
    numero_complesso<double> numeroB(parteReale2, parteImmaginaria2);

    std::cout << "\nHai inserito:" << std::endl;
    std::cout << "Numero complesso A: " << numeroA << std::endl;
    std::cout << "Numero complesso B: " << numeroB << std::endl;

    // Operazioni fra i due numeri complessi
    auto somma = numeroA + numeroB;
    auto prodotto = numeroA * numeroB;
    std::cout << "\nA + B = " << somma << std::endl;
    std::cout << "A * B = " << prodotto << std::endl;
    
    // Input di un numero reale per operazioni miste
    double numeroReale;
    std::cout << "\nInserisci un numero reale per operare con A: ";
    std::cin >> numeroReale;
    
    auto somma_mista1 = numeroA + numeroReale;
    auto somma_mista2 = numeroReale + numeroA;
    auto prodotto_misto1 = numeroA * numeroReale;
    auto prodotto_misto2 = numeroReale * numeroA;
    
    std::cout << "\nOperazioni miste con il numero reale " << numeroReale << ":" << std::endl;
    std::cout << "A + " << numeroReale << " = " << somma_mista1 << std::endl;
    std::cout << numeroReale << " + A = " << somma_mista2 << std::endl;
    std::cout << "A * " << numeroReale << " = " << prodotto_misto1 << std::endl;
    std::cout << numeroReale << " * A = " << prodotto_misto2 << std::endl;
    
    // Visualizzazione del coniugato del primo numero complesso
    std::cout << "\nIl coniugato di A è: " << numeroA.coniugato() << std::endl;

    return 0;
}
