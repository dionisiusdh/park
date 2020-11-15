#include "../boolean.h"
#include "stdlib.h"
#include "stddef.h"


/**
 * 
 * G :
 *  '1' -> '2' -> '3' -> '4'
 *  '2' -> '1' -> '3'
 *  '3' -> '1' -> '2'
 *  '4' -> '1'
*/

#define NMap 4
#define Nil NULL

typedef struct node_graph_struct {
  char MapName;
  Node_Graph* Next;
} Node_Graph;

typedef struct edge_graph_struct {
  char SrcMap;
  char DestMap;
} Edge_Graph;

typedef struct graph_struct {
  Node_Graph MapList[NMap];
} Graph;

void InitializeGraph (Graph* G);

void InitializeNode (Node_Graph* N, char Map);

/* Edge */
void CreateEdge (Edge_Graph* E, char MapA, char MapB);

boolean IsEdgeListEmpty (Edge_Graph* EdgeList);
void InitializeEdges (Edge_Graph* EdgeList);  //  array of edges
void InsertEdge (Edge_Graph* EdgeList, Edge_Graph NewEdge);       //  array of edges
void DeleteEdge (Edge_Graph* EdgeList, Edge_Graph DeleteEdge);
