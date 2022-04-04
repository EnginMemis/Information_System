#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>


typedef struct ders{
	char kod[50];
	char isim[50];
	int *numaralar;
	int kredi;
	int kontenjan;
	int kayitli_sayisi;
	int acikMi;
	struct ders *next;
}DERS;

typedef struct ogrenci{
	char isim[50];
	char soyisim[50];
	int ders_sayisi;
	int kredi_sayisi;
	int numara;
	int max_kredi;
	int max_ders;
	struct ogrenci *next;
	struct ogrenci *prev;
}OGRENCI;

typedef struct kayit{
	int id;
	char ders_kod[50];
	char tarih[50];
	int ogr_no;
	char kayit_durumu[50];
	struct kayit *next;
}KAYIT;

void temizleDers(DERS *root){
	DERS *temp;
	while(root != NULL){
		temp = root;
		root = root->next;
		temp = NULL;
		free(temp);
	}
}

void temizleOgr(OGRENCI *root){
	OGRENCI *temp;
	while(root != NULL){
		temp = root;
		root = root->next;
		temp = NULL;
		free(temp);
	}
}

void temizleKayit(KAYIT *root){
	KAYIT *temp;
	while(root != NULL){
		temp = root;
		root = root->next;
		temp = NULL;
		free(temp);
	}
}

int yonetici_menu(){
	int choice;
	
	do{
		system("cls");
		printf("1-Ders Acma\n2-Ders Kapama\n3-Ogrenci Ekle\n4-Ogrenci Sil\n5-Derse Kayitli Ogrencileri Yazdir\n6-Ogrencinin Aldigi Dersleri Yazdir\n7-Ana Menuye Don\n");
		printf("Secim:");
		scanf("%d",&choice);
	}while(choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7);
	
	return choice;	
}


int ogr_menu(){
	int choice;
	
	do{
		system("cls");
		printf("1-Ders Kayit\n2-Ders Kayit Sil\n3-Ana Menuye Don\n");
		printf("Secim:");
		scanf("%d",&choice);
	}while(choice != 1 && choice != 2 && choice != 3);
	
	return choice;
}


int ana_menu(){
	int choice;
	
	do{
		system("cls");
		printf("1-Yonetici Girisi\n2-Ogrenci Girisi\n3-Cikis\n");
		printf("Secim:");
		scanf("%d",&choice);
	}while(choice != 1 && choice != 2 && choice != 3);
	
	return choice;	
}




int searchDers(DERS *root, char aranilan_ders[50]){
	
	DERS *iter = root;
	int control = 0;
	while(iter != NULL && control == 0){
		if( strcmp(iter->kod, aranilan_ders) == 0){
			control = 1;
		}
		iter = iter->next;
	}
	return control;
}

int searchOgrenci(OGRENCI *root, int numara){
	OGRENCI *iter = root;
	int control = 0;
	while(iter != NULL && control == 0){
		if( iter->numara == numara){
			control = 1;
		}
		iter = iter->next;
	}
	return control;
}

void dersInputAlma(DERS *node){
	printf("Dersin Ismini Giriniz:");
	scanf(" %[^\n]",node->isim);
	
	printf("Dersin Kredisini Giriniz:");
	scanf("%d",&node->kredi);
	
	printf("Dersin Kontenjanini Giriniz:");
	scanf("%d",&node->kontenjan);
}



DERS* createDersNode(char ders_kodu[50]){
	
	DERS *temp = (DERS *)malloc(sizeof(DERS));
	temp->next = NULL;
	strcpy(temp->kod, ders_kodu);
	temp->acikMi = 1;
	temp->kayitli_sayisi = 0;
	return temp;
}


OGRENCI* createOgrenciNode(int max_ders, int max_kredi){
	OGRENCI *temp = (OGRENCI *)malloc(sizeof(OGRENCI));
	temp->kredi_sayisi = 0;
	temp->ders_sayisi = 0;
	temp->max_ders = max_ders;
	temp->max_kredi = max_kredi;
	return temp;
}

KAYIT* createKayitNode(){
	KAYIT *temp = (KAYIT * )malloc(sizeof(KAYIT));
	temp->next = NULL;
	return temp;
}

