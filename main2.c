//
// Created by nabiamad29 on 13/01/23.
//
#include "fonctions.h"


int main(int argc , char ** argv){
    if(argc!=4)
    {

        printf("Wrong usage .\n Please use %s hostname port file",argv[0]);
        exit(EXIT_FAILURE);
    }
    printf("Welcome to 2g1tp1's implemntation of a tftp client\n");
    printf("sending %s to the host %ss\n",argv[3],argv[1],argv[2]);

    char requete[128];
    char buf[1024]={0};
    char receive[1024];
    char receive2[1024];
    char ACK[4]={0,4,0,0};
    char data[1024]={0};
    int namefile[15]={0};
    FILE* fichier=NULL;

    fichier=fopen(namefile,"r");
    int adresse;
    int info;
    int nread,Nbcharead ;
    struct addrinfo hints;
    struct addrinfo *res;
    struct addrinfo * otherhints=calloc(1,sizeof(struct addrinfo));
    struct addrinfo *copie =res;
    struct sockaddr socketReceived;
    int socketReceiveSize;
    memset(&hints,0,sizeof (hints));
    hints.ai_family=AF_INET;
    hints.ai_protocol=IPPROTO_UDP;
    adresse= getaddrinfo(argv[1],argv[2],&hints,&res);
    const char * error_code=gai_strerror(adresse);
    printf("Resultat de getaddrifo pour %s \n",argv[1]);
if(adresse==-1)
{
    printf("It seems ike i can't find the host %s \r",argv[1]);
}

    info=socket(res->ai_family,res->ai_socktype,res->ai_protocol);
    printf("socket :%d\n",info);
    buf[1]=4;
    sprintf(buf+2,"%s",argv[3]);
    sprintf(buf+strlen(argv[3])+3,"%s\r\n","NETASCII");

    if(info==-1)
    {
        perror("erreur");
        exit(EXIT_FAILURE);
    }

    sendto(info,buf,strlen(argv[3])+12,res->ai_flags,res->ai_addr,res->ai_addrlen);

    //send(1,buf, strlen(buf),res->ai_flags);
    //memset(buf,'\0',1024);
    nread=recvfrom(info,receive,1024,res->ai_flags,&socketReceived,&socketReceiveSize);


    if (receive[1]==5)
    {

    printf("Error code received from the server :\n%s\"",receive+4);
    exit(EXIT_SUCCESS);

    }
    if(receive[1]==3)
    {
        printf(" I received %d bytes",nread-4);
        ACK[3]=receive[3];
        sendto(info,ACK,4,0,&socketReceived,&socketReceiveSize);

    }

    Nbcharead = read(1, namefile, 15);
    namefile[Nbcharead-1]='\0';
    if(fichier!=NULL)
    {
        sendto(info,namefile,strlen(namefile),0,&socketReceived,&socketReceiveSize);
    while(fread(data,1,1024,fichier)!=NULL)
    {
        sendto(info,data,1024,0,&socketReceived,&socketReceiveSize);

        recvfrom(info,ACK,strlen(ACK-1),0,&socketReceived,&socketReceiveSize);
        printf("ACK :%s\n", ACK);

        if(strcmp(ACK,"OK")==0)
        {
            printf("Packet du fichier bien envoyé et bien reçu\n");
        }
        else
        {
            printf("Un bloc n'a pas été envoyé ");
            exit(EXIT_FAILURE);

        }

    }

    }
    //sendto(sd,retour,strlen(retour));


return 0;



}