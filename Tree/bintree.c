#include "../boolean.h"
#include "./bintree.h"
#include <stdlib.h>
#include <stdio.h>

/* Manajemen Memory */
addrNodeWahana AlokNode(wahanatype X)
/* Mengirimkan addrNode hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addrNode tidak Nil, dan misalnya menghasilkan P,
  maka Akar(P) = X, Left(P) = Nil, Right(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
  addrNodeWahana N = (addrNodeWahana)malloc(sizeof(NodeWahana));
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

void DealokNode(addrNodeWahana P)
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

void BacaWahana(BinTree *WahanaTree1, BinTree *WahanaTree2, BinTree *WahanaTree3)
/* Membaca Wahana dan Deskripsinya dari file wahana.txt */
{
  /* KAMUS */
  FILE *PFile;
  int i,j,k,l;
  char val;
  wahanatype X;
  BinTree TempTree,wahana;
  Kata temp,tempNama,tempHargaTiket,tempKapasitas,tempDurasi,tempDeskripsi,tempUang,tempMaterial;

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
          tempNama.Length = 0;
          while(val == '\n'){
            val = fgetc(PFile);
          }
          while(val != ','){
            if(val != '\n' && val != BLANK){
              tempNama.TabKata[j] = val;
              tempNama.Length ++;
              j++;
            }
            val = fgetc(PFile);
          }
          WahanaNama(X) = tempNama;
          val = fgetc(PFile);
          
          // Baca Harga Tiket Wahana
          j = 0;
          tempHargaTiket.Length = 0;
          while(val != ','){
            tempHargaTiket.TabKata[j] = val;
            tempHargaTiket.Length ++;
            j++;
            val = fgetc(PFile);
          }
          WahanaHarga(X) = KataToInteger(tempHargaTiket);
          val = fgetc(PFile);

          // Baca Kapasitas Wahana
          j = 0;
          tempKapasitas.Length = 0;
          while(val != ','){
            tempKapasitas.TabKata[j] = val;
            tempKapasitas.Length ++;
            j++;
            val = fgetc(PFile);
          }
          WahanaKapasitas(X) = KataToInteger(tempKapasitas);
          val = fgetc(PFile);

          // Baca Durasi Wahana
          j = 0;
          tempDurasi.Length = 0;
          while(val != ','){
            tempDurasi.TabKata[j] = val;
            tempDurasi.Length ++;
            j++;
            val = fgetc(PFile);
          }   
          WahanaDurasi(X) = KataToInteger(tempDurasi);
          val = fgetc(PFile);

          // Baca Deskripsi Wahana
          j = 0;
          tempDeskripsi.Length = 0;
          while(val != ','){
            tempDeskripsi.TabKata[j] = val;
            tempDeskripsi.Length ++;
            j++;
            val = fgetc(PFile);
          }
          WahanaDeskripsi(X) = tempDeskripsi;
          val = fgetc(PFile);

          // Baca Uang yang dibutuhkan Wahana
          j = 0;
          tempUang.Length = 0;
          while(val != ','){
            tempUang.TabKata[j] = val;
            tempUang.Length ++;
            j++;
            val = fgetc(PFile);
          }
          WahanaCostUp(X) = KataToInteger(tempUang);

          // Baca Bahan bangunan yang dibutuhkan Wahana
          j = 0;
          val = fgetc(PFile);          
          while(val != '*' && val != '/'){
            k = 0;
            tempMaterial.Length = 0;
            while(val != '_' && val != '*' && val != '/'){
              tempMaterial.TabKata[k] = val;
              tempMaterial.Length ++;
              k++;
              val = fgetc(PFile);
            }
            WahanaMatUp(X,j) = KataToInteger(tempMaterial);
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
    printf("\n");
    PrintKata(AkarNama(Wahana2));
    printf("\n");
    PrintKata(AkarNama(Wahana3));
    printf("\n");
}

boolean IsWahanaTypeSama (BinTree Wahana1, BinTree Wahana2)
/* Mengembalikan true apabila Wahana1 = Wahana2, dan false apabila tidak */
{
    return IsEQKata(AkarNama(Wahana1),AkarNama(Wahana2));
}