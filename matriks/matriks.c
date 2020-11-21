/* File: matriks.c */
/* *** Realisasi ABSTRACT DATA TYPE MATRIKS *** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matriks.h"

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NB, int NK, MATRIKS * M){
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */
    NBrsEff(*M) = NB;
    NKolEff(*M) = NK;
}

/* *** Selektor "DUNIA MATRIKS" *** */
boolean IsIdxValid (int i, int j){
/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */
    boolean valid = false;
    if ((i>=BrsMin && i<=BrsMax)&&(j>=BrsMin&&j<=BrsMax)){
        valid = true;
    }
    return valid;
}
/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (MATRIKS M){
/* Mengirimkan indeks baris terkecil M */
    return BrsMin;
}
indeks GetFirstIdxKol (MATRIKS M){
/* Mengirimkan indeks kolom terkecil M */
    return KolMin;
}
indeks GetLastIdxBrs (MATRIKS M){
/* Mengirimkan indeks baris terbesar M */
    return (NBrsEff(M) - 1);
}
indeks GetLastIdxKol (MATRIKS M){
/* Mengirimkan indeks kolom terbesar M */
    return NKolEff(M)-1;
}
boolean IsIdxEff (MATRIKS M, indeks i, indeks j){
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
    return ((i>=BrsMin && i<=(GetLastIdxBrs(M))) && (j>=KolMin && j<=(GetLastIdxKol(M))));
}

/* ********** Assignment  MATRIKS ********** */
void CopyMATRIKS (MATRIKS MIn, MATRIKS * MHsl){
    /* Melakukan assignment MHsl  MIn */
    //KAMUS LOKAL
    *MHsl = MIn;
}

/* ********** KELOMPOK BACA/TULIS ********** */
void BacaMATRIKS (MATRIKS * M, int NB, int NK){
    /* I.S. IsIdxValid(NB,NK) */
    /* F.S. M terdefinisi nilai elemen efektifnya, berukuran NB x NK */
    /* Proses: Melakukan MakeMATRIKS(M,NB,NK) dan mengisi nilai efektifnya */
    /* Selanjutnya membaca nilai elemen per baris dan kolom */
    /* Contoh: Jika NB = 3 dan NK = 3, maka contoh cara membaca isi matriks :
    1 2 3
    4 5 6
    8 9 10
    */
    //KAMUS LOKAL
    int i,j; int val;
    //ALGORITMA
    MakeMATRIKS(NB, NK,&*M);
    for (i=GetFirstIdxBrs(*M); i<=GetLastIdxBrs(*M); i++){
        for (j=GetFirstIdxKol(*M); j<=GetLastIdxKol(*M); j++){
            scanf("%d",&val);
            Elmt(*M,i,j) = val;
        }
    }
}
void BacaMATRIKSTxt (MATRIKS * M, int NB, int NK, char* filename){
    /* I.S. IsIdxValid(NB,NK) */
    /* F.S. M terdefinisi nilai elemen efektifnya, berukuran NB x NK */
    /* Proses: Melakukan MakeMATRIKS(M,NB,NK) dan mengisi nilai efektifnya */
    /* Selanjutnya membaca nilai elemen per baris dan kolom */
    /* Contoh: Jika NB = 3 dan NK = 3, maka contoh cara membaca isi matriks :
    1 2 3
    4 5 6
    8 9 10
    */
    //KAMUS LOKAL
    int i,j; 
    char val;
    FILE *PFile;

    //ALGORITMA
    MakeMATRIKS(NB, NK, &*M);
    PFile = fopen(filename, "r");
    if (PFile != NULL){
        for (i=0; i<NB; i++){
            for (j=0; j<NK; j++){
                //fscanf(PFile, "%c", &val);
                val = fgetc(PFile);
                Elmt(*M,i,j) = val;
            }
        }
        fclose(PFile);
    }
}
void TulisMATRIKS (MATRIKS M){
    /* I.S. M terdefinisi */
    /* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris
       dipisahkan sebuah spasi */
    /* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
    /* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
    1 2 3
    4 5 6
    8 9 10
    */
    //KAMUS LOKAL
    int i,j;
    //ALGORITMA
    for (i=0; i<10; i++){
        for (j=0; j<20; j++){
                printf("%c",Elmt(M,i,j));
            }        
        printf("\n");
    }
}