DERS* dersDosyaOku(DERS *root){
	
	DERS *iter;
	DERS *temp;
	int size;
	char kod[50];
	FILE *file = fopen("./Txt Files/dersler.txt","r");
	
	if(file == NULL){
		printf("Dosya Acilamadi!\nDosyaniz dersler.txt isimli olmali!");
		exit(1);
	}
	
	if(file != NULL){
		fseek (file, 0, SEEK_END);
		size = ftell(file);
		if(size != 0){
			fseek(file,0,SEEK_SET);
			
			while(!feof(file)){
				fscanf(file," %[^,],",kod);
				temp = createDersNode(kod);
				fscanf(file,"%[^,],",temp->isim);
				fscanf(file,"%d,",&temp->kredi);
				fscanf(file,"%d\n",&temp->kontenjan);
				
				if(root == NULL){
					root = temp;
				}
				else{
					iter = root;
					while(iter->next != NULL){
						iter = iter->next;
					}
					iter->next = temp;
				}
			}
		}
	}
	
	
	fclose(file);
	return root;
}

OGRENCI* ogrDosyaOku(OGRENCI *root, int max_ders, int max_kredi){
	OGRENCI *iter;
	OGRENCI *temp;
	int size;
	FILE *file2 = fopen("./Txt Files/ogrenciler.txt","r");
	
	if(file2 == NULL){
		printf("Dosya Acilamadi!\nDosyaniz ogrenciler.txt isimli olmali!");
		exit(1);
	}
	
	if (NULL != file2) {
		fseek (file2, 0, SEEK_END);
		size = ftell(file2);
		if (size != 0) {
			fseek(file2,0,SEEK_SET);
			while(!feof(file2)){
				temp = createOgrenciNode(max_ders, max_kredi);
				fscanf(file2,"%d,",&temp->numara);
				fscanf(file2,"%[^,],",temp->isim);
				fscanf(file2,"%[^,],",temp->soyisim);
				fscanf(file2,"%d,",&temp->kredi_sayisi);
				fscanf(file2,"%d\n",&temp->ders_sayisi);
			
				if(root == NULL){
					root = temp;
					root->next = NULL;
					root->prev = NULL;
				}
				else{
					iter = root;
					while(iter->next != NULL){
						iter = iter->next;
					}
					iter->next = temp;
					temp->prev = iter;
					temp->next = NULL;
					
				}	
			}
		}
	}
	
	fclose(file2);
	return root;
}


KAYIT* kayitDosyaOku(KAYIT *root){
	
	KAYIT *iter;
	KAYIT *temp;
	int size;
	
	FILE *file = fopen("./Txt Files/OgrenciDersKayit.txt","r");
	
	if(file == NULL){
		printf("Dosya Acilamadi!\nDosyaniz OgrenciDersKayit.txt isimli olmali!");
		exit(1);
	}
	
	if (NULL != file) {
		fseek (file, 0, SEEK_END);
		size = ftell(file);
		if (size != 0) {
			fseek(file,0,SEEK_SET);		
			while(!feof(file)){
				temp = createKayitNode();
				fscanf(file,"%d,",&temp->id);
				fscanf(file,"%[^,],",temp->ders_kod);
				fscanf(file,"%d,",&temp->ogr_no);
				fscanf(file,"%[^,],",temp->tarih);
				fscanf(file,"%[^\n]\n",temp->kayit_durumu);
				
				if(root == NULL){
					root = temp;
				}
				else{
					iter = root;
					while(iter->next != NULL){
						iter = iter->next;
					}
					iter->next = temp;
					
				}
			}
		}
	}
	
	
	fclose(file);
	return root;
}


DERS* dersKapat(DERS *root, OGRENCI *ogr_root, KAYIT *kayit_root, char ders_kodu[50]){
	
	DERS *temp;
	DERS *iter;
	OGRENCI *iter_ogrenci;
	KAYIT *iter_kayit;
	int i;
	
	if( strcmp(root->kod, ders_kodu) == 0){
		temp = root;
		root = root->next;	
	}
	else{
		iter = root;
		while(iter->next != NULL && strcmp(iter->next->kod, ders_kodu) != 0){
			iter = iter->next;
		}
		temp = iter->next;
		iter->next = iter->next->next;
	}
	
	
	
	i = 0;
	while(i < temp->kayitli_sayisi){
		
		iter_ogrenci = ogr_root;
		while(temp->numaralar[i] != iter_ogrenci->numara){
			iter_ogrenci = iter_ogrenci->next;
		}
		iter_ogrenci->kredi_sayisi -= temp->kredi;
		iter_ogrenci->ders_sayisi -= 1;
		i++;
	}
	
	iter_kayit = kayit_root;
	
	while( iter_kayit != NULL){
		if( strcmp(iter_kayit->ders_kod, ders_kodu) == 0 ){
			strcpy(iter_kayit->kayit_durumu, "ders kapandi");
		}
		iter_kayit = iter_kayit->next;
	}

	temp = NULL;
	free(temp);
	return root;
}


