#include "prioqueue.h"
#include "../pengunjung/pengunjung.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* ********* Prototype ********* */
boolean IsEmptyQueue (Queue Q)
/* Mengirim true jika Q kosong: lihat definisi di atas */
{
    return (Head(Q)==NilQueue) && (Tail(Q)==NilQueue);
}

boolean IsFullQueue (Queue Q)
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
{
    return NBElmtQueue(Q)==MaxElQueue(Q);
}

int NBElmtQueue (Queue Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
{
    if(IsEmptyQueue(Q)){
        return 0;
    }
    else{
        return Tail(Q) - Head(Q) + 1;
    }
}
/* *** Kreator *** */
void CreateEmptyQueue (Queue * Q, int Max)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */
{   (*Q).T = (queuetype*) malloc ((Max)*sizeof(queuetype));
    if((*Q).T != NULL){
        MaxElQueue(*Q) = Max;
        Head(*Q) = NilQueue;
        Tail(*Q) = NilQueue;
    }
    else{
        MaxElQueue(*Q) = 0;
    }
}
/* *** Destruktor *** */
void DeAlokasiQueue (Queue * Q)
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */
{
    free((*Q).T);
    MaxElQueue(*Q) = 0;
}

/* *** Primitif Add/Delete *** */
void AddQueue (Queue * Q, queuetype X)
/* Proses: Menambahkan X pada Q dengan aturan priority queue, terurut mengecil berdasarkan prio */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi elemen baru disisipkan pada posisi yang tepat sesuai dengan prioritas. 
        Apabila jumlah wahana yang dimiliki oleh X adalah 0, elemen tidak ditambahkan ke dalam queue */
{   //KAMUS
    int i;
    boolean add;
    queuetype temp1,temp2;
    //ALGORITMA
    if (NeffPengunjung(Pengunjung(X)) != 0){
        if(IsEmptyQueue(*Q)){
            ElmtQueue(*Q,0) = X;
            Head(*Q) = 0;
            Tail(*Q) = 0;
        }
        else{
            i = Head(*Q);
            add = false;
            temp1 = X;
            while (i<=Tail(*Q) && !add){
                if (PrioQueue(ElmtQueue(*Q,i)) < PrioQueue(X)){
                    add = true;;
                }
                else{
                    i++;
                }
            }
            while (i<=Tail(*Q)){
                temp2 = ElmtQueue(*Q,i);
                ElmtQueue(*Q,i) = temp1;
                temp1 = temp2;
                i++; 
            }
            Tail(*Q) += 1;
            ElmtQueue(*Q,Tail(*Q)) = temp1;
        }
    }
}

void DelQueue (Queue * Q, queuetype * X, Kata Wahana)
/* Proses: Menghapus X pada Q yang di dalamnya terdapat Nama Wahana aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = NilQueue elemen disetor di X dihilangkan dari queue tetapi queue rata kiri ; 
        Q mungkin kosong */
{   //KAMUS
    int lokasi,i;
    //ALGORITMA
    lokasi = SearchQueue(*Q,Wahana);
    *X = ElmtQueue(*Q,lokasi);
    for (i=lokasi; i<Tail(*Q); i++){
        ElmtQueue(*Q,i) = ElmtQueue(*Q,i+1); 
    }
    Tail(*Q) -= 1;
    if (Tail(*Q) == NilQueue){
        Head(*Q) = NilQueue;
    }
}

/* Operasi Tambahan */
void PrintQueue (Queue Q)
/* Mencetak isi queue Q ke layar */
/* I.S. Q terdefinisi, mungkin kosong */
/* F.S. Q tercetak ke layar dengan format:
<prio-1> <elemen-1>
...
<prio-n> <elemen-n>
#
*/
// Wahana | Nama | Kesabaran | 
{   //KAMUS
    int i;
    //ALGORITMA
    printf("Antrian [%d/5]\n", NBElmtQueue(Q));

    if (NBElmtQueue(Q) == 0) {
        printf("Antrian kosong\n");
    } else {
        for (i=Head(Q); i<=Tail(Q); i++){
            TulisWahana(Pengunjung(ElmtQueue(Q,i)));
            printf(" | Kesabaran: %d", Kesabaran(Pengunjung(ElmtQueue(Q,i))));
            printf(" | Customer %c\n",NamaPengunjung(ElmtQueue(Q,i)));
        }  
    }
}

int SearchQueue (Queue Q, Kata Wahana)
//Mencari posisi dari elemen pertama queue yang memiliki wahana di dalamnya
{   //KAMUS
    int i = Head(Q);
    boolean found = false;
    //ALGORITMA
    while (i<=Tail(Q) && !found){
        if (SearchPengunjung(Pengunjung(ElmtQueue(Q,i)), Wahana)){
            found = true;
        }
        else{
            i++;
        }
    }
    if (found){
        return i;
    }
    else{
        return NilQueue;
    }
}

void initQueue (Queue *Antrian, TabInt Kapasitas) {
  // KAMUS LOKAL
  int jumlahOrang, i, nama;
  PENGUNJUNG P;

  // ALGORITMA
  srand(time(NULL));
  jumlahOrang = 1 + rand()%4;

  CreateEmptyQueue(Antrian, 5);
  i=0;
  nama = 65;
  while (i<jumlahOrang) {
    MakePENGUNJUNG(&P, i, Kapasitas);
    Pengunjung(ElmtQueue(*Antrian,i)) = P;
    NamaPengunjung(ElmtQueue(*Antrian,i)) = (char) nama;
    PrioQueue(ElmtQueue(*Antrian,i)) = 0;
    i++;
    nama++;
  }
  Head(*Antrian) = 0;
  Tail(*Antrian) = i-1;
}

void AddRandomPengunjung (Queue *Antrian, TabInt Kapasitas) {
/* Menambahkan pengunjung secara random ke Antrian */
/* Chance pengunjung baru datang 20% */
    // KAMUS LOKAL
    int jumlahOrang, i, nama, chance, randomForName;
    PENGUNJUNG P;
    queuetype NewQElem;

    // ALGORITMA
    srand(time(NULL));
    chance = 1 + rand()%10;
    i = NBElmtQueue(*Antrian);

    if (!IsFullQueue(*Antrian)) {
        if (chance>8) {
            randomForName = 5 + rand()%20;
            nama = randomForName + i + 60;
            MakePENGUNJUNG(&P, i, Kapasitas);
            Pengunjung(NewQElem) = P;
            NamaPengunjung(NewQElem) = (char) nama;
            PrioQueue(NewQElem) = 0;
            AddQueue(Antrian, NewQElem);
        }
    }
}


void KurangKesabaran(Queue *Q)
/* Mengurangkan kesabaran orang yang apabila terjadi dellqueue*/
{   //KAMUS
    int i;
    //ALGORITMA
    for (i=Head(*Q); i<=Tail(*Q); i++){
        Kesabaran(Pengunjung(ElmtQueue(*Q,i))) -= 1;
    }
}

void DellKesabaran0(Queue *Q)
/*Menghilangkan pengunjung dengan kesabaran 0 dari antrian*/
{   //KAMUS
    int i,j;
    //ALGORITMA
    i = Head(*Q);
    while (i != Tail(*Q)+1){
        if (Kesabaran(Pengunjung(ElmtQueue(*Q,i))) == 0){
            for (j=i+1; j<=Tail(*Q); j++){
                ElmtQueue(*Q,j-1) = ElmtQueue(*Q,j); 
            }
            Tail(*Q) -= 1;
        }
        else{
            i++;
        }
    }
}

void TambahPrioritas(Queue *Q)
/* Menambah prioritas orang yang tidak dilayani*/
{   //KAMUS
    int i;
    //ALGORITMA
    for (i=Head(*Q); i<=Tail(*Q); i++){
        PrioQueue(ElmtQueue(*Q,i)) += 1;
    }
}