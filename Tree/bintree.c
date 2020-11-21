#include "../boolean.h"
#include "./bintree.h"
#include <stdlib.h>
#include <stdio.h>

/* Manajemen Memory */
addrNode AlokNode(wahanatype X)
/* Mengirimkan addrNode hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addrNode tidak Nil, dan misalnya menghasilkan P,
  maka Akar(P) = X, Left(P) = Nil, Right(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
  addrNode N = (addrNode)malloc(sizeof(Node));
  if (N != Nil)
  {
    Akar(N) = X;
    Left(N) = Nil;
    Right(N) = Nil;
    return N;
  }
  else
  {
    return Nil;
  }
}

void DealokNode(addrNode P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addrNode P */
{
  free(P);
}

/* *** Konstruktor *** */
BinTree Tree(wahanatype Akar, BinTree L, BinTree R)
/* Menghasilkan sebuah pohon biner dari A, L, dan R, jika alokasi berhasil */
/* Menghasilkan pohon kosong (Nil) jika alokasi gagal */
{
  BinTree T = (BinTree)malloc(sizeof(BinTree));
  if (T != Nil)
  {
    Akar(T) = Akar;
    Left(T) = L;
    Right(T) = R;
    return T;
  }
  else
    return Nil;
}

void MakeTree(wahanatype Akar, BinTree L, BinTree R, BinTree *P)
/* I.S. Akar, L, R terdefinisi. P Sembarang */
/* F.S. Membentuk pohon P dengan Akar(P)=Akar, Left(P)=L, dan Right(P)=R
   jika alokasi berhasil. P = Nil jika alokasi gagal. */
{
  (*P) = Tree(Akar, L, R);
}

/* *** Predikat-Predikat Penting *** */
boolean IsTreeEmpty(BinTree P)
/* Mengirimkan true jika P adalah pohon biner kosong */
{
  return (P == Nil);
}

boolean IsTreeOneElmt(BinTree P)
/* Mengirimkan true jika P adalah pohon biner tidak kosong dan hanya memiliki 1 elemen */
{
  // return !IsTreeEmpty(P) && (((Left(P) != Nil) | (Right(P) != Nil)) && !(Left(P) != Nil && Right(P) != Nil));
  return !IsTreeEmpty(P) && (Left(P) == Nil) && (Right(P) == Nil);
}

boolean IsUnerLeft(BinTree P)
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerleft: hanya mempunyai subpohon kiri */
{
  return (Left(P) != Nil && Right(P) == Nil);
}
boolean IsUnerRight(BinTree P)
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerright: hanya mempunyai subpohon kanan*/
{
  return (Right(P) != Nil && Left(P) == Nil);
}
boolean IsBiner(BinTree P)
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon biner: mempunyai subpohon kiri dan subpohon kanan*/
{
  return (Right(P) != Nil && Left(P) != Nil);
}

/* *** Traversal *** */
void PrintPreorder(BinTree P)
/* I.S. P terdefinisi */
/* F.S. Semua simpul P sudah dicetak secara preorder: akar, pohon kiri, dan pohon kanan.
   Setiap pohon ditandai dengan tanda kurung buka dan kurung tutup ().
   Pohon kosong ditandai dengan ().
   Tidak ada tambahan karakter apa pun di depan, tengah, atau akhir. */
/* Contoh:
   (A()()) adalah pohon dengan 1 elemen dengan akar A
   (A(B()())(C()())) adalah pohon dengan akar A dan subpohon kiri (B()()) dan subpohon kanan (C()()) */
{
  if (IsTreeEmpty(P))
    printf("()");
  else
  {
    printf("(");
    printf("%d", Akar(P));
    PrintPreorder(Left(P));
    PrintPreorder(Right(P));
    printf(")");
  }
}

