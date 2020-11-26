/* File : dpoint.c */
/* Deskripsi: Program utama (driver) ADT Point*/

#include <stdio.h>
#include <math.h>
#include "../boolean.h"
#include "point.h"

int main () {
	/* KAMUS */
	POINT P1, P2;
	float deltaX, deltaY;
	
	/* ALGORITMA */
	/* Test Baca dan Tulis */
	printf("Masukkan nilai absis dan ordinat P1: \n");
	BacaPOINT(&P1);
	printf("Masukkan nilai absis dan ordinat P2: \n");
	BacaPOINT(&P2);
	printf("Titik yang dibaca ");
	TulisPOINT(P1);
	
	/* Test IsOrigin */
	if (IsOrigin(P1)) {
		printf("P1 adalah titik origin");
	} else {
		printf("P1 bukan titik origin");
	}
	printf("\n");
	
	/*Test EQ, NEQ*/
	if (EQ(P1,P2)) {
		printf("P1 sama dengan P2\n");
	} else {
		printf("P1 beda dengan P2\n");
	}
	
	if (NEQ(P1,P2)) {
		printf("Benar, P1 beda dengan P2\n");
	} else {
		printf("Salah, P1 sama dengan P2\n");
	}
	
	/* Test IsOnSbX dan IsOnSbY */
	if (IsOnSbX(P1)) {
		printf("P1 ada di sumbu X");
	} else {
		printf("P1 bukan di sumbu X");
	}
	printf("\n");
	
	if (IsOnSbY(P1)) {
		printf("P1 ada di sumbu Y");
	} else {
		printf("P1 bukan di sumbu Y");
	}
	printf("\n");
	
	/*Test Kuadran*/
	printf("P1 ada di kuadran %d\n",Kuadran(P1));
	
	/*Test Jarak0*/
	printf("\nJarak P1 ke 0 adalah: %.2f\n",Jarak0(P1));
	
	/*Test Panjang*/
	printf("Jarak dari P1 ke P2 adalah: %.2f\n",Panjang(P1,P2));
	
	/* Test Geser */
	printf("Geser P1 sejajar sumbu x sebesar = ");
	scanf("%f", &deltaX);
	printf("Geser P1 sejajar sumbu y sebesar = ");
	scanf("%f", &deltaY);
	printf("P1 Setelah digeser = ");
	Geser(&P1,deltaX,deltaY);
	TulisPOINT(P1);
	printf("\n");
	
	/*Test GeserKeSbX dan GeserKeSbY*/
	printf("P1 digeser ke Sb X dan ke Sb Y menjadi:\n");
	GeserKeSbX(&P1);
	GeserKeSbY(&P1);
	TulisPOINT(P1);
	
	/*Test Mirror*/
	printf("\nMirror P1 thd Sb X:\n");
	Mirror(&P1, true);
	TulisPOINT(P1);
	
	/*Test Putar*/
	printf("\nP1 ada di putar 30 derajat menghasilkan:\n");
	Putar(&P1, 30);
	TulisPOINT(P1);
	return 0;
}
