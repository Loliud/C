#include<stdio.h>
#include<stdlib.h>
#include<stdio_ext.h>
#include<string.h>
// tạo kiểu struct sinh viên
typedef struct SinhVien{
    char username[30];
    char password[30];
    float point;
}SV;
// tạo struct node có chứa data là sinh viên
typedef struct Node{
    SV data;
    struct Node *left;
    struct Node *right;
}Node;
// hàm tạo 1 node mới có dữ liệu là sinh viên
Node *createNode(SV data){
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
}
// hàm chèn node có dữ liệu sinh viên vào cay nhị phân tìm kiếm
Node *insertNode(Node *root, SV data){
    Node *newNode = createNode(data);
    if(root == NULL) root = newNode; // dữ liệu đầu tiên được chèn vào là root 
    else
    {
        if(strcmp(data.username, root->data.username) > 0){ // dùng hàm so sánh chuỗi 
            root->right = insertNode(root->right, data);
        }else if(strcmp(data.username, root->data.username) < 0){
            root->left = insertNode(root->left, data);
        }
    }
    return root;
}
// hàm in danh sách sinh viên theo thứ tự bảng chữ cái a b c d ...
void printList(Node *root){ 
    if(root != NULL){
        printList(root->left);
        if(strcmp(root->data.username, "Admin") != 0){ // đề bài yêu cầu không cần in ra admin
            printf("%s - %s - %.2f\n", root->data.username,root->data.password,root->data.point);
            // %.2f định dạng làm tròn 2 chữ số sau dấu phẩy
        }
        printList(root->right);
    }
}
/* hàm duyệt từng các node trong cây nhị phân (tương tự như hàm in cây), tuy nhiên thay vì in ra dữ liệu ra màn hình console
thì chúng ta ghi dữ liệu đó vào file --> chỉ thay đổi hàm printf */
// hàm này sẽ được gọi bởi hàm writeFile tý nữa viết bên dưới.
void duyetNodeVaGhiFile(Node *root, FILE *file){
    if(root != NULL){
        duyetNodeVaGhiFile(root->left, file);
        fprintf(file, "%s   %s   %f\n", root->data.username, root->data.password, root->data.point);
        // chỉ thay đổi printf thành fprintf
        duyetNodeVaGhiFile(root->right, file);
    }
}
// hàm lấy dữ liệu từ file và đẩy hêt dữ liệu vào cây nhị phân tìm kiếm
Node *inputFromFile(Node *root, char *filename){
    // Mở file
    FILE *file = fopen(filename, "r");
    if(!file){
        printf("Khong doc dc file\n");
    }
    // khai báo biến sv làm trung gian để gán dữ liệu
    SV sv;
    // fscanf môi lần chạy sẽ đọc 1 dòng và lấy dữ liệu gán vào biến sv
    while(fscanf(file, "%s  %s  %f", sv.username, sv.password, &sv.point) != EOF){
        // sau khi biến sv đã có được dữ liệu, ta chèn nó vào trong cây nhị phân tìm kiếm (như chèn cây bình thường)
        root = insertNode(root, sv);
    }
    // đóng file
    fclose(file);
    // trả lại về root 
    return root;
}
// hàm ghi vào file
void writeFile(Node *root, char *filename){
    // mở file
    FILE *file = fopen(filename, "w");
    // Gọi hàm này, lúc nãy đã giải thích ở trên, hàm này nhận tham số là nút gốc và file đã khai báo trên
    duyetNodeVaGhiFile(root, file);
    // đóng file kẻo dư liệu bị hỏng, ghi vào file lung tung
    fclose(file);
}
// hàm tìm kiếm node 
Node *search(Node *root, char *username, char *password){
    if (root == NULL || strcmp(root->data.username, username) == 0 && strcmp(root->data.password, password) == 0){
        return root;
    } 
    if (strcmp(root->data.username, username) < 0) 
        return search(root->right, username, password); 

    return search(root->left, username, password); 
}
// hàm tìm con phần tử nhỏ nhất, hàm này giúp ta trong bươc tìm con kế cận trong bước xóa node
// Ở bươc xóa node ta sẽ duyệt sang phải nên sẽ là tìm con bé nhất bên nhánh phải thế lên thằng bị xóa (đôi vs node có 2 con)
Node * minValueNode(Node *node) 
{   
    // tạo node min mặc định là node ban đầu truyền vào
    Node *minNode = node;
    // nếu minNode tồn tại và có con trái thì vòng while cứ tiếp tục, cho đến khi không còn con trái thì node hiện tại chính
    // là node be nhất cần tìm kiếm.
    while (minNode && minNode->left != NULL){
        // cập nhật lại minNode thành con bên trái
        minNode = minNode->left; 
    }
    // trả về node bé nhất 
    return minNode; 
}

