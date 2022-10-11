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

/*double dddFunA(double x) {
    return 79.2 * x - (8 * (6 * pow((0.02 + x * x), 2) - 24 * x * x * (0.02 + x * x)) - 48 * x * x * x - 24 * x * pow((0.02 + x * x), 2)) / pow((0.02 + x * x), 5);
}*/

double FunB(double x) {
    return  2.7 * pow(sin(x), 3) + 3.3 * pow(cos(x), 3);
}

double dFunB(double x) {
    return 8.1 * pow(sin(x), 2) * cos(x) - 9.9 * sin(x) * pow(cos(x), 2);
}
double ddFunB(double x) {
    return -8.1 * pow(sin(x), 3) + 19.8 * pow(sin(x), 2) * cos(x) + 16.2 * sin(x) * pow(cos(x), 2) - 9.9 * pow(cos(x), 3);
}

bool Max(double x, double y) {
    return x <= y;
}

bool Min(double x, double y) {
    return x >= y;
}

void Print(std::string name, double(*Fun)(double), double esp, double point, int counter, bool(*Operation)(double, double) = Min) {
    std::string fun = Fun == FunA ? "FunA" : "FunB"; std::string operation = Operation == Min ? "Min" : "Max";
    std::cout << "Method " << name << std::endl;
    std::cout << fun << std::endl;
    std::cout << "Eps = " << esp << "\nPoint " << operation << " = " << point << "\nFunction value in point " << Fun(point) << "\nCounter = " << counter << std::endl;
}

/*double MidPoint(double(*Fun)(double), double a, double b, bool(*Operator)(double, double)) {
    double x, esp = 0.001;
    double(*dFun)(double) = Fun == FunA ? dFunA : dFunB;

    while ((b - a) > 2 * esp) {
        x = (a + b) / 2;

        if (Operator(dFun(x),0))
            b = x;
        else
            a = x;
    }

    return (a + b) / 2;
}*/

void Indent(int n = 1) {
    for (int i = 0; i < n; i++)
        std::cout << "=====================================================================" << std::endl;
    std::cout << "\n\n";
}

void Tangent(double(*Fun)(double), double esp, double a, double b, bool(*Operator)(double, double) = Min) {
    int counter = 0; double x = 0, dfa, dfb;
    double(*dFun)(double) = Fun == FunA ? dFunA : dFunB;
    //dFun = dF; Fun = F;

    while ((b - a) > 2 * esp) {
        dfa = dFun(a); dfb = dFun(b);
        x = (Fun(a) - Fun(b) - a * dfa + b * dfb) / (dfb - dfa);

        if (Operator(dFun(x), 0))
            b = x;
        else
            a = x;

        counter++;
        if (counter > 1000000) break;
    }

    Print("Tangent", Fun, esp, (a + b) / 2, counter, Operator);
}


void MidPoint(double(*Fun)(double), double esp, double a, double b, bool(*Operator)(double, double) = Min) {
    int counter = 0; double x, dfx;
    double(*dFun)(double) = Fun == FunA ? dFunA : dFunB;

    while ((b - a) > 2 * esp) {
        x = (a + b) / 2;
        dfx = dFun(x);

        if (Operator(dFun(x), 0))
            b = x;
        else
            a = x;

        counter++;
    }

    Print("Mid Point", Fun, esp, (a + b) / 2, counter, Operator);
}

void Newton(double(*Fun)(double), double esp, double xn) {
    int counter = 0; double x = xn, x1 = xn-1;
    double(*dFun)(double) = Fun == FunA ? dFunA : dFunB;
    double(*ddFun)(double) = Fun == FunA ? ddFunA : ddFunB;
    
    while (abs(x-x1) > esp) {
        x1 = x;
        x = x - dFun(x) / ddFun(x);
        counter++;
    }

    Print("Newton", Fun, esp, x, counter, ddFunB(x) <= 0 ? Max : Min);
}

/*double SearchPointForNewton(double(*Fun)(double), double a, double b) {
    double M3, m2, x;
    M3 = MidPoint(Fun, a, b, Max);
    m2 = MidPoint(Fun, a, b, Min);
    x = MidPoint(Fun, a, b, Min);

    return 2*m2/M3 + x + 0.0001;
}*/

int main()
{
    std::cout << "Input interval for Fun A" << std::endl;
    double a, b;
    std::cin >> a >> b;

    for (double esp = 0.001; esp >= 0.00001; esp /= 100) {
        MidPoint(FunA, esp, a, b);
        std::cout << "\n\n";
    }

    Indent();

    for (double esp = 0.001; esp >= 0.00001; esp /= 100) {
        Tangent(FunA, esp, a, b);
        std::cout << "\n\n";
    }

    Indent();

    for (double esp = 0.001; esp >= 0.00001; esp /= 100) {
        Newton(FunA, esp, b);
        std::cout << "\n\n";
    }

    Indent(2);

    std::cout << "Fun B" << std::endl;
    std::cout << "Intervals function B" << std::endl;

    std::vector<double> intervals = { 0,0.5,0.9,3 * PI / 4 };

    for (int i = 0; i < intervals.size() - 1; i++)
        std::cout << "(" << intervals[i] << ";" << intervals[i + 1] << ") ";

    std::cout << "\n\n";


    for (double esp = 0.001; esp >= 0.00001; esp /= 100) {
        for (int i = 0; i < intervals.size() - 1; i++) {
            MidPoint(FunB, esp, intervals[i], intervals[i + 1], i % 2 == 0 ? Max : Min);
            std::cout << "\n\n";
        }
        Indent();
    }


    for (double esp = 0.001; esp >= 0.00001; esp /= 100) {
        for (int i = 0; i < intervals.size() - 1; i++) {
            Tangent(FunB, esp, intervals[i], intervals[i + 1], i % 2 == 0 ? Max : Min);
            std::cout << "\n\n";
        }
        Indent();
    }

    for (double esp = 0.001; esp >= 0.00001; esp /= 100) {
        for (int i = 0; i < intervals.size() - 1; i++) {
            Newton(FunB, esp, intervals[i]);
            std::cout << "\n\n";
        }
        Indent();
    }


    return 0;
}