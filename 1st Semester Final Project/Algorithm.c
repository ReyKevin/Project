#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h> 
#include<time.h>

int ind_brg=0;
int ind_mmbr=0;
int ind_resi=0;
int ind_pjln=0;
int ind_cart=0;
int index=0;
int index_beli=0;
int stok_beli;

struct pt {
	char us[50],ps[20];
}LOGIN[50];

struct brg
{
	char kode_brg[50];
	char nama_brg[50];
	int stok_brg;
	int harga_brg;
	
}BRG[500],cart[500];

struct mmbr
{
	char nama[50];
	char alamat[50];
	char tgllhr[50];
}MMBR[500];

struct trx
{
	char no_resi[50];
	char nama_pembeli[50];
	char brg_dibeli[50];
	char tgl_beli[50];
}TRX[500];

FILE *brg;
FILE *mmbr;
FILE *resi;
FILE *pjln;
FILE *pf;

void file(){	
	pf=fopen("daftar.txt","r");
	while(fscanf(pf,"%s %s\n",&LOGIN[index].us,&LOGIN[index].ps)!=EOF){
		index++;
	}
	fclose(pf);
}

//BACA FILE"
//baca file barang
void load_brg()
{
	brg=fopen("brg.txt","r");
	while(fscanf(brg,"%[^\'.'].%[^\'.'].%d.%d\n",BRG[ind_brg].kode_brg,BRG[ind_brg].nama_brg,&BRG[ind_brg].stok_brg,&BRG[ind_brg].harga_brg)!=EOF)
	{
		ind_brg++;
	}
	fclose(brg);
}

//baca file member
void load_mmbr()
{
	mmbr=fopen("mmbr.txt","r");
	while(fscanf(mmbr,"%[^\'.'].%[^\'.'].%[^\n]\n",MMBR[ind_mmbr].nama,MMBR[ind_mmbr].alamat,MMBR[ind_mmbr].tgllhr)!=EOF)
	{
		ind_mmbr++;
	}
	fclose(mmbr);	
}

//baca file resi
void load_resi()
{
	resi=fopen("resi.txt","r");
	while(fscanf(resi,"%[^\'.'].%[^\n]\n",TRX[ind_resi].nama_pembeli,TRX[ind_resi].no_resi)!=EOF)
	{
		ind_resi++;
	}
	fclose(resi);
}

//baca file penjualan
void load_pjln()
{
	pjln=fopen("pjln.txt","r");
	while(fscanf(pjln,"%[^\'.'].%[^\n]\n",TRX[ind_pjln].brg_dibeli,TRX[ind_pjln].tgl_beli)!=EOF)
	{
		ind_pjln++;
	}
	fclose(pjln);
}

//FUNGSI" SEARCH
//search kode
int cari_kode(char *key)
{
	for(int i=0; i<ind_brg; i++)
	{
		if(strcmp(key,BRG[i].kode_brg)==0)
		return i;
	}
	return -1;
}

//search nama member
int cari_nama(char *key)
{
	for(int i=0; i<ind_mmbr; i++)
	{
		if(strcmp(key,MMBR[i].nama)==0)
		return i;
	}
	return -1;
}

//search nama resi
int cari_resi(char *key)
{
	for(int i=0; i<ind_resi; i++)
	{
		if(strcmp(key,TRX[i].nama_pembeli)==0)
		return i;
	}
	return -1;
}

//FUNGSI" SORT
//sort harga barang
void sorthrgbrg() 
{  
   for (int i = 0; i < ind_brg; i++)
   {
       for (int j = ind_brg-1; j >= 1 ; j--)
	   {
           if (BRG[j-1].harga_brg > BRG[j].harga_brg)
		   {
			  struct brg temp;
			  temp = BRG[j]; 
 			  BRG[j]= BRG[j-1]; 
  			  BRG[j-1] = temp;  
        	}
    	}
	}
}

