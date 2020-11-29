#include "graph.h"


int main() {
    // KAMUS
    Graph G;

    // ALGORITMA
    InitializeGraph(&G);
    PrintGraph(G);
    AddSrcToDest(&G, 1, 2, 'd');
    AddSrcToDest(&G, 1, 4, 's');
    AddSrcToDest(&G, 2, 1, 'a');
    AddSrcToDest(&G, 2, 3, 's');
    AddSrcToDest(&G, 3, 2, 'w');
    AddSrcToDest(&G, 3, 4, 'a');
    AddSrcToDest(&G, 4, 1, 'w');
    AddSrcToDest(&G, 4, 3, 'd');
    PrintGraph(G);

    return 0;
}