void ogrNoSirala(DERS *node){
	int i,j,temp;
	for(i = 0 ; i < node->kayitli_sayisi - 1 ; i++){
		for(j = i+1 ; j < node->kayitli_sayisi ; j++){
			if(node->numaralar[i] > node->numaralar[j]){
				temp = node->numaralar[i];
				node->numaralar[i] = node->numaralar[j];
				node->numaralar[j] = temp;
			}
		}
	}
}



OGRENCI* ogrSil(OGRENCI *root, KAYIT *root_kayit, DERS *root_ders, int numara){
	OGRENCI *iter = root;
	OGRENCI *temp;
	KAYIT *iter_kayit = root_kayit;
	DERS *iter_ders = root_ders;
	int i;
	
	if(root->numara == numara){
		temp = root;
		root = root->next;
		free(temp);
	}
	else{
		while(iter->next != NULL && iter->next->numara != numara){
			iter = iter->next;
		}
		temp = iter->next;
		iter->next = iter->next->next;
		free(temp);
	}
	
	while(iter_ders != NULL){
		i = 0;
		while(i < iter_ders->kayitli_sayisi){
			if(iter_ders->numaralar[i] == numara){
				iter_ders->numaralar[i] = INT_MAX;
				ogrNoSirala(iter_ders);
				iter_ders->kayitli_sayisi -= 1;
				iter_ders->numaralar = (int*)realloc(iter_ders->numaralar, iter_ders->kayitli_sayisi);
			}
			i++;
		}
		iter_ders = iter_ders->next;
	}
	
	while(iter_kayit != NULL){
		if(iter_kayit->ogr_no == numara){
			strcpy( iter_kayit->kayit_durumu, "okuldan ayrildi" );
		}
		iter_kayit = iter_kayit->next;
	}
	return root;
}

DERS* addDersList(DERS *root, DERS *eklenilen){
	DERS *iter;
	
	if(root == NULL){
		root = eklenilen;
		root->next = NULL;
		return root;
	}
	if( strcmp(root->kod, eklenilen->kod) > 0 ){
		eklenilen->next = root;
		root = eklenilen;
		return root;
	}
	
	iter = root;
	while(iter->next != NULL && strcmp(iter->next->kod, eklenilen->kod) <= 0){
		iter = iter->next;
	}
	eklenilen->next = iter->next;
	iter->next = eklenilen;
	return root;
	
}

OGRENCI* addOgrenci(OGRENCI *root, OGRENCI *eklenilen){		
	OGRENCI *iter;
	if(root == NULL){
		root = eklenilen;
		root->next = NULL;
		root->prev = NULL;
		return root;
	}
	if(root->numara > eklenilen->numara){
		eklenilen->next = root;
		root->prev = eklenilen;
		eklenilen->prev = NULL;
		root = eklenilen;
		return root;
	}
	iter = root;
	while(iter->next != NULL && eklenilen->numara > iter->next->numara){
		iter = iter->next;
	}
	if(iter->next != NULL){
		eklenilen->next = iter->next;
		iter->next->prev = eklenilen;
		iter->next = eklenilen;
		eklenilen->prev = iter;
	}
	else{
		eklenilen->next = iter->next;
		eklenilen->prev = iter;
		iter->next = eklenilen;
	}
	return root;
	
}


KAYIT* kayitEkle(KAYIT *root, KAYIT *eklenilen){
	KAYIT *iter;
	if(root == NULL){
		root = eklenilen;
		root->next = NULL;
		return root;
	}
	
	iter = root;
	while(iter != NULL){
		if( strcmp(iter->ders_kod, eklenilen->ders_kod) == 0 && strcmp(iter->kayit_durumu, "sildi") == 0 && iter->ogr_no == eklenilen->ogr_no){
			strcpy(iter->kayit_durumu, "kayitli");
			return root;
		}
		iter = iter->next;
	}
	
	
	if( strcmp(root->ders_kod, eklenilen->ders_kod) > 0 ){
		eklenilen->next = root;
		root = eklenilen;
		return root;
	}
	iter = root;
	while(iter->next != NULL && strcmp(iter->next->ders_kod, eklenilen->ders_kod) <= 0){
		iter = iter->next;
	}
	eklenilen->next = iter->next;
	iter->next = eklenilen;
	
	return root;
	
	
}



void dersDosyasinaKaydet(DERS *root){
	
	DERS *iter = root;
	
	FILE *file = fopen("./Txt Files/dersler.txt","w");
	while(iter != NULL){
		fprintf(file,"%s,%s,%d,%d\n",iter->kod, iter->isim, iter->kredi, iter->kontenjan);	
		iter = iter->next;
	}
	
	fclose(file);
}

