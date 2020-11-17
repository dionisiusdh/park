#include "../boolean.h"
#include "stdlib.h"
#include "stddef.h"
#include "stdio.h"


/**
 *  1---2
 *  |   |
 *  4---3
 * 
 * 
 * Graph G adalah array of
 * Contoh: 
 * G :
 *  [1|'+'| ] --> [2|'d'| ] --> [4|'s'|Nil]
 *  [2|'+'| ] --> [1|'a'| ] --> [3|'s'|Nil]
 *  [3|'+'| ] --> [2|'w'| ] --> [4|'a'|Nil]
 *  [4|'+'| ] --> [1|'w'| ] --> [3|'d'|Nil]
 * Node terdiri atas komponen:
 *  > char MapName
 *  > char ReqMove    // required move command yang diperlukan untuk mengakses Map.
 *                       '+' untuk Map itu sendiri
 *  > NodePointer Next  // untuk mengakses Destinasi Map selanjutnya yang mungkin
*/

#define NMap 4
#define Nil NULL

typedef struct node_graph_struct* NodePointer;

typedef struct node_graph_struct {
  int MapName;
  char ReqMove;
  NodePointer Next;
} NodeGraph;

typedef struct graph_struct {
  NodeGraph MapList[NMap];
} Graph;


/*
typedef struct edge_graph_struct {
  char SrcMap;
  char DestMap;
} Edge_Graph;
*/


/*** Selektor ***/
#define NodeMapName(PNode)          (PNode)->MapName
#define NodeReqMove(PNode)          (PNode)->ReqMove
#define NodeNext(PNode)             (PNode)->Next
#define GraphNode(PGraph, i)        (PGraph)->MapList[(i)]
#define GraphNodeMapName(PGraph, i) (PGraph)->MapList[(i)].MapName
#define GraphNodeReqMove(PGraph, i) (PGraph)->MapList[(i)].ReqMove
#define GraphNodeNext(PGraph, i)    (PGraph)->MapList[(i)].Next

void InitializeGraph (Graph* G);
/** Membuat graph kosong G dengan nilai Map 1 sampai NMap */

NodePointer CreateNode (int Map);
/** Membuat Node N dengan komponen MapName = Map*/

void DeallocateNode (NodePointer N);

void AppendNode (Graph* G, NodePointer N, int Src, char ReqMove);
/** Menambahkan Node N, NodeMapName(Dest), pada elemen G*/
/** I.S. G terinisialisasi
 *       NodeMapName(N) valid
 *       Src validSrc valid. Src adalah MapName "asal" pada G
 *       ReqMove didasarkan representasi Map
*/
/** F.S. Terdapat Node N pada graph G*/

boolean IsMapNameValid (int MapName);
/* true jika MapName pada interval 1..NMap */

boolean IsNodeAlreadyExist (Graph G, int Src, int Dest);
/** Mengecek keberadaan Node yang menghubungkan Src dan Dest pada G*/

boolean IsGraphNodeHasNoList (Graph* G, int i);
/* true jika GraphNode(G,i) belum memiliki Node yang ditunjuk */

boolean IsNodeLast (NodePointer N);
/* true jika N menunjuk ke Nil */

void AddSrcToDest (Graph* G, int Src, int Dest, char ReqMove);
/* Menambahkan edge pada Graph G yang merepresentasikan hubungan Src ke Dest dengan command ReqMove */

void PrintGraph (Graph G);
/** Mencetak Graph G dengan format:
 * [1|'+'| ] --> [2|'a'| ] --> [3|'s'|Nil]
 * [2|'+'|Nil]
 * ...
 * [4|'+'| ] --> [2|'s'|Nil]
*/

char IntToChar (int I);
/* convert single digit int to char based on ASCII */

int CharToInt (char C);
/* convert number digit char to int based on ASCII */

/* Edge */
/*
void CreateEdge (Edge_Graph* E, char MapA, char MapB);

boolean IsEdgeListEmpty (Edge_Graph* EdgeList);
void InitializeEdges (Edge_Graph* EdgeList);  //  array of edges
void InsertEdge (Edge_Graph* EdgeList, Edge_Graph NewEdge);       //  array of edges
void DeleteEdge (Edge_Graph* EdgeList, Edge_Graph DeleteEdge);
*/