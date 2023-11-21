/* echoclient p.968 */

#include "csapp.h"

/**
 * int main(int argc, char **argv)
 *      @include : <csapp.h>
 *      @brief : fgets함수가 EOF를 만날 때 까지, 반복적으로
 *               텍스트 라인을 서버에게 보내고, 서버로부터 오는 에코라인을 읽고, 결과를 출력한다.
 *               루프 종료시, 디스크립터를 클로즈한다.
 *      @param[in] argc : 안쓰임. 왜안쓰이지..?
 *      @param[in] 별별argv : argv[1] - host정보, argv[2] - port정보
 *      @param[in] p->ai_protocol : int protocol
*/
int main(int argc, char **argv)
{
    int clientfd;
    char *host, *port, buf[MAXLINE];
    rio_t rio; 

    if (argc != 3) {
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        exit(0);
    }
    host = argv[1];
    port = argv[2];
    
    clientfd = Open_clientfd(host, port); 
    Rio_readinitb(&rio, clientfd); /* Associate a descriptor with a read buffer and reset buffer   */
    
    while (Fgets(buf, MAXLINE, stdin) != NULL) {
        Rio_writen(clientfd, buf, strlen(buf));
        Rio_readlineb(&rio, buf, MAXLINE);
        Fputs(buf, stdout);
    }
    Close(clientfd);
    exit(0);


}
