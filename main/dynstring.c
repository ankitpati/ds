/* dynstring.c */
/* Date  : 11 January 2016
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>

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

char *sconcat(char *str1, char *str2)
{
    char *str;
    size_t len1, len2, i;
    len1 = len2 = i = 0;

    while(str1[len1]) ++len1;
    while(str2[len2]) ++len2;
    if(!(str = malloc(len1 + len2 + 1))) exit(12);

    while((str[i++] = *str1++));
    --i;
    while((str[i++] = *str2++));

    return str;
}

int main()
{
    char *s1, *s2, *s;

    puts("Enter two strings:");
    if(!(s1 = getstr()) || !(s2 = getstr())) exit(12);

    printf("Concatenated string is \"%s\".", s = sconcat(s1, s2));

    free(s1);
    free(s2);
    free(s);
    return 0;
}
/* end of dynstring.c */

/* OUTPUT

Enter two strings:
hello
world
Concatenated string is "helloworld".

*/