//sort stok barang
void sortstokbrg() 
{  
   for (int i = 0; i < ind_brg; i++)
   {
       for (int j = ind_brg-1; j >= 1 ; j--)
	   {
           if (BRG[j-1].stok_brg > BRG[j].stok_brg)
		   {
			  struct brg temp;
			  temp = BRG[j]; 
 			  BRG[j]= BRG[j-1]; 
  			  BRG[j-1] = temp; 
        	}
    	}
	}
}



//FUNCTION MENU OWNER
//Display data barang(owner)/menu1
void databrg1()
{
	system("cls");
	printf("==========================================================================================\n");
	printf(" No. | Kode Barang        | Nama Barang        | Stok Barang        | Harga Barang       |\n");
	printf("==========================================================================================\n");
	for(int i=0;i<ind_brg;i++)
	{
		printf(" %2d  | %-18s | %-18s | %-18d | %-18d |\n",i+1, BRG[i].kode_brg, BRG[i].nama_brg, BRG[i].stok_brg, BRG[i].harga_brg);
	}
	fflush(stdin);
}

//Display data member(owner)/menu2
void datammbr1()
{
	system("cls");
	printf("=====================================================================\n");
	printf(" No. | Nama               | Alamat             | Tanggal lahir      |\n");
	printf("=====================================================================\n");
	for(int i=0;i<ind_mmbr;i++)
	{
		printf(" %2d  | %-18s | %-18s | %-18s |\n",i+1, MMBR[i].nama, MMBR[i].alamat, MMBR[i].tgllhr);
	}
	fflush(stdin);
}

//tambah data barang/menu3
void tmbbrg1()
{
	system("cls");
	printf("==================\n");
	printf("Tambah Data Barang\n");
	printf("==================\n\n");
	printf("Masukkan kode barang (angka 3 digit): ");
	fflush(stdin);
	scanf("%s",BRG[ind_brg].kode_brg);
	printf("Masukkan nama barang : ");
	fflush(stdin);
	scanf("%[^\n]",BRG[ind_brg].nama_brg);
	printf("Masukkan stok barang : ");
	fflush(stdin);
	scanf("%d",&BRG[ind_brg].stok_brg);
	printf("Masukkan harga barang : ");
	fflush(stdin);
	scanf("%d",&BRG[ind_brg].harga_brg);
	printf("\n\nData berhasil ditambahkan\nPress ENTER to continue");
	fflush(stdin);
	ind_brg++;
}

//tambah data member/menu4
void tmbmmbr1()
{
	system("cls");
	printf("==================\n");
	printf("Tambah Data Member\n");
	printf("==================\n\n");
	printf("Masukkan nama : ");
	fflush(stdin);
	scanf("%[^\n]",MMBR[ind_mmbr].nama);
	printf("Masukkan alamat : ");
	fflush(stdin);
	scanf("%[^\n]",MMBR[ind_mmbr].alamat);
	printf("Masukkan tanggal lahir [dd/mm/yy]: ");
	fflush(stdin);
	scanf("%s",&MMBR[ind_mmbr].tgllhr);
	printf("\n\nData berhasil ditambahkan\nPress ENTER to continue");
	fflush(stdin);
	ind_mmbr++;
}

//edit data barang/menu5
void editbrg1()
{
	char kode_edit[4];
	int index_edit;
	printf("================\n");
	printf("Edit Data Barang\n");
	printf("================\n");
	databrg1();
	printf("\nMasukkan kode barang yang ingin diedit: ");
	scanf("%s",kode_edit);
	index_edit = cari_kode(kode_edit);
	if(index_edit == -1)
	{
		printf("Barang tidak ditemukan!");
	}
	else
	{
		printf("Masukkan stok barang terbaru: ");
		scanf("%d",&BRG[index_edit].stok_brg);
		printf("\nDATA ALREADY CHANGED!");
	}
	fflush(stdin);
}