/* ********** Operasi lain ********** */
int NBElmt (MATRIKS M){
/* Mengirimkan banyaknya elemen M */
    return (NBrsEff(M)*NKolEff(M));
}

/* ********** GETTER POSISI OBJEK ********** */
POINT initializePlayerPosition (MATRIKS* M) {
    /* Menentukan posisi Player pertama kali */
    indeks i, j;
    while (IsIdxValid(i, j)) {
        if (Elmt(*M, i, j) == '-') {
            Elmt(*M, i, j) = 'P';
        }
    }
}

POINT getPlayer (MATRIKS M) {
/* Mengirimkan posisi player */
/* Posisi dihitung mulai dari 0,0 */
    //KAMUS LOKAL
    int i,j;
    POINT P;

    //ALGORITMA
    for (i=0; i<10; i++){
        for (j=0; j<20; j++){
            if (Elmt(M, i, j) == 'P') {
                P = MakePOINT(i, j);
                return P;
            }
        }  
    }
}

POINT getOffice (MATRIKS M) {
/* Mengirimkan posisi office */
/* Posisi dihitung mulai dari 0,0 */
    //KAMUS LOKAL
    int i,j;
    POINT P;

    //ALGORITMA
    for (i=0; i<10; i++){
        for (j=0; j<20; j++){
            if (Elmt(M, i, j) == 'O') {
                P = MakePOINT(i, j);
                return P;
            }
        }  
    }
}

POINT getAntrian (MATRIKS M) {
/* Mengirimkan posisi office */
/* Posisi dihitung mulai dari 0,0 */
    //KAMUS LOKAL
    int i,j;
    POINT P;

    //ALGORITMA
    for (i=0; i<10; i++){
        for (j=0; j<20; j++){
            if (Elmt(M, i, j) == 'A') {
                P = MakePOINT(i, j);
                return P;
            }
        }  
    }
}

POINT getGerbangUp (MATRIKS M) {
/* Mengirimkan posisi gerbang */
/* Posisi dihitung mulai dari 0,0 */
/* Mengembalikan (-1, -1) jika tidak ditemukan */
    //KAMUS LOKAL
    int i,j;
    POINT P;

    //ALGORITMA
    for (i=0; i<10; i++){
        for (j=0; j<20; j++){
            if (Elmt(M, i, j) == '^') {
                P = MakePOINT(i, j);
                return P;
            }
        }  
    }
    return MakePOINT(-1,-1);
}
POINT getGerbangDown (MATRIKS M) {
/* Mengirimkan posisi gerbang */
/* Posisi dihitung mulai dari 0,0 */
/* Mengembalikan (-1, -1) jika tidak ditemukan */
    //KAMUS LOKAL
    int i,j;
    POINT P;

    //ALGORITMA
    for (i=0; i<10; i++){
        for (j=0; j<20; j++){
            if (Elmt(M, i, j) == 'v') {
                P = MakePOINT(i, j);
                return P;
            }
        }  
    }
    return MakePOINT(-1,-1);
}
POINT getGerbangLeft (MATRIKS M) {
/* Mengirimkan posisi gerbang */
/* Posisi dihitung mulai dari 0,0 */
/* Mengembalikan (-1, -1) jika tidak ditemukan */
    //KAMUS LOKAL
    int i,j;
    POINT P;

    //ALGORITMA
    for (i=0; i<10; i++){
        for (j=0; j<20; j++){
            if (Elmt(M, i, j) == '<') {
                P = MakePOINT(i, j);
                return P;
            }
        }  
    }
    return MakePOINT(-1,-1);
}
POINT getGerbangRight (MATRIKS M) {
/* Mengirimkan posisi gerbang */
/* Posisi dihitung mulai dari 0,0 */
/* Mengembalikan (-1, -1) jika tidak ditemukan */
    //KAMUS LOKAL
    int i,j;
    POINT P;

    //ALGORITMA
    for (i=0; i<10; i++){
        for (j=0; j<20; j++){
            if (Elmt(M, i, j) == '>') {
                P = MakePOINT(i, j);
                return P;
            }
        }  
    }
    return MakePOINT(-1,-1);
}
POINT getPlayerTransportedPosition (MATRIKS MDest, POINT GDest) {
    /* Mengirimkan posisi Player setelah berpindah Map ke MDest, berdasarkan
    posisi Gerbang GDest pada Map tujuan */
    indeks xG = Absis(GDest);
    indeks yG = Ordinat(GDest);
    POINT PlayerNew;
    if (Elmt(MDest, xG, yG) == '^') {
        Absis(PlayerNew) = xG+1;
        Ordinat(PlayerNew) = yG;
    }
    else if (Elmt(MDest, xG, yG) == 'v') {
        Absis(PlayerNew) = xG-1;
        Ordinat(PlayerNew) = yG;
    }
    else if (Elmt(MDest, xG, yG) == '<') {
        Absis(PlayerNew) = xG;
        Ordinat(PlayerNew) = yG+1;
    }
    else if (Elmt(MDest, xG, yG) == '>') {
        Absis(PlayerNew) = xG;
        Ordinat(PlayerNew) = yG-1;
    }
    return PlayerNew;
}


