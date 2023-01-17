//
// Created by nabiamad29 on 13/01/23.
//

#ifndef TP_RESEAU_FONCTIONS_H
#define TP_RESEAU_FONCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>

#endif //TP_RESEAU_FONCTIONS_H

int getaddrinfo(const char *node ,const char *service
,const struct addrinfo *hints,struct addrinfo **res);

int gamenameinfo(const struct sockaddr *addr,socklen_t addrlen, char *host,socklen_t hostlen,char *serv,socklen_t servlen ,int flags);


