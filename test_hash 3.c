#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


struct node{
	int kode;
    char judul[100];
    char kategori[40];
    int stok;		
	struct node *next;
}*hashTable[26], *curr, *curr_next;

char kategori_list[26][40];


void pushBuku(int hashKey, int kode, char judul[], char kategori[], int stok);
void inputKategori();
int hashBuku(char kategori[]);
int getLenLinkedList(int indeks);
void sortLinkedlist();
void inputBuku();
void tampilBuku();
void MenuUtama();
int isAdaKategori(char nodekategori[40]);
int isAda(int nodekode, char nodejudul[100]);
void clear_screen();

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system ("clear");
#endif
}

void pushBuku(int hashKey, int kode, char judul[100], char kategori[40], int stok){
	struct node *newBuku = (struct node*) malloc(sizeof(struct node));
	newBuku->kode = kode;
	strcpy(newBuku->judul, judul);
	strcpy(newBuku->kategori, kategori);
	newBuku->stok = stok;

	newBuku->next = NULL;
	//printf("Hashkey: %d", hashKey);
	if(hashTable[hashKey] == NULL){
		hashTable[hashKey] = newBuku;
	}
	else{
		curr = hashTable[hashKey];
		while(curr->next!= NULL) curr = curr->next;
		curr->next = newBuku;
	}
}

void inputKategori(){
	clear_screen();
	int cAmount;
	char ckategori[40];
	printf("|---------------------------------------------------------||");
	printf("\n|							  ||");
	printf("\n|			INPUT KATEGORI  		  ||");
	printf("\n|---------------------------------------------------------|| \n");

	printf("\nMasukkan Banyak Kategori yang akan diinput: ");
	scanf("%d", &cAmount);

	int tem;
	for(tem=1;tem<=cAmount; tem++){
		printf("\n-->Masukkan Kategori: ");
		scanf("%s", &ckategori);
		size_t n = sizeof(kategori_list) / sizeof(kategori_list[0]);

		if(isAdaKategori(ckategori) > 1){
			printf("[ERROR] Kategori Sudah Ada Membatalkan Input...\n\n");
			break;
		}
		int k;
		for(k=0; k<26;k++){
			if (strlen(kategori_list[k]) == 0){
				strcpy(kategori_list[k], ckategori);
				printf("[INFO] Input Kategori [%s] Sukses [%d]\n\n", ckategori, k);
				break;
			}
		}
	}
	int dummy;
	printf("Tekan Apa Saja Untuk Lanjut...");
	scanf("%c",&dummy);getchar();
}

int hashBuku(char kategori[40]){
	
	int i,j;
	for(j = 0; kategori[j]; j++){
		kategori[j] = tolower(kategori[j]);
	}
	
    for (i=0; i<4; i++)
    {
        if(strcmp(kategori, kategori_list[i]) == 0){
            return i;
        }
    }
	return -1;
}

int getLenLinkedList(int indeks){
	int banyak=0;
	curr = hashTable[indeks];
	while(curr != NULL){
		curr = curr->next;
		banyak++;
	}
	return banyak;
}

void sortLinkedlist()
{
	int temp_kode, temp_stok,htable,a,b;
	char temp_judul[100];
	char temp_kategori[40];
	for(htable=0; htable<26; htable++){
		for(a=0; a<getLenLinkedList(htable); a++){
			for(b=0; b<getLenLinkedList(htable); b++){
				curr = hashTable[htable];

				if (curr == NULL){
					continue;
				}

				curr_next = curr->next;
				//printf("Masuk 1");
				if(strcmp(curr->judul, curr_next->judul) > 0)
				{
					temp_kode = curr->kode;
					strcpy(temp_judul, curr->judul);
					strcpy(temp_kategori, curr->kategori);
					temp_stok = curr->stok;
					//printf("Masuk 2");


					curr->kode = curr_next->kode;
					strcpy(curr->judul, curr_next->judul);
					strcpy(curr->kategori, curr_next->kategori);
					//printf("Masuk 3");

					curr_next->kode = temp_kode;
					strcpy(curr_next->judul, temp_judul);
					strcpy(curr_next->kategori, temp_kategori);
					//printf("Masuk 4");
				}

				curr = curr_next;
				curr_next = curr_next->next;
				//printf("Masuk 5");
			}
		}
	}
}

int isAda(int nodekode, char nodejudul[100]){
	int i,j,o;
	for(i=0;i<26;i++){
		char temp[100];
		curr = hashTable[i];
		while(curr != NULL){
			strcpy(temp, curr->judul);
			if(nodekode == curr->kode){
				return 1; //1 means kode is already exists
			}

			for(j = 0; nodejudul[j]; j++){
				nodejudul[j] = tolower(nodejudul[j]);
			}

			for(o = 0; temp[o]; o++){
				temp[o] = tolower(temp[o]);
			}

			if(strcmp(nodejudul, temp) == 0){
				return 2;
			}

			return 0;
		}
	}
}

