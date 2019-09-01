#include "graphRead.h"
#define MAX 100

//********** Problema 1 **********

// returneaza pozitia unui actor in graf
// sau 0 daca actorul nu este in graf
int getNamePosition(Graph g, char *nume)
{
    int i;

    for (i = 1; i < g->V; i++)
    {
        if (strcmp(g->names[i], nume) == 0)
            return i;
    }

    return 0;
}

// verifica daca exista o conexiune intre 2 muchii din graf
int isConnection(Graph g, int u, int v)
{
    List tmp = g->adjList[u];

    while (tmp != NULL)
    {
        if (tmp->v == v)
            return 1;
        tmp = tmp->next;
    }

    return 0;
}

// determina numarul total de actori din fisier
// nu se tine cont daca un actor apare de mai multe ori
int maxActors(FILE *file)
{
    int lines = 0, movies;
    char buffer[MAX];

    fscanf(file, "%d", &movies);
    // '\n'
    fgetc(file);

    while (fgets(buffer, MAX, file))
    {
        lines++;
    }

    // se scad din numarul total de linii liniile ce contin:
    // - numele filmelor
    // - numarul de actori din film
    return lines - 2 * movies;
}

Graph readGraphPb1(FILE *file, int V)
{
    int movies, i, j, k, actors, index;
    Graph g = initGraph(V);
    char buffer[MAX];

    fscanf(file, "%d", &movies);
    // '\n'
    fgetc(file);

    for (i = 0; i < movies; i++)
    {
        // numele filmului
        fgets(buffer, MAX, file);

        // numarul de actori din film
        fscanf(file, "%d", &actors);

        // '\n' sfarsit de linie
        fgetc(file);

        // vector ce contine pozitiile fiecarui actor din film
        int *movieActors = (int *)malloc(actors * sizeof(int));

        index = 0;
        for (j = 0; j < actors; j++)
        {
            // numele actorilor
            fgets(buffer, MAX, file);

            // sterge '\n' din nume
            buffer[strlen(buffer) - 1] = '\0';

            // obtine pozitia actorului in graf
            int pos = getNamePosition(g, buffer);

            // daca pozitia e 0, inseamna ca actorul nu exista in graf
            if (pos == 0)
            {
                // adauga actorul in graf si ii atribuie o pozitie
                g->names[g->V] = strdup(buffer);
                pos = g->V;
                g->V++;
            }

            // se introduce in vector pozitia actorului curent
            movieActors[index] = pos;
            index++;
        }

        for (j = 0; j < index; j++)
        {
            for (k = j + 1; k < index; k++)
            {
                // se fac legaturile intre toti actorii dintr-un film
                // daca acestea nu exista
                if (isConnection(g, movieActors[j], movieActors[k]) == 0)
                {
                    g = insertEdge(g, movieActors[j], movieActors[k], 0);
                }
            }
        }

        free(movieActors);
    }

    return g;
}

//********** ---------- **********

//********** Problema 2 **********

// se citesc:
// - tipul de camere
// - momentele de timp in care se afla patrule in camere
List *readPortals(List *patrol, FILE *file, int N)
{
    int i, n;
    unsigned long time;
    char c;
    char buffer[MAX];

    for (i = 1; i <= N; i++)
    {
        //ramene un \n de la sfarsit de linie
        fgets(buffer, MAX, file);
        fscanf(file, "%c%d", &c, &n);

        if (c == 'N')
        {
            patrol[i] = addLast(patrol[i], 0, 0);
        }
        if (c == 'Y')
        {
            patrol[i] = addLast(patrol[i], 1, 0);
        }

        while (n != 0)
        {
            fscanf(file, "%lu", &time);
            patrol[i] = addLast(patrol[i], 0, time);

            n--;
        }
    }

    return patrol;
}

// citirea grafului
Graph readGraphPb2(Graph g, FILE *file, int M)
{
    int i, u, v;
    unsigned long cost;

    for (i = 0; i < M; i++)
    {
        fscanf(file, "%d%d%lu", &u, &v, &cost);
        if (u <= g->V && v <= g->V)
        {
            g = insertEdge(g, u, v, cost);
        }
    }

    return g;
}

//********** ---------- **********