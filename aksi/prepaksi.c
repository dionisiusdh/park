#include <stdio.h>
#include "prepaksi.h"

/* ********** MENU ********** */
/* *********** BUY ***********  */
void MenuBuy(TabInt *Inventory, TabInt *ListMaterial, int *Money, aksitype *CurrentAksi, boolean *Valid)
/* I.S. Terdapat File Eksternal Material.txt */
/* F.S. Menampilkan Daftar Material yang dapat dibeli ke layar, menerima input jumlah material yang dibeli
        Apabila uang mencukupi, masukkan perintah eksekusi ke dalam stack. Apabila uang tidak cukup atau 
        waktu yang tersedia tidak cukup, menampilkan error ke layar (Memakan Waktu)  */
{
    /* KAMUS */
    int Harga, TempPrice, TempMoney, JumlahBarang;
    Kata NamaBarang;
    int i;

    /* ALGORITMA */
    // Menu Buy Material //
    printf("Ingin membeli apa?\n");
    printf("List: \n");
    
    for (i=0; (i<NeffArray(*ListMaterial)); i++){
        PrintKata(Nama(ElmtArray(*ListMaterial,i)));
        printf("   Harga: %d\n", Value(ElmtArray(*ListMaterial,i)));
    }
    printf("\nPetunjuk : Input Dalam Format (<Jumlah Barang> <Nama Barang>); Contoh: 1000 Wood\n");

    STARTKATA();
    JumlahBarang = KataToInteger(CKata);
    ADVKATA();
    NamaBarang = CKata;

    Harga = GetValue(ListMaterial, NamaBarang);
    TempMoney = *Money-(Harga*JumlahBarang);
    TempPrice = Harga*JumlahBarang;
    if(TempMoney >= 0){
        InfoNamaAksi(*CurrentAksi) = NamaBarang;
        InfoJumlahAksi(*CurrentAksi) = JumlahBarang;
        Harga(*CurrentAksi) = TempPrice;
    }
    else{
        *Valid = false;
        
        // Uang Tidak Cukup
        printf("\nUang Anda tidak memenuhi untuk melakukan pembelian material tersebut.\n");
    }
}

void Buy(TabInt *Inventory, TabInt *ListMaterial, Kata NamaBarang, int JumlahBarang){
/* Membeli barang. Menambahkan NamaBarang pada TempInventory sebanyak JumlahBarang */
/* Mengurangi money dengan nilai total harga material dikali JumlahBarang */
    /* KAMUS */
    int CurrentJumlah, NewJumlah;

    /* ALGORITMA */
    CurrentJumlah = GetValue(Inventory, NamaBarang);
    NewJumlah = CurrentJumlah + JumlahBarang; 
    ChangeValue(Inventory, NamaBarang, NewJumlah);
}

