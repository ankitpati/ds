/* sizeof.c */
/* Date  : 11 January 2016
 * Author: Ankit Pati
 */

#include <stdio.h>

int main()
{
    puts  ("+---------------+---------------+");
    puts  ("|   Data Type   | Size in Bytes |");
    puts  ("+---------------+---------------+");
    printf("|          void |            %2lu |\n", sizeof(void));
    printf("|          char |            %2lu |\n", sizeof(char));
    printf("|           int |            %2lu |\n", sizeof(int));
    printf("|      long int |            %2lu |\n", sizeof(long int));
    printf("| long long int |            %2lu |\n", sizeof(long long int));
    printf("|         float |            %2lu |\n", sizeof(float));
    printf("|        double |            %2lu |\n", sizeof(double));
    printf("|   long double |            %2lu |\n", sizeof(long double));
    printf("+---------------+---------------+\n");
    return 0;
}
/* end of sizeof.c */