void ogrDosyasinaKaydet(OGRENCI *root){
	FILE *file2 = fopen("./Txt Files/ogrenciler.txt","w");
	while(root != NULL){
		fprintf(file2,"%d,%s,%s,%d,%d\n",root->numara, root->isim, root->soyisim, root->kredi_sayisi, root->ders_sayisi);
		root = root->next;
	}
	
	fclose(file2);
}

void kayitDosyasinaKaydet(KAYIT *root){
	KAYIT *iter = root;
	int id = 10000;
	
	FILE *file = fopen("./Txt Files/OgrenciDersKayit.txt","w");
	while(iter != NULL){
		iter->id = id;
		fprintf(file,"%d,%s,%d,%s,%s\n",iter->id, iter->ders_kod, iter->ogr_no, iter->tarih, iter->kayit_durumu);		
		iter = iter->next;
		id++;
	}
	
	fclose(file);
}

void derslerYazdir(DERS *root){
	int count = 1;
	printf("		Acik Olan Dersler\n\n");
	if(root == NULL){
		printf("		Acik Olan Ders Bulunmamaktadir!\n\n");
	}
	while(root != NULL){
		printf("%2d - %8s   %-50s %4d %4d %4d\n",count, root->kod, root->isim, root->kredi, root->kontenjan, root->kayitli_sayisi);
		count++;
		root = root->next;		
	}
}

int* numaraYerAc(int *node, int kayitli_sayisi){
	
	if(kayitli_sayisi == 0){
		node = (int *)malloc(sizeof(int));
		return node;
	}
	
	node = (int *)realloc(node, kayitli_sayisi+1);
	if(node == NULL){
		printf("Numaralarin Oldugu Dizide Alan Acilamadi!");
		exit(1);
	}
	return node;
}



int derseKaydet(DERS *root, OGRENCI *ogr, char kayit_olunan_ders[50], int kayit_olan_numara){
	DERS *iter = root;
	int control = 0;
	static int i= 0;
	while( strcmp(iter->kod, kayit_olunan_ders) != 0 ){
		iter = iter->next;
	}
	
	if(iter->kontenjan <= iter->kayitli_sayisi){
		control = 1;
	}
	else{
		if( ogrenciKayitliMi(iter, kayit_olan_numara) == 0 ) {
			if( ogrenciKrediDoluMu(ogr, iter, kayit_olan_numara) == 1){
				iter->numaralar = numaraYerAc(iter->numaralar, iter->kayitli_sayisi);
				iter->kayitli_sayisi += 1;
				iter->numaralar[iter->kayitli_sayisi-1] = kayit_olan_numara;
				ogrNoSirala(iter);
			}
			else{
				control = 3;
			}
			
		}
		else{
			control = 2;
		}
		
	}
	return control;
}



int ogrenciKayitliMi(DERS *node, int kayit_olan_numara){
	
	int i;
	int control = 0;
	i = 0;																					
	while( i < node->kayitli_sayisi  && control == 0 ){
		if(node->numaralar[i] == kayit_olan_numara){
			control = 1;
		}
		else{
			i++;
		}
	}
	return control;
}

int ogrenciKrediDoluMu(OGRENCI *root, DERS *node, int kayit_olan_numara){
	OGRENCI *iter = root;
	int control = 1;
	while(iter != NULL && iter->numara != kayit_olan_numara){
		iter = iter->next;
	}
	
	if( (iter->kredi_sayisi + node->kredi) > iter->max_kredi){
		control = 0;
	}
	else if(iter->ders_sayisi + 1 > iter->max_ders){
		control = 0;
	}
	else{
		iter->kredi_sayisi += node->kredi;
		iter->ders_sayisi += 1;
	}
	
	return control;
}



void dersDosyasiniKayittanGuncelle(DERS *dersler, OGRENCI *ogrenciler, KAYIT *kayitlar){            
	KAYIT *iter = kayitlar;
	int control;
	while(iter != NULL){
		if( strcmp(iter->kayit_durumu, "kayitli") == 0 ){	
			control = derseKaydet(dersler,ogrenciler,iter->ders_kod,iter->ogr_no);
		}
		iter = iter->next;
	}
}	

void ogrListeGuncelle(OGRENCI *root){
	OGRENCI *iter = root;
	while(iter != NULL){
		iter->ders_sayisi = 0;
		iter->kredi_sayisi = 0;
		iter = iter->next;
	}
}

