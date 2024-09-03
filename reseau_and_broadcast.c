#include "reseau_and_broadcast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


char** alloc_2(int dim)
{
    char** str=NULL;
    str=(char**)malloc(dim*sizeof(char*));
    if(str==NULL)
    {
        printf("allocation echouee 2D");
        exit(1);
    }
    for(int i=0 ; i<dim ; i++)
    {
        str[i]=alloc();
    }
    return str;
}

char* alloc()
{
    char* str=NULL;
    str=(char*)malloc(MAX*sizeof(char));
    if(str==NULL)
    {
        printf("allocation echouee char");
        exit(1);
    }

    return str;
}

char* get_ip()
{
    char* adresse_ip_binary=alloc();
    adresse ip_number;
    int index=0;
    int comma=0;
    char* ip=alloc();
    int i;
    ask:
    printf("ip:");
    scanf("%s",ip);
    comma=0;
    for(int i=0 ; i<strlen(ip) ; i++)
    {
        if(ip[i]=='.')
        {
            index++;
            comma++;
        }
        else
        {
            if(strchr("0123456789",ip[i])==NULL||index>1)
            {
                printf("ip invalide \n");
                goto ask;
            }
            index=0;
        }
    }

    if(comma!=3)
    {
        printf("ip invalide\n");
        goto ask;
    }
    ip_number=decompose(ip);
    for(int i=0 ; i<4 ; i++)
    {
        if(ip_number.composante[i]>255||ip_number.composante[i]<0)
        {
            printf("ip invalide\n");
            goto ask;
        }
    }
    adresse_bin ip_bin=bin(ip_number);
    strcpy(ip,"");
    strcpy(adresse_ip_binary,"");

    for(int i=0 ; i<4 ; i++)
    {
        strcat(ip,ip_bin.composante[i]);
        strcat(adresse_ip_binary,ip_bin.composante[i]);
        if(i!=3)
        {
            strcat(ip,".");
        }
    }
    //printf("%s\n" ,ip);
    //decimal(ip);
    return ip;
}

char* getmask()
{
    char* adresse_mask_binary=alloc();
    int misy_0=0;
    int misy_1=0;
    adresse mask_number;
    int index=0;
    int comma=0;
    char* mask=alloc();
    int i;
    ask:
    printf("mask:");
    scanf("%s",mask);
    comma=0;
    for(int i=0 ; i<strlen(mask) ; i++)
    {
        if(mask[i]=='.')
        {
            index++;
            comma++;
        }
        else
        {
            if(strchr("0123456789",mask[i])==NULL||index>1)
            {
                printf("mask invalide \n");
                goto ask;
            }
            index=0;
        }
    }
    if(comma!=3)
    {
        printf("mask invalide\n");
        goto ask;
    }

    mask_number=decompose(mask);
    for(int i=0 ; i<4 ;i++)
    {
        if(mask_number.composante[i]>255)
        {
            printf("mask invalide\n");
            goto ask;
        }
    }
    adresse_bin mask_binary=bin(mask_number);
    strcpy(mask,"");
    strcpy(adresse_mask_binary,"");

    for(int i=0 ; i<4 ; i++)
    {
        strcat(mask,mask_binary.composante[i]);
        strcat(adresse_mask_binary,mask_binary.composante[i]);
        if(i!=3)
        {
            strcat(mask,".");
        }
    }

    //printf("%s\n" ,mask);
    if(strchr(adresse_mask_binary,'0')==NULL||strchr(adresse_mask_binary,'0')==NULL)
    {

            printf("mask invalide\n");
            goto ask;
    }
    for(int i=0; i<strlen(adresse_mask_binary)-1 ; i++)
    {
        if(adresse_mask_binary[i]=='0'&&adresse_mask_binary[i+1]=='1')
        {
            printf("mask invalide\n");
            goto ask;
        }
    }
    /*for(int i=0; i<3; i++)
    {
        printf("%s.",mask_binary.composante[i]);
    }
        printf("%s",mask_binary.composante[3]);
    misy_0=0;
    for(int i=0 ; i<4 ; i++)
    {
        for(int j=0 ; j<strlen(mask_binary.composante[i])-1 ; j++)
        {
            if(mask_binary.composante[i][j]=='0')
            {
                misy_0++;
            }
            else
            {
                if(misy_0!=0)
                {
                    printf("mask invalide\n");
                    misy_0=0;
                    misy_1=0;
                    goto ask;
                }
                else
                    misy_1++;
            }
        }
    }
    if(misy_0==0||misy_1==0)
    {
        printf("mask invalide\n");
        goto ask;
    }
    */
    return mask;
    }

