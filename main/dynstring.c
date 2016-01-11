/* dynstring.c */
/* Date  : 11 January 2016
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getstr()
{
    int c;
    size_t n;
    char *s, *t;
    if(!(s=t=malloc(1))) return NULL;
    for(n=0; (c=getchar())!=EOF && c-'\n' && (t=realloc(s, n+2)); s[n++]=c) s=t;
    if(!t){
        free(s);
        return NULL;
    }
    s[n]='\0';
    return s;
}

int main()
{
    char *s1, *s2, *d;
    size_t i, j;

    puts("Enter two strings:");
    if(!(s1 = getstr())) goto alocerr;
    if(!(s2 = getstr())) goto alocerr;

    if(!(d = malloc(strlen(s1) + strlen(s2) + 1))) goto alocerr;

    i = j = 0;
    while((d[i] = s1[i])) ++i;
    while((d[i++] = s2[j++]));

    printf("Concatenated string is \"%s\".", d);

    free(s1);
    free(s2);
    free(d);
    return 0;

alocerr:
    fprintf(stderr, "Cannot allocate memory!\n");
    return 12;
}
/* end of dynstring.c */
