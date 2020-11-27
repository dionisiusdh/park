// Realisasi Dari wahana.h

#include "./wahana.h"
#include <time.h>

/* ********** KONSTRUKTOR ********** */
void MakeWahana(Wahana *W, BinTree datawahana, POINT posisiwahana, List historyupgrade, boolean statuswahana, int mapwahana){
    /* KAMUS */

    /* ALGORITMA */
    DeskripsiWahana(*W) = datawahana;
    PosisiWahana(*W) = posisiwahana;
    HistoryWahana(*W) = historyupgrade;
    StatusWahana(*W) = statuswahana;
    MapWahana(*W) = mapwahana;
}

/* ********** GETTER ********** */
BinTree GetDataWahana(Wahana W)
/* Sebuah Getter untuk mengembalikan data wahana dalam bentuk wahanatype */
{
    /* KAMUS */

    /* ALGORITMA */
    return DeskripsiWahana(W);
}

POINT GetPosisiWahana(Wahana W)
/* Sebuah Getter untuk mengembalikan posisi wahana dalam bentuk POINT */
{
    /* KAMUS */

    /* ALGORITMA */
    return PosisiWahana(W);
}

List GetHistoryWahana(Wahana W)
/* Sebuah Getter untuk mengembalikan history upgrade wahana dalam bentuk List */
{
    /* KAMUS */

    /* ALGORITMA */
    return HistoryWahana(W);
}

boolean GetStatusWahana(Wahana W)
/* Sebuah Getter untuk mengembalikan status wahana dalam bentuk boolean */
{
    /* KAMUS */

    /* ALGORITMA */
    return StatusWahana(W);
}

boolean GetStatusNamaWahana(ListWahana *LWahana, Kata NamaWahana)
/* Mengambil status wahana dalam bentuk boolean berdasarkan nama wahana */
{
    /* KAMUS */

    /* ALGORITMA */
    addressWahana P = FirstWahana(*LWahana);
    while (!IsEQKata(NamaWahana, AkarNama(DeskripsiWahana(InfoWahana(P))))){
        P = NextWahana(P);
    }
    return StatusWahana(InfoWahana(P));
}

int GetMapWahana(Wahana W)
/* Sebuah Getter untuk mengembalikan nomor wahana dalam bentuk integer */
{
    /* KAMUS */

    /* ALGORITMA */
    return MapWahana(W);
}

Wahana GetInfoWahanaAtTitik (ListWahana L, POINT P)
/* Mengambil informasi wahana dari list wahana pada titik P */
{
    /* KAMUS LOKAL */
    addressWahana A;
    boolean found = false;

    /* ALGORITMA */
    A = FirstWahana(L);

    while (A != Nil) {
        if(EQ(PosisiWahana(InfoWahana(A)),P)){
            return InfoWahana(A);
        }
        A = NextWahana(A);
    }

}

ListWahana GetWahanaNearPlayer (ListWahana L, POINT P, int CurrentMap) {
/* Mengembalikan ListWahana yang ada di sekitar Player */
    ListWahana LNear;
    CreateEmptyListWahana(&LNear);
    
    addressWahana PWahana = FirstWahana(L);
    while (PWahana != Nil) {
        if (MapWahana(InfoWahana(PWahana)) != CurrentMap) {
            PWahana = NextWahana(PWahana);
            continue;
        }
        if (AreTwoPointsNear(PosisiWahana(InfoWahana(PWahana)), P)) {
            InsertFirstWahana(&LNear, InfoWahana(PWahana));
        }
        PWahana = NextWahana(PWahana);
    }
    return LNear;
}

/* ********** SETTER ********** */
void SetDataWahana(Wahana *W, BinTree X)
/* Mengubah attribut datawahana pada W menjadi X */
{
    /* KAMUS */

    /* ALGORITMA */
    DeskripsiWahana(*W) = X;
}

void SetPosisiWahana(Wahana *W, POINT X)
/* Mengubah attribut posisi pada W menjadi X */
{
    /* KAMUS */

    /* ALGORITMA */
    PosisiWahana(*W) = X;
}

void SetHistoryWahana(Wahana *W, List X)
/* Mengubah attribut historyupgrade pada W menjadi X */
{
    /* KAMUS */

    /* ALGORITMA */
    HistoryWahana(*W) = X;
}

void SetStatusWahana(Wahana *W, boolean X)
/* Mengubah status wahana dalam bentuk boolean */
{
    /* KAMUS */

    /* ALGORITMA */
    StatusWahana(*W) = X;
}

void SetStatusNamaWahana(ListWahana *LWahana, Kata NamaWahana, boolean X)
/* Mengubah status wahana dalam bentuk boolean berdasarkan nama wahana */
{
    /* KAMUS */

    /* ALGORITMA */
    addressWahana P = FirstWahana(*LWahana);
    while (!IsEQKata(NamaWahana, AkarNama(DeskripsiWahana(InfoWahana(P))))){
        P = NextWahana(P);
    }
    StatusWahana(InfoWahana(P)) = X;
}

