#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct Room {
    char roomId[5];   
    int type;               
    double price;
    int status;               
};
struct Room rooms[100];
int size = 0;
void printfMenu();
void addRoom();
void updateRoom();
void lockRoom();
void showRoom(struct Room rooms[], int count);
void searchRoom(struct Room rooms[] , int size);
void roomArrangement(struct Room rooms[], int size);
int main() {
	int choice;
	do{
		printfMenu();
		scanf("%d",&choice);
		getchar();
		switch(choice){
			case 1:
				system("cls");
				addRoom();
				break;
			case 2:
				system("cls");
				updateRoom();
				break;
			case 3:
				system("cls");
				lockRoom();
				break;
			case 4:
				system("cls");
				showRoom(rooms,size);
				break;
			case 5:
				searchRoom(rooms,size);
				break;
			case 6:
				roomArrangement(rooms,size);
				system("cls");
				break;
			case 7:
				break;
			case 8:
				break;
			case 9:
				printf("Thoat chuong trinh\n");
				break;
			default:
				printf("Lua chon khong hop le . Moi ban nhap lai\n");
				break;
		}
	}while(choice != 9);
    return 0;
}




//menu chuc nang
void printfMenu(){	
	printf("----------MENU----------\n");
	printf("1 . Them phong moi\n");
	printf("2 . Cap nhat phong\n");
	printf("3 . Bao tri phong\n");
	printf("4 . Hien thi danh sach\n");
	printf("5 . Tim kiem\n");
	printf("6 . Sap xep danh sach\n");
	printf("7 . Check in\n");
	printf("8 . Lich su thue\n");
	printf("9 . Thoat chuong trinh\n");
	printf("------------------------\n");
	printf("Moi ban nhap lua chon : ");	
}




//Them phong moi
void addRoom(){
	struct Room room1;
	do{
		printf("Moi ban nhap so phong : ");
		fgets(room1.roomId , sizeof(room1.roomId) , stdin);
		room1.roomId[strcspn(room1.roomId , "\n")] = '\0';
		if(strlen(room1.roomId) == 0){
			printf("Loi: So phong khong duoc de trong!\n");
		}		
	}while(strlen(room1.roomId) == 0);
	int isDuplicate;
	do{
		isDuplicate = 0;
		for(int i = 0 ; i < size ; i++){
			if(strcmp(rooms[i].roomId , room1.roomId) == 0){
				printf("Loi: Phong da ton tai!\n");
				isDuplicate = 1;
				break;
			}
		}
		if(isDuplicate){
			printf("Moi ban nhap so phong : ");
			fgets(room1.roomId, sizeof(room1.roomId), stdin);
			room1.roomId[strcspn(room1.roomId, "\n")] = '\0';
		}			
	}while(isDuplicate == 1);	
	do{
		printf("Moi ban nhap loai phong (1.Phong don , 2.Phong doi) : ");
		scanf("%d",&room1.type);
		if(room1.type != 1 && room1.type != 2){
			printf("Loi: Loai phong chi duoc chon 1(Don) hoac 2(Doi)!\n");
		}
	}while(room1.type != 1 && room1.type != 2);
	do{
		printf("Moi ban nhap gia phong : ");
		scanf("%lf",&room1.price);
		if(room1.price <= 0){
			printf("Loi : Gia phong phai lon hon 0!\n");
		}
	}while(room1.price <= 0);
	room1.status = 0;
	rooms[size] = room1;
	size++;
	printf("Them phong thanh cong\n");	
}




//Cap nhat phong
void updateRoom(){
	char roomId[10];
	printf("Nhap so phong can cap nhat : ");
	scanf("%s",roomId);
	int found = 0;
	for(int i = 0 ; i < size ; i++){
		if(strcmp(rooms[i].roomId , roomId) == 0){
			found = 1;
			printf("Thong tin hien tai:\n");
            printf("So phong: %s\n", rooms[i].roomId);
            printf("Loai phong: %d\n", rooms[i].type);
            printf("Gia phong: %.2lf\n", rooms[i].price);
            do{
            	printf("Moi ban nhap loai phong moi (1.Phong don , 2.Phong doi) : ");
            	scanf("%d",&rooms[i].type);
            	if(rooms[i].type != 1 && rooms[i].type != 2){
            		printf("Loi: Loai phong chi duoc chon 1(Don) hoac 2(Doi)!\n");
				}
			}while(rooms[i].type != 1 && rooms[i].type != 2);
			do{
				printf("Moi ban nhap gia phong moi : ");
				scanf("%lf",&rooms[i].price);
				if(rooms[i].price <= 0){
					printf("Loi : Gia phong phai lon hon 0!\n");					
				}
			}while(rooms[i].price <= 0);
			printf("Cap nhat thong tin phong thanh cong\n");
			break;
		}
	}
	if(!found){
		printf("Loi:Khong tim thay phong!\n");
	}	
}




