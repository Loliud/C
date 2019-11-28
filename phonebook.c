#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct 
{
	char name[31];
	char phone[11];
	char email[31];
}PHONEBOOK;

PHONEBOOK* lstContacts = NULL;
int nContacts = 0;

int NhapTuBanPhim(PHONEBOOK** pb)
{
	int n = 0;
	printf("So luong: ");
	scanf("%d",&n);
	PHONEBOOK* tmp = (PHONEBOOK*)calloc(n, sizeof(PHONEBOOK));
	for (int i = 0;i < n;i++)
	{
		__fpurge(stdin);
		printf("Ten: ");
		gets(tmp[i].name);
		__fpurge(stdin);
		printf("Dien thoai: ");
		gets(tmp[i].phone);
		__fpurge(stdin);
		printf("Email: ");
		gets(tmp[i].email);
	}
	*pb = tmp;
	return n;
}

void GhiFile(char* fname)
{
	FILE* f = fopen(fname,"wb");
	if (nContacts > 0)
	{
		fwrite(lstContacts, sizeof(PHONEBOOK), nContacts, f);
	}
	fclose(f);
}

void DocFile(char* fname)
{
	FILE* f = fopen(fname,"rb");
	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	nContacts = size / sizeof(PHONEBOOK);
	fseek(f, 0, SEEK_SET);
	lstContacts = (PHONEBOOK*)calloc(nContacts, sizeof(PHONEBOOK));
	fread(lstContacts, sizeof(PHONEBOOK), nContacts, f);
	fclose(f);
}

void main()
{
	nContacts = NhapTuBanPhim(&lstContacts);
	printf("So luong da nhap la: %d\n", nContacts);
}
	