void PrintInorder(BinTree P)
/* I.S. P terdefinisi */
/* F.S. Semua simpul P sudah dicetak secara inorder: pohon kiri, akar, dan pohon kanan.
   Setiap pohon ditandai dengan tanda kurung buka dan kurung tutup ().
   Pohon kosong ditandai dengan ().
   Tidak ada tambahan karakter apa pun di depan, tengah, atau akhir. */
/* Contoh:
   (()A()) adalah pohon dengan 1 elemen dengan akar A
   ((()B())A(()C())) adalah pohon dengan akar A dan subpohon kiri (()B()) dan subpohon kanan (()C()) */
{
  printf("(");
  if (!IsTreeEmpty(P))
  {
    PrintInorder(Left(P));
    printf("%d", Akar(P));
    PrintInorder(Right(P));
  }
  printf(")");
}

void PrintPostorder(BinTree P)
/* I.S. P terdefinisi */
/* F.S. Semua simpul P sudah dicetak secara postorder: pohon kiri, pohon kanan, dan akar.
   Setiap pohon ditandai dengan tanda kurung buka dan kurung tutup ().
   Pohon kosong ditandai dengan ().
   Tidak ada tambahan karakter apa pun di depan, tengah, atau akhir. */
/* Contoh:
   (()()A) adalah pohon dengan 1 elemen dengan akar A
   ((()()B)(()()C)A) adalah pohon dengan akar A dan subpohon kiri (()()B) dan subpohon kanan (()()C) */
{
  if (IsTreeEmpty(P))
    printf("()");
  else
  {
    printf("(");
    PrintPostorder(Left(P));
    PrintPostorder(Right(P));
    printf("%d", Akar(P));
    printf(")");
  }
}

void PrintTree2(BinTree P, int h, int current_indent)
{
  if (!IsTreeEmpty(P))
  {

    printf("%*s%d\n", current_indent, "", Akar(P));

    PrintTree2(Left(P), h, current_indent + h);
    PrintTree2(Right(P), h, current_indent + h);
  }
}

void PrintTree(BinTree P, int h)
/* I.S. P terdefinisi, h adalah jarak indentasi (spasi) */
/* F.S. Semua simpul P sudah ditulis dengan indentasi (spasi) */
/* Penulisan akar selalu pada baris baru (diakhiri newline) */
/* Contoh, jika h = 2: 
1) Pohon preorder: (A()()) akan ditulis sbb:
A
2) Pohon preorder: (A(B()())(C()())) akan ditulis sbb:
A
  B
  C
3) Pohon preorder: (A(B(D()())())(C()(E()()))) akan ditulis sbb:
A
  B
    D
  C
    E
*/
{
  PrintTree2(P, h, 0);
}

/* *** Fungsi-Fungsi Lain *** */
int NbElmt(BinTree P)
/* Mengirimkan banyaknya elemen (node) pohon biner P */
{
  if (IsTreeEmpty(P))
    return 0;
  else
  {
    return 1 + NbElmt(Left(P)) + NbElmt(Right(P));
  }
}

int NbDaun(BinTree P)
/* Mengirimkan banyaknya daun (node) pohon biner P */
/* Prekondisi: P tidak kosong */
{
  if (!IsBiner(P))
    return 1;
  else
  {
    return NbDaun(Left(P)) + NbDaun(Right(P));
  }
}

boolean IsSkewLeft(BinTree P)
/* Mengirimkan true jika P adalah pohon condong kiri */
/* Pohon kosong adalah pohon condong kiri */
{
  if (IsTreeEmpty(P))
  {
    return true;
  }
  else
  {
    if (IsBiner(P) | IsUnerRight(P))
      return false;
    else
      return IsSkewLeft(Left(P));
  }
}

