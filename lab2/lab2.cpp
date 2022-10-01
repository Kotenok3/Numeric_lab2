#include <iostream>
#include <vector>
const double PI = 3.141592653589793238463;

double F(double x) {
    return x * x;
}

double dF(double x) {
    return 2 * x;
}

double FunA(double x) {
    return 3.3 * x * x * x * x + 3 / (0.02 + x * x);
}

double dFunA(double x) {
    return 13.2 * x * x * x - 6 * x / pow((0.02 + x * x), 2);
}

double ddFunA(double x) {
    return 39.6 * x * x + (6 * pow((0.02 + x * x), 2) - 24 * x * x * (0.02 + x * x)) / pow((0.02 + x * x), 4);
}

double dddFunA(double x) {
    return 79.2 * x - (8 * (6 * pow((0.02 + x * x), 2) - 24 * x * x * (0.02 + x * x)) - 48 * x * x * x - 24 * x * pow((0.02 + x * x), 2)) / pow((0.02 + x * x), 5);
}

double FunB(double x) {
    return  2.7 * pow(sin(x), 3) + 3.3 * pow(cos(x), 3);
}

double dFunB(double x) {
    return -1;
}
double ddFunB(double x) {
    return -1;
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

double MidPoint(double(*Fun)(double), double a, double b) {
    double x, esp = 0.001;
    double(*dFun)(double) = Fun == FunA ? dFunA : dFunB;

    while ((b - a) > 2 * esp) {
        x = (a + b) / 2;

        if (dFun(x) >= 0)
            b = x;
        else
            a = x;
    }

    return (a + b) / 2;
}

void Indent(int n = 1) {
    for (int i = 0; i < n; i++)
        std::cout << "=====================================================================" << std::endl;
    std::cout << "\n\n";
}

void Tangent(double(*Fun)(double), double esp, double a, double b) {
    int counter = 0; double x1 = 0, x2, dfa, dfb;
    double(*dFun)(double) = Fun == FunA ? dFunA : dFunB;
    //dFun = dF; Fun = F;

    while ((b - a) > 2 * esp) {
        dfa = dFun(a); dfb = dFun(b);
        x1 = (Fun(a) - Fun(b) - a * dfa + b * dfb) / (dfb - dfa);

        if (dFun(x1) >= 0)
            b = x1;
        else
            a = x1;

        counter++;
    }

    Print("Tangent", Fun, esp, (a + b) / 2, counter);
}

void MidPoint(double(*Fun)(double), double esp, double a, double b) {
    int counter = 0; double x, dfx;
    double(*dFun)(double) = Fun == FunA ? dFunA : dFunB;

    while ((b - a) > 2 * esp) {
        x = (a + b) / 2;
        dfx = dFun(x);

        if (dFun(x) >= 0)
            b = x;
        else
            a = x;

        counter++;
    }

    Print("Mid Point", Fun, esp, (a + b) / 2, counter);
}

void Newton(double(*Fun)(double), double esp, double xn) {
    int counter = 0; double x = xn;
    double(*dFun)(double) = Fun == FunA ? dFunA : dFunB;
    double(*ddFun)(double) = Fun == FunA ? ddFunA : ddFunB;
    
    while (abs(dFun(x)) > esp) {
        x = x - dFun(x) / ddFun(x);
        counter++;
    }

    Print("Newton", Fun, esp, x, counter);
}



int main()
{
    std::cout << "Input interval for Fun A" << std::endl;
    double a, b;
    std::cin >> a >> b;

    for (double esp = 0.001; esp >= 0.00001; esp /= 100) {
        MidPoint(FunA, esp, a, b);
        std::cout << "\n\n";
    }

    for (double esp = 0.001; esp >= 0.00001; esp /= 100) {
        Newton(FunA, esp,(a+b)/2);
        std::cout << "\n\n";
    }

    


    return 0;
}