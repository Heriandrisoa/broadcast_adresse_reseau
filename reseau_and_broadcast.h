#ifndef __INCLUDE__
#define _INCLUDE__
#define MAX 100

typedef struct reseau
{
    int composante[4];
}adresse;

typedef struct reseau_bin
{
    char** composante;
}adresse_bin;

char* alloc();
char** alloc_2(int dim);
char* get_ip();
char* getmask();
adresse decompose(char* A);
adresse_bin bin(adresse reseau);
void reverseString(char* str);
char* adresse_reseau(char* ip, char* mask);
char* get_broadcast(char* ip, char* mask);
char* decimal(char* bin);
#endif