//edit data member/menu6
void editmmbr1()
{
	char data_edit[4];
	int index_edit;
	printf("================\n");
	printf("Edit Data Member\n");
	printf("================\n");
	datammbr1();
	printf("\nMasukkan nama member yang ingin diedit: ");
	scanf("%s",data_edit);
	index_edit = cari_nama(data_edit);
	if(index_edit == -1)
	{
		printf("Member tidak ditemukan!");
	}
	else
	{
		printf("Masukkan nama baru: ");
		scanf("%s",MMBR[index_edit].nama);
		printf("Masukkan alamat baru: ");
		scanf("%s",MMBR[index_edit].alamat);
		printf("Masukkan tanggal lahir: ");
		scanf("%s",MMBR[index_edit].tgllhr);
		printf("\nDATA ALREADY CHANGED!");
	}
	fflush(stdin);
}

//display resi/menu4
void dataresi1()
{	
	system("cls");
	printf("================================================\n");
	printf(" No. | Nama               | Nomor Resi         |\n");
	printf("================================================\n");
	for(int i=0;i<ind_resi;i++)
	{
		printf(" %2d  | %-18s | %-18s |\n",i+1, TRX[i].nama_pembeli, TRX[i].no_resi);
	}
	fflush(stdin);
}

//Edit data resi//menu7
void editresi1()
{
	char data_edit[4];
	int index_edit;
	printf("%s", TRX[ind_resi].nama_pembeli);
	printf("\nMasukkan nama resi yang ingin diedit: ");
	scanf("%s",data_edit);
	index_edit = cari_resi(data_edit);
	if(index_edit == -1)
	{
		printf("Nama tidak ditemukan!");
	}
	else
	{
		printf("Masukkan nama baru: ");
		scanf("%s",TRX[index_edit].nama_pembeli);
		printf("\nDATA ALREADY CHANGED!");
	}
	fflush(stdin);
}


//display data penjualan/menu8
void datapjln1()
{
	system("cls");
	printf("================================================\n");
	printf(" No. | Nama Barang        | Tanggal Beli       |\n");
	printf("================================================\n");
	for(int i=0;i<ind_pjln;i++)
	{
		printf(" %2d  | %-18s | %-18s |\n",i+1, TRX[i].brg_dibeli, TRX[i].tgl_beli);
	}
	fflush(stdin);
}

//save data/menu9/menu5
//cetak ke file brg
void savebrg1()
{
	brg=fopen("brg.txt","w");
	for(int i=0;i<ind_brg;i++)
	{
		fprintf(brg,"%s.%s.%d.%d\n",BRG[i].kode_brg,BRG[i].nama_brg,BRG[i].stok_brg,BRG[i].harga_brg);
	}
	fclose(brg);
}

//cetak ke file member
void savemmbr1()
{
	mmbr=fopen("mmbr.txt","w");
	for(int i=0;i<ind_mmbr;i++)
	{
		fprintf(mmbr,"%s.%s.%s\n",MMBR[i].nama,MMBR[i].alamat,MMBR[i].tgllhr);
	}
	fclose(mmbr);
}

//cetak ke file resi
void saveresi1()
{
	resi=fopen("resi.txt","w");
	for(int i=0;i<ind_resi;i++)
	{
		fprintf(resi,"%s.%s\n",TRX[i].nama_pembeli,TRX[i].no_resi);
	}
	fclose(resi);
}

//cetak ke file penjualan
void savepjln1()
{
	pjln=fopen("pjln.txt","a");
	for(int i=0;i<ind_cart;i++)
	{
		fprintf(pjln,"%s.%s\n",TRX[i].brg_dibeli,TRX[i].tgl_beli);
	}
	fclose(pjln);
}