/* ********** MOVEMENT ********** */
/* Titik 0,0 berada di pojok kiri atas matriks */
void moveUp (MATRIKS *M) {
/* Menggerakan player ke atas */

    //KAMUS LOKAL
    int x, y;
    int xNew, yNew;
    POINT PPlayer;

    //ALGORITMA
    PPlayer = getPlayer(*M);

    x = Absis(PPlayer);
    y = Ordinat(PPlayer);

    xNew = x-1;
    yNew = y;

    if (!hitWall(M, xNew, yNew)) {  
        Elmt(*M, x, y) = '-';
        Elmt(*M, xNew, yNew) = 'P';
    } else {
        printf("Anda menabrak dinding!\n");
    }
}

void moveDown (MATRIKS *M) {
/* Menggerakan player ke bawah */

    //KAMUS LOKAL
    int x, y;
    int xNew, yNew;
    POINT PPlayer;

    //ALGORITMA
    PPlayer = getPlayer(*M);

    x = Absis(PPlayer);
    y = Ordinat(PPlayer);

    xNew = x+1;
    yNew = y;

    if (!hitWall(M, xNew, yNew)) {  
        Elmt(*M, x, y) = '-';
        Elmt(*M, xNew, yNew) = 'P';
    } else {
        printf("Anda menabrak dinding!\n");
    }
}

void moveLeft (MATRIKS *M) {
/* Menggerakan player ke kiri */

    //KAMUS LOKAL
    int x, y;
    int xNew, yNew;
    POINT PPlayer;

    //ALGORITMA
    PPlayer = getPlayer(*M);

    x = Absis(PPlayer);
    y = Ordinat(PPlayer);

    xNew = x;
    yNew = y-1;

    if (!hitWall(M, xNew, yNew)) {  
        Elmt(*M, x, y) = '-';
        Elmt(*M, xNew, yNew) = 'P';
    } else {
        printf("Anda menabrak dinding!\n");
    }
}

void moveRight (MATRIKS *M) {
/* Menggerakan player ke kanan */

    //KAMUS LOKAL
    int x, y;
    int xNew, yNew;
    POINT PPlayer;

    //ALGORITMA
    PPlayer = getPlayer(*M);

    x = Absis(PPlayer);
    y = Ordinat(PPlayer);

    xNew = x;
    yNew = y+1;

    if (!hitWall(M, xNew, yNew)) {  
        Elmt(*M, x, y) = '-';
        Elmt(*M, xNew, yNew) = 'P';
    } else {
        printf("Anda menabrak dinding!\n");
    }
}

boolean hitWall (MATRIKS *M, int xNew, int yNew){
/* Cek apakah player menabrak dinding, wahana, atau objek lainnya (Kecuali office) */
    return (Elmt(*M, xNew, yNew) == '*' || Elmt(*M, xNew, yNew) == 'W' || Elmt(*M, xNew, yNew) == 'A');
}

