#include <stdio.h>
#include <math.h>

#define NX 10
#define NT 100

/* Thomas Algorithm for tridiagonal system */
void thomasSolver(
    int n,
    double a[],
    double b[],
    double c[],
    double d[],
    double x[]
) {
    double c_star[n];
    double d_star[n];

    c_star[0] = c[0] / b[0];
    d_star[0] = d[0] / b[0];

    for (int i = 1; i < n; i++) {
        double m = b[i] - a[i] * c_star[i - 1];
        c_star[i] = c[i] / m;
        d_star[i] = (d[i] - a[i] * d_star[i - 1]) / m;
    }

    x[n - 1] = d_star[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        x[i] = d_star[i] - c_star[i] * x[i + 1];
    }
}

int main() {

    double L = 1.0;
    double T = 0.1;
    double alpha = 0.01;

    double dx = L / (NX - 1);
    double dt = T / NT;
    double r = alpha * dt / (dx * dx);

    double u[NX];
    double u_new[NX];

    /* Initial condition u(x,0) = sin(pi x) */
    for (int i = 0; i < NX; i++) {
        double x = i * dx;
        u[i] = sin(M_PI * x);
    }

    /* Crank–Nicolson coefficients */
    double a[NX - 2], b[NX - 2], c[NX - 2];

    for (int i = 0; i < NX - 2; i++) {
        a[i] = -r / 2.0;
        b[i] = 1.0 + r;
        c[i] = -r / 2.0;
    }

    FILE *fp = fopen("solution.csv", "w");

    /* Time stepping */
    for (int n = 0; n < NT; n++) {
        double d[NX - 2];
        double interior[NX - 2];

        for (int i = 1; i < NX - 1; i++) {
            d[i - 1] =
                r / 2.0 * u[i - 1] +
                (1.0 - r) * u[i] +
                r / 2.0 * u[i + 1];
        }

        thomasSolver(NX - 2, a, b, c, d, interior);

        for (int i = 1; i < NX - 1; i++) {
            u_new[i] = interior[i - 1];
        }

        u_new[0] = 0.0;
        u_new[NX - 1] = 0.0;

        for (int i = 0; i < NX; i++) {
            u[i] = u_new[i];
            fprintf(fp, "%lf%s", u[i], (i == NX - 1) ? "\n" : ",");
        }
    }

    fclose(fp);

    printf("Simulation complete. Data saved to solution.csv\n");
    return 0;
}