//FUNCTION MENU BUYER
//beli barang/menu2 
void beli2()
{
	char lanjut;
	do
	{
		system("cls");
		char kode_beli[4];
		printf("===\n");
		printf("BUY\n");
		printf("===\n");
		databrg1();
		printf("\nMasukkan kode barang yang ingin dibeli: ");
		scanf("%s",kode_beli);
		index_beli = cari_kode(kode_beli);
		if(index_beli == -1)
		{
			printf("Barang tidak ditemukan!");
		}
		else
		{
			do
			{	
				printf("Masukkan jumlah barang yang ingin dibeli [1..%d]: ",BRG[index_beli].stok_brg);
				fflush(stdin);
				scanf("%d",&stok_beli);
			}while(stok_beli<1 || stok_beli>BRG[index_beli].stok_brg);
			BRG[index_beli].stok_brg=BRG[index_beli].stok_brg-stok_beli;
			cart[ind_cart] = BRG[index_beli];
			cart[ind_cart].stok_brg = stok_beli;
			cart[ind_cart].harga_brg = stok_beli * BRG[index_beli].harga_brg;
			ind_cart++;
		}
		do
		{
			printf("\nApakah anda ingin beli lagi?[Y/N] ");
			fflush(stdin);
			scanf("%c",&lanjut);
		}while(lanjut != 'Y' && lanjut != 'y' && lanjut != 'n' && lanjut != 'N');
	}while(lanjut == 'Y' || lanjut == 'y');
	fflush(stdin);
}

//bayar barang/menu3
void bayar2()
{
	int total_harga = 0,pembayaran,kembalian,jadi;
	printf("=======\n");
	printf("Payment\n");
	printf("=======\n\n");
	for(int i=0; i<ind_cart; i++)
	{
		printf(" %d | %3s | %-18s | %d | %-18d |\n", i+1, cart[i].kode_brg, cart[i].nama_brg, cart[i].stok_brg, cart[i].harga_brg);
	}
	for(int i=0; i<ind_cart; i++)
	{
		total_harga = total_harga + cart[i].harga_brg;
	}
	for(int i=0; i<30; i++)
	{
		printf(" ");
	}
	printf("Total | %-18d |", total_harga);
	printf("\nMasukkan nominal pembayaran: ");
	scanf("%d",&pembayaran);
	kembalian=pembayaran-total_harga;
	if(kembalian<0)
	{
		printf("\nMaaf uang anda kurang!\n");
		printf("Apakah anda jadi beli [Y/N]: ");
		fflush(stdin);
		scanf("%c",&jadi);
		if(jadi == 'Y'||jadi == 'y')
		{
			printf("\n");
			bayar2();	
		}
		else
		{
			printf("\nPastikan uangmu cukup ya lain kali..");
			BRG[index_beli].stok_brg=BRG[index_beli].stok_brg+stok_beli;
			ind_cart=0;
		}
	}
	else if(kembalian>0)
	{
		printf("\nUang yang anda berikan lebih\n");
		printf("Kembalian anda: %d", kembalian);
		ind_cart = 0;
	}
	else
	{
		printf("THANK YOU FOR SHOPPING!");
		ind_cart = 0;
	}
	
}