Node *deleteNode(Node *root, char *username){
    if (root == NULL) return root; 
    // đây là bước duyệt trong cây để tìm node cần xóa
    if (strcmp(username, root->data.username) < 0){
        // node cần xóa nằm bên trái, ta cần duyệt sang trái
        root->left = deleteNode(root->left, username); 
    } 
    else if (strcmp(username, root->data.username) > 0){
        // node cần xóa nằm bên phải, ta cần duyệt sang phải
        root->right = deleteNode(root->right, username); 
    }
    else // trường hợp đã duyệt đến node cần xóa, ta bắt đầu đên thao tác xóa
    {   
        // nếu mà con trái null --> node có 1 con phải hoặc node không có con
        if (root->left == NULL) 
        {   
        // ở đoạn này, lấy giá trị của con phải vào temp
        // xóa node cần xóa và nối node phải(temp) lên cha của thằng bị xóa, nếu node phải NUll thì thằng cha không nối với
        // node nào hết
            Node *temp = root->right; 
            free(root); 
            return temp; 
        }
        // nếu mà con phải null --> node có 1 con trái hoặc node không có con
        else if (root->right == NULL) 
        { 
        // ở đoạn này, lấy giá trị của con trái vào temp
        // xóa node cần xóa và nối node trái(temp) lên cha của thằng bị xóa, nếu node trái NUll thì thằng cha không nối với
        // node nào hết
            Node *temp = root->left; 
            free(root); 
            return temp; 
        }
        // nếu không vào 2 trường hợp trên --> node có 2 con, đoạn code dưới sẽ được thực hiện
        Node *temp = minValueNode(root->right); // lấy thằng bé nhất bên nhánh phải (node kế cận)
        root->data = temp->data; // hoán đổi data của node cần xóa và node kế cận tìm đưuọc ở trên
        // cập nhật lại node kế cận nãy tìm được --> null
        root->right = deleteNode(root->right, temp->data.username); 
    } 
    return root; 
}
void menuBegin(){
    printf("1. Dang nhap\n");
    printf("2. Thaot\n");
}
void menuSV(){
    printf("1. Xem diem\n");
    printf("2. Reset pass\n");
    printf("3. Ghi len file\n");
}
void menuAdmin(){
    printf("1. Them sv\n");
    printf("2. In ra ds\n");
    printf("3. Xoa sv\n");
    printf("4. Ghi len file\n");
}
int main(){
    Node *root = NULL;
    SV sv;
    root = inputFromFile(root, "./data.txt");
    int select;
    
    // menu đầu tiên
    while(68){
        menuBegin();
        printf("Nhap lua chon: ");
        scanf("%d", &select);
        // xóa bộ nhớ đệm
        __fpurge(stdin);
        if(select == 1){
            // tạo biến đếm để dùng lúc đăng nhập sai 3 lần
            int count = 0;
            while(22){
            // bước đăng nhập
            printf("Nhap ten: ");
            gets(sv.username);
            __fpurge(stdin);
            printf("Nhap mat khau: ");
            gets(sv.password);
            __fpurge(stdin);
            // tạo node trung gian tý nữa chứa dữ liệu
            Node *node = NULL;
            // dùng hảm search vs tham số có username, password và hàm đó trả về 1 node thỏa mãn khi đăng nhập đúng
            // hoặc null nếu đăng nhập sai
            node  = search(root, sv.username, sv.password);
            // node khắc null --> đăng nhập đúng
            if(node != NULL){
                // vào nhánh admin
                if(strcmp(node->data.username, "Admin") == 0){
                    int status; // tạo cờ hiệu dùng để thoat admin khi thao tác xong
                    while(89){
                        menuAdmin();
                        printf("Select: ");
                        scanf("%d", &select);
                        __fpurge(stdin);
                        switch(select){
                            case 1:
                                printf("Nhap ten: ");
                                gets(sv.username);
                                __fpurge(stdin);
                                printf("Nhap mat khau: ");
                                gets(sv.password);
                                __fpurge(stdin);
                                printf("Nhap diem: ");
                                scanf("%f", &sv.point);
                                __fpurge(stdin);
                                // chèn , tạo sinh viên mới
                                root = insertNode(root, sv);
                                break;
                            case 2:
                                // in ds sinh viên
                                printList(root);
                                break;
                            case 3:
                                // xóa sinh viên
                                __fpurge(stdin);
                                printf("Nhap username muon xoa: ");
                                gets(sv.username);
                                __fpurge(stdin);
                                root = deleteNode(root, sv.username);
                                break;
                            case 4:
                                // ghỉ ra file và thoat khỏi chế dộ admin
                                writeFile(root, "./data.txt");
                                status = 1;
                                break;
                        }
                        if(status == 1){
                            
                            count = 4;
                            break;
                        }
                    }
                 //vào sinh viên   
                }else{
                    int status;
                    while(44){
                        menuSV();
                        printf("Nhap select: ");
                        scanf("%d", &select);
                        switch(select){
                            case 1:
                                // xem ddiemr sv
                                printf("Diem cua sinh vien: %f\n", node->data.point);
                                break;
                            case 2:
                                // reset lại mật khảu
                                printf("Nhap mk moi: ");
                                char newPass[30];
                                char confirmNewPass[30];
                                __fpurge(stdin);
                                gets(newPass);
                                __fpurge(stdin);
                                printf("Confirm mk moi: ");
                                gets(confirmNewPass);
                                __fpurge(stdin);
                                if(strcmp(confirmNewPass, newPass) == 0){
                                    printf("THanh cong\n");
                                    // thảy dổi data của sv trong cây
                                    strcpy(node->data.password, newPass);
                                    printList(root);
                                }else{
                                    printf("Khogn thanh cong\n");
                                }
                                break;
                            case 3:
                                // ghi vào file
                                writeFile(root, "./data.txt");
                                status = 1;
                                break;
                        }
                        // khi status == 1 tức đã thao tác xong ở sinhvien hoặc admin 
                        if(status == 1){
                            // gán count == 4 để tý dùng thoát ra menu ban đầu
                            count = 4;
                            // break để thoát khỏi sv và admin
                            break;
                        }
                        
                    }                    
                }
            }else{ // 
                printf("Sai , hay nhap lai\n");
                count += 1;
            }
            if(count == 3){ // thoat khỏi chương trình khi nhập sai 3 lần
                return 0;
            }
            if(count == 4){ // thoat khỏi admin hoạc sinh viên quay về menu đầu tiên
                break;
            }
            }
        }else if(select == 2){ // thoát chương trình
            return 0;
        }
    }
    return 0;
}
