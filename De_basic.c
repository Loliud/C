#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
typedef struct _NODE
{
	char* word;
	char* meaning;
	struct _NODE* left;
	struct _NODE* right;
}NODE;

NODE* InsertNode(NODE* root, char* word, char* meaning)
{
	if (root == NULL)
	{
		NODE* tmp = (NODE*)calloc(1, sizeof(NODE));
		tmp->word = (char*)calloc(1, strlen(word) + 1);
		strcpy(tmp->word, word);
		tmp->meaning = (char*)calloc(1, strlen(meaning) + 1);
		strcpy(tmp->meaning, meaning);
		tmp->left = NULL;
		tmp->right = NULL;
		return tmp;
	}else
	{
		if (strcmp(root->word, word) < 0)
		{
			root->right = InsertNode(root->right, word, meaning);
		}else if (strcmp(root->word, word) > 0)
		{
			root->left = InsertNode(root->left, word, meaning);
		}
		return root;
	}
}

void PrintBST(NODE* root)
{
	if (root != NULL)
	{   
		printf("%s --> %s\n",root->word, root->meaning);
        PrintBST(root->left);
    	PrintBST(root->right);
	}
}

NODE *inputFromFile(NODE *root, char *filename){
    FILE *file = fopen(filename, "r");
    char word[244];
    char meaning[244];
    while(fscanf(file, "%s %s", word, meaning) != EOF){
        printf("%s %s\n", word, meaning);
        root = InsertNode(root, word, meaning);
    }
    return root;
}
NODE *AddWord(NODE *root){
    char word[200];
    char meaning[200];
    printf("Nhap vao word: ");
    fflush(stdin);
    gets(word);
    printf("Nhap vao meaning: ");
    fflush(stdin);
    gets(meaning);
    root = InsertNode(root, word, meaning);
    return root;
}

NODE *search(NODE *root, char *word) 
{ 
    if(root == NULL){
        return root;
    }
    if (strcmp(root->word, word) == 0){
        printf("Word nay co trong tu dien. Co muon sua ko ?\n");
        char c;
        fflush(stdin);
        scanf("%c", &c);
        if(c == 'y'){
            printf("Nhap meaning: ");
            char meaning[50];
            fflush(stdin);
            gets(meaning);
            root->meaning = meaning;
            return root;
        }
        return root; 
    }
     
    if (strcmp(root->word, word) < 0){
        return search(root->right, word); 
    } 
    return search(root->left, word); 
}
NODE * minValueNode(NODE *node) 
{   
    // tạo node min mặc định là node ban đầu truyền vào
    NODE *minNode = node;
    // nếu minNode tồn tại và có con trái thì vòng while cứ tiếp tục, cho đến khi không còn con trái thì node hiện tại chính
    // là node be nhất cần tìm kiếm.
    while (minNode && minNode->left != NULL){
        // cập nhật lại minNode thành con bên trái
        minNode = minNode->left; 
    }
    // trả về node bé nhất 
    return minNode; 
}

NODE *deleteNode(NODE *root, char *word){
    if (root == NULL) return root; 
    // đây là bước duyệt trong cây để tìm node cần xóa
    if (strcmp(word, root->word) < 0){
        // node cần xóa nằm bên trái, ta cần duyệt sang trái
        root->left = deleteNode(root->left, word); 
    } 
    else if (strcmp(word, root->word) > 0){
        // node cần xóa nằm bên phải, ta cần duyệt sang phải
        root->right = deleteNode(root->right, word); 
    }
    else // trường hợp đã duyệt đến node cần xóa, ta bắt đầu đên thao tác xóa
    {   
        // nếu mà con trái null --> node có 1 con phải hoặc node không có con
        if (root->left == NULL) 
        {   
        // ở đoạn này, lấy giá trị của con phải vào temp
        // xóa node cần xóa và nối node phải(temp) lên cha của thằng bị xóa, nếu node phải NUll thì thằng cha không nối với
        // node nào hết
            NODE *temp = root->right; 
            free(root); 
            return temp; 
        }
        // nếu mà con phải null --> node có 1 con trái hoặc node không có con
        else if (root->right == NULL) 
        { 
        // ở đoạn này, lấy giá trị của con trái vào temp
        // xóa node cần xóa và nối node trái(temp) lên cha của thằng bị xóa, nếu node trái NUll thì thằng cha không nối với
        // node nào hết
            NODE *temp = root->left; 
            free(root); 
            return temp; 
        }
        // nếu không vào 2 trường hợp trên --> node có 2 con, đoạn code dưới sẽ được thực hiện
        NODE *temp = minValueNode(root->right); // lấy thằng bé nhất bên nhánh phải (node kế cận)
        root->word = temp->word;
        root->meaning = temp->meaning; // hoán đổi word của node cần xóa và node kế cận tìm đưuọc ở trên
        // cập nhật lại node kế cận nãy tìm được --> null
        root->right = deleteNode(root->right, temp->word); 
    } 
    return root; 
} 

void translate(NODE *root){
    printf("Nhap vao 1 tu tieng anh: ");
    char word[200];
    fflush(stdin);
    gets(word);
    //PrintBST(root);
    NODE *findWord = search(root, word);
    if(findWord == NULL){
        printf("Nhap meaning: ");
        char meaning[200];
        fflush(stdin);
        gets(meaning);
        root = InsertNode(root, word, meaning);
    }else{
        strcpy(word, findWord->word);
        char meaning[200];
        strcpy(meaning, findWord->meaning);
        root = deleteNode(root, findWord->word);
        root = InsertNode(root, word, meaning);
        // PrintBST(root);
        // printf("%s -- %s \n", findWord->word, findWord->meaning);
    }
}
void deleteTree(NODE *node)  
{ 
    if (node == NULL) return; 
  
   
    deleteTree(node->left); 
    deleteTree(node->right); 
    
    //printf("\n Deleting node: %d", node->data); 
    free(node); 
}  
void showMenu(){
    printf("Chon 1. Nap tu dien\n");
    printf("Chon 2. In tu dien\n");
    printf("Chon 3. Them/ sua tu dien\n");
    printf("Chon 4. Thoat chuong trinh\n");
    printf("Chon 5. Giai phong cay\n");
}
int main( int argc, char *argv[] ){
    int select;
    NODE *root = NULL;
    while(69){
        showMenu();
        printf("Hay nhap lua chon: ");
        scanf("%d", &select);
        fflush(stdin);
        switch(select){
            case 1:
                root = inputFromFile(root, "dict.txt");
                break;
            case 2:
                PrintBST(root);
                break;
            case 3:

                translate(root);
                break;
            case 4:
                break;
            case 5:
                deleteTree(root);
                return 0;
            default:
                printf("Hay lua chon 1 - 4");
                break;
        }
    }
    return 0;
}
