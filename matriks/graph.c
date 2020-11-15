#include "graph.h"

void InitializeGraph (Graph* G) {
  int i;
  Node_Graph N;
  for (i=0; i<NMap; i++) {
    G->MapList[i].MapName = (char) i;
    G->MapList[i].Next = Nil;
  }
}

void InitializeNode (Node_Graph* N, char Map) {
  N = (Node_Graph*) malloc (sizeof(Node_Graph));
  N->MapName = Map;
  N->Next = Nil;
}



/*
void CreateEdge (Edge_Graph* E, char MapA, char MapB) {
  while (MapA != MapB) {
    printf("Masukkan Map yang berbeda!");
    printf("Map asal = "); scanf("%c", &MapA);
    printf("Map tujuan = "); scanf("%c", &MapB);
  }
  E->SrcMap = MapA;
  E->DestMap = MapB;
}

boolean IsEdgeListEmpty (Edge_Graph* EdgeList) {
  return (EdgeList == Nil);
}

void InitializeEdges (Edge_Graph* EdgeList) { //  array of edges
  EdgeList = Nil;
}
void InsertEdge (Edge_Graph* EdgeList, Edge_Graph NewEdge) {       //  array of edges
  if (IsEdgeListEmpty(EdgeList)) {
    EdgeList[0] = NewEdge;
  }
  else {
    int i = 0;
    char check;
    boolean foundExistingEdge = false;
    do {
      if (EdgeList[i].SrcMap == NewEdge.SrcMap) {
        if (EdgeList[i].DestMap == NewEdge.DestMap) {
          foundExistingEdge = true;
        }
      }
      i++;
    } while (!foundExistingEdge && i < NMap);

    if (!foundExistingEdge) {

    }
  }
}
void DeleteEdge (Edge_Graph* EdgeList, Edge_Graph DeleteEdge);
*/