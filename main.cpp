#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;

double FunctionFromTask(double x) {
    return -sqrt(x) * std::sin(x) + 2;
}

void PrintPart1(double ak, double bk) {
    cout << '|' << std::setw(13) << ak << ' '
         << '|' << std::setw(13) << bk << ' '
         << '|' << std::setw(13) << bk - ak << ' '
         << '|' << std::setw(13) << FunctionFromTask(ak) << ' '
         << '|' << std::setw(13) << FunctionFromTask(bk) << ' ' << '|' << '\n';
}

void PrintPart2(uint N, double xk, double delta) {
    cout << '|' << std::setw(10) << N << "      "
         << '|' << std::setw(10) << xk << " +- " << delta << " |" << '\n';
}

const double LOWER_EDGE = 1.;
const double UPPER_EDGE = 4.;
const double EPSILON = 0.1;

void Dichotomy(double lower, double upper) {
    cout << "Part 1. Sequential search (dichotomy) :\n"
         << std::string(76, '_') << '\n'
         << '|' << std::string(3, ' ') << "Start of" << std::string(3, ' ')
         << '|' << std::string(4, ' ') << "End of" << std::string(4, ' ')
         << '|' << std::string(2, ' ') << "Length of" << std::string(3, ' ')
         << '|' << std::string(14, ' ')
         << '|' << std::string(14, ' ') << '|' << '\n'
         << '|' << std::string(1, ' ') << "the interval" << std::string(1, ' ')
         << '|' << std::string(1, ' ') << "the interval" << std::string(1, ' ')
         << '|' << std::string(1, ' ') << "the interval" << std::string(1, ' ')
         << '|' << std::string(4, ' ') << "f(ak)" << std::string(5, ' ')
         << '|' << std::string(4, ' ') << "f(bk)" << std::string(5, ' ') << '|' << '\n'
         << '|' << std::string(5, ' ') << "(ak)" << std::string(5, ' ')
         << '|' << std::string(5, ' ') << "(bk)" << std::string(5, ' ')
         << '|' << std::string(5, ' ') << "(l)" << std::string(6, ' ')
         << '|' << std::string(14, ' ')
         << '|' << std::string(14, ' ') << '|' << '\n'
         << std::string(76, '_') << '\n';
    const double DELTA = .01;
    while (upper - lower > EPSILON) {
        PrintPart1(lower, upper);
        double x1 = lower + (upper - lower) / 2 - DELTA,
                x2 = lower + (upper - lower) / 2 + DELTA;
        FunctionFromTask(x1) < FunctionFromTask(x2)
        ? upper = x1
        : lower = x2;
    }
    cout << '|' << std::setw(13) << lower << ' '
         << '|' << std::setw(13) << upper << ' '
         << '|' << std::setw(13) << upper - lower << ' '
         << '|' << std::string(9, ' ') << "l < epsilon" << std::string(9, ' ') << '|' << '\n'
         << std::string(76, '_') << '\n'
         << "x = " << std::fixed << std::setprecision(3)
         << (lower + upper) / 2 << " +- " << (lower + upper) / 2 - lower << "\n\n";
}

void OptimalPassiveSearch(double lower, double upper) {
    cout << "Part 2. Optimal passive search :\n"
         << std::string(39, '_') << '\n'
         << '|' << std::string(4, ' ') << "Number of" << std::string(3, ' ') ///16|20
         << '|' << std::string(3, ' ') << "The value of X" << std::string(3, ' ') <<"|\n"
         << '|' << std::string(1, ' ') << "the points (N)" << std::string(1, ' ')
         << '|' << std::string(3, ' ') << "in the minimum" << std::string(3, ' ') << "|\n"
            << std::string(39, '_') << '\n';
    uint N = 1;
    double delta = (upper - lower) / (N + 1);
    double xForMinY;
    while (delta > EPSILON) {
        std::vector<double> VectorOfYk;
        delta = (upper - lower) / (N + 1);
        for (uint k = 1; k <= N; ++k) {
            VectorOfYk.push_back(FunctionFromTask((upper - lower) / (N + 1) * k + lower));
        }
        uint kForMinY = std::min_element(VectorOfYk.begin(), VectorOfYk.end()) - VectorOfYk.begin() + 1;
        xForMinY = (upper - lower) / (N + 1) * kForMinY + lower;
        PrintPart2(N, xForMinY, delta);
        N++;
    }
    cout << std::string(39, '_') << '\n'
            << "x = " << std::fixed << std::setprecision(3)
            << xForMinY << " +- " << delta << "\n\n";
}

int main() {
    cout << "Variant 7: \t -sqrt(x) * sin(x) + 2 \t [" << LOWER_EDGE << "; " << UPPER_EDGE << "]\n";

    Dichotomy(LOWER_EDGE, UPPER_EDGE);  // Part 1. Dichotomy

    OptimalPassiveSearch(LOWER_EDGE, UPPER_EDGE); // Part 2. Optimal Passive Search

    return 0;
}