boolean IsSkewRight(BinTree P)
/* Mengirimkan true jika P adalah pohon condong kanan */
/* Pohon kosong adalah pohon condong kanan */
{
  if (IsTreeEmpty(P))
  {
    return true;
  }
  else
  {
    if (IsBiner(P) | IsUnerLeft(P))
      return false;
    else
      return IsSkewRight(Right(P));
  }
}
int Tinggi(BinTree P)
/* Pohon Biner mungkin kosong. Tinggi pohon kosong = 0.
   Mengirim "height" yaitu tinggi dari pohon */
{
  if (IsTreeEmpty(P))
    return 0;
  else
  {
    int mL = Tinggi(Left(P));
    int mR = Tinggi(Right(P));
    if (mL >= mR)
    {
      return 1 + mL;
    }
    else
    {
      return 1 + mR;
    }
  }
}

// /* *** Operasi lain *** */
// void AddDaunTerkiri(BinTree *P, wahanatype X)
// /* I.S. P boleh kosong */
// /* F.S. P bertambah simpulnya, dengan X sebagai simpul daun terkiri */
// {
//   if (IsTreeEmpty(*P))
//   {
//     *P = Tree(X, Nil, Nil);
//   }
//   else
//   {
//     AddDaunTerkiri(&Left(*P), X);
//   }
// }

// void AddDaun(BinTree *P, wahanatype X, wahanatype Y, boolean Kiri)
// /* I.S. P tidak kosong, X adalah salah satu daun Pohon Biner P */
// /* F.S. P bertambah simpulnya, dengan Y sebagai anak kiri X (jika Kiri = true), atau
//         sebagai anak Kanan X (jika Kiri = false) */
// /*		Jika ada > 1 daun bernilai X, diambil daun yang paling kiri */
// {
//   if (IsTreeOneElmt(*P) && Akar(*P) == X)
//     if (Kiri)
//       Left(*P) = Tree(Y, Nil, Nil);
//     else
//       Right(*P) = Tree(Y, Nil, Nil);
//   else
//   {
//     if (SearchTree(Left(*P), X))
//       AddDaun(&Left(*P), X, Y, Kiri);
//     else
//       AddDaun(&Right(*P), X, Y, Kiri);
//   }
// }

// void DelDaunTerkiri(BinTree *P, wahanatype *X)
// /* I.S. P tidak kosong */
// /* F.S. P dihapus daun terkirinya, dan didealokasi, dengan X adalah info yang semula
//         disimpan pada daun terkiri yang dihapus */
// {
//   if (IsTreeOneElmt(*P))
//   {
//     *X = Akar(*P);
//     addrNode temp = *P;
//     *P = Nil;
//     DealokNode(temp);
//   }
//   else
//   {
//     if (IsUnerRight(*P))
//     {
//       DelDaunTerkiri(&Right(*P), X);
//     }
//     else
//     {
//       DelDaunTerkiri(&Left(*P), X);
//     }
//   }
// }

// void DelDaun(BinTree *P, wahanatype X)
// /* I.S. P tidak kosong, minimum ada 1 daun bernilai X. */
// /* F.S. Semua daun bernilai X dihapus dari P. */
// {
//   if (!IsTreeEmpty(*P))
//   {

//     if (IsTreeOneElmt(*P) && Akar(*P) == X)
//     {
//       (*P) = Nil;
//       DealokNode(*P);
//     }
//     else
//     {
//       DelDaun(&Left(*P), X);
//       DelDaun(&Right(*P), X);
//     }
//   }
// }

// List MakeListDaun(BinTree P)
// /* Jika P adalah pohon kosong, maka menghasilkan list kosong. */
// /* Jika P bukan pohon kosong: menghasilkan list yang elemennya adalah semua daun pohon P,
//    jika semua alokasi list berhasil.
//    Daun terkiri menjadi elemen pertama dari list, diikuti elemen kanannya, dst.
//    Menghasilkan list kosong jika ada alokasi yang gagal. */
// {
//   if (IsTreeEmpty(P))
//     return Nil;
//   else if (IsTreeOneElmt(P))
//     return Alokasi(Akar(P));
//   else
//   {
//     List Left = MakeListDaun(Left(P));
//     List Right = MakeListDaun(Right(P));
//     return Concat(Left, Right);
//   }
// }

