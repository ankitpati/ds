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
    printf("|      pointers |            %2lu |\n", sizeof(char *));
    printf("+---------------+---------------+\n");
    return 0;
}
/* end of sizeof.c */

/* OUTPUT

+---------------+---------------+
|   Data Type   | Size in Bytes |
+---------------+---------------+
|          void |             1 |
|          char |             1 |
|           int |             4 |
|      long int |             8 |
| long long int |             8 |
|         float |             4 |
|        double |             8 |
|   long double |            16 |
|      pointers |             8 |
+---------------+---------------+

*/
