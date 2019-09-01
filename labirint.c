#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "graphRead.h"
#include "stack.h"
#define INF 99999999
#define MAX 100

// scrierea in fisier a rezultatelor
void writeResult(unsigned long min, Stack s)
{
    FILE *file = fopen("labirint.out", "w");

    // scrierea timpului minim necesar
    fprintf(file, "%lu\n", min);

    // refacerea drumului
    while (isEmptyStack(s) != 1)
    {
        fprintf(file, "%d ", top(s));
        s = pop(s);
    }
    fprintf(file, "\n");

    fclose(file);
}

// calculul timpului de asteptare dintr-o camera
unsigned long delay(List patrol, unsigned long time)
{
    unsigned long delay = 0;

    while (patrol != NULL)
    {
        if (patrol->cost == time)
        {
            delay++;
            time++;
        }

        patrol = patrol->next;
    }

    return delay;
}

// calculul timpului minim de la un nod la toate celelalte
void dijkstra(Graph g, List *patrol, int start)
{
    unsigned long *time, min;
    int i, j, index, *path;

    // vector pentru timpul minim
    time = (unsigned long *)malloc((g->V + 1) * sizeof(unsigned long));
    // vector pentru refacerea drumului
    path = (int *)malloc((g->V + 1) * sizeof(int));

    // initilizare vector de timp cu INF
    for (i = 1; i <= g->V; i++)
    {
        time[i] = INF;
    }

    List tmp = g->adjList[start];

    // initilizare vector de timp cu timpii de la pozitia de start;
    // si vector de cai; de asemenea se aplica delay-ul initial
    unsigned long initDelay = delay(patrol[start]->next, 0);
    while (tmp != NULL)
    {
        time[tmp->v] = tmp->cost + delay(patrol[tmp->v]->next, tmp->cost + initDelay) + initDelay;
        path[tmp->v] = start;

        tmp = tmp->next;
    }

    // dijkstra - implementare cu vectori
    g->visited[start] = 1;
    for (i = 1; i <= g->V; i++)
    {
        min = INF;
        // determinare timp minim
        for (j = 1; j <= g->V; j++)
        {
            if (g->visited[j] == 0 && time[j] < min)
            {
                min = time[j];
                index = j;
            }
        }

        g->visited[index] = 1;
        tmp = g->adjList[index];

        while (tmp != NULL)
        {
            if (g->visited[tmp->v] == 0)
            {
                unsigned long delayTmp = 0;
                // daca din camera nu se poate iesii,
                // se determina timpul potential de asteptare
                if (patrol[tmp->v]->v == 0)
                    delayTmp = delay(patrol[tmp->v]->next, time[index] + tmp->cost);
                if (tmp->cost + time[index] + delayTmp < time[tmp->v])
                {
                    time[tmp->v] = tmp->cost + time[index] + delayTmp;
                    path[tmp->v] = index;
                }
            }
            tmp = tmp->next;
        }
    }

    min = INF;
    index = -1;
    // determina drumul minim pana la iesire
    for (i = 1; i <= g->V; i++)
    {
        if (patrol[i]->v == 1 && time[i] < min)
        {
            min = time[i];
            index = i;
        }
    }

    // determina numarul de camere minime prin care trebuie sa treaca
    // robotul pentru a evada pentru toate iesirile de drum minim
    int minChamberNr = INF;
    int chamberNr;
    for (i = 1; i <= g->V; i++)
    {
        // daca timpul este minim si din camera se poate iesii
        if (time[i] == min && patrol[i]->v == 1)
        {
            chamberNr = 0;
            j = i;
            // determina numarul de camere prin care se trece
            while (path[j] != start)
            {
                j = path[j];
                chamberNr++;
            }

            // daca numarul de camere este minim se tine minte indicele
            if (chamberNr < minChamberNr)
            {
                minChamberNr = chamberNr;
                index = i;
            }
        }
    }

    // se introduce in stiva drumul,
    // acesta fiind de la punctul final la cel initial;
    // si se scrie in fisier rezultatul
    Stack sTmp = NULL;
    if (index != -1)
    {
        Stack s = NULL;
        s = push(s, index);
        while (path[index] != start)
        {
            index = path[index];
            s = push(s, index);
        }
        s = push(s, start);

        writeResult(min, s);
    }
    else
    {
        writeResult(-1, NULL);
    }

    free(time);
    free(path);
}

int main()
{
    FILE *file = fopen("labirint.in", "r");
    int N, M, start, i;

    fscanf(file, "%d%d%d", &N, &M, &start);

    Graph g = initGraph(N);
    g->V = N;

    List *patrol = (List *)malloc((N + 1) * sizeof(List));

    for (i = 0; i < N + 1; i++)
    {
        patrol[i] = NULL;
    }

    // citirea grafului si a tipurilor de camere si patrule
    g = readGraphPb2(g, file, M);
    patrol = readPortals(patrol, file, N);

    dijkstra(g, patrol, start);

    // eliberari de memorie
    for (i = 0; i < N + 1; i++)
    {
        deleteList(patrol[i]);
    }
    deleteGraph(g);
    free(patrol);
    fclose(file);

    return 0;
}