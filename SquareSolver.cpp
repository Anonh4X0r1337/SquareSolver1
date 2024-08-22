#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <TXLib.h>

const int INF_ROOTS = 10;
const double eps = 0.000001;

//-----------------------------------------------------------------------------

double ScanIn ();

void flush ();

void PrintOut (int nRoots, double x1, double x2);

bool Compare (double a, double b);

int SolveLinear (double b, double c, double* x1);

int SolveSquare (double a, double b, double c, double* x1, double* x2);

int Solver (double a, double b, double c, double* x1, double* x2);

//-----------------------------------------------------------------------------

int main()
{
    double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
    a = ScanIn ();
    b = ScanIn ();
    c = ScanIn ();
    int nRoots = Solver (a, b, c, &x1, &x2);
    PrintOut (nRoots, x1, x2);

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

double ScanIn ()
{
    while (1)
    {
        double a = 0;
        int result = scanf ("%lg", &a);
        if (result == 0 || getchar () != '\n')
        {
            flush ();
            printf ("������� ��������� ��������:\n");
            continue;
        }
        else
        {
            return a;
        }
    }
}

//-----------------------------------------------------------------------------

void PrintOut (int nRoots, double x1, double x2)
{
    switch (nRoots)
    {
        case 2:
            printf ("2 �����: X1 = %lg, X2 = %lg", x1, x2);
            break;
        case 1:
            printf ("1 ������: X = %lg", x1);
            break;
        case 0:
            printf ("��� ������");
            break;
        case INF_ROOTS:
            printf ("�-����� �����");
            break;

        default: printf ("main(): ERROR: nRoots = %d\n", nRoots);
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

bool Compare (double a, double b)
{
    return (fabs (a-b) < eps) ? 1 : 0;
}

//-----------------------------------------------------------------------------

/*int RT (double a, double b, double c, double x1Expected, double x2Expected, int nRootsExpected)
{
    double x1 = 0, x2 = 0;
    int nRoots = Solver (a, b, c, &x1, &x2);
    if (nRoots != nRootsExpected || x1 != x1Expected || x2 != x2Expected)
    {
        printf ("ERROR Test %d; a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, nRoots = %d"
            "Expected: x1 = %lg, x2 = %lg, nRoots = %d\n",
            a, b, c, x1, x2, nRoots, x1Expected, x2Expected, nRootsExpected);
        return -1;
    }
    else
    {
        return 0;
    }
} */
