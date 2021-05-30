#include<stdio.h>
#include<string.h>
#include<stdlib.h>

clear(){
	system("cls");
}

struct node{
	char plat[10];
	char mobil[30];
	char status[10];
	int price;
	struct node *left;
	struct node *right;
};
struct node* root = NULL;


void mainMenu(){
	clear();
	printf("SWJr Car Rental\n");
	printf("----------\n\n");
	
	printf("1. Tambah mobil\n");
	printf("2. Sewa mobil\n");
	printf("3. Update Data mobil\n");
	printf("4. Delete Data Mobil\n");
	printf("5. Inorder, Preorder, Postorder\n");

	printf("6. Exit\n");
}


struct node *newNode(char *plat,char *mobil,char *status, int price){
	struct node *temp = (struct node*)malloc(sizeof(struct node));
	strcpy(temp->plat,plat);
	strcpy(temp->mobil,mobil);
	strcpy(temp->status,status);
	temp->price = price;
	temp->left = NULL;
	temp->right = NULL;
};

int convert(char *plat){
	char src[10];
	int key;
	strcpy(src,plat);
	memmove(&src[0],&src[1],strlen(src));//tuker n dapet kode angka
	key = atoi(src);//convert to int
	return key;	
}


void tampil(struct node *root){
	if(root != NULL){
		printf("|%-9s | %-20s | Rp %-3d | %-6s |\n",root->plat,root->mobil,root->price,root->status);
		tampil(root->left);
		tampil(root->right);
	}
}

struct node* insert(struct node *temp, char *plat,char *mobil,char *status, int price){
	int key, node;
	if(temp == NULL){
		return newNode(plat,mobil,status,price);
	}
	key = convert(plat);
	node = convert(temp->plat);
	if(key < node){
		temp->left = insert(temp->left,plat,mobil,status,price);
	}
	else if(key > node){
		temp->right = insert(temp->right,plat,mobil,status,price);
	}
	return temp;
};

struct node *findParent(struct node *temp,char *plat){
	if(temp == NULL){
		return NULL;
	}
	if(temp->left == NULL && temp->right == NULL){
		return NULL;
	}
	if(temp->left != NULL && strcmp(temp->left->plat,plat) == 0 || temp->right != NULL && strcmp(temp->right->plat,plat) == 0){
		return temp;
	}
	int key = convert(plat);
	int keynode = convert(temp->plat);
	if(keynode > key){
		return findParent(temp->left,plat);
	}
	if(keynode < key){
		return findParent(temp->right,plat);
	}
}

struct node *inorder(struct node *temp){
	struct node *current = temp;
	while(current && current->left != NULL){
		current = current->left;
	}
	return current;
}

struct node *del(struct node *temp){
	if(temp->left == NULL && temp->right == NULL){
		struct node *parent = findParent(root,temp->plat);
		if(parent->left == temp){
			parent->left = NULL;
		}else if(parent->right == temp){
			parent->right = NULL;
		}
		temp = NULL;
		return temp;
	}else if(temp->left == NULL){ 
        struct node *temp = temp->right;
		strcpy(temp->plat,temp->plat);
		strcpy(temp->status,temp->status);
		strcpy(temp->mobil,temp->mobil);
		temp->price = temp->price;
		free(temp);
		temp = NULL;
		temp->right = temp;
		return temp;
	}else if (temp->right == NULL){ 
        struct node *temp = temp->left;
		strcpy(temp->plat,temp->plat);
		strcpy(temp->status,temp->status);
		strcpy(temp->mobil,temp->mobil);
		temp->price = temp->price;
		free(temp);
		temp = NULL;
		temp->left = temp;
		return temp; 
    }else{
	    struct node* temp = inorder(temp->right);
	    strcpy(temp->plat,temp->plat);
		strcpy(temp->status,temp->status);
		strcpy(temp->mobil,temp->mobil);
		temp->price = temp->price;
	  	temp->right = del(temp->right);
	}
	return temp; 
}