//Bao tri phong
void lockRoom(){
	char roomId[10];
	printf("Nhap ma phong can bao tri : ");
	scanf("%s",roomId);
	int found = -1;
	for(int i = 0 ; i < size ; i++){
		if(strcmp(rooms[i].roomId , roomId) == 0){
			found = i;
			break;
		}
	}
	if(found == -1){
		printf("Loi: Khong tim thay phong\n");
		return;
	}
	if(rooms[found].status == 1){
		printf("Phong dang co khach , khong the dua vao bao tri!\n");
		return;
	}
	if(rooms[found].status == 2){
		printf("Phong da duoc bao tri\n");
		return;
	}
	rooms[found].status = 2;
	printf("Da dua phong vao trang thai bao tri thanh cong!\n");
}




//Hien thi danh sach
void showRoom(struct Room rooms[], int size){
	if(size == 0){
		printf("Danh sach hien tai trong , moi ban nhap them phong\n");
		return;
	}
	int page = 0;
	int pageSize = 10;
	int totalPage = (size + pageSize - 1) / pageSize;	
	while(1){
		printf("Moi ban chon so trang can xem : ");
		scanf("%d",&page);
		if(page < 1 || page > totalPage){
			printf("Trang khong hop le\n");
			continue;
		}
		int start = (page - 1) * pageSize;
		int end = start + pageSize;
		printf("Trang %d/%d : \n\n",page,totalPage);
		printf("+----------+------------+----------+----------+\n");
		printf("|%-10s|%-12s|%-10s|%-10s|\n", "So Phong", "Loai Phong", "Gia tien", "Trang thai");
		printf("+----------+------------+----------+----------+\n");
		for(int i = start ; i < end && i < size ; i++){
			int statusNumber = rooms[i].status;
			char roomType[10];
			if (rooms[i].type == 1) {				
    			strcpy(roomType, "Don");
			} else if (rooms[i].type == 2) {
    			strcpy(roomType, "Doi");
			} else {
    			strcpy(roomType, "Khong xac dinh");
			}
			printf("|%-10s|%-12s|%-10.2lf|%-10d|\n", rooms[i].roomId, roomType, rooms[i].price, statusNumber);
		}
		printf("+----------+------------+----------+----------+\n");
		while (getchar() != '\n');
		printf("Ban co muon thoat hay ko ? (y/n)");
		char ch = getchar();
		if (ch == 'y' || ch == 'Y'){
			break;
		}
	}
}





//Tim kiem phong trong theo loai
void searchRoom(struct Room rooms[] , int size){
	if(size == 0){
		printf("Danh sach phong trong , moi ban nhap lai");
		return;
	}
	int type;
	do{
		printf("Moi ban nhap loai phong (1.Phong don , 2.Phong doi) : ");
		scanf("%d",&type);
		if(type != 1 && type != 2){
			printf("Loi: Loai phong chi duoc chon 1(Don) hoac 2(Doi)!\n");			
		}
	}while(type != 1 && type != 2);
	printf("Cac phong trong thuoc loai %d :\n",type);
	printf("|%-10s|%-12s|%-10s|%-10s|\n", "So Phong", "Loai Phong", "Gia tien", "Trang thai");
	int found = 0;
	for(int i = 0 ; i < size ; i++){
		if(rooms[i].type == type && rooms[i].status == 0){
			char roomType[10];
			if(rooms[i].type == 1){
				strcpy(roomType,"Don");
			}else{
				strcpy(roomType,"Doi");
			}
			printf("|%-10s|%-12s|%-10.2lf|Trong     |\n",
				rooms[i].roomId,
				roomType,
				rooms[i].price);
			found = 1;
		}
	}
	if(!found){
		printf("Khong co phong trong nao thuoc loai %d\n",type);
	}
	
}







//Sap xep danh sach phong theo gia giam dan
void roomArrangement(struct Room rooms[], int size){
	if(size == 0){
		printf("Danh sach phong trong , khong can sap xep\n");
		return;
	}
	for(int i = 0 ; i < size ; i++){
		for(int j = i + 1 ; j < size ; j++){
			if(rooms[i].price < rooms[j].price){
				struct Room temp = rooms[i];
				rooms[i] = rooms[j];
				rooms[j] = temp;
			}
		}
	}
	printf("Da sap xep danh sach phong theo gia giam dan thanh cong\n");
	showRoom(rooms,size);	
}
