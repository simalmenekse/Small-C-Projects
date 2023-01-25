#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define N 10
#define K 10

int main(void)
{
    
    
    printf("\t\t---------------------------Oyuna Hosgeldiniz---------------------------\n");
    printf("\t\t      ----------------------Oyunun Kurallari----------------------\n");
    printf("\t1)Hareket etmek icin wasd tuslarini kullanin.\n\t2)5 gizli elmas vardir. Bunlarin hepsini toplarsaniz oyunu kazanirsiniz.\n");
    printf("\t3)Elmaslari koruyan muhafizlar vardir. Muhafizlara yakalanirsaniz basa donersiniz ve caniniz azalir.\n\t4)Toplam 3 caniniz vardir.\n");
    printf("\n\tIyi Sanslar!\n\n");
	 
	srand(time(NULL)); //rastgele sayı yaratmak için gerekli olan fonksiyon
	
	int i=0, j=0, flag=0, lives=4; //loop değişkenleri, bulunan elmas sayısı için flag ve can değeri
	int a=2, b=4; //oyuncunun başlangıç koordinatları
	int dis1, dis2, dis3, dis4, dis5; //elmaslara olan uzaklık değişkenleri
	char map[N][K], direction;//karakter matrixi(harita) ve gidilen yön
    char player = 'O';//oyuncunun bulunduğu konumu gösteren gösterge
	
	//elmasların ve muhafızların konumunu belirlemek için kullanılan arrayler  
    int rowcor[10] = {0,1,2,3,4,5,6,7,8,9}; //istenilen sayılar girilmiştir
    int colcor[10] = {0,1,2,3,4,5,6,7,8,9}; //istenilen sayılar girilmiştir
    int guardcor_row[5];
    int guardcor_col[5];

    //aşağıdaki 2 loop, rowcor ve colcor arraylerini shuffle'lamaktadır.
	//yani oyunu her başlattığınızda array rastgele sayılar ile dolmaktadır.
	for(i=0; i<10; i++){
		int temp = rowcor[i];
		int randomIndex = rand() % 9;
		rowcor[i] = rowcor[randomIndex];
		rowcor[randomIndex] = temp;
	}
    
   for(j=0; j<10; j++){
		int temp2 = colcor[j];
		int randomIndex2 = rand() % 9;
		colcor[j] = colcor[randomIndex2];
		colcor[randomIndex2] = temp2;
	}
	
	//aşağıdaki loop ise rowcow ve colcor arraylerinin herhangi bir değerinin 
	//oyuncunun başlangıç noktasına eşit olmasını engellemektedir.
	for(i=0; i<5; i++){
		if(rowcor[i] == 2 && colcor[i] == 4){
			rowcor[i] = rowcor[6];
			colcor[i] = colcor[6];
		}
	}
	
	
	//aşağıdaki uzun for loopu; muhafızların haritadaki konumlarını elmasların koordinatlarına göre rastgele belirlemektedir.
	//muhafızların konumu, elmasların komşularıdır. 
	for(i=0;i<5;i++){
		int rn;
		rn = rand() % 8; //random bir değişken atanır, bu farklı durumlar için kullanılır.
		
		//printf("%d\n", rn); buradan hangi durumun geldiğini takip edebilirsiniz
		
		if(rn == 0){//satır 1 azalır, sütun aynı kalır, kuzey komşu
			if(rowcor[i] != 0){ //bu ifade 0-9 sayı sınırınn dışına çıkılmaması içindir
				guardcor_row[i] = rowcor[i] -1;
				guardcor_col[i] = colcor[i];
			}
				
			else if(rowcor[i] != 9){ //bu ifade 0-9 sayı sınırınn dışına çıkılmaması içindir
				guardcor_row[i] = rowcor[i] +1;
				guardcor_col[i] = colcor[i];	
			}	
		}
		
		else if(rn == 1){//satır 1 artar, sütun aynı kalır, güney komşu 
			if(rowcor[i] != 9){//bu ifade 0-9 sayı sınırınn dışına çıkılmaması içindir
				guardcor_row[i] = rowcor[i] +1;
				guardcor_col[i] = colcor[i];
			}
				
			else if(rowcor[i] != 0){//bu ifade 0-9 sayı sınırınn dışına çıkılmaması içindir
				guardcor_row[i] = rowcor[i] -1;
				guardcor_col[i] = colcor[i];	
			}		
		}
		
		else if(rn == 2){//sütun 1 artar, satır aynı kalır, doğu komşu
			if(colcor[i] != 9){//bu ifade 0-9 sayı sınırınn dışına çıkılmaması içindir
				guardcor_col[i] = colcor[i] +1;
				guardcor_row[i] = rowcor[i];
			}
				
			else if(colcor[i] != 0){//bu ifade 0-9 sayı sınırınn dışına çıkılmaması içindir
				guardcor_col[i] = colcor[i] -1;
				guardcor_row[i] = rowcor[i];	
			}
		}
		
		else if(rn == 3){//sütun 1 azalır, satır aynı kalır, batı komşu
			if(colcor[i] != 0){//bu ifade 0-9 sayı sınırınn dışına çıkılmaması içindir
				guardcor_col[i] = colcor[i] -1;
				guardcor_row[i] = rowcor[i];
			}
				
			else if(colcor[i] != 9){//bu ifade 0-9 sayı sınırınn dışına çıkılmaması içindir
				guardcor_col[i] = colcor[i] +1;
				guardcor_row[i] = rowcor[i];	
			}
		}
		
		else if(rn==4){//sütun 1 azalır, satır 1 azalır, sol üst çapraz komşu
			if(colcor[i] != 0){//bu ifade 0-9 sayı sınırınn dışına çıkılmaması içindir
				guardcor_col[i] = colcor[i] -1;
				if(rowcor[i] != 0)
					guardcor_row[i]= rowcor[i] -1;
				else
					guardcor_row[i] = rowcor[i] +1;
			}
				
			else if(colcor[i] != 9){//sütun 1 artar, satır 1 artar, sağ aşağı çapraz komşu
				guardcor_col[i] = colcor[i] +1;
				if(rowcor[i] != 9)
					guardcor_row[i]= rowcor[i] +1;
				else
					guardcor_row[i]= rowcor[i] -1;	
			}
		}
		
		else if(rn==5){//satır 1 azalır, sütun 1 azalır, sol üst çapraz komşu 
			if(rowcor[i] != 0){//bu ifade 0-9 sayı sınırınn dışına çıkılmaması içindir
				guardcor_row[i] = rowcor[i] -1;
				if(colcor[i] != 0)
					guardcor_col[i]= colcor[i] -1;
				else
					guardcor_col[i] = colcor[i] +1;
			}
				
			else if(rowcor[i] != 9){//satır 1 artar, sütun 1 artar, sağ aşağı çapraz komşu
				guardcor_row[i] = rowcor[i] +1;
				if(colcor[i] != 9)
					guardcor_col[i]= colcor[i] +1;
				else
					guardcor_col[i]= colcor[i] -1;	
			}
		}
		
		else if(rn==6){//satır 1 azalır, sütun 1 artar, sağ üst çapraz komşu
			if(rowcor[i] != 0){//bu ifade 0-9 sayı sınırınn dışına çıkılmaması içindir
				guardcor_row[i] = rowcor[i] -1;
				if(colcor[i] != 9)
					guardcor_col[i]= colcor[i] +1;
				else
					guardcor_col[i] = colcor[i] -1;
			}
				
			else if(rowcor[i] != 9){//satır 1 artar, sütun 1 azalır, sol ağağı çapraz komşu
				guardcor_row[i] = rowcor[i] +1;
				if(colcor[i] != 0)
					guardcor_col[i]= colcor[i] -1;
				else
					guardcor_col[i]= colcor[i] +1;	
			}
		}
		
		else if(rn==7){//sütun 1 azalır, satır 1 artar, sol aşağı çapraz komşu
			if(colcor[i] != 0){//bu ifade 0-9 sayı sınırınn dışına çıkılmaması içindir
				guardcor_col[i] = colcor[i] -1;
				if(rowcor[i] != 9)
					guardcor_row[i]= rowcor[i] +1;
				else
					guardcor_row[i] = rowcor[i] -1;
			}
				
			else if(colcor[i] != 9){//sütun 1 artar, satır 1 azalır,sağ üst çapraz komşu
				guardcor_col[i] = colcor[i] +1;
				if(rowcor[i] != 0)
					guardcor_row[i]= rowcor[i] -1;
				else
					guardcor_row[i]= rowcor[i] +1;	
			}
		}
	}
	
	
	//aşağıdaki looplardan elmasların ve onlara ait olan muhafızların konumlarını takip edebilirsiniz. Bu bilgi oyuncuya gizlidir.
	/*for(i=0; i<5; i++)
	{
		printf("%d ", guardcor_row[i]);
		printf("%d ", guardcor_col[i]);
	}
		 
	
	printf("\n");
	for(i=0;i<5;i++)
	{
		printf("%d ", rowcor[i]);
		printf("%d ", colcor[i]);
	}*/
	
	printf("\n");
    for(i=0; i<N; i++){//oyunun başlangıç haritasını oluşturur
        for(j=0; j<K; j++)
            map[i][j]='*';//matrisin tüm elementleri, (2,4) hariç *'dır.
	}
	
	label://oyuncu öldüğünde buraya döner
	
    for(i=0; i<N; i++){//oyun haritasını bastırır
        map[a][b]=player;//matrisin (2,4) elementini oyuncu olarak belirler 
            for(j=0; j<K; j++)
            	printf("%c ",map[i][j]);
                
		printf("\n");
    }
        

    while (flag < 5 && lives != 0){//oyuncu ölene veya elmasların hepsini bulana kadar
	
        if (direction!='\n'){
            		dis1 = abs(a - rowcor[0]) + abs(b - colcor[0]) ;//elmas1e olan uzaklığı hesaplar, abs mutlak değer alma fonksiyonudur
    				dis2 = abs(a - rowcor[1]) + abs(b - colcor[1]) ;//elmas2e olan uzaklığı hesaplar, abs mutlak değer alma fonksiyonudur
    				dis3 = abs(a - rowcor[2]) + abs(b - colcor[2]) ;//elmas3e olan uzaklığı hesaplar, abs mutlak değer alma fonksiyonudur
    				dis4 = abs(a - rowcor[3]) + abs(b - colcor[3]) ;//elmas4e olan uzaklığı hesaplar, abs mutlak değer alma fonksiyonudur
    				dis5 = abs(a - rowcor[4]) + abs(b - colcor[4]) ;//elmas5e olan uzaklığı hesaplar, abs mutlak değer alma fonksiyonudur
    				
    				char found[10] = {"bulundu!"};
    				 
    				//elmaslardan herhangi biri bulunduğunda ona olan konumu 0'a sabitler.
    				if(rowcor[0] == 10){
    					dis1 = 0;	
					}
					if(rowcor[1] == 10){
						dis2 = 0;
					}
					if(rowcor[2] == 10){
						dis3 = 0;
					}
					if(rowcor[3] == 10){
						dis4 = 0;
					}
					if(rowcor[4] == 10){
						dis5 = 0;
					}
					
					printf("\n\t1. Elmasa mesafe: %d\n\t2. Elmasa mesafe: %d\n\t3. Elmasa mesafe: %d\n\t4. Elmasa mesafe: %d\n\t5. Elmasa mesafe: %d\n",dis1,dis2,dis3,dis4,dis5);
			}
			
			direction=getchar();//oyuncunun gitmek istediği yönü alır
		 
		 if(direction=='s' || direction =='S') {//aşağı
				
				if(a+1 == 10){//matris dışına çıkıldığında
                	printf("\n\tOraya gidemezsiniz. Sinir disi!\n\n");
                	direction=getchar();//oyuncudan tekrar input ister
				}
				else{
					int tmp = a;
                	a++;
                	map[a][b] = 'O';
               		map[tmp][b]='*';//oyuncu hareket ettiğinde eski konumu , * a eşitlenir
                
                	for(i=0; i<5; i++){
                		if(a == guardcor_row[i] && b == guardcor_col[i]){//oyuncu muhafıza yakalanır
                			lives--;//canı azalır
                			if(lives == 0){//eğer can 0'a eşitse oyun biter
                				printf("\n\tOldunuz.Bir daha deneyin!\n\n");
								exit(0);
							}
								
							printf("\n\tMuhafiza yakalandiginiz icin basa dondunuz. Kalan caniniz %d'dir.\n\n", lives-1);
							map[a][b] ='*';//oyuncunun muhafıza yakalandığı konum tekrar * a eşitlenir
							a=2;//oyuncunun başlangıç koordinatlarına geri dönülür
							b=4;
							goto label;//oyuncu başa döner (2,4)
						}
						
						else if(a == rowcor[i] && b == colcor[i]){//oyuncu elmas konumunu bulur
                			flag++;//elmas sayacı artar
							rowcor[i] = 10;//elmasın olduğu konum, başka bir sayıya atanır böylece bulunan elmas bir daha bulunmaz
							colcor[i] =  10;
							printf("\n\t%d elmas buldunuz!\n\n", flag);
						}		               	
					}

					for(i=0; i<N; i++){//haritanın son durumu bastırılır.
                        for(j=0; j<K; j++)
                            printf("%c ",map[i][j]);
                        printf("\n");
							}
				}
        }
         
        else if(direction=='w' || direction == 'W'){//yukarı(aşağı yönü için kurallar tüm yönler için aynıdır.)
        		if(a-1 == -1){
                	printf("\n\tOraya gidemezsiniz. Sinir disi!\n\n");
                	direction=getchar();
				}
				else{
					int tmp = a;
                	a--;
                	map[a][b] = 'O';
                	map[tmp][b]='*';
                
                 	for(i=0; i<5; i++){
                		if(a == guardcor_row[i] && b == guardcor_col[i]){	
							lives--;
							if(lives == 0){
                				printf("\n\tOldunuz.Bir daha deneyin!\n\n");
								exit(0);
							}
							
                			printf("\n\tMuhafiza yakalandiginiz icin basa dondunuz. Kalan caniniz %d'dir.\n\n", lives-1);
							map[a][b] ='*';
							a=2;
							b=4;
							goto label;
						}
						
						else if(a == rowcor[i] && b == colcor[i]){
                			flag++;
							rowcor[i] = 10;
							colcor[i] =  10;
							printf("\n\t%d elmas buldunuz!\n\n", flag);
						}		    
					}		

                    for(i=0; i<N; i++){
                        for(j=0; j<K; j++)
                            printf("%c ",map[i][j]);
                            printf("\n");
							}
				}         
        }
        
		else if(direction=='d' || direction == 'D') {//sağ
        		if(b+1 == 10){
                	printf("\n\tOraya gidemezsiniz. Sinir disi!\n\n");
                	direction=getchar();
				}
				else{
					int tmp = b;
                	b++;
               	 	map[a][b] = 'O';
                	map[a][tmp]='*';
                
                 	for(i=0; i<5; i++){
                		if(a == guardcor_row[i] && b == guardcor_col[i]){
                			lives--;
                			if(lives == 0){
                				printf("\n\tOldunuz.Bir daha deneyin!\n\n");
								exit(0);
							}
							
                			printf("\n\tMuhafiza yakalandiginiz icin basa dondunuz. Kalan caniniz %d'dir.\n\n", lives-1);	
							map[a][b] ='*';
							a=2;
							b=4;
							goto label;
						}
						
						else if(a == rowcor[i] && b == colcor[i]){
                			flag++;
							rowcor[i] = 10;
							colcor[i] =  10;
							printf("\n\t%d elmas buldunuz!\n\n", flag);
						}		    
					}
				
                    for(i=0; i<N; i++){
                        for(j=0; j<K; j++)
                            printf("%c ",map[i][j]);
                            printf("\n");
							}
				}
        }
         else if(direction=='a' || direction == 'A') {//sol
         	if(b-1 == -1) {
                	printf("\n\tOraya gidemezsiniz. Sinir disi!\n\n");
                	direction=getchar();
				}
			else{
				int tmp = b;
                b--;
                map[a][b] = 'O';
                map[a][tmp]='*';
                
                 for(i=0; i<5; i++){
                	if(a == guardcor_row[i] && b == guardcor_col[i]){	
							lives--;
							if(lives == 0){
                				printf("\n\tOldunuz.Bir daha deneyin!\n\n");
								exit(0);
							}
							
							printf("\n\tMuhafiza yakalandiginiz icin basa dondunuz. Kalan caniniz %d'dir.\n\n", lives-1);
							map[a][b] ='*';
							a=2;
							b=4;
							goto label;
						}
						
						else if(a == rowcor[i] && b == colcor[i]){
                			flag++;
							rowcor[i] = 10;
							colcor[i] =  10;
							printf("\n\t%d elmas buldunuz!\n\n", flag);
						}		    	
				}
                   
				    for(i=0; i<N; i++){
                        for(j=0; j<K; j++)
                            printf("%c ",map[i][j]);
                            printf("\n");
							}
				}
        	}
        } 
        
        if(flag == 5)
        	printf("\n\tTebrikler! 5 elmasi da bularak oyunu kazandiniz!\n");
		
		return 0;
    }
    
    

		