//MAIN MENU
//Menu OWNER
void menu1()
{
	int pilih1;
	do
	{
		system("cls");
		printf("========\n");
		printf("= MENU =\n");
		printf("========\n\n");
		printf("1. Data Barang\n");
		printf("2. Data Member\n");
		printf("3. Tambah Data Barang\n");
		printf("4. Tambah Data Member\n");
		printf("5. Edit Data Barang\n");
		printf("6. Edit Data Member\n");
		printf("7. Edit Resi\n");
		printf("8. Data Penjualan\n");
		printf("9. Save\n");
		printf("\nEnter Your Choice: ");
		scanf("%d", &pilih1);
		switch(pilih1)
		{
			case 1: 
			{
				system("cls");
				int choice;
				databrg1();
				printf("\n1. Urutkan berdasarkan harga barang\n2. Urutkan berdasarkan stok barang\n3. Kembali");
				printf("\nMasukkan pilihanmu: ");
				fflush(stdin);
				scanf("%d", &choice);
				if(choice == 1)
				{
					sorthrgbrg();
					system("cls");
					databrg1();
					getch();
				}
				else if(choice == 2)
				{
					sortstokbrg();
					system("cls");
					databrg1();
					getch();
				}
				
				break;
			}
			case 2:
			{
				system("cls");
				datammbr1();
				getch();
				break;
			}
			case 3:
			{
				system("cls");
				tmbbrg1();
				getch();
				break;
			}
			case 4: 
			{
				system("cls");
				tmbmmbr1();
				getch();
				break;
			}
			case 5:
			{
				system("cls");
				editbrg1();
				getch();	
				break;
			}
			case 6:
			{
				system("cls");
				editmmbr1();
				getch();
				break;
			}
			case 7:
			{	
				system("cls");
				printf("=========\n");
				printf("Edit Resi\n");
				printf("=========\n");
				dataresi1();
				editresi1();
				break;
			}
			case 8:
			{
				system("cls");
				datapjln1();
				getch();
				break;
			}
			case 9:
			{
				system("cls");
				savebrg1();
				savemmbr1();
				saveresi1();
				savepjln1();
				printf("DATA SAVED!\n");
				getch();
				break;
			}
			default:
			{
				break;
			}
		}
	}while(pilih1 != 9);
}
//MENU BUYER			
void menu2()
{	
	int pilih2;
	do
	{	
		system("cls");
		printf("==============================\n");
		printf("= WELCOME TO OUR RETAIL SHOP =\n");
		printf("==============================\n\n");
		printf("1. Katalog Barang\n");
		printf("2. Beli Barang\n");
		printf("3. Bayar\n");
		printf("4. Cek Resi\n");
		printf("5. Selesai\n");
		printf("\nEnter Your Choice: ");
		scanf("%d", &pilih2);
		switch(pilih2)
		{
			case 1:
			{
				system("cls");
				int choice;
				databrg1();
				printf("\n1. Urutkan berdasarkan harga barang\n2. Urutkan berdasarkan stok barang\n3. Kembali");
				printf("\nMasukkan pilihanmu: ");
				fflush(stdin);
				scanf("%d", &choice);
				if(choice == 1)
				{
					sorthrgbrg();
					system("cls");
					databrg1();
					getch();
				}
				else if(choice == 2)
				{
					sortstokbrg();
					system("cls");
					databrg1();
					getch();
				}
				break;	
			}
			case 2:
			{
				system("cls");
				beli2();
				break;
			}
			case 3:
			{
				system("cls");
				bayar2();
				getch ();
				break;
			}
			case 4:
			{
				system("cls");
				srand (time(0));
				printf("====\n");
				printf("Resi\n");
				printf("====\n");
				printf("masukkan username: ");
				fflush(stdin);
				scanf("%s",TRX[ind_resi].nama_pembeli);
				for(int i=0;i<9;i++)
				{
					TRX[ind_resi].no_resi[i]=rand()%9+48;	
				}
				printf("\n\nNomor resi telah ditambahkan!");
				ind_resi++;
				dataresi1();
				getch ();
				break;
			}
			case 5:
			{
				system("cls");
				savebrg1();
				saveresi1();
				printf("THANK YOU FOR SHOPPING!");
				getch();
				break;
			}
			default:
			{
				break;
			}	
		}
	}while(pilih2!=5);	
		
}


//LOGIN			
void login()
{
	int k,l=1;
	char user[50],pass[20];
	file();
	printf("======\n");
	printf("LOGIN!\n");
	printf("======\n");
	printf("Masukkan Username & Password anda\n\n");
	printf("Username : ");
	scanf("%s",user);
	printf("Password : ");
	scanf("%s",pass);
	if(strcmp(user,"owner")==0 || strcmp(pass,"owner")==0){
		menu1();
	}
	if(strcmp(user,"owner")!=0 || strcmp(pass,"owner")!=0){
			for(k=0;k<=index;k++){
				if(strcmp(user,LOGIN[k].us)==0 && strcmp(pass,LOGIN[k].ps)==0){
					l=k;
					menu2();
					}
				}
			}
	if(strcmp(user,"owner")!=0 || strcmp(pass,"owner")!=0){
		if(strcmp(user,LOGIN[l].us)!=0 || strcmp(pass,LOGIN[l].ps)!=0){
			system("cls");
			login();
		}
	}
}


int main()
{
	load_brg();
	load_mmbr();
	load_resi();
	load_pjln();
	login();
	return 0;
}
