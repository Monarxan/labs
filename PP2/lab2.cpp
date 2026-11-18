#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {

const double a = 0.0;
const double b = 1.0;

/**
 * Sums the power series of variant 179 up to the first term with |term| <= eps.
 * No argument checks are made: x in [a; b] and eps > 0 are expected.
 * Recurrence: u0 = x / 2, u(n+1) = u(n) * (-x * (n+1)^2) / ((2n+3) * (2n+4)).
 */
double s(double x, double eps) {
    double term = x / 2.0;
    double sum = term;
    double n = 0.0;
    while (term > eps || term < -eps) {
        term *= -x * (n + 1.0) * (n + 1.0) / ((2.0 * n + 3.0) * (2.0 * n + 4.0));
        sum += term;
        n += 1.0;
    }
    return sum;
}

/**
 * Consumes the rest of the current input line.
 * Returns true if it contains anything except whitespace.
 */
bool hasExtraInput() {
    std::string rest;
    std::getline(std::cin, rest);
    return rest.find_first_not_of(" \t\r") != std::string::npos;
}

/**
 * Reads x from the input; throws if the input is not a real number
 * or if x is outside the domain [a; b].
 */
double readX() {
    double x{};
    std::cout << "Enter a real x from [0; 1]: ";
    std::cin >> x;
    if (std::cin.fail()) {
        throw std::runtime_error("Input error: x must be a real number.");
    }
    if (x < a || x > b) {
        throw std::out_of_range("Value error: x is outside the domain [0; 1].");
    }
    if (hasExtraInput()) {
        throw std::runtime_error("Input error: x must be a real number.");
    }
    return x;
}

/**
 * Reads eps from the input; throws if the input is not a real number
 * or if eps is not positive.
 */
double readEps() {
    double eps{};
    std::cout << "Enter positive eps: ";
    std::cin >> eps;
    if (std::cin.fail()) {
        throw std::runtime_error("Input error: eps must be a real number.");
    }
    if (!(eps > 0.0)) {
        throw std::out_of_range("Value error: eps must be positive.");
    }
    if (hasExtraInput()) {
        throw std::runtime_error("Input error: eps must be a real number.");
    }
    return eps;
}

void printIntroduction() {
    std::cout << "Author: Popov Kostiantyn, group ITK-11\n"
              << "Variant 179: computes the sum of a power series S(x)\n"
              << "at a given point x from [0; 1] with a given accuracy eps.\n";
}

/**
 * Prints the entered data and the result in the required formats.
 */
void printReport(double x, double eps, double result) {
    std::cout << std::uppercase << std::scientific
              << "for x = " << std::setprecision(7) << x << '\n'
              << "for eps = " << std::setprecision(9) << eps << '\n'
              << std::fixed << std::setprecision(8)
              << "result = " << result << '\n';
}

}  // namespace

int main() {
    printIntroduction();
    try {
        const double x = readX();
        const double eps = readEps();
        std::cout << "\n***** do calculations ...";
        const double result = s(x, eps);
        std::cout << " done\n";
        printReport(x, eps, result);
    } catch (const std::exception& error) {
        std::cout << "\n***** error\n" << error.what() << '\n';
    }
    return 0;
}
