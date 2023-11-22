/**
 * 
*/
#include "csapp.h"

int main(void) {
    char *buf, *p;
    char arg1[MAXLINE], arg2[MAXLINE], content[MAXLINE];
    int n1 = 0, n2 = 0;

    /* Extract the two arguments */
    if ((buf = getenv("QUERY_STRING")) != NULL) {
        p = strchr(buf, '&');
        *p = '\0';
        // strcpy(arg1, buf);
        // strcpy(arg2, p + 1);
        // n1 = atoi(arg1);
        // n2 = atoi(arg2);
        
        // 이건 서연이 코드고 서연이가 실행하면 문제 없는데 내가 실행하면 뒤의 숫자가 앞의 숫자랑 같아지는데 왜 그런지 못찾음. 
        // n1 = atoi(strchr(arg1, '=') + 1);
        // n2 = atoi(strchr(arg1, '=') + 1);

        sscanf(buf, "first=%d", &n1);
        sscanf(p+1, "second=%d", &n2);
        
    }

    /* Make the response body */
    sprintf(content, "QUERY_STRING=%s", buf);
    sprintf(content, "Welcome to add.com: ");
    sprintf(content, "%sTHE Internet addition portal.\r\n<p>", content);
    sprintf(content, "%sThe answer is: %d + %d = %d\r\n<p>",
            content, n1, n2, n1 + n2);
    sprintf(content, "%sThanks for visiting!\r\n", content);

    /* Generate the HTTP response */
    printf("Connection: close\r\n");
    printf("Content-length: %d\r\n", (int)strlen(content));
    printf("Content-type: text/html\r\n\r\n");
    printf("%s", content);
    fflush(stdout);

    exit(0);
}