// List MakeListPreorder(BinTree P)
// /* Jika P adalah pohon kosong, maka menghasilkan list kosong. */
// /* Jika P bukan pohon kosong: menghasilkan list yang elemennya adalah semua elemen pohon P
//    dengan urutan preorder, jika semua alokasi berhasil.
//    Menghasilkan list kosong jika ada alokasi yang gagal. */
// {
//   if (IsTreeEmpty(P))
//     return Nil;
//   else
//   {
//     List Left = MakeListPreorder(Left(P));
//     List Right = MakeListPreorder(Right(P));

//     return Concat(Konso(Akar(P), Left), Right);
//   }
// }

// List MakeListLevel(BinTree P, int N)
// /* Jika P adalah pohon kosong, maka menghasilkan list kosong. */
// /* Jika P bukan pohon kosong: menghasilkan list yang elemennya adalah semua elemen pohon P
//    yang levelnya=N, jika semua alokasi berhasil.
//    Elemen terkiri menjadi elemen pertama dari list, diikuti elemen kanannya, dst.
//    Menghasilkan list kosong jika ada alokasi yang gagal. */
// {
//   if (IsTreeEmpty(P))
//     return Nil;
//   else if (N == 1)
//     return Alokasi(Akar(P));
//   else
//   {
//     List Left = MakeListLevel(Left(P), N - 1);
//     List Right = MakeListLevel(Right(P), N - 1);

//     return Concat(Left, Right);
//   }
// }

// /* *** Binary  Search  Tree  *** */
// boolean BSearch(BinTree P, wahanatype X)
// /* Mengirimkan true jika ada node dari P yang bernilai X */
// {
//   return SearchTree(Left(P), X) | SearchTree(Right(P), X);
// }

// void InsSearch(BinTree *P, wahanatype X)
// /* Menghasilkan sebuah pohon Binary Search Tree P dengan tambahan simpul X. Belum ada simpul P yang bernilai X. */
// {
//   if (IsTreeEmpty(*P))
//   {
//     MakeTree(X, Nil, Nil, P);
//   }
//   else
//   {
//     if (X > Akar(*P))
//     {
//       InsSearch(&Right(*P), X);
//     }
//     else if (X < Akar(*P))
//     {
//       InsSearch(&Left(*P), X);
//     }
//   }
// }

// void DelNode(BinTree *P)
// {
//   addrNode q;
//   if (Right(*P) != Nil)
//   {
//     DelNode(&Right(*P));
//   }
//   else
//   {
//     q = *P;
//     *P = Left(*P);
//   }
// }

// void DelBtree(BinTree *P, wahanatype X)
// /* I.S. Pohon P tidak  kosong */
// /* F.S. Nilai X yang dihapus pasti ada */
// /* Sebuah node dengan nilai X dihapus */
// {
//   addrNode q;
//   if (X < Akar(*P))
//   {
//     DelBtree(&Left(*P), X);
//   }
//   else if (X > Akar(*P))
//   {
//     DelBtree(&Right(*P), X);
//   }
//   else if (X == Akar(*P))
//   {
//     q = Tree(Akar(*P), Left(*P), Right(*P));
//     if (Right(q) == Nil)
//     {
//       (*P) = Left(q);
//     }
//     else if (Left(q) == Nil)
//     {
//       (*P) = Right(q);
//     }
//     else
//     {
//       DelNode(&Left(q));
//       free(&q);
//     }
//   }
// }