//void goToOtherMap (MATRIKS* MActive, MATRIKS* MAsal, MATRIKS* MTujuan, Map* ActiveMap, POINT* Player, Graph G, char MoveCommand) {
    /**
     * I.S. Player bergerak menuju gerbang dan terdapat graf yang menghubungkan Map asal ke tujuan
     * F.S. Jika Gagal, tidak ada yang berubah.
     *      Jika berhasil:
     *      Posisi Player pada Map lama dihapus
     *      Map aktif MActive menjadi Map selanjutnya
     *      Posisi Player pada Map baru bergantung dari posisi gerbang ia keluar
     * Proses:
     *      Menghapus 'P' dari Map Asal
     *      Menempatkan 'P' pada Map Tujuan
     *      Mengubah Map Aktif ke Map tujuan
    */
    //if (isNearGerbang(*MAsal, *Player)) {
    //if (isGoingTowardGerbang(*MAsal, *Player, MoveCommand)) {
    //if (IsSrcByReqMoveExist(G, *ActiveMap, MoveCommand)) {
    
    // Menghapus posisi Player dari Map asal
    /*Elmt(*MActive, Absis(*Player), Ordinat(*Player)) = '-';
    CopyMATRIKS(*MActive, MAsal);
    
    // Mencari posisi gerbang di Map tujuan
    POINT GDest;
    if (MoveCommand=='w') { GDest = getGerbangDown(*MTujuan); }
    else if (MoveCommand=='s') { GDest = getGerbangUp(*MTujuan); }
    else if (MoveCommand=='a') { GDest = getGerbangRight(*MTujuan); }
    else if (MoveCommand=='d') { GDest = getGerbangLeft(*MTujuan); }
    printf("GDest: ");
    TulisPOINT(GDest);
    printf("\n");
    // Mencari posisi Player di Map tujuan
    *Player = getPlayerTransportedPosition(*MTujuan, GDest);
    printf("Player ");
    TulisPOINT(*Player);
    printf("\n");
    // Mengubah Map Tujuan dan mengganti MapActive
    CopyMATRIKS(*MTujuan, MActive);
    Elmt(*MActive, Absis(*Player), Ordinat(*Player)) = 'P';
    
    *ActiveMap = ReturnMapDest(&G, *ActiveMap, MoveCommand);
    //}
    //}
    //}
}*/


/* ********** POSITION CHECKER ********** */
boolean isNearWahana (MATRIKS M, POINT P) {
     //KAMUS LOKAL
    int i,j;

    //ALGORITMA
    if (Elmt(M, Absis(P)+1, Ordinat(P)) == 'W') {
        return true;
    } else if (Elmt(M, Absis(P)-1, Ordinat(P)) == 'W') {
        return true;
    } else if (Elmt(M, Absis(P), Ordinat(P)+1) == 'W') {
        return true;
    } else if (Elmt(M, Absis(P), Ordinat(P)-1) == 'W') {
        return true;
    } else if (Elmt(M, Absis(P)+1, Ordinat(P)+1) == 'W') {
        return true;
    } else if (Elmt(M, Absis(P)+1, Ordinat(P)-1) == 'W') {
        return true;
    } else if (Elmt(M, Absis(P)-1, Ordinat(P)+1) == 'W') {
        return true;
    } else if (Elmt(M, Absis(P)-1, Ordinat(P)-1) == 'W') {
        return true;
    }

    return false;
}

boolean isNearAntrian (MATRIKS M, POINT P) {
     //KAMUS LOKAL
    int i,j;

    //ALGORITMA
    if (Elmt(M, Absis(P)+1, Ordinat(P)) == 'A') {
        return true;
    } else if (Elmt(M, Absis(P)-1, Ordinat(P)) == 'A') {
        return true;
    } else if (Elmt(M, Absis(P), Ordinat(P)+1) == 'A') {
        return true;
    } else if (Elmt(M, Absis(P), Ordinat(P)-1) == 'A') {
        return true;
    } else if (Elmt(M, Absis(P)+1, Ordinat(P)+1) == 'A') {
        return true;
    } else if (Elmt(M, Absis(P)+1, Ordinat(P)-1) == 'A') {
        return true;
    } else if (Elmt(M, Absis(P)-1, Ordinat(P)+1) == 'A') {
        return true;
    } else if (Elmt(M, Absis(P)-1, Ordinat(P)-1) == 'A') {
        return true;
    }

    return false;
}

