#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define MAX_BUF 1000
#define MAX_LINES 8192

int stringcmp(const void *a, const void *b) {
    char *_a = *(char **) a;
    char *_b = *(char **) b;
    return strcmp(_a, _b);
}

int main(int argc, char **argv) {

    if (argc < 3) {
        printf("Nalezy podac min. 2 argumenty, tj. skrypt <plik_z_tekstem> <plik_z_nr_linii> [wyjscie]\n");
        return 1;
    }

    FILE *ln = fopen(argv[1], "r");//tekst
    FILE *nr = fopen(argv[2], "r");//numery linii
    FILE *ps = fopen(argc>3?argv[3]:"plik_z_wynikiem", "w");//zapis posortowanych

    if (ln == NULL || nr == NULL) {
        printf("Nie mozna bylo wczytac plikow: %s lub %s\n", argv[1], argv[2]);
        return 1;
    }


    char *buf = malloc((MAX_BUF + 1) * sizeof(*buf));
    char **linie = malloc(MAX_LINES * sizeof(*linie));

    int ile = 0;
    for (; fgets(buf, MAX_BUF + 1, ln) != NULL && ile < MAX_LINES; ile++)
        strcpy((linie[ile] = malloc((strlen(buf) + 1) * sizeof(**linie))), buf);

    int ile_dp;
    int buf_i;
    char **linie_dp = malloc(MAX_LINES * sizeof(*linie));
    for (ile_dp = 0; fscanf(nr, "%d", &buf_i) == 1 && ile_dp < MAX_LINES; ile_dp++)
        strcpy((linie_dp[ile_dp]=malloc((strlen(linie[buf_i - 1]) + 1) * sizeof **linie)), linie[buf_i - 1]);

    qsort(linie_dp, ile_dp, sizeof(*linie_dp), stringcmp);

    int i;
    for (i = 0; i < ile_dp; i++)
        fprintf(ps, linie_dp[i][strlen(linie_dp[i])-1] != '\n' ? "%s\n" : "%s", linie_dp[i]);

    printf("Posortowane linie zapisano do: %s\n", argc>3?argv[3]:"plik_z_wynikiem");
    return 0;
}