struct node* search(struct node *temp, char *plat){
	int key, node;
	if(temp != NULL){
		key = convert(plat);
		node = convert(temp->plat);
		if(node == key){
			return temp;
		}
		else if(node < key){
			return search(temp->right, plat);
		}
		else{
			return search(temp->left, plat);
		}
	}
};

void addMobil(){
	fflush(stdin);
	clear();
	char plat[10], mobil[30], status[2];
	int price;	
	do{
		printf("\n Input plat mobil [a-z][0-9][0-9][0-9][a-z] :  ");
		gets(plat);
	}while(strlen(plat) > 5);	
	do{
		printf("\n Input Merek Mobil : ");
		gets(mobil);
	}while(strlen(mobil) < 1 || strcmp(mobil," ") == 0);
	
	printf("\n Input harga Rp : Rp ");
	scanf("%d",&price);
	
	
	fflush(stdin);
	do{
		printf("\n Apakah mobil sudah disewa? (y/n) : ");
		gets(status);
	}while(strcmp(status,"y") != 0 && strcmp(status,"n") != 0);
	
	
	
	
	if(root == NULL){
		root = insert(root,plat,mobil,status,price);
		printf("\n--- Add mobil Success ---");
	} 
	else if(strcmp(plat,root->plat) == 0){
		printf("\n\n --- Plat mobil sudah ada!! ---");
	}
	else{
		insert(root,plat,mobil,status,price);	
		printf("\n--- Add mobil Success ---");
	}	
	
}

struct node *sewaMobil(struct node *temp){
	char plat[10], status[2];
	int found;
	clear();
	if(root == NULL){
		printf("\n ---There is no data---");
		return;
	}
	else{
		printf("\t--- DATA MOBIL ---\n");
		printf("+----------+----------------------+-----------+--------+\n");
		printf("|Plat Mobil|         Mobil        |   Harga   | Status |\n");
		printf("+----------+----------------------+-----------+--------+\n");
		tampil(root);
		printf("+----------+----------------------+-----------+--------+\n");
	
		do{
			printf("\n Input plat [a-z][1-9][0-9][0-9][a-z] : ");
			fflush(stdin);
			gets(plat);
		}while(strlen(plat) > 5);
		temp = search(temp,plat);
		if(temp == NULL){
			printf("\n\n ---Plat Mobil Tidak Ditemukan---");
			getch();
			return temp;
		}
		printf("\n\n Plat Mobil : %s",temp->plat);
		printf("\n Mobil      : %s",temp->mobil);
		printf("\n Harga      : %d",temp->price);
		do{
			printf("\n\n Apakah anda ingin menyewa mobil ini? (y/n):");
			fflush(stdin);
			gets(status);
		}while(strcmp(status,"y") != 0 && strcmp(status,"n") != 0);	
		
		if(strcmp(status,"y") == 0){
			strcpy(temp->status,status);
			printf("\n\n\n ---Sewa Mobil Success---");		
		}
		else{
			printf("\n\n\n ---Sewa Mobil Dibatalkan---");		
		}
	}
	return temp;
} 

