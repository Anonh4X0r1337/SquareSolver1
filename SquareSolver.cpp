#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "TXLib.h"

const int BESK = 10;
double eps = 0.000001;

//-----------------------------------------------------------------------------

bool Compare(double a);

int SolveLinear (double b, double c, double* x1);

int SolveSquare (double a, double b, double c, double* x1, double* x2);

void Solver (double a, double b, double c, double* x1, double* x2);

//-----------------------------------------------------------------------------

int main() {
double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
scanf("%lf %lf %lf", &a, &b, &c);
Solver (a, b, c, &x1, &x2);

return 0;
}

//-----------------------------------------------------------------------------

bool Compare(double a) {
if (fabs(a-0)<eps) {
    return true;
}
else {
    return false;
}
}

//-----------------------------------------------------------------------------

int SolveLinear (double b, double c, double* x1) {
if (Compare (b)) {
    return (Compare(c))? BESK : 0;
    }
else {
    if (Compare(c)) {
        return 1;
    }
    else {
        *x1 = -b/c;
        return 1;
        }
    }
}

//-----------------------------------------------------------------------------

int SolveSquare (double a, double b, double c, double* x1, double* x2) {
double d = b*b-4*a*c;
if (d<0) {
    return 0;
}
else if (Compare(d)) {
    *x1 = -b/(2*a);
    return 1;
}
else {
    double k = sqrt(d);
    *x1 = (-b+k)/(2*a);
    *x2 = -(b+k)/(2*a);
    return 2;
    }
}

//-----------------------------------------------------------------------------

void Solver (double a, double b, double c, double* x1, double* x2) {
if (Compare(a)) {
    int nRoots = SolveLinear(b, c, x1);
    switch (nRoots) {
        case 1:
            printf ("1 корень: X = %lg", *x1);
            break;
        case 0:
            printf ("Нет корней");
            break;
        case BESK:
            /*assert (std::isfinite(a));
            assert (std::isfinite(b));
            assert (std::isfinite(c));

            assert (x1 != NULL);
            assert (x2 != NULL);
            assert (x1 != x2);*/

            printf ("Х-любое число");
            break;
        default: printf ("main(): ERROR: nRoots = %d\n", nRoots);
    }
}
else {
    int nRoots = SolveSquare(a, b, c, x1, x2);
    switch (nRoots) {
        case 2:
            printf ("2 корня: X1 = %lg, X2 = %lg", *x1, *x2);
            break;
        case 1:
            printf ("1 корень: X = %lg", *x1);
            break;
        case 0:
            printf ("Нет корней");
            break;
        default: printf ("main(): ERROR: nRoots = %d\n", nRoots);
    }
}
}