/* *********** BUILD ***********  */
void MenuBuild(MATRIKS *Map, TabInt *Inventory, BinTree Wahana1, BinTree Wahana2, BinTree Wahana3, int *CurrentWahana, boolean *Valid, ListWahana *LWahana){
/* I.S. Terdapat file eksternal wahana.txt yang memberi info bahan bangunan yang dibutuhkan */
/* F.S. Menampilkan ingin membangun apa kemudian meminta masukan dari pemain akan wahana apa yang hendak
        dibangun kemudian akan menyimpan perintah bangun ke dalam stack yang akan dijalankan saat execute.
        Apabila bahan bangunan tidak cukup atau waktu tidak cukup, maka akan ditampilkan error (Memakan Waktu) */
    /* KAMUS */
    Kata NamaWahana;
    wahanatype InfoWahana;
    int i;
    Wahana W;
    List Upgrade;

    /* ALGORITMA */
    // Print list wahana
    PrintNamaWahana(Wahana1, Wahana2, Wahana3);
    printf("$ ");
    STARTKATA();
    NamaWahana = CKata;
    
    // Cek input
    if (IsEQKata(NamaWahana, StringToKata("flyfly", 6)) || IsEQKata(NamaWahana, StringToKata("Flyfly", 6))) {
        *CurrentWahana = 1;
        GetInfoWahana(Wahana1, &InfoWahana);
    } else if (IsEQKata(NamaWahana, StringToKata("fallfall", 8)) || IsEQKata(NamaWahana, StringToKata("Fallfall", 8))) {
        *CurrentWahana = 2;
        GetInfoWahana(Wahana2, &InfoWahana);
    } else if (IsEQKata(NamaWahana, StringToKata("walkwalk", 8)) || IsEQKata(NamaWahana, StringToKata("Walkwalk", 8))) {
        *CurrentWahana = 3;
        GetInfoWahana(Wahana3, &InfoWahana);
    }
    
    for (i=0;i<5;i++) {
        if (WahanaMatUp(InfoWahana, i) > Value(ElmtArray(*Inventory, i))) {
            *Valid = false;
            printf("Material anda tidak mencukupi.\n");
            break;
        }
        Value(ElmtArray(*Inventory, i)) -= WahanaMatUp(InfoWahana, i);
    }

    if (*Valid) {
        printf("Selamat, rancangan wahana anda bersimbol \'w\' telah ditambahkan\n");
        PlaceRancanganWahana(Map, getPlayer(*Map));
        
        // Mengganti list wahana
        int MapWahana = 1; // Biar ga error dulu
        CreateEmptyListLinier(&Upgrade);

        if (CurrentWahana == 1) {
            GetInfoWahana(Wahana1, &InfoWahana);
            MakeWahana(&W, Wahana1, GetTitikNearRancanganWahana(*Map), Upgrade, true, MapWahana);
        } else if (CurrentWahana == 2) {
            GetInfoWahana(Wahana2, &InfoWahana);
            MakeWahana(&W, Wahana2, GetTitikNearRancanganWahana(*Map), Upgrade, true, MapWahana);
        } else if (CurrentWahana == 3) {
            GetInfoWahana(Wahana3, &InfoWahana);
            MakeWahana(&W, Wahana3, GetTitikNearRancanganWahana(*Map), Upgrade, true, MapWahana);
        } 
        
        InsertLastWahana(LWahana, W);
    }
}

void Build(MATRIKS *Map, TabInt *Inventory, BinTree Wahana1, BinTree Wahana2, BinTree Wahana3, int CurrentWahana){
    /* KAMUS */
    wahanatype InfoWahana;
    int i;

    /* ALGORITMA */
    // Mengambil info wahana berdasarkan current wahana yang ingin dibangun
    if (CurrentWahana == 1) {
        GetInfoWahana(Wahana1, &InfoWahana);
    } else if (CurrentWahana == 2) {
        GetInfoWahana(Wahana2, &InfoWahana);
    } else if (CurrentWahana == 3) {
        GetInfoWahana(Wahana3, &InfoWahana);
    } 

    // Mengurangkan jumlah item di inventory sesuai dengan bahan yang diperlukan
    for (i=0;i<5;i++) {
        Value(ElmtArray(*Inventory, i)) -= WahanaMatUp(InfoWahana, i);
    }

    // Place wahana di Map
    BuildWahana(Map);
}