int isAdaKategori(char nodekategori[40]){
	char temp[40];
	char temp2[40];
	int ka,s;
	size_t n = sizeof(kategori_list) / sizeof(kategori_list[0]);
	if(n !=0){
		for(ka=0; ka<n; ka++){
			strcpy(temp, kategori_list[ka]);
			strcpy(temp2, nodekategori);
			for(s=0;s< strlen(kategori_list[ka]); s++){
				temp[s] = tolower(temp[s]);
				temp2[s] = tolower(temp2[s]);
			}

			if(strcmp(temp, temp2) == 0){
				return 3;
			}
		}
	}
	return 0;
}
void inputBuku(){
	clear_screen();
	int jml_buku;
	int jml=0;

	int nodekode;
	int nodestok;
	char nodejudul[100];
	char nodekategori[40];
	printf("|---------------------------------------------------------||");
	printf("\n|							  ||");
	printf("\n|			INPUT BUKU  		  	  ||");
	printf("\n|---------------------------------------------------------|| \n");


	printf("\nJumlah Buku Yang Diinput : ");
	scanf("%d",&jml_buku);
	do{

		printf("-->Kode Buku : ");
		scanf("%d",&nodekode);

		if(nodekode == -1) break;
		getchar();

        printf("-->Judul Buku : ");
		scanf("%[^\n]%*c", &nodejudul); 

        printf("-->Kategori Buku : ");
		scanf("%[^\n]%*c", &nodekategori); 

        printf("-->Stok Buku : ");
		scanf("%d",&nodestok);

		if (isAda(nodekode, nodejudul) >0){
			printf("[ERROR] Data Sudah Ada Membatalkan Input...\n\n");
			int dummy;
			printf("Tekan Apa Saja Untuk Lanjut...");
			scanf("%c",&dummy);getchar();
			return;
		}
		if (isAdaKategori(nodekategori) < 1){
			printf("[ERROR] Kategori Tidak Terdaftar Membatalkan Input...\n\n");
			int dummy;
			printf("Tekan Apa Saja Untuk Lanjut...");
			scanf("%c",&dummy);getchar();
			return;
		}
		pushBuku(hashBuku(nodekategori), nodekode, nodejudul, nodekategori, nodestok);
		jml++;
		printf("[INFO] Input Buku [%s] Sukses\n\n", nodejudul);
	}while(jml != jml_buku);

	sortLinkedlist();

}

void tampilBuku(){
	clear_screen();
	int pilihan = 0;
	int instrumen=0;
	int indekx = 0;
	int dummy;
	do{
		clear_screen();
		printf("|---------------------------------------------------------||");
		printf("\n|							  ||");
		printf("\n|			TAMPIL BUKU  		  	  ||");
		printf("\n|---------------------------------------------------------|| \n");

		printf("\nDaftar Kategori:\n");
		
		int k;
		for(k=0; k<26;k++){
			if (strlen(kategori_list[k]) != 0){
				printf("[%d] %s\n", k+1, kategori_list[k]);
			}
		}
		printf("[9999] Kembali Ke Menu Utama\n");

		printf("Pilih Kategori: ");
		scanf("%d", &pilihan);

		if(pilihan == 9999){
			break;
		}
		pilihan--;
		//printf("%d", pilihan);
		size_t n = sizeof(kategori_list) / sizeof(kategori_list[0]);
		if((pilihan < 0) || (pilihan > n) || (strlen(kategori_list[pilihan]) == 0)){
			printf("[ERROR] Kategori Tidak Terdaftar\n\n");
		}
		else{
			clear_screen();
			printf("\nView Kategori [%s]\n\n", kategori_list[pilihan]);
			printf("--------------------------------List Buku-----------------------------------\n");

			curr = hashTable[pilihan];
			while(curr != NULL){
				indekx++;
				printf("|*************************************\n");
				printf("| No\t\t: %d\n", indekx);
				printf("| Kode\t\t: %d\n", curr->kode);
				printf("| Judul\t\t: %s\n", curr->judul);
				printf("| Banyak Buku\t: %d\n", curr->stok);
				printf("|*************************************\n\n");
				curr=curr->next;
			}
			printf("\n\nTotal Buku: %d\n\n", indekx);
			printf("Tekan Apa Saja Untuk Lanjut...");
			scanf("%c",&dummy);getchar();
			//break;
		}
	}while(instrumen == 0);
	//MenuUtama();
}

void MenuUtama(){
	int instrumen = 0;
	int pilihan;
	//Menu Utama
	do{
		clear_screen();
		printf("------------------------Menu Utama-------------------------");
		printf("\nAppName: Aplikasi Input Buku Sederhana");
		printf("\nVersion: 0.1");
		printf("\n-------------------------Welcome---------------------------\n");

		printf("Pilihan Menu:\n");
		printf("[1] Input Kategori Buku\n");
		printf("[2] Input Buku\n");
		printf("[3] Tampilkan Buku Berdasarkan Kategori\n");
		printf("[4] Keluar\n");

		printf("\nPilih Menu: ");
		scanf("%d", &pilihan);

		switch (pilihan)
		{
			case 1: inputKategori();
					break;
			case 2: inputBuku();
					break;
			case 3: tampilBuku();
					break;
			case 4: instrumen = 1; break;
			default: printf("Pilihan Invalid. Masukkan Lagi\n\n");
							break;
		} 
	}while(instrumen == 0);

	printf("\n\n[INFO] Keluar Dari Program...\n");
	printf("[INFO] Terima Kasih Sudah Menggunakan App Sedehana Ini.\n");
}
int main(){
	
	MenuUtama();
	return 0;
}
