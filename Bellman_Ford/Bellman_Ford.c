// Bellman Ford Algorithm in C

#include <stdio.h>
#include <stdlib.h>

#define INFINITY 99999

//struct for the edges of the graph
struct Edge {
    int u;  //start vertex of the edge
    int v;  //end vertex of the edge
    int w;  //weight of the edge (u,v)
};

//Graph - it consists of edges
struct Graph {
    int V;        //total number of vertices in the graph
    int E;        //total number of edges in the graph
    struct Edge *edge;  //array of edges
};

void bellmanford(struct Graph *g, int source);
void display(int arr[], int size);

void makeGraph(struct Graph* graph, int nodes, int weight){

    //array of edges for graph
    graph->edge = (struct Edge *)malloc(graph->E * sizeof(struct Edge));

    //total nodes
    graph->V = nodes;
    //total edges
    graph->E = nodes - 1;


    int child1 = 0;
    int child2 = 0;
    int j = 0;

    for(int i = 0; i < nodes; i++){
        child1 = (2*i) + 1;
        child2 = (2*i) + 2;

        if(child1 < nodes){
            graph->edge[j].u = i;
            graph->edge[j].v = child1;
            graph->edge[j].w = i%3 * weight;
            j++;
        }
        if(child2 < nodes){
            graph->edge[j].u = i;
            graph->edge[j].v = child2;
            graph->edge[j].w = 0;
            j++;
        }

    }
}

int main(int argc, char *argv[]) {
    //first input is number of nodes
    //second input is the weight scale
    //third input is source vertex

    //create graph
    struct Graph *g = (struct Graph *)malloc(sizeof(struct Graph));

    makeGraph(g, atoi(argv[1]), atoi(argv[2]));


    //------- adding the edges of the graph
    /*
          edge(u, v)
          where 	u = start vertex of the edge (u,v)
                  v = end vertex of the edge (u,v)

          w is the weight of the edge (u,v)
      */



    bellmanford(g, atoi(argv[3]));  //0 is the source vertex

    return 0;
}

void bellmanford(struct Graph *g, int source) {
    //variables
    int i, j, u, v, w;

    //total vertex in the graph g
    int tV = g->V;

    //total edge in the graph g
    int tE = g->E;

    //distance array
    //size equal to the number of vertices of the graph g
    int d[tV];

    //predecessor array
    //size equal to the number of vertices of the graph g
    int p[tV];

    //step 1: fill the distance array and predecessor array
    for (i = 0; i < tV; i++) {
        d[i] = INFINITY;
        p[i] = 0;
    }

    //mark the source vertex
    d[source] = 0;

    //step 2: relax edges |V| - 1 times
    for (i = 1; i <= tV - 1; i++) {
        for (j = 0; j < tE; j++) {
            //get the edge data
            u = g->edge[j].u;
            v = g->edge[j].v;
            w = g->edge[j].w;

            if (d[u] != INFINITY && d[v] > d[u] + w) {
                d[v] = d[u] + w;
                p[v] = u;
            }
        }
    }

    //step 3: detect negative cycle
    //if value changes then we have a negative cycle in the graph
    //and we cannot find the shortest distances
    for (i = 0; i < tE; i++) {
        u = g->edge[i].u;
        v = g->edge[i].v;
        w = g->edge[i].w;
        if (d[u] != INFINITY && d[v] > d[u] + w) {
            printf("Negative weight cycle detected!\n");
            return;
        }
    }

    //No negative weight cycle found!
    //print the distance and predecessor array
    printf("Distance array: ");
    display(d, tV);
    printf("Predecessor array: ");
    display(p, tV);
}

void display(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}