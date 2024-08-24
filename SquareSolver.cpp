#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <TXLib.h>

struct CheckSolver
{
    double a, b, c;
    double x1Expected, x2Expected;
    int nRootsExpected, numTest;
};

enum Roots
{
    TWO_ROOTS =  2,
    ONE_ROOT  =  1,
    NO_ROOTS  =  0,
    INF_ROOTS = -1,
};

//-----------------------------------------------------------------------------

const double eps = 1e-9;

//-----------------------------------------------------------------------------

void flush ();

void PrintError (CheckSolver, double x1, double x2, int nRoots);

void RunTests (CheckSolver*);

void RunOneTest (CheckSolver);

bool CompareDoubles (double a, double b);

int SolveLinear (double b, double c, double* x1);

int SolveSquare (double a, double b, double c, double* x1, double* x2);

int Solver (double a, double b, double c, double* x1, double* x2);

//-----------------------------------------------------------------------------

int main()
{
    CheckSolver arr [13] = {{1,     5, 0, -5, 0, TWO_ROOTS, 1},
                            {1,     0, -4, -2, 2, TWO_ROOTS, 2},
                            {2,     3, -5, -2.5, 1, TWO_ROOTS, 3},
                            {9,   -98, 89, 1, 89.0/9, TWO_ROOTS, 4},
                            {  1,     4, 4, NAN, -2, ONE_ROOT, 5},
                            {178,   1, 3, NAN, NAN, NO_ROOTS, 6},
                            {  0,     6, 5, NAN, -5.0/6, ONE_ROOT, 7},
                            {  3,   -24, 45, 3, 5, TWO_ROOTS, 8},
                            {  0,     0, -18, NAN, NAN, NO_ROOTS, 9},
                            {  0,     0, 0, NAN, NAN, INF_ROOTS, 10},
                            {  3,   -24, 45, 3, 5, TWO_ROOTS, 11},
                            {9,      0, -729, -9, 9, TWO_ROOTS, 12},
                            {2, 0, -3, -sqrt(1.5), sqrt(1.5), TWO_ROOTS, 13}};

    RunTests (arr);

    return 0;
}

//-----------------------------------------------------------------------------

int SolveLinear (double b, double c, double* x2)
{
    assert (isfinite (b));
    assert (isfinite (c));
    assert (x2 != NULL);

    if (CompareDoubles (b, 0.0))
    {
        *x2 = NAN;
        return (CompareDoubles (c, 0.0)) ? INF_ROOTS : NO_ROOTS;
    }
    else
    {
        if (CompareDoubles (c, 0.0))
        {
            return ONE_ROOT;
        }
        else
        {
            *x2 = -c/b;
            return ONE_ROOT;
        }
    }
}

//-----------------------------------------------------------------------------

int SolveSquare (double a, double b, double c, double* x1, double* x2)
{
    assert (isfinite (a));
    assert (isfinite (b));
    assert (isfinite (c));
    assert (x1 != x2);
    assert (x1 != NULL);
    assert (x2 != NULL);

    double d = b*b-4*a*c;
    if (d < 0)
    {
        *x1 = NAN;
        *x2 = NAN;
        return NO_ROOTS;
    }
    else if (CompareDoubles (d, 0.0))
    {
        *x2 = -b/(2*a);
        *x1 = NAN;
        return ONE_ROOT;
    }
    else
    {
        double sqrtD = sqrt (d);
        *x1 = -(b+sqrtD)/(2*a);
        *x2 = (-b+sqrtD)/(2*a);
        return TWO_ROOTS;
    }
}

//-----------------------------------------------------------------------------

int Solver (double a, double b, double c, double* x1, double* x2)
{
    assert (isfinite (a));
    assert (isfinite (b));
    assert (isfinite (c));
    assert (x1 != x2);
    assert (x1 != NULL);
    assert (x2 != NULL);

    if (CompareDoubles (a, 0.0))
    {
        *x1 = NAN;
        return SolveLinear (b, c, x2);
    }
    else
    {
        return SolveSquare (a, b, c, x1, x2);
    }
}

//-----------------------------------------------------------------------------

void flush ()
{
    while (getchar () != '\n')
    {
        continue;
    }
}

//-----------------------------------------------------------------------------

bool CompareDoubles (double a, double b)
{
    return (fabs (a-b) < eps) ? 1 : 0;
}

//-----------------------------------------------------------------------------

void RunTests (CheckSolver* arr)
{
    for (int i = 0; i < 13; i++)
    {
        RunOneTest (arr[i]);
    }
}

//-----------------------------------------------------------------------------

void PrintError (CheckSolver Test, double x1, double x2, int nRoots)
{
    printf ("ERROR Test %d: a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, nRoots = %d.\n"
                "Expected: x1 = %lg, x2 = %lg, nRoots = %d.\n",
                 Test.numTest, Test.a, Test.b, Test.c, x1, x2, nRoots, Test.x1Expected, Test.x2Expected, Test.nRootsExpected);
}

//-----------------------------------------------------------------------------

void RunOneTest (CheckSolver Test)
{
    double x1 = 0, x2 = 0;
    int nRoots = Solver (Test.a, Test.b, Test.c, &x1, &x2);
    if (nRoots != Test.nRootsExpected)
    {
        PrintError (Test, x1, x2, nRoots);
        return;
    }
    if (isnan (Test.x1Expected))
    {
        if (isnan (x1))
        {
            if (isnan (Test.x2Expected))
            {
                if (isnan (x2))
                {
                    printf ("Тест%d завершился успешно.\n", Test.numTest);
                    return;
                }
                else
                {
                    PrintError (Test, x1, x2, nRoots);
                    return;
                }
            }
            else if (CompareDoubles (x2, Test.x2Expected))
            {
                printf ("Тест%d завершился успешно.\n", Test.numTest);
                return;
            }
            else
            {
                PrintError (Test, x1, x2, nRoots);
                return;
            }
        }
        else
        {
            PrintError (Test, x1, x2, nRoots);
            return;
        }
    }
    else if (CompareDoubles (x1, Test.x1Expected) && CompareDoubles (x2, Test.x2Expected))
    {
        printf ("Тест%d завершился успешно.\n", Test.numTest);
        return;
    }
    else
    {
        PrintError (Test, x1, x2, nRoots);
        return;
    }
}