boolean isInOffice (POINT PPlayer, POINT POffice) {
    return EQ(PPlayer, POffice);
} 

boolean isNearGerbang (MATRIKS M, POINT P) {
    /* Cek apakah ada Gerbang di posisi sekitar player */
    int x = Absis(P);
    int y = Ordinat(P);
    if (Elmt(M, x-1, y) == '^' || Elmt(M, x-1, y) == 'v' || Elmt(M, x-1, y) == '<' || Elmt(M, x-1, y) == '>') {
        return true;
    }
    else if (Elmt(M, x+1, y) == '^' || Elmt(M, x+1, y) == 'v' || Elmt(M, x+1, y) == '<' || Elmt(M, x+1, y) == '>') {
        return true;
    }
    else if (Elmt(M, x, y-1) == '^' || Elmt(M, x, y-1) == 'v' || Elmt(M, x, y-1) == '<' || Elmt(M, x, y-1) == '>') {
        return true;
    }
    else if (Elmt(M, x, y+1) == '^' || Elmt(M, x, y+1) == 'v' || Elmt(M, x, y+1) == '<' || Elmt(M, x, y+1) == '>') {
        return true;
    }
    return false;
}

//boolean isAllowedToChangeMap (MATRIKS M, Graph G, POINT P, Map Src, char MoveCommand) {
/*  P berada di dekat gerbang.
    Cek berdasarkan input Move apakah Player menuju Gerbang
    Fungsi mengecek pada graph, apakah Player dapat berpindah Map*/
    /*boolean toward = false;

    // CEK MOVE
    indeks x = Absis(P);
    indeks y = Ordinat(P);
    // Cek posisi relatif P dengan gerbang
    if (Elmt(M, x-1, y) == '^') {
        if (MoveCommand == 'w') {
            toward = true;
        }
    }
    if (Elmt(M, x+1, y) == 'v') {
        if (MoveCommand == 's') {
            toward = true;
        }
    }
    if (Elmt(M, x, y-1) == '<') {
        if (MoveCommand == 'w') {
            toward = true;
        }
    }
    if (Elmt(M, x, y+1) == '>') {
        if (MoveCommand == 'w') {
            toward = true;
        }
    }

    // CEK GRAPH
    boolean graphAllowed = IsSrcByReqMoveExist(G, Src, MoveCommand);

    return (toward && graphAllowed);
}*/


/*** BUILD ***/
void PlaceWahana (MATRIKS* M, POINT Player) {
    /* Menempatkan posisi rancangan pembangunan wahana pada MapActive */
    /* Menempatkan posisi rancangan wahana 'w' (w kecil) di atas, bawah, kiri atau kanan Player */
    /**
     * I.S. Setidaknya masih ada ruang diantar keempat posisi relatif dari Player
     * F.S. Ditambahkan rencana wahana 'w' di M
     * Proses: Cek posisi yang tersedia untuk membangun wahana berdasarkan posisi Player
     *         Perhatikan bahwa tidak boleh menmpatkan wahana persis di sebelah gerbang
    */
    // Cek dengan urutan Atas, Bawah, Kiri, Kanan
    POINT GerbangUp = getGerbangUp(*M);
    POINT GerbangDown = getGerbangDown(*M);
    POINT GerbangLeft = getGerbangLeft(*M);
    POINT GerbangRight = getGerbangRight(*M);
    POINT wahana;
    int x = Absis(Player);
    int y = Ordinat(Player);

    wahana = MakePOINT(x+1,y);
}
    

/*
boolean isInPortal (POINT PPlayer, POINT PPortal) {
    return EQ(PPlayer, PPortal);
} 
*/