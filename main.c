 #include <string.h>
 #include "reseau_and_broadcast.h"
#include <stdlib.h>


int main()
{
    char* ip=alloc();
    char* mask=alloc();
    char* adresseReseau=alloc();
    char* broadcast=alloc();
    strcpy(ip,get_ip());
    strcpy(mask,getmask());
    strcpy(adresseReseau,adresse_reseau(ip,mask));
    strcpy(broadcast,get_broadcast(ip,mask));

    free(ip);
    free(mask);
    free(adresseReseau);
    return 0;
}
