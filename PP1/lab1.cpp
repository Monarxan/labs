#include <cmath>
#include <iomanip>
#include <iostream>
#include <numbers>
#include <optional>

namespace {

/**
 * Checks whether the expression is defined for x.
 * Only arccos(x - 6) restricts x here: |x - 6| <= 1, i.e. x in [5; 7].
 * On that segment the denominators (x - 14), (x + 9) and the radicand
 * (x + 10) are always fine, so no other conditions are needed.
 */
bool isInDomain(double x) {
    return std::abs(x - 6.0) <= 1.0;
}

/**
 * Evaluates the expression of variant 179 at x. No checks are made.
 */
double f(double x) {
    return std::sin(12.0 / 53.0) - 20.0 * std::numbers::pi
           + 51.0 * std::numbers::e * 12.0 / ((x - 14.0) * (x + 9.0))
           + 15.0 * std::acos(x - 6.0)
           - (13.0 + std::sqrt(x + 10.0)) / (x - 14.0);
}

/**
 * Returns f(x), or an empty value if x is outside the domain.
 */
std::optional<double> calculate(double x) {
    if (!isInDomain(x)) {
        return std::nullopt;
    }
    return f(x);
}

void printIntroduction() {
    std::cout << "Author: Popov Kostiantyn, group ITK-11\n"
              << "Variant 179: computes a function of a real variable x\n"
              << "(prints \"undefined\" if x is outside the domain).\n"
              << "Enter a real number x (5 <= x <= 7): ";
}

/**
 * Runs the calculation for x and prints the report in the required format.
 */
void reportResult(double x) {
    std::cout << "\n***** do calculations ...";
    const std::optional<double> result = calculate(x);
    std::cout << " done\n";

    std::cout << std::fixed << std::setprecision(5) << "for x = " << x << '\n';
    if (result) {
        std::cout << std::setprecision(9) << "result = " << *result << '\n';
    } else {
        std::cout << "result = undefined\n";
    }
}

}  // namespace

int main() {
    printIntroduction();

    double x{};
    std::cin >> x;

    if (std::cin.fail()) {
        std::cout << "\nwrong input\n";
    } else {
        reportResult(x);
    }
    return 0;
}
