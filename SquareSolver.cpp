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

//CheckSolver Test4 = {2, 0, -3, sqrt(1.5), -sqrt(1,5), 2, 4};



//-----------------------------------------------------------------------------

const int INF_ROOTS = -1;
const double eps = 0.00000001;

//-----------------------------------------------------------------------------

void flush ();

void RunTests (CheckSolver);

bool Compare (double a, double b);

int SolveLinear (double b, double c, double* x1);

int SolveSquare (double a, double b, double c, double* x1, double* x2);

int Solver (double a, double b, double c, double* x1, double* x2);

//-----------------------------------------------------------------------------

int main()
{
    CheckSolver Test1 = {1, 5, 0, 0, -5, 2, 1};
    CheckSolver Test2 = {1, 0, -4, 2, -2, 2, 2};
    CheckSolver Test3 = {2, 3, -5, 1, -2.5, 2, 3};
    CheckSolver Test4 = {9, -98, 89, 1, 89.0/9, 2, 4};
    CheckSolver Test5 = {1, 4, 4, -2, 0, 1, 5};
    CheckSolver Test6 = {178, 1, 3, 0, 0, 0, 6};
    CheckSolver Test7 = {1, 6, 5, -1, -5, 2, 7};
    CheckSolver Test8 = {3, -24, 45, 3, 5, 2, 8};
    CheckSolver Test9 = {1, 3, -18, -6, 3, 2, 9};
    CheckSolver Test10 = {0, 0, 0, 0, 0, -1, 10};
    CheckSolver arr [10] = {Test1, Test2, Test3, Test4, Test5, Test6, Test7, Test8, Test9, Test10};
    for (int i = 0; i < 10; i++)
    {
        RunTests (arr [i]);
    }
    return 0;
}

//-----------------------------------------------------------------------------

int SolveLinear (double b, double c, double* x1)
{
    if (Compare (b, 0))
    {
        return (Compare (c, 0)) ? INF_ROOTS : 0;
    }
    else
    {
        if (Compare (c, 0))
        {
            return 1;
        }
        else
        {
            *x1 = -b/c;
            return 1;
        }
    }
}

//-----------------------------------------------------------------------------

int SolveSquare (double a, double b, double c, double* x1, double* x2)
{
    double d = b*b-4*a*c;
    if (d < 0)
    {
        return 0;
    }
    else if (Compare (d, 0))
    {
        *x1 = -b/(2*a);
        return 1;
    }
    else
    {
        double sqrtD = sqrt (d);
        *x1 = (-b+sqrtD)/(2*a);
        *x2 = -(b+sqrtD)/(2*a);
        return 2;
    }
}

//-----------------------------------------------------------------------------

int Solver (double a, double b, double c, double* x1, double* x2)
{
    assert (isfinite(a));
    assert (isfinite(b));
    assert (isfinite(c));

    return (Compare (a, 0))? SolveLinear (b, c, x1) : SolveSquare (a, b, c, x1, x2);
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

bool Compare (double a, double b)
{
    return (fabs (a-b) < eps) ? 1 : 0;
}

//-----------------------------------------------------------------------------

void RunTests (CheckSolver Test)
{
    double x1 = 0, x2 = 0;
    int nRoots = Solver (Test.a, Test.b, Test.c, &x1, &x2);
    if (nRoots != Test.nRootsExpected)
    {
        printf ("ERROR Test %d: a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, nRoots = %d.\n"
                "Expected: x1 = %lg, x2 = %lg, nRoots = %d.\n",
                 Test.numTest, Test.a, Test.b, Test.c, x1, x2, nRoots, Test.x1Expected, Test.x2Expected, Test.nRootsExpected);

        return;
    }
    if (Compare (x1, Test.x1Expected) && Compare (x2, Test.x2Expected))
    {
        printf ("Тест%d завершился успешно.\n", Test.numTest);
        return;
    }
    else if (Compare (x1, Test.x2Expected) && Compare (x2, Test.x1Expected))
    {
        printf ("Тест%d завершился успешно.\n", Test.numTest);
        return;
    }
    else
    {
        printf ("ERROR Test %d: a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, nRoots = %d.\n"
                "Expected: x1 = %lg, x2 = %lg, nRoots = %d.\n",
                 Test.numTest, Test.a, Test.b, Test.c, x1, x2, nRoots, Test.x1Expected, Test.x2Expected, Test.nRootsExpected);
        return;
    }
}