int ogrencininKayitliOlduguDersler(DERS *root, int ogrenci_no){
	DERS *iter = root;
	int i;
	int count = 1;
	int control = 0;
	printf("		Kayit Olunan Dersler\n\n");
	while(iter != NULL){
		i = 0;
		while(i < iter->kayitli_sayisi && ogrenci_no != iter->numaralar[i]){
			i++;
		}
		if(iter->kayitli_sayisi != 0){
			if(ogrenci_no == iter->numaralar[i]){
				printf("%2d - %8s   %-50s %4d %4d %4d\n",count, iter->kod, iter->isim, iter->kredi, iter->kontenjan, iter->kayitli_sayisi);
				count++;
				control = 1;
			}
		}
		
		iter = iter->next;
	}
	return control;
}

DERS* silinecekDersBulma(DERS *root, char silinen_ders[50]){
	DERS *iter = root;
	while(iter != NULL && strcmp(iter->kod, silinen_ders) != 0){
		iter = iter->next;
	}
	return iter;
}


void ogrKayitSil(OGRENCI *root_ogr, DERS *root_ders, KAYIT *root_kayit, char silinen_ders_kodu[50], int ogrenci_no){
	DERS *iter_ders = root_ders;
	OGRENCI *iter_ogr = root_ogr;
	KAYIT *iter_kayit = root_kayit;
	int i;
	while( strcmp(iter_ders->kod, silinen_ders_kodu) != 0 ){
		iter_ders = iter_ders->next;
	}
	
	i = 0;
	while(i < iter_ders->kayitli_sayisi && iter_ders->numaralar[i] != ogrenci_no){
		i++;
	}
	iter_ders->numaralar[i] = INT_MAX;
	ogrNoSirala(iter_ders);
	iter_ders->kayitli_sayisi -= 1;
	if(iter_ders->kayitli_sayisi == 0){
		iter_ders->numaralar = NULL;
	}
	else{
		iter_ders->numaralar = (int*)realloc(iter_ders->numaralar, iter_ders->kayitli_sayisi);
	}
	
	
	
	while(iter_ogr->numara != ogrenci_no){
		iter_ogr = iter_ogr->next;
	}
	iter_ogr->ders_sayisi -= 1;
	iter_ogr->kredi_sayisi -= iter_ders->kredi;
	
	
	
	while( strcmp(iter_kayit->ders_kod, iter_ders->kod) != 0  || iter_kayit->ogr_no != ogrenci_no || strcmp(iter_kayit->kayit_durumu, "kayitli") != 0){
		iter_kayit = iter_kayit->next;
	}
	strcpy( iter_kayit->kayit_durumu, "sildi" );
}


void derseKayitliOgrencilerYazdir(DERS *root_ders, OGRENCI *root_ogr, char yazdirilan_ders[50]){
	DERS *iter_ders = root_ders;
	OGRENCI *iter_ogr = root_ogr;
	int i;
	int count;
	char dosyaIsmi[40] = "./Txt Files/";
	FILE *file;
	
	
	while(iter_ders != NULL && strcmp(iter_ders->kod, yazdirilan_ders) != 0){
		iter_ders = iter_ders->next;
	}
	strcat(dosyaIsmi,iter_ders->kod);
	strcat(dosyaIsmi,".txt");

	printf("\n\n***%s - %s***\n\n",iter_ders->kod, iter_ders->isim);

	file = fopen(dosyaIsmi,"w");
	
	count = 1;
	for(i = 0 ; i < iter_ders->kayitli_sayisi ; i++){
		iter_ogr = root_ogr;
		while(iter_ogr != NULL && iter_ogr->numara != iter_ders->numaralar[i]){
			iter_ogr = iter_ogr->next;
		}
		printf("%d- %d %s %s\n",count,iter_ogr->numara,iter_ogr->isim, iter_ogr->soyisim);
		fprintf(file,"%d- %d %s %s\n",count,iter_ogr->numara,iter_ogr->isim, iter_ogr->soyisim);
		count++;
	}
	if(iter_ders->kayitli_sayisi <= 0){
		printf("Derse Kayitli Ogrenci Bulunmamaktadir!\n");
	}
	
	fclose(file);
}

void tumDerslerdekiOgrencileriYazdir(DERS *root_ders, OGRENCI *root_ogrenci){
	DERS *iter_ders = root_ders;
	
	while(iter_ders != NULL){
		derseKayitliOgrencilerYazdir(root_ders, root_ogrenci, iter_ders->kod);
		iter_ders = iter_ders->next;
	}
}