/* *********** UPGRADE ***********  */
void MenuUpgrade(TabInt *Inventory, boolean *Valid, ListWahana *CurrentDataWahana, ListWahana *LUpgrade, POINT Player, Map CurrentMap){
/* I.S. Terdapat file eksternal wahana.txt yang memberi info bahan bangunan dan uang yang dibutuhkan*/
/* F.S. Menampilkan ingin upgrade apa kemudian meminta masukan dari pemain akan wahana apa yang hendak
        di-upgrade kemudian akan menyimpan perintah upgrade ke dalam stack yang akan dijalankan saat execute.
        Apabila bahan bangunan tidak cukup atau waktu tidak cukup atau uang tidak cukup, maka akan ditampilkan error (Memakan Waktu) */
    /* KAMUS */
    BinTree CurrentTree, CurrentUpgradeTree, CurrentFinalUpgradeTree;
    POINT PosisiWahana;
    wahanatype InfoWahana;
    *Valid = true;
    Wahana tempUpgrade;
    List historyUpgrade;
    ListWahana LWahanaNearby;
    int i, NomorUpgrade, NomorOpsiUpgrade, MapWahanaUpgrade;

    /* ALGORITMA */
    // Mencari Wahana apa saja yang ada (sudah di-build) di sekitar posisi pemain
    LWahanaNearby = GetWahanaNearPlayer(*CurrentDataWahana, Player, CurrentMap);

    // *CurrentUpgrade = 0; // Jika sampai akhir fungsi CurrentUpgrade masih bernilai 0, maka tidak ada upgrade yang terjadi.
    // Print list wahana
    PrintNamaUpgradeWahana(LWahanaNearby);
    printf("Petunjuk : Harap Masukan Nomor Upgrade (misal 1).\n");
    printf("$ ");
    STARTKATA();
    NomorUpgrade = KataToInteger(CKata);

    while (NomorUpgrade < 1) {
        printf("Maaf upgrade tersebut tidak tersedia, harap masukan nomor upgrade (misal 1).\n");
        printf("$ ");
        ADVKATA();
        NomorUpgrade = KataToInteger(CKata);
    } 

    PosisiWahana = PosisiWahana(InfoWahana(GetWahanaByIndex(LWahanaNearby,NomorUpgrade-1)));
    MapWahanaUpgrade = MapWahana(InfoWahana(GetWahanaByIndex(LWahanaNearby,NomorUpgrade-1)));
    CurrentUpgradeTree = DeskripsiWahana(InfoWahana(GetWahanaByIndex(LWahanaNearby,NomorUpgrade-1)));

    PrintOpsiUpgradeWahana(CurrentUpgradeTree);
    printf("Petunjuk : Harap Masukan Nomor Opsi Upgrade (misal 1).\n");
    printf("$ ");
    STARTKATA();
    NomorOpsiUpgrade = KataToInteger(CKata);

    while (NomorOpsiUpgrade < 1 && NomorOpsiUpgrade > 2) {
        printf("Maaf opsi upgrade tersebut tidak tersedia, harap masukan nomor opsi upgrade (misal 1).\n");
        printf("$ ");
        ADVKATA();
        NomorOpsiUpgrade = KataToInteger(CKata);
    }

    // Cek input
    if (NomorOpsiUpgrade == 1) {
        CurrentFinalUpgradeTree = Left(CurrentTree);
        GetInfoWahana(Left(CurrentTree), &InfoWahana);
    } else if (NomorOpsiUpgrade == 2) {
        CurrentFinalUpgradeTree = Right(CurrentTree);
        GetInfoWahana(Right(CurrentTree), &InfoWahana);
    }
    
    for (i=0;i<5;i++) {
        if (WahanaMatUp(InfoWahana, i) > Value(ElmtArray(*Inventory, i))) {
            *Valid = false;
            printf("Material tidak mencukupi.\n");
            break;
        }
    }

    if(*Valid){
        printf("Upgrade Berhasil.\n");
        MakeWahana(&tempUpgrade, CurrentFinalUpgradeTree, PosisiWahana, historyUpgrade, false, MapWahanaUpgrade);
        InsertLastWahana(&L, tempUpgrade);
    } 
}

