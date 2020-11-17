#include "graph.h"

void InitializeGraph (Graph* G) {
/** Membuat graph kosong G dengan nilai Map 1 sampai NMap */
  int i;
  for (i=0; i<NMap; i++) {
    GraphNodeMapName(G, i) = i+1;
    GraphNodeReqMove(G, i) = '+';
    GraphNodeNext(G, i) = Nil;
  }
}

NodePointer CreateNode (int Map) {
/** Membuat Node N dengan komponen MapName = Map*/
  NodePointer N;
  N = (NodePointer) malloc (sizeof(NodeGraph));
  NodeMapName(N) = Map;
  NodeReqMove(N) = '+';
  NodeNext(N) = Nil;
  return N;
}

void DeallocateNode (NodePointer N) {
  free(N);
}

void AppendNode (Graph* G, NodePointer N, int Src, char ReqMove) {
  /** Menambahkan Node N, NodeMapName(Dest), pada elemen G*/
  /** I.S. G terinisialisasi
   *       NodeMapName(N) valid
   *       Src valid. Src adalah MapName "asal" pada G
   *       ReqMove didasarkan representasi Map
  */
  /** F.S. Terdapat Node N pada graph G*/

  if (!IsNodeAlreadyExist(*G, Src, NodeMapName(N))) {
    // mencari Src yang sesuai di G
    printf("AppendNote: !IsNodeAlreadyExists(*G,%d,%d)\n", Src, NodeMapName(N));
    NodeReqMove(N) = ReqMove;
    int i;
    for (i=0; GraphNodeMapName(G,i) != Src; i++) { }
    // GraphNodeMapName(G,i) == Src
    printf("AppendNote: Found %d in G\n", Src);
    // Menambahkan Node N pada linked list
    // mencari posisi yang tepat

    NodePointer P;
    if (!IsGraphNodeHasNoList(G,i)) {
      printf("AppendNode: Node %d pada G sudah memiliki list", Src);
      P = GraphNodeNext(G,i);
      while (NodeNext(P) != Nil) {
        // kondisi pada while untuk menyesuaikan keterurutan  (opsional)
        if (NodeMapName(N) >= NodeMapName(NodeNext(P))) {
          break;
        }
        P = NodeNext(P);
      }
      printf("AppendNote: Passes while\n");
      // N ditempatkan diantara P dan NodeNext(P)
      if (IsNodeLast(P)) {
        NodeNext(N) = Nil;
        NodeNext(P) = N;
      }
      else {
        NodeNext(N) = NodeNext(P);
        NodeNext(P) = N;
      }
    }
    else {
      GraphNodeNext(G,i) = N;
    }
  }
}

boolean IsMapNameValid (int MapName) {
  /* true jika MapName pada interval 1..NMap */
  return ((MapName >= 1) && (MapName <= NMap));
}

boolean IsNodeAlreadyExist (Graph G, int Src, int Dest) {
  /** Mengecek keberadaan Node yang menghubungkan Src dan Dest pada G*/
  boolean found = false;
  int i=0;
  while (GraphNodeMapName(&G,i) != Src) {
    i++;
  }
  printf("IsNodeAlreadyExist: Found GraphNodeMapName(&G,i) == %d\n", Src);
  // ditemukan Map Src pada G
  if (IsGraphNodeHasNoList(&G, i)) {
    return false;
  }

  NodePointer PNode = GraphNodeNext(&G, i);
  int k=0;
  printf("%d", k);
  while (PNode!=Nil && NodeMapName(PNode)!=Dest) {
    PNode = NodeNext(PNode);
    k++; printf("%d", k);
  }
  printf("IsNodeAlreadyExist: Passes while\n");

  if (PNode == Nil) {
    return false;
  }
  
  if (NodeMapName(PNode) == Dest) {
    found = true;
  }

  /*
  for (i=0; i<NMap; i++) {
    if (GraphNodeMapName(&G, i) == Src) {
      NodePointer PNode;
      for (PNode=&(GraphNode(&G,i)); PNode!=Nil; PNode=NodeNext(PNode)) {
        if (NodeMapName(PNode) == Dest) {
          found = true;
          break;
        }
      } // for loop: linked list
    }
  } // for loop: graph
  */
  if (found) {
    printf("IsNodeAlreadyExist: Node %d to %d exists \n", Src, Dest);
  }
  return found;
}

boolean IsGraphNodeHasNoList (Graph* G, int i) {
  /* true jika GraphNode(G,i) belum memiliki Node yang ditunjuk */
  return (GraphNodeNext(G,i) == Nil);
}

boolean IsNodeLast (NodePointer N) {
  /* true jika N menunjuk ke Nil */
  return (NodeNext(N) == Nil);
}

void AddSrcToDest (Graph* G, int Src, int Dest, char ReqMove) {
  /* Menambahkan edge pada Graph G yang merepresentasikan hubungan Src ke Dest dengan command ReqMove */
  
  // Membuat Node yang merepresentasikan Map tujuan
  NodePointer PNode = CreateNode(Dest);
  printf("putting %d to %d \n", Src, Dest);
  /*
  // Mencari Map asal yang bersesuaian
  int i;
  for (i=0; GraphNodeMapName(G,i)!=Src; i++) { }
  // GraphNodeMapName(G,i)!=Src
  */

  AppendNode(G, PNode, Src, ReqMove);
}


void PrintGraph (Graph G) {
  /** Mencetak Graph G dengan format:
   * ['1'|'+'| ] --> ['2'|'a'| ] --> ['3'|'s'|Nil]
   * ['2'|'+'|Nil]
   * ...
   * ['4'|'+'| ] --> ['2'|'s'|Nil]
  */
  /**
   * Kamus Lokal:
   * PiGraph    : Graph*      { menunjuk elemen Graph ke i }
   * PNode      : NodePointer { menunjuk Node pada linked list }
  */
  int i;
  Graph* PiGraph = &G;
  NodePointer PNode;
  for (i=0; i<NMap; i++) {
    printf("[");
    
    // cetak MapName
    printf("%d|'+'|", GraphNodeMapName(PiGraph,i) );
    
    // jika linked list belum memiliki Node selain yang ada pada G
    if (IsGraphNodeHasNoList(PiGraph, i)) {
      printf("Nil]\n");
      continue;
    }
    printf(" ]");

    // cetak linked list
    for (PNode=GraphNodeNext(PiGraph,i); PNode!=Nil; PNode=NodeNext(PNode)) {
      printf(" --> ");
      printf("[%d|'%c'|", NodeMapName(PNode), NodeReqMove(PNode));
      if (NodeNext(PNode) == Nil) {
        // jika sudah mencapai akhir
        printf("Nil]\n");
        break;
      }
      printf(" ]");
    }
  }
}

char IntToChar (int I) {
  /* convert single digit int to char based on ASCII */
  return ((char) (48+I));
}

int CharToInt (char C) {
  /* convert number digit char to int based on ASCII */
  return (((int) C) - 48);
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