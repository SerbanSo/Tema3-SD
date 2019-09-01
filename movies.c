#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "graphRead.h"
#include "task3.h"
#include "bonus.h"
#define ARG 1
#define INFILE 2
#define OUTFILE 3
#define MAX 100

int main(int argc, char **argv)
{
    int i = 0, max;
    Graph g = NULL;

    if (argc < 4)
    {
        printf("Prea putine argumente!\n");
        return -1;
    }

    FILE *file = fopen(argv[INFILE], "r");
    FILE *out = fopen(argv[OUTFILE], "w");

    //se determina numarul maxim de actori din filme
    max = maxActors(file);
    fclose(file);
    file = fopen(argv[INFILE], "r");

    //citirea grafului
    g = readGraphPb1(file, max);

    if (strcmp(argv[ARG], "-c1") == 0)
    {
        //***** Task 1 *****

        fprintf(out, "%d\n", connectedComponents(g));

        //***** ------ *****
    }
    else if (strcmp(argv[ARG], "-c2") == 0)
    {
        //***** Task 2 *****

        char buffer[MAX], buffer2[MAX];
        int start, end;

        //citire cele 2 nume pentru care trebuie determinat gradul
        fgets(buffer, MAX, file);
        fgets(buffer2, MAX, file);

        //eliminare '\n' din nume
        buffer[strlen(buffer) - 1] = '\0';
        buffer2[strlen(buffer2) - 1] = '\0';

        //deterimare pozitie din graf a celor 2 nume
        start = getNamePosition(g, buffer);
        end = getNamePosition(g, buffer2);

        //calculul drumului dintre cei 2 actori
        int distance = minDistance(g, start, end);

        //scrierea in fisier
        fprintf(out, "%d\n", distance);

        //***** ------ *****
    }
    else if (strcmp(argv[ARG], "-c3") == 0)
    {
        //***** Task 3 *****

        task3Main(g, out);

        //***** ------ *****
    }
    else if (strcmp(argv[ARG], "-b") == 0)
    {
        //***** Bonus *****

        bonusMain(g, out);

        //***** ----- *****
    }
    else
    {
        printf("Argument incorect pentru rularea cerintei.\n");
        g = deleteGraph(g);
        fclose(file);
        fclose(out);
        return -1;
    }

    g = deleteGraph(g);

    fclose(file);
    fclose(out);
    return 0;
}