char* get_broadcast(char* ip, char* mask)
{
    for(int i=0 ; i<35; i++)
    {
        if(mask[i]=='1')
            mask[i]='0';
        else if(mask[i]=='0')
            mask[i]='1';
    }
    char* adresse_broadcast_result=alloc();
    for(int i=0 ; i<35 ; i++)
    {
        if(ip[i]=='0'&&mask[i]=='0')
        {
            strcat(adresse_broadcast_result,"0");
        }
        else if(ip[i]=='.')
            strcat(adresse_broadcast_result,".");
        else
            strcat(adresse_broadcast_result,"1");
    }
    adresse_broadcast_result=decimal(adresse_broadcast_result);
    printf("adresse broadcast:%s\n",adresse_broadcast_result);
    
    return adresse_broadcast_result;
}

adresse decompose(char* A)
{
    adresse reseau;
    int index=0;
    char* buffer;
    buffer=strtok(A,".");
    while(buffer!=NULL)
    {
        reseau.composante[index]=atoi(buffer);
        buffer=strtok(NULL,".");
        index++;
    }
    return reseau; 
}

adresse_bin bin(adresse reseau)
{
    char* buffer=alloc();
    int reste;
    adresse_bin binaire;
    binaire.composante=alloc_2(4);
    
    for(int i=0 ; i<4 ; i++)
    {
        if(reseau.composante[i]!=0&&reseau.composante[i]!=1)
        {
        while(reseau.composante[i]!=0&&reseau.composante[i]!=1)
        {
            reste=reseau.composante[i]%2;
            sprintf(buffer,"%d",reste);
            strcat(binaire.composante[i],buffer);
            reseau.composante[i]=(reseau.composante[i]-reste)/2;    /* code */
        }
            strcat(binaire.composante[i],"1");
            for(int j=strlen(binaire.composante[i]); j<8 ;j++)
            {
            strcat(binaire.composante[i],"0");
            }
            reverseString(binaire.composante[i]);
        }
        else
        {
            sprintf(buffer,"%d",reseau.composante[i]);
            strcat(binaire.composante[i],buffer);
            for(int j=strlen(binaire.composante[i]); j<8 ;j++)
            {
                strcat(binaire.composante[i],"0");
            }
            reverseString(binaire.composante[i]);
  
        }
    }
    return binaire;
}

char* adresse_reseau(char* ip, char* mask)
{
    char *ip_buffer=alloc(),*mask_buffer=alloc();
    strcpy(ip_buffer,ip);
    strcpy(mask_buffer,mask);
    char* adresse_reseau_result=alloc();
    for(int i=0 ; i<35 ; i++)
    {
        if(ip[i]=='1'&&mask[i]=='1')
        {
            strcat(adresse_reseau_result,"1");
        }
        else if(ip[i]=='.')
            strcat(adresse_reseau_result,".");
        else
            strcat(adresse_reseau_result,"0");
    } 
    printf("ip               :%s\nmask             :%s\nadresse reseau   :%s\n",decimal(ip_buffer),decimal(mask_buffer),decimal(adresse_reseau_result));
    
    return adresse_reseau_result;
}

void reverseString(char* str) 
{
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}


char* decimal(char* bin)
{
    char* decimal_result=alloc();
    int j=0;
    char* buffer;
    adresse ametrahana;
    buffer=strtok(bin,".");
    for(int i=0 ;i<4 ; i++)
    {
        ametrahana.composante[i]=0;
    }
    while(buffer!=NULL)
    {
        for(int i=0 ; i<strlen(buffer); i++)
        {
            ametrahana.composante[j]+=(int)pow(2,(7-i))*(buffer[i]-48);
           // printf("%d--", ametrahana.composante[j]);
        }
        
        //printf("%d", ametrahana.composante[j]);
        j++;
        buffer=strtok(NULL,".");
    }
    buffer=alloc();
    for(int i=0 ; i<4 ; i++)
    {
        sprintf(buffer,"%d", ametrahana.composante[i]);
        strcat(decimal_result,buffer);
        if(i!=3)
            strcat(decimal_result,".");
    }
    //printf("%s", decimal_result);
    return decimal_result;
}
