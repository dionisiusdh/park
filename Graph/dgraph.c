#include "graph.h"


int main() {

  Graph G;
  InitializeGraph(&G);
  printf("Check G\n");
  PrintGraph(G);

  printf("test\n\n");
  AddSrcToDest(&G, 1, 2, 'd');
  PrintGraph(G);
  AddSrcToDest(&G, 1, 4, 's');
  AddSrcToDest(&G, 2, 1, 'a');
  AddSrcToDest(&G, 2, 3, 's');
  printf("test2\n\n");
  AddSrcToDest(&G, 3, 2, 'w');
  AddSrcToDest(&G, 3, 4, 'a');
  AddSrcToDest(&G, 4, 1, 'w');
  AddSrcToDest(&G, 4, 3, 'd');

  printf("test3\n\n");
  PrintGraph(G);
  printf("test4\n\n");

  return 0;
}