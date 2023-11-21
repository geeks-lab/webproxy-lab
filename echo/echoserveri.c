/* echoclient p.970 */

/**
 * int main(int argc, char **argv)
 *      @include : <csapp.h>
 *      @brief : 리스닝 디스크립터를 열고 무한루프에 들어가서 반복적으로
 *               클라이언트로부터의 연결을 기다리고,
 *               연결된 클라이언트의 도메인 이름과 포트를 출력하고,
 *               클라이언트의 echo 함수를 호출한다.
 *      @param[in] argc : 
 *      @param[in] 별별argv : argv[0] - ?, argv[1] - port정보
*/

#include "csapp.h"

void echo(int connfd);

int main(int argc, char **argv)
{
    int listenfd, connfd;
    socklen_t clientlen;
    /**
     * 여기 아래에 clientaddr을 주목할 필요가 있다.
     *      struct sockaddr_in 아니라 sockaddr_storage 구조체로 한 이유는 
     *      이 구조체는 어떤 타입의 소켓 주소를 담아도 충분히 크기 때문에 프로토콜에 독립적이기 때문이다.
     *      따라서 accept가 리턴되기 전에 클라이언트 소켓의 주소를 clientaddr에 채워넣어진다.
    */
    struct sockaddr_storage clientaddr;
    char client_hostname[MAXLINE], client_port[MAXLINE];

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    listenfd = Open_listenfd(argv[1]);
    while (1) {
        clientlen = sizeof(struct sockaddr_storage);
        /**
         * Accept(listenfd, (SA *)&clientaddr, &clientlen)
         * Accept(int s, struct sockaddr *addr, <error-type> *addrlen)
        */
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        Getnameinfo((SA *)&clientaddr, clientlen, client_hostname, MAXLINE,
                    client_port, MAXLINE, 0);
        printf("Connected to (%s, %s)\n", client_hostname, client_port);
        echo(connfd);
        Close(connfd);
    }

    exit(0);
}
/**
 * repeatedly reads and writes lines of text until the rio_readlineb function encounters EOF

*/
void echo(int connfd)
{
    size_t n;
    char buf[MAXLINE];
    rio_t rio;

    Rio_readinitb(&rio, connfd);
    while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
        Rio_writen(connfd, buf, n);
    }
}

