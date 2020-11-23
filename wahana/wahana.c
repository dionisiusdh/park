// Realisasi Dari wahana.h

#include "./wahana.h"

/* ********** KONSTRUKTOR ********** */
void MakeWahana(Wahana *W, NodeWahana datawahana, POINT posisiwahana, List historyupgrade){
    /* KAMUS */

    /* ALGORITMA */
    Deskripsi(*W) = datawahana;
    Posisi(*W) = posisiwahana;
    History(*W) = historyupgrade;
}

/* ********** GETTER ********** */
NodeWahana GetDataWahana(Wahana W)
/* Sebuah Getter untuk mengembalikan data wahana dalam bentuk wahanatype */
{
    /* KAMUS */

    /* ALGORITMA */
    return Deskripsi(W);
}

POINT GetPosisiWahana(Wahana W)
/* Sebuah Getter untuk mengembalikan posisi wahana dalam bentuk POINT */
{
    /* KAMUS */

    /* ALGORITMA */
    return Posisi(W);
}

List GetHistoryWahana(Wahana W)
/* Sebuah Getter untuk mengembalikan history upgrade wahana dalam bentuk List */
{
    /* KAMUS */

    /* ALGORITMA */
    return History(W);
}

/* ********** SETTER ********** */
void SetDataWahana(Wahana *W, NodeWahana X)
/* Mengubah attribut datawahana pada W menjadi X */
{
    /* KAMUS */

    /* ALGORITMA */
    Deskripsi(*W) = X;
}

void SetPosisiWahana(Wahana *W, POINT X)
/* Mengubah attribut posisi pada W menjadi X */
{
    /* KAMUS */

    /* ALGORITMA */
    Posisi(*W) = X;
}

void SetHistoryWahana(Wahana *W, List X)
/* Mengubah attribut historyupgrade pada W menjadi X */
{
    /* KAMUS */

    /* ALGORITMA */
    History(*W) = X;
}

/* ^^^^^^^^^^ LIST WAHANA ^^^^^^^^^^^ */
/* ********** KONSTRUKTOR ********** */
boolean IsEmptyListWahana (ListWahana L)
/* Mengirim true jika list wahana kosong */
{
    /* KAMUS LOKAL */

    /* ALGORITMA */
    return FirstWahana(L) == Nil;
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptyListWahana (ListWahana *L)
/* I.S. sembarang             */
/* F.S. Terbentuk list wahana kosong */
{
    /* KAMUS LOKAL */

    /* ALGORITMA */
    FirstWahana(*L) = Nil;
}

/****************** Manajemen Memori ******************/
addressWahana AlokasiWahana (Wahana W)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
    /* KAMUS LOKAL */
    addressWahana P;

    /* ALGORITMA */
    P = (addressWahana) malloc (sizeof(ElmtListWahana));

    if (P != Nil) {
        InfoWahana(P) = W;
        NextWahana(P) = Nil;
        return P;
    } else {
        return Nil;
    }
}

void DealokasiWahana (address *P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
    /* KAMUS LOKAL */

    /* ALGORITMA */
    free(*P);
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
addressWahana SearchWahana (ListWahana L, Wahana W)
/* Mencari apakah ada elemen list dengan info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
{
    // /* KAMUS LOKAL */
    // address P;

    // /* ALGORITMA */
    // P = FirstWahana(L);

    // while (P != Nil && InfoWahana(P) != X) {
    //     P = Next(P);
    // }

    // return P;
}

boolean SearchPosisiWahana (ListWahana L, POINT P)
/* Mencari apakah ada Wahana yang menempati Posisi P*/
/* Jika ada, mengirimkan true. */
/* Jika tidak ada, mengirimkan false */
{
    /* KAMUS LOKAL */
    addressWahana A;
    boolean found = false;

    /* ALGORITMA */
    A = FirstWahana(L);

    while (A != Nil && !found) {
        if(EQ(Posisi(InfoWahana(A)),P)){
            found = true;
        }
        else{
            A = NextWahana(A);
        }
    }

    return found;
}

void InsertFirstWahana (ListWahana *L, Wahana W)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
    /* KAMUS LOKAL */
    addressWahana P;

    /* ALGORITMA */
    P = AlokasiWahana(W);

    if (P != Nil) {
        NextWahana(P) = FirstWahana(*L);
        FirstWahana(*L) = P;
    }
}

void InsertAfterWahana (ListWahana *L, addressWahana P, addressWahana Prec){
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    NextWahana(P) = NextWahana(Prec);
    NextWahana(Prec) = P;
}

void InsertLastWahana (ListWahana *L, Wahana W)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    /* KAMUS LOKAL */
    addressWahana P,Last;

    /* ALGORITMA */
    if (IsEmptyListWahana(*L)) {
        InsertFirstWahana(L,W);
    } else {
        P = AlokasiWahana(W);
        if (P != Nil) {
            Last = FirstWahana(*L);
            while(NextWahana(Last) != Nil) {
                Last = NextWahana(Last);
            }
            InsertAfterWahana(L, P, Last);
        }
    }
}

void DelFirstWahana (ListWahana *L, addressWahana *P){
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    *P = FirstWahana(*L);

    if (NextWahana(*P) != Nil) {
        FirstWahana(*L) = NextWahana(*P);
        NextWahana(*P) = Nil;
    } else {
        CreateEmptyListWahana(L);
    }
}

void DelAfterWahana (ListWahana *L, addressWahana *Pdel, addressWahana Prec){
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    *Pdel = NextWahana(Prec);
    NextWahana(Prec) = NextWahana(*Pdel);
    NextWahana(*Pdel) = Nil;     
}

void DeleteWahana (ListWahana *L, Wahana W)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
{
    /* KAMUS LOKAL */
    addressWahana P, Prec;
    addressWahana A;
    boolean found=false;

    /* ALGORITMA */
    if (!IsEmptyListWahana(*L)) {
    	P = FirstWahana(*L);
    	if (IsWahanaSama(InfoWahana(P),W)) {
    		DelFirstWahana(L, &A);
    	} else {
    		Prec = Nil;
    		while ((P != Nil) && !found) {
    			if (IsWahanaSama(InfoWahana(P),W)) {
    				DelAfterWahana(L, &P, Prec);
    				DealokasiWahana(&P);
    				found = true;
    			} else {
    				Prec = P;
    				P = NextWahana(P);
    			}
    		}
    	}
    }
}