void dosyalariSil(KAYIT *root){
	KAYIT *iter = root;
	char silinecek_dosya[40] = "./Txt Files/";
	while(iter != NULL){
		strcpy(silinecek_dosya, "");
		strcat(silinecek_dosya, iter->ders_kod);
		strcat(silinecek_dosya,".txt");
		remove(silinecek_dosya);
		iter = iter->next;
	}
}

void dersProgramiDosyalariSil(KAYIT *root){
	KAYIT *iter = root;
	char silinecek_dosya[40] = "./Txt Files/";
	char numara[20] = "";
	while(iter != NULL){
		strcpy(silinecek_dosya, "");
		itoa(iter->ogr_no, numara, 10);
		strcat(silinecek_dosya, numara);
		strcat(silinecek_dosya,"_DERSPROGRAMI.txt");
		remove(silinecek_dosya);
		iter = iter->next;
	}
}


void ogrencininKayitliOlduguDersleriYazdir(DERS *ders_root, OGRENCI *root_ogr, int yazdirilacak_no){
	DERS *iter_ders = ders_root;
	int i;
	int count,temp;
	char dosyaIsmi[50] = "./Txt Files/";
	char numara[20] = "";
	int rakam;
	
	itoa(yazdirilacak_no, numara, 10);
	
	strcat(dosyaIsmi, numara);
	strcat(dosyaIsmi, "_DERSPROGRAMI.txt");
	FILE *file = fopen(dosyaIsmi, "w");
	
	count = 1;
	while(iter_ders != NULL){
		for(i=0 ; i < iter_ders->kayitli_sayisi ; i++){
			if(iter_ders->numaralar[i] == yazdirilacak_no){
				printf("%d - %s %s\n",count,iter_ders->kod, iter_ders->isim);
				fprintf(file,"%d - %s %s\n",count,iter_ders->kod, iter_ders->isim);
				count++;
			}
		}
		iter_ders = iter_ders->next;
	}
	
	fclose(file);
}



