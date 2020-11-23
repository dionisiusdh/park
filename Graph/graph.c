#include "graph.h"


/*** Konstruktor ***/
void InitializeGraph (Graph* G) {
/** Membuat graph kosong G dengan nilai Map 1 sampai NMap */
  int i;
  for (i=0; i<NMap; i++) {
    GraphNodeMapName(G, i) = i+1;
    GraphNodeReqMove(G, i) = '+';
    GraphNodeNext(G, i) = Nil;
  }
}

NodePointer CreateNode (Map Map) {
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

void MakeGMain(Graph* GMain) {
  /** Mengkonstruksi Graph spesifik yang akan dipakai di Game */
  //printf("Check GMain\n");
  //PrintGraph(*GMain);
  InitializeGraph(GMain);
  printf("test\n\n");
  AddSrcToDest(GMain, 1, 2, 'd');
  //PrintGraph(*GMain);
  AddSrcToDest(GMain, 1, 4, 's');
  AddSrcToDest(GMain, 2, 1, 'a');
  AddSrcToDest(GMain, 2, 3, 's');
  //printf("test2\n\n");
  AddSrcToDest(GMain, 3, 2, 'w');
  AddSrcToDest(GMain, 3, 4, 'a');
  AddSrcToDest(GMain, 4, 1, 'w');
  AddSrcToDest(GMain, 4, 3, 'd');
}

/*** PREDIKAT ***/
boolean IsMapNameValid (Map MapName) {
  /* true jika MapName pada interval 1..NMap */
  return ((MapName >= 1) && (MapName <= NMap));
}

boolean IsSrcToDestExist (Graph G, Map Src, Map Dest) {
  /** Mengecek keberadaan Node yang menghubungkan Src dan Dest pada G*/
  boolean found = false;
  int i = SearchIndexSrc(G, Src);
  if (i != -1) {    // terdapat Src di G
      // printf("IsSrcToDestExist: Found GraphNodeMapName(&G,i) == %d\n", Src);
    // Ditemukan Map Src pada G
    if (IsGraphNodeHasNoList(&G, i)) {
      return false;
    }

    NodePointer PNode = GraphNodeNext(&G, i);
    while (PNode!=Nil && NodeMapName(PNode)!=Dest) {
      PNode = NodeNext(PNode);
    }
      // printf("IsSrcToDestExist: Passes while\n");

    if (PNode == Nil) {
      // jika tidak ditemukan Node Dest sampai ujung list
      return false;
    }
    if (NodeMapName(PNode) == Dest) {
      found = true;
    }
  }
  return found;
}

boolean IsSrcByReqMoveExist (Graph G, Map Src, char ReqMove) {
  /** Mengecek apakah terdapat Node yang dituju dari Src dengan input ReqMove*/
  boolean found = false;
  int i = SearchIndexSrc(G, Src);
  if (i != -1) {   // terdapat Src di G
    if (IsGraphNodeHasNoList(&G, i)) {
      // GraphNode di index i tidak memiliki list
      return false;
    }
    NodePointer PNode = GraphNodeNext(&G, i);
    while (PNode!=Nil && NodeReqMove(PNode)!=ReqMove) {
      PNode = NodeNext(PNode);
    }
      /***printf("IsSrcToDestExist: Passes while\n"); */

    if (PNode == Nil) {
      // jika tidak ditemukan Node Dest sampai ujung list
      return false;
    }
    if (NodeReqMove(PNode) == ReqMove) {
      found = true;
    }
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


/*** Searching ***/
int SearchIndexSrc (Graph G, Map Src) {
  /* Mengembalikan Index Src di Graph G, -1 jika tidak ada */
  int i = 0;
  while (GraphNodeMapName(&G, i)!=Src && i<NMap) {
    i++;
  }
  if (i < NMap) {
    return i;
  }
  else {
    return -1;
  }
}

NodePointer SearchNodeMapName(NodePointer GNode, Map Dest) {
  /* Mengembalikan NodePointer pada list yang ditunjuk GNode, node pada Graph
    mengembalikan Nil jika tidak ada */
  if (NodeNext(GNode) != Nil) {
    NodePointer PNode = NodeNext(GNode);
    while (PNode!=Nil && NodeMapName(PNode)!=Dest) {
      PNode = NodeNext(PNode);
    }
      /***printf("IsSrcToDestExist: Passes while\n"); */

    if (PNode == Nil) {
      // jika tidak ditemukan Node Dest sampai ujung list
      return Nil;
    }
    else {
      return PNode;
    }
  }
  else {
    return Nil;
  }
}

NodePointer SearchNodeReqMove(NodePointer GNode, char ReqMove) {
  /* Mengembalikan NodePointer pada list yang ditunjuk GNode, node pada Graph, berdasarkan ReqMove
    mengembalikan Nil jika tidak ada */
  if (NodeNext(GNode) != Nil) {
    NodePointer PNode = NodeNext(GNode);
    while (PNode!=Nil && NodeReqMove(PNode)!=ReqMove) {
      PNode = NodeNext(PNode);
    }
      /***printf("IsSrcToDestExist: Passes while\n"); */

    if (PNode == Nil) {
      // jika tidak ditemukan Node Dest sampai ujung list
      return Nil;
    }
    else {
      return PNode;
    }
  }
  else {
    return Nil;
  }
}


/*** Menambah Node pada Graph ***/
void AppendNode (Graph* G, NodePointer N, Map Src, char ReqMove) {
  /** Menambahkan Node N, NodeMapName(Dest), pada elemen G*/
  /** I.S. G terinisialisasi
   *       NodeMapName(N) valid
   *       Src valid. Src adalah MapName "asal" pada G
   *       ReqMove didasarkan representasi Map
  */
  /** F.S. Terdapat Node N pada graph G*/

  if (!IsSrcToDestExist(*G, Src, NodeMapName(N))) {
    // Mencari Src yang sesuai di G
      // printf("AppendNote: !IsSrcToDestExists(*G,%d,%d)\n", Src, NodeMapName(N));
    NodeReqMove(N) = ReqMove;
    int i;
    for (i=0; GraphNodeMapName(G,i) != Src; i++) { }
    // GraphNodeMapName(G,i) == Src
      // printf("AppendNote: Found %d in G\n", Src);
    // Menambahkan Node N pada linked list
    
    // Mencari posisi yang tepat
    NodePointer P;
    if (!IsGraphNodeHasNoList(G,i)) {
        /***printf("AppendNode: Node %d pada G sudah memiliki list", Src); */
      P = GraphNodeNext(G,i);
      while (NodeNext(P) != Nil) {
        // kondisi pada while untuk menyesuaikan keterurutan  (opsional)
        if (NodeMapName(N) >= NodeMapName(NodeNext(P))) {
          break;
        }
        P = NodeNext(P);
      }
        /***printf("AppendNote: Passes while\n"); */
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

void AddSrcToDest (Graph* G, Map Src, Map Dest, char ReqMove) {
  /* Menambahkan edge pada Graph G yang merepresentasikan hubungan Src ke Dest dengan command ReqMove */
  
  // Membuat Node yang merepresentasikan Map tujuan
  NodePointer PNode = CreateNode(Dest);
  // printf("putting %d to %d \n", Src, Dest);
  /*
  // Mencari Map asal yang bersesuaian
  int i;
  for (i=0; GraphNodeMapName(G,i)!=Src; i++) { }
  // GraphNodeMapName(G,i)!=Src
  */

  AppendNode(G, PNode, Src, ReqMove);
}


/*** PERPINDAHAN MAP ***/
Map ReturnMapDest (Graph* G, Map Src, char MoveCommand) {
  /* Mengembalikan Map tujuan berdasarkan Map asal dan command yang diberikan
      Mengembalikan -1 jika tidak terdapat Map hubungan antara Map asal ke tujuan dengan command MoveCommand */
  Map MapDest = -1;
  if (IsMapNameValid(Src))  {
    if (IsSrcByReqMoveExist(*G, Src, MoveCommand)) {
      int i = SearchIndexSrc(*G, Src);
      NodePointer GNode = &(GraphNode(G, i));
      NodePointer PDest = SearchNodeReqMove(GNode, MoveCommand);
      MapDest = NodeMapName(PDest);
    }
  }
  return MapDest;
}



/*** OUTPUT ***/
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





/*
char IntToChar (int I) {
  //convert single digit int to char based on ASCII
  return ((char) (48+I));
}

int CharToInt (char C) {
  //convert number digit char to int based on ASCII
  return (((int) C) - 48);
}
*/

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