void SetMapWahana(Wahana *W, int X)
/* Mengubah map wahana dalam bentuk integer */
{
    /* KAMUS */

    /* ALGORITMA */
    MapWahana(*W) = X;
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

void DealokasiWahana (addressWahana *P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
    /* KAMUS LOKAL */

    /* ALGORITMA */
    free(*P);
}

boolean IsWahanaSama (Wahana W1, Wahana W2)
{
    return (IsWahanaTypeSama(DeskripsiWahana(W1),(DeskripsiWahana(W2))) && EQ(PosisiWahana(W1),PosisiWahana(W2)) && MapWahana(W1) == MapWahana(W2));
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
        if(EQ(PosisiWahana(InfoWahana(A)),P)){
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
    boolean found = false;

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

void DeleteWahanaByPosition (ListWahana *L, POINT Posisi, int MapWahana)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
{
    /* KAMUS LOKAL */
    addressWahana P, Prec;
    addressWahana A;
    boolean found = false;

    /* ALGORITMA */
    if (!IsEmptyListWahana(*L)) {
    	P = FirstWahana(*L);
    	if (EQ(PosisiWahana(InfoWahana(P)),Posisi) && MapWahana(InfoWahana(P)) == MapWahana){
    		DelFirstWahana(L, &A);
    	} else {
    		Prec = Nil;
    		while ((P != Nil) && !found) {
    			if (EQ(PosisiWahana(InfoWahana(P)),Posisi) && MapWahana(InfoWahana(P)) == MapWahana) {
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


void DelLastWahana (ListWahana *L, addressWahana *P){
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */
    /* KAMUS LOKAL */
    addressWahana Last, PrecLast;

    /* ALGORITMA */
    Last = FirstWahana(*L);
    PrecLast = Nil;

    while (NextWahana(Last) != Nil) {
        PrecLast = Last;
        Last = NextWahana(Last);
    }

    *P = Last;

    if (FirstWahana(*L) != Last) {
        NextWahana(PrecLast) = Nil;
    } else {
    	CreateEmptyListWahana(L);
    }
}

void PrintListWahana (ListWahana L)
/* I.S. ListWahana L terdefinisi */
/* F.S. Menampilkan List Wahana dalam format : [(<NamaWahana>,<PosisiWahana>)]  */
{
    /* KAMUS LOKAL */

    /* ALGORITMA */
    addressWahana P = FirstWahana(L);
    if (IsEmptyListWahana(L)){
        printf("[]");
    }
    else{
        printf("[");
        while (P != Nil){
            printf("(");
            PrintKata(AkarNama(DeskripsiWahana(InfoWahana(P))));
            printf(",");
            TulisPOINT(PosisiWahana(InfoWahana(P)));
            printf(",");
            printf("%d",MapWahana(InfoWahana(P)));
            printf(")");
            P = NextWahana(P);
        }
        printf("]");
    }
}

void PrintHistoryUpgradeWahana (Wahana W) {
/* I.S. ListWahana L terdefinisi */
/* F.S. Menampilkan List Wahana dalam format : <NamaWahana> -> <NamaWahana2> */
    /* KAMUS LOKAL */

    /* ALGORITMA */

    // BELUM DIIMPLEMENTASIKAN
    printf("[]");
}

void PrintNamaUpgradeWahana (ListWahana AvailableWahanas){
/* Menampilkan List Nama Upgrade Wahana yang bisa dibangun ke Layar */
    /* KAMUS LOKAL */
    addressWahana P;
    int i;

    /* ALGORITMA */
    printf("Wahana Apa yang Ingin Anda Upgrade?\n");
    printf("List :\n");
    P = FirstWahana(AvailableWahanas);
    i = 1;
    while (P != Nil) {
        // Memeriksa apakah wahana di sekitar pemain sudah diupgrade atau belum
        if (Left(DeskripsiWahana(InfoWahana(P))) != Nil && Right(DeskripsiWahana(InfoWahana(P))) != Nil) {
            printf("%d. ",i);
            PrintKata(AkarNama(DeskripsiWahana(InfoWahana(P))));
            printf(" ");
            TulisPOINT(PosisiWahana(InfoWahana(P)));
            printf("\n");
            i++;
        }
        P = NextWahana(P);
    }
}

void PrintOpsiUpgradeWahana (BinTree UpgradeWahana)
/* Menampilkan List Nama Upgrade Wahana yang bisa dibangun ke Layar */
{
    /* KAMUS LOKAL */

    /* ALGORITMA */
    printf("Upgrade Apa yang ingin Anda Lakukan?\n");
    printf("List :\n");
    printf("  1. ");
    PrintKata(AkarNama(Left(UpgradeWahana)));
    printf("\n  2. ");
    PrintKata(AkarNama(Right(UpgradeWahana)));
}

addressWahana GetWahanaByIndex (ListWahana L, int i)
/* Mengambil Wahana pada ListWahana L dengan index i (index pertama = 0) */
{
    /* KAMUS LOKAL */
    addressWahana P;
    int j;

    /* ALGORITMA */
    P = FirstWahana(L);
    j = 0;
    while (j < i) {
        if (j != i) {
            P = NextWahana(P);
        }
        j++;
    }
    return P;
}

addressWahana GetAddressByWahana (ListWahana L, Wahana W)
/* Mengembalikan address dari Wahana W di dalam ListWahana */
{
    /* KAMUS LOKAL */
    addressWahana P;
    boolean flag = false;

    /* ALGORITMA */
    P = FirstWahana(L);
    while (P != Nil && !flag) {
        if (IsWahanaSama(InfoWahana(P),W)) {
            flag = true;
        }
        else {
            P = NextWahana(P);
        }
    }
    return P;
}

boolean BrokenRandomizer () {
/* Menghasilkan true or false secara acak untuk membuat sebuah wahana rusak, jika true, wahana akan rusak */
/* 20% Wahana akan rusak */
    /* KAMUS LOKAL */
    int randomNumber;

    /* ALGORITMA */
    srand(time(NULL));
    randomNumber = rand()%10;

    if (randomNumber > 7) {
        return false;
    } else {
        return true;
    }

}