void Upgrade(MATRIKS *Map, TabInt *Inventory, BinTree Wahana1, BinTree Wahana2, BinTree Wahana3, int CurrentWahana, int CurrentUpgrade){
    /* KAMUS */
    wahanatype InfoWahana;
    BinTree CurrentTree, CurrentUpgradeTree;
    int i;

    /* ALGORITMA */
    // Mengambil info wahana berdasarkan current wahana yang ingin dibangun
    if (CurrentWahana == 1) {
        CurrentTree = Wahana1;
    } else if (CurrentWahana == 2) {
        CurrentTree = Wahana2;
    } else if (CurrentWahana == 3) {
        CurrentTree = Wahana3;
    } 

    if (CurrentUpgrade == 1) {
        CurrentUpgradeTree = Left(CurrentTree);
        GetInfoWahana(Left(CurrentTree), &InfoWahana);
    } else if (CurrentUpgrade == 2) {
        CurrentUpgradeTree = Right(CurrentTree);
        GetInfoWahana(Right(CurrentTree), &InfoWahana);
    }

    // Mengurangkan jumlah item di inventory sesuai dengan bahan yang diperlukan dan mengurangkan jumlah uang di money sesuai yang dibutuhkan
    for (i=0;i<5;i++) {
        Value(ElmtArray(*Inventory, i)) -= WahanaMatUp(InfoWahana, i);
    }

    // Place wahana di Map
    //PlaceWahana(Map, getPlayer(*Map));
}

/* ************ FUNGSI-FUNGSI PROGRAM ************ */
void Undo (Stack * S, aksitype *X, ListWahana *LWahana) {
/* Melakukan undo dengan pop elemen dari stack */
    /* KAMUS LOKAL */
    addressWahana Trash;

    /* ALGORITMA */
    if (!IsEmptyStack(*S)) {
        Pop(S, X);
        CurrentDuration(*S) = KurangJAM(Durasi(*X), CurrentDuration(*S));

        if (IsEQKata(Aksi(*X), StringToKata("build",5))) {
            DelLastWahana(LWahana, &Trash);
        }
        printf("Berhasil undo.\n");
    } else {
        printf("Anda belum memasukkan aksi apapun.\n");
    }
}

void Execute(MATRIKS *Map, Stack *S, int *Money, TabInt *Inventory, TabInt *ListMaterial, ListWahana *LWahana, BinTree Wahana1, BinTree Wahana2, BinTree Wahana3, boolean *prep_status, boolean *main_status){
/* I.S. Terdapat stack perintah sembarang yang mungkin kosong */
/* F.S. Semua perintah dijalankan satu per satu dari top hingga stack kosong, 
        kemudian fase berubah dari preparation ke main*/
        /* KAMUS */
        aksitype X;

        /* ALGORITMA */
        *Money -=  JumlahBiaya(*S);
        
        while (!IsEmptyStack(*S)) {
            Pop(S, &X);
            if (IsEQKata(Aksi(X),StringToKata("buy",3))){
                Buy(Inventory, ListMaterial, InfoNamaAksi(X), InfoJumlahAksi(X));
            } else if (IsEQKata(Aksi(X),StringToKata("build",5))){
                Build(Map, Inventory, Wahana1, Wahana2, Wahana3, InfoJumlahAksi(X));
            } else if (IsEQKata(Aksi(X),StringToKata("upgrade",7))){
                // Upgrade()
            }
        }

        *prep_status = false;
        *main_status = true;
}

void Main(Stack *S){
/* I.S. Execute tidak dijalankan */
/* F.S. Stack Kosong dan Memulai Main Phase */
    /* KAMUS LOKAL */
    aksitype X;

    /* ALGORITMA */
    while(Top(*S) != NilStack){
        Pop(S,&X);
    }
}

void AddAksi (Stack *S, aksitype X) {
/* Menambahkan aksi ke dalam stack aksi */
    /* KAMUS LOKAL */
    long D1, D2, DHsl;

    /* ALGORITMA */
    if (!IsFullStack(*S)) {
        Push(S,X);
        CurrentDuration(*S) = TambahJAM(CurrentDuration(*S), Durasi(X));
        printf("Berhasil menambahkan aksi.\n");
    } else {
        printf("Anda tidak memiliki durasi yang cukup.\n");
    }
}

int JumlahAksi(Stack S){
    //KAMUS

    //ALGORITMA
    return TotalAksi(S);
}

int JumlahBiaya (Stack S) {
    //KAMUS

    //ALGORITMA
    return TotalBiaya(S);
} 