struct node *updateMobil(struct node *temp){
	char plat[10], mobil[30],choice;
	int price;
	clear();
	if(root == NULL){
		printf("\n ---There is no data---");
		return;
	}
	else {
		printf("\t--- DATA MOBIL ---\n");
		printf("+----------+----------------------+-----------+--------+\n");
		printf("|Plat Mobil|         Mobil        |   Harga   | Status |\n");
		printf("+----------+----------------------+-----------+--------+\n");
		tampil(root);
		printf("+----------+----------------------+-----------+--------+\n");
	
		do{
			printf("\n Input plat [a-z][1-9][0-9][0-9][a-z] : ");
			fflush(stdin);
			gets(plat);
		}while(strlen(plat) > 5);
		temp = search(temp,plat);
		if(temp == NULL){
			printf("\n\n ---Plat Mobil Tidak Ditemukan---");
			getch();
			return temp;
		}
		printf("\n\n Plat Mobil : %s",temp->plat);
		printf("\n Mobil      : %s",temp->mobil);
		printf("\n Harga      : %d",temp->price);
		do{
			printf("\n\n Apakah anda ingin mengupdate data mobil ini? (y/n): ");
			fflush(stdin);
			scanf("%c",&choice);
		}while(choice == 'y' && choice == 'n');
		if(choice == 'y'){
			do{
				fflush(stdin);
				printf("Plat Mobil : ");
				gets(plat);
			}while(strlen(plat) > 5);
			do{
				fflush(stdin);
				printf("Jenis Mobil : ");
				gets(mobil);	
			}while(strlen(mobil) < 1 || strcmp(mobil," ") == 0);
			printf("\n Input harga Rp : Rp ");
			scanf("%d",&price);
			printf("\n\n\n ---Update Data Mobil Success---");
			strcpy(temp->plat,plat);
			strcpy(temp->mobil,mobil);
			temp->price = price;
		} else{
			printf("\n\n ---Update dibatalkan---");
		}	
	}

	return temp;
} 

void delMobil(struct node *temp){
	if(root == NULL){
		printf("\n\n ---There is No Data---");
		getch();
		return;
	}else{
		char plat[10];
		clear();
		if(root == NULL){
			printf("\n ---There is no data---");
			getch();
			return;
		}
		else{
			printf("\t--- DATA MOBIL ---\n");
			printf("+----------+----------------------+-----------+--------+\n");
			printf("|Plat Mobil|         Mobil        |   Harga   | Status |\n");
			printf("+----------+----------------------+-----------+--------+\n");
			tampil(root);
			printf("+----------+----------------------+-----------+--------+\n");
			do{
				printf("\n Input Plat Mobil [a-z][1-9][0-9][0-9][a-z] : ");
				fflush(stdin);
				gets(plat);
				
			}while(strlen(plat) > 5);
			temp = search(root,plat);
			if(temp == NULL){
				printf("\n\n ---Plat tidak ditemukan!---");
				getch();
				return;
			}
			if(temp == root && root->left == NULL && root->right == NULL){
				root = NULL;
			}else{
				temp = del(temp);
			}
			printf("\n\n ---Delete Data Mobil Success---");
		}
		
	}
}

void post(struct node *root){
	if(root != NULL){
		post(root->left);
		post(root->right);
		printf("\n - %s %s [Rp %2d ] [ %s ] ",root->plat,root->mobil,root->price,root->status);
	}
}

void pre(struct node *root){
	if(root != NULL){
		printf("\n - %s %s [Rp %2d ] [ %s ] ",root->plat,root->mobil,root->price,root->status);
		pre(root->left);
		pre(root->right);
	}
}

void in(struct node *root){
	if(root != NULL){
		in(root->left);
		printf("\n - %s %s [Rp %2d ] [ %s ] ",root->plat,root->mobil,root->price,root->status);
		in(root->right);
	}
}

void transversal(){
	if(root == NULL){
		printf(" --- There is No data in The Tree ---");
	}
	else{
		printf("Postorder   : ");
		post(root);
		printf("\nPreorder   : ");
		pre(root);
		printf("\nInorder    : ");
		in(root);
	}
}

int main(){
	int pilih;
	do{
		do{
			mainMenu();
			printf("\n>>> Input your choice [1-6] : ");
			scanf("%d",&pilih);
		} while(pilih > 6 || pilih < 1);
		
		switch(pilih){
			case 1 : addMobil();
					 getch();
					 break;
			case 2 : sewaMobil(root);
					 getch();
					 break;
			case 3 : updateMobil(root);
					 getch();
					 break;
			case 4 : delMobil(root);
					 getch();
					 break;
			case 5 : transversal();
					 getch();
					 break;
			
			
		}
	} while(pilih < 6);
}