void BacaWahana(BinTree *WahanaTree1, BinTree *WahanaTree2, BinTree *WahanaTree3)
/* Membaca Wahana dan Deskripsinya dari file wahana.txt */
{
  /* KAMUS */
  FILE *PFile;
  int i,j,k,l;
  char val;
  wahanatype X;
  BinTree TempTree,wahana;
  Kata temp;

  /* ALGORITMA */
  int JUMLAH_WAHANA = 3;
  int JUMLAH_UPGRADE_PER_WAHANA = 3;

  PFile = fopen("../wahana.txt", "r");

  if (PFile != NULL){
      i = 0;
      val = fgetc(PFile);
      
      while (i != JUMLAH_WAHANA){
        i++;
        for (l=0; l<JUMLAH_UPGRADE_PER_WAHANA; l++){
          // Baca Nama Wahana
          j = 0;
          temp.Length = 0;
          while(val != ','){
            temp.TabKata[j] = val;
            temp.Length ++;
            j++;
            val = fgetc(PFile);
          }
          WahanaNama(X) = temp;
          val = fgetc(PFile);
          
          // Baca Harga Tiket Wahana
          j = 0;
          temp.Length = 0;
          while(val != ','){
            temp.TabKata[j] = val;
            temp.Length ++;
            j++;
            val = fgetc(PFile);
          }
          WahanaHarga(X) = KataToInteger(temp);
          val = fgetc(PFile);

          // Baca Kapasitas Wahana
          j = 0;
          temp.Length = 0;
          while(val != ','){
            temp.TabKata[j] = val;
            temp.Length ++;
            j++;
            val = fgetc(PFile);
          }
          WahanaKapasitas(X) = KataToInteger(temp);
          val = fgetc(PFile);

          // Baca Durasi Wahana
          j = 0;
          temp.Length = 0;
          while(val != ','){
            temp.TabKata[j] = val;
            temp.Length ++;
            j++;
            val = fgetc(PFile);
          }   
          WahanaDurasi(X) = KataToInteger(temp);
          val = fgetc(PFile);

          // Baca Deskripsi Wahana
          j = 0;
          temp.Length = 0;
          while(val != ','){
            temp.TabKata[j] = val;
            temp.Length ++;
            j++;
            val = fgetc(PFile);
          }
          WahanaDeskripsi(X) = temp;
          val = fgetc(PFile);

          // Baca Uang yang dibutuhkan Wahana
          j = 0;
          temp.Length = 0;
          while(val != ','){
            temp.TabKata[j] = val;
            temp.Length ++;
            j++;
            val = fgetc(PFile);
          }
          WahanaCostUp(X) = KataToInteger(temp);

          // Baca Bahan bangunan yang dibutuhkan Wahana
          j = 0;
          val = fgetc(PFile);          
          while(val != '*' && val != '/'){
            k = 0;
            temp.Length = 0;
            while(val != '_' && val != '*' && val != '/'){
              temp.TabKata[k] = val;
              temp.Length ++;
              k++;
              
              val = fgetc(PFile);
            }
            WahanaMatUp(X,j) = KataToInteger(temp);
            j++;    
            if (val == '*' || val == '/') { break; }
            val = fgetc(PFile);
          }

          TempTree = AlokNode(X);
          val = fgetc(PFile);
          if(l==0){
            wahana = TempTree;
          }
          else if(l==1){
            Left(wahana) = TempTree;
          }
          else if(l == 2){
            Right(wahana) = TempTree;
          }
        }
        if (i == 1){
          *WahanaTree1 = wahana;
        }
        else if (i == 2){
          *WahanaTree2 = wahana;
        }
        else if (i == 3){
          *WahanaTree3 = wahana;
        }
      }
  }
}

void GetInfoWahana (BinTree Wahana, wahanatype *InfoWahana){
  *InfoWahana = Akar(Wahana);
}

void PrintNamaWahana (BinTree Wahana1, BinTree Wahana2, BinTree Wahana3){
  printf("Ingin Membangun Apa?\n");
  printf("List :\n");
  PrintKata(AkarNama(Wahana1));
  PrintKata(AkarNama(Wahana2));
  PrintKata(AkarNama(Wahana3));
  printf("\n");
}