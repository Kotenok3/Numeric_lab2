#include <iostream>
#include <vector>
const double PI = 3.141592653589793238463;

double FunA(double x) {

    return 3.3 * x * x * x * x + 3 / (0.02 + x * x);
}

double FunB(double x) {

    return  2.7 * std::pow(std::sin(x), 3) + 3.3 * std::pow(std::cos(x), 3);
}

bool Min(double x, double y) {
    return x <= y;
}

bool Max(double x, double y) {
    return x >= y;
}

void Print(std::string name, double(*Fun)(double), double esp, double point, int counter, bool(*Operation)(double, double) = Min) {
    std::string fun = Fun == FunA ? "FunA" : "FunB"; std::string operation = Operation == Min ? "Min" : "Max";
    std::cout << "Method " << name << std::endl;
    std::cout << fun << std::endl;
    std::cout << "Eps = " << esp << "\nPoint " << operation << " = " << point << "\nFunction value in point " << Fun(point) << "\nCounter = " << counter << std::endl;
}

void Indent(int n = 1) {
    for (int i = 0; i < n; i++)
        std::cout << "=====================================================================" << std::endl;
    std::cout << "\n\n";
}

void Dichotomy(double(*Fun)(double), double esp, double a, double b, double delta = 0.001, bool(*Operation)(double, double) = Min) {
    int counter = 0; double x1, x2;

    while ((b - a) > 2 * esp) {
        x1 = (a + b - delta) / 2;
        x2 = (a + b + delta) / 2;

        if (Operation(Fun(x1), Fun(x2)))
            b = x2;
        else
            a = x1;

        counter++;
    }

    Print("Dichotomy", Fun, esp, (a + b) / 2, counter, Operation);
}

void GoldenSection(double(*Fun)(double), double esp, double a, double b, bool(*Operation)(double, double) = Min) {
    int counter = 0; double x1, x2;

    while ((b - a) > 2 * esp) {
        x1 = a + (3 - std::sqrt(5)) * (b - a) / 2;
        x2 = a + (std::sqrt(5) - 1) * (b - a) / 2;

        if (Operation(Fun(x1), Fun(x2)))
            b = x2;
        else
            a = x1;

        counter++;
    }

    Print("GoldenSection", Fun, esp, (a + b) / 2, counter, Operation);
}

int main()
{
    std::cout << "Input interval for Fun A" << std::endl;
    double a, b;
    std::cin >> a >> b;
    double(*Fun)(double) = FunA;


    for (double esp = 0.001; esp >= 0.00001; esp /= 100) {
        Dichotomy(Fun, esp, a, b, esp);
        std::cout << "\n\n";
    }

    Indent();

    for (double esp = 0.001; esp >= 0.00001; esp /= 100) {
        GoldenSection(Fun, esp, a, b);
        std::cout << "\n\n";
    }



    Indent(2);
    std::cout << "Fun B" << std::endl;
    std::cout << "Intervals function B" << std::endl;

    std::vector<double> intervals = { 0,0.5,1,3 * PI / 4 };  Fun = FunB;

    for (int i = 0; i < intervals.size() - 1; i++)
        std::cout << "(" << intervals[i] << ";" << intervals[i + 1] << ") ";

    std::cout << "\n\n";


    for (double esp = 0.001; esp >= 0.00001; esp /= 100) {
        for (int i = 0; i < intervals.size() - 1; i++) {
            Dichotomy(Fun, esp, intervals[i], intervals[i + 1], esp, i % 2 == 0 ? Max : Min);
            std::cout << "\n\n";
        }
        Indent();
    }


    for (double esp = 0.001; esp >= 0.00001; esp /= 100) {
        for (int i = 0; i < intervals.size() - 1; i++) {
            GoldenSection(Fun, esp, intervals[i], intervals[i + 1], i % 2 == 0 ? Max : Min);
            std::cout << "\n\n";
        }
        Indent();
    }



    return 0;
}