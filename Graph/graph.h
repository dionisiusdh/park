#include "../boolean.h"
#include "stdlib.h"
#include "stddef.h"
#include "stdio.h"


/**
 * (Representasi Graph berdasarkan diktat kuliah halaman 182)
 * Graph G adalah array of NodeGraph dengan elemen semua Map yang ada di game.
 * Setiap NodeGraph pada G memiliki list dengan implementasi linked list.
 * NodeGraph pada G melambangkan Map asal (Src), sementara linked list melambangkan
 * Map tujuan (Dest) yang berkorespondensi dengan NodeGraph pada G tersebut.
 * NodeGraph memiliki komponen MapName, ReqMove, dan pointer ke NodeGraph selanjutnya.
 * ReqMove adalah command yang diperlukan agar Player berpindah dari Src ke Dest.
 *
 * Contoh: 
 * Map berikut dapat direpresentasikan dengan Graph G
 *  1---2
 *  |   |
 *  4---3
 * G :
 *  [1|'+'| ] --> [2|'d'| ] --> [4|'s'|Nil]
 *  [2|'+'| ] --> [1|'a'| ] --> [3|'s'|Nil]
 *  [3|'+'| ] --> [2|'w'| ] --> [4|'a'|Nil]
 *  [4|'+'| ] --> [1|'w'| ] --> [3|'d'|Nil]
 */

#define NMap 4
#define Nil NULL

typedef int Map;
typedef struct node_graph_struct* NodePointer;

typedef struct node_graph_struct {
  Map MapName;
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


/*** Konstruktor ***/
void InitializeGraph (Graph* G);
  /** Membuat graph kosong G dengan nilai Map 1 sampai NMap */
NodePointer CreateNode (Map Map);
  /** Membuat Node N dengan komponen MapName = Map*/
void DeallocateNode (NodePointer N);
void MakeGMain(Graph* GMain);
  /** Mengkonstruksi Graph spesifik yang akan dipakai di Game */


/*** PREDIKAT ***/
boolean IsMapNameValid (Map MapName);
  /* true jika MapName pada interval 1..NMap */

boolean IsSrcToDestExist (Graph G, Map Src, Map Dest);
  /** Mengecek keberadaan Node yang menghubungkan Src dan Dest pada G*/

boolean IsSrcByReqMoveExist (Graph G, Map Src, char ReqMove);
  /** Mengecek apakah terdapat Node yang dituju dari Src dengan input ReqMove*/

boolean IsGraphNodeHasNoList (Graph* G, int i);
  /* true jika GraphNode(G,i) belum memiliki Node yang ditunjuk */

boolean IsNodeLast (NodePointer N);
  /* true jika N menunjuk ke Nil */


/*** Searching ***/
int SearchIndexSrc (Graph G, Map Src);
  /* Mengembalikan Index Src di Graph G, -1 jika tidak ada */

NodePointer SearchNodeMapName(NodePointer GNode, Map Dest);
  /* Mengembalikan NodePointer pada list yang ditunjuk GNode, node pada Graph, berdasarkan Dest
    mengembalikan Nil jika tidak ada */

NodePointer SearchNodeReqMove(NodePointer GNode, char ReqMove);
  /* Mengembalikan NodePointer pada list yang ditunjuk GNode, node pada Graph, berdasarkan ReqMove
    mengembalikan Nil jika tidak ada */


/*** MENAMBAH NODE ***/
void AppendNode (Graph* G, NodePointer N, Map Src, char ReqMove);
  /** Menambahkan Node N, NodeMapName(Dest), pada elemen G*/
  /** I.S. G terinisialisasi
   *       NodeMapName(N) valid
   *       Src validSrc valid. Src adalah MapName "asal" pada G
   *       ReqMove didasarkan representasi Map
  */
  /** F.S. Terdapat Node N pada graph G*/

void AddSrcToDest (Graph* G, Map Src, Map Dest, char ReqMove);
  /* Menambahkan edge pada Graph G yang merepresentasikan hubungan Src ke Dest dengan command ReqMove */


/*** PERPINDAHAN MAP ***/
Map ReturnMapDest (Graph* G, Map Src, char MoveCommand);
  /* Mengembalikan Map tujuan berdasarkan Map asal dan command yang diberikan
    Mengembalikan -1 jika tidak terdapat Map hubungan antara Map asal ke tujuan dengan command MoveCommand */


/*** OUTPUT ***/
// for debugging
void PrintGraph (Graph G);
  /** Mencetak Graph G dengan format:
   * [1|'+'| ] --> [2|'a'| ] --> [3|'s'|Nil]
   * [2|'+'|Nil]
   * ...
   * [4|'+'| ] --> [2|'s'|Nil]
  */



/* 
char IntToChar (int I);
  //convert single digit int to char based on ASCII

int CharToInt (char C);
  //convert number digit char to int based on ASCII
*/

/* Edge */
/*
void CreateEdge (Edge_Graph* E, char MapA, char MapB);

boolean IsEdgeListEmpty (Edge_Graph* EdgeList);
void InitializeEdges (Edge_Graph* EdgeList);  //  array of edges
void InsertEdge (Edge_Graph* EdgeList, Edge_Graph NewEdge);       //  array of edges
void DeleteEdge (Edge_Graph* EdgeList, Edge_Graph DeleteEdge);
*/