int main(){

	int ana_choice, yonetici_choice, ogr_choice;
	char acilan_ders_kodu[50];
	char kapatilan_ders_kodu[50];
	char kayit_olunan_ders[50];
	char silinen_ders[50];
	char yazdirilacak_ders[50];
	int yazdirilacak_ogr;
	int eklenen_ogrenci_no;
	int silinen_ogr_no;
	int giris_no;
	int control;
	int max_ders,max_kredi;
	int sinir;
	char tarih[12];
	
	DERS *root_ders = NULL;
	OGRENCI *root_ogrenci = NULL;
	KAYIT *root_kayit = NULL;

	DERS *silinen_ders_node;
	DERS *ders_node;
	OGRENCI *ogr_node;
	KAYIT *kayit_node;
	
	OGRENCI *iter_ogrenci;
	
	root_ders = dersDosyaOku(root_ders);
	root_ogrenci = ogrDosyaOku(root_ogrenci,max_ders, max_kredi);
	root_kayit = kayitDosyaOku(root_kayit);
	ogrListeGuncelle(root_ogrenci);
	dersDosyasiniKayittanGuncelle(root_ders, root_ogrenci, root_kayit);
	ogrDosyasinaKaydet(root_ogrenci);
	
	
	dosyalariSil(root_kayit);
	dersProgramiDosyalariSil(root_kayit);
	
	
	/*printf("\n%d\n",root_ders->kayitli_sayisi);
	printf("%d",root_ders->numaralar[0]);*/
	
	printf("Tarihi Giriniz:");
	scanf("%s",tarih);
	
	do{
		iter_ogrenci = root_ogrenci;
		sinir = 0;
		printf("Ogrencilerin Alabilecegi Maksimum Ders Sayisini Giriniz:");
		scanf("%d",&max_ders);
		printf("\nOgrencilerin Alabilecegi Maksimum Kredi Sayisini Giriniz:");
		scanf("%d",&max_kredi);
		system("cls");
		
		while(iter_ogrenci != NULL && sinir == 0){
			if(max_ders < iter_ogrenci->ders_sayisi || max_kredi < iter_ogrenci->kredi_sayisi){
				sinir = 1;
			}
			iter_ogrenci = iter_ogrenci->next;
		}
		
	}while(sinir == 1);
	
	
	iter_ogrenci = root_ogrenci;
	while(iter_ogrenci != NULL){
		iter_ogrenci->max_ders = max_ders;
		iter_ogrenci->max_ders = max_ders;
		iter_ogrenci = iter_ogrenci->next;
	}
	
	
	
	do{
		ana_choice = ana_menu();
		
		switch(ana_choice){
			
			case 1:
				
				do{
					yonetici_choice = yonetici_menu();
					
					switch(yonetici_choice){
						case 1:
							
							printf("Acilacak Dersin Kodunu Giriniz:");
							scanf("%s",acilan_ders_kodu);
							
							if(searchDers(root_ders, acilan_ders_kodu) == 0){
								ders_node = createDersNode(acilan_ders_kodu);
								dersInputAlma(ders_node);
								root_ders = addDersList(root_ders, ders_node);
								dersDosyasinaKaydet(root_ders);
								printf("Ders Basarili Bir Sekilde Acilmistir!\n");
								printf("\n\nDevam Etmek Icin Enter'a Basiniz!");
								getch();
							}
							
							else{
								printf("Acmak Istediginiz Ders Daha Onceden Acilmistir!\n");
								getch();
							}
							
							break;
						case 2:
							printf("Kapatilacak Dersin Kodunu Giriniz:");
							scanf("%s",kapatilan_ders_kodu);
							
							if( searchDers(root_ders, kapatilan_ders_kodu) == 1 ){
								root_ders = dersKapat(root_ders, root_ogrenci, root_kayit, kapatilan_ders_kodu);
								ogrDosyasinaKaydet(root_ogrenci);
								dersDosyasinaKaydet(root_ders);
								kayitDosyasinaKaydet(root_kayit);
								printf("Ders Basarili Bir Sekilde Kapatilmistir!\n");
								printf("\n\nDevam Etmek Icin Enter'a Basiniz!");
								getch();
							}
							else{
								printf("Kapatmak Istediginiz Ders Bulunmamaktadir!\n");
								printf("\n\nDevam Etmek Icin Enter'a Basiniz!");
								getch();
							}
								dersDosyasinaKaydet(root_ders);
							
							
							break;
						case 3:
							printf("Eklemek istediginiz ogrencinin numarasini giriniz:");
							scanf("%d",&eklenen_ogrenci_no);
							
							if(searchOgrenci(root_ogrenci,eklenen_ogrenci_no) == 1){
								printf("Eklemek Istediginiz Ogrenci Daha Onceden Eklenmistir!");
								printf("\n\nDevam Etmek Icin Enter'a Basiniz!");
								getch();	
							}
							else{
								ogr_node = createOgrenciNode(max_ders, max_kredi);
								ogr_node->numara = eklenen_ogrenci_no;
								printf("Ogrencinin Adini Giriniz:");
								scanf(" %[^\n]s",ogr_node->isim);
								
								printf("Ogrencinin Soyismini Giriniz:");
								scanf(" %[^\n]s",ogr_node->soyisim);
								
								root_ogrenci = addOgrenci(root_ogrenci,ogr_node);
								ogrDosyasinaKaydet(root_ogrenci);
								printf("Ogrenci Basarili Sekilde Eklenmistir!");
								printf("\n\nDevam Etmek Icin Enter'a Basiniz!");
								getch();
							}
							break;
						
						case 4:
							printf("Silmek Istediginiz Ogrenci Numarasini Giriniz:");
							scanf("%d",&silinen_ogr_no);
							
							if(searchOgrenci(root_ogrenci, silinen_ogr_no) == 1){
								root_ogrenci = ogrSil(root_ogrenci, root_kayit, root_ders, silinen_ogr_no);
								ogrDosyasinaKaydet(root_ogrenci);
								kayitDosyasinaKaydet(root_kayit);
								printf("Ogrenci Basarili Sekilde Silinmistir!");
								printf("\n\nDevam Etmek Icin Enter'a Basiniz!");							
								getch();
							}
							else{
								printf("Silmek Istediginiz Ogrenci Bulunmamaktadir!");
								printf("\n\nDevam Etmek Icin Enter'a Basiniz!");
								getch();
							}
							break;
						case 5:
							system("cls");
							tumDerslerdekiOgrencileriYazdir(root_ders,root_ogrenci);
							printf("\n\nDevam Etmek Icin Enter'a Basiniz!");
							getch();
							
							break;
							
						case 6:
							system("cls");
							printf("Ders Programini Istediginiz Ogrencinin Numarasini Giriniz:");
							scanf("%d",&yazdirilacak_ogr);
							if(searchOgrenci(root_ogrenci, yazdirilacak_ogr) == 1){
								printf("Ogrencinin Ders Programi\n\n");
								ogrencininKayitliOlduguDersleriYazdir(root_ders, root_ogrenci, yazdirilacak_ogr);
								printf("\n\nDevam Etmek Icin Enter'a Basiniz!");
								getch();
							}
							else{
								printf("Girdiginiz Ogrenci Bulunmamaktadir!");
								printf("\n\nDevam Etmek Icin Enter'a Basiniz!");
								getch();
							}
							break;
			
					}
					
				}while(yonetici_choice != 7);
				
				break;
			
			case 2:
				
				printf("Giris Yapacak Ogrenci Numarasini Giriniz:");
				scanf("%d",&giris_no);
				
				if( searchOgrenci(root_ogrenci, giris_no) == 1 ){
					do{
						ogr_choice = ogr_menu();
						
						switch(ogr_choice){
							case 1:
								
								derslerYazdir(root_ders);
								
								printf("\n	Kayit Olmak Istediginiz Dersin Kodunu Giriniz:");
								scanf("%s",kayit_olunan_ders);
								
								if( searchDers(root_ders, kayit_olunan_ders) == 1 ){
									
									control = derseKaydet(root_ders, root_ogrenci, kayit_olunan_ders, giris_no);
									
									if( control == 0){
										kayit_node = createKayitNode();
										kayit_node->ogr_no = giris_no;
										strcpy(kayit_node->ders_kod, kayit_olunan_ders);
										kayit_node->id = 1000;
										strcpy(kayit_node->kayit_durumu, "kayitli");
										strcpy(kayit_node->tarih, tarih);
										
										root_kayit = kayitEkle(root_kayit, kayit_node);
										kayitDosyasinaKaydet(root_kayit);
										ogrDosyasinaKaydet(root_ogrenci);
										printf("Basarili Sekilde Kayit Oldunuz!");
										printf("\n\nDevam Etmek Icin Enter'a Basiniz!");
										getch();
									}
									else if(control == 1){
										printf("Kayit Olmak Istediginiz Dersin Kontenjani Doludur!");
										printf("\n\nDevam Etmek Icin Enter'a Basiniz!");
										getch();
									}
									
									else if(control == 2){
										printf("Derse Zaten Kayitlisiniz!");
										printf("\n\nDevam Etmek Icin Enter'a Basiniz!");
										getch();
									}
									else{
										printf("Max Kredi Veya Ders Sayisini Gectiginiz Icin Bu Dersi Alamazsiniz!");
										printf("\n\nDevam Etmek Icin Enter'a Basiniz!");
										getch();
									}
									
								}
								else{
									printf("Kayit Olmak Istediginiz Ders Bulunmamaktadir!");
									printf("\n\nDevam Etmek Icin Enter'a Basiniz!");
									getch();
								}
								
								break;	
							case 2:
								
								
								if(ogrencininKayitliOlduguDersler(root_ders,giris_no) == 1){
									printf("\n	Kaydinizi Silmek Istediginiz Dersin Kodunu Giriniz:");
									scanf("%s",silinen_ders);
									
									if( searchDers(root_ders, silinen_ders) == 1 ){                                             
										silinen_ders_node = silinecekDersBulma(root_ders, silinen_ders);
			
										if(ogrenciKayitliMi(silinen_ders_node, giris_no) == 1){
											ogrKayitSil(root_ogrenci, root_ders, root_kayit, silinen_ders, giris_no);
											kayitDosyasinaKaydet(root_kayit);
											ogrDosyasinaKaydet(root_ogrenci);
											printf("Ders Kaydi Basarili Sekilde Silinmistir!");
											printf("\n\nDevam Etmek Icin Enter'a Basiniz!");
											getch();
										}
										else{
											printf("Kaydinizi Silmek Istediginiz Derse Kaydiniz Bulunmamaktadir!");
											printf("\n\nDevam Etmek Icin Enter'a Basiniz!");
											getch();
										}
									}
									else{
										printf("Kaydinizi Silmek Istediginiz Ders Bulunmamaktadir!");
										printf("\n\nDevam Etmek Icin Enter'a Basiniz!");
										getch();
									}
								}
								else{
									printf("Ogrencinin Kayitli Oldugu Ders Bulunmamaktadir!\n\n");
									printf("Devam etmek icin ENTER'a Basiniz");
									getch();
								}
								
							
								
								break;
						}
					
					}while(ogr_choice != 3);
				}
				else{
					printf("Girilen Numaraya Ait Ogrenci Bulunmamaktadir!");
					printf("\n\nDevam Etmek Icin Enter'a Basiniz!");
					getch();
				}
				
				
				break;
		}
	}while(ana_choice != 3);
	
	
	temizleDers(root_ders);
	temizleOgr(root_ogrenci);
	temizleKayit(root_kayit);
	
	return 0;
}


