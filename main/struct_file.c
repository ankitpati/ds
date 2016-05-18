/* struct_file.c */
/* Date  : 18 April 2016
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char name[50];
    unsigned height;
} s;

int main(int argc, char **argv)
{
    size_t i, n;
    s stht[50];
    FILE *fp;

    if(argc < 2){
        fprintf(stderr, "Usage:\n\tstruct_file <filename>");
        exit(1);
    }

    if(!(fp = fopen(argv[1], "wb+"))){
        fprintf(stderr, "File could not be opened!\n");
        exit(5);
    }

    printf("Number of Students? ");
    scanf(" %zu%*c", &n);

    for(i = 0; i < n; ++i){
        printf("\nStudent %zu\n", i + 1);
        printf("Name   : "); fgets(stht[i].name, 50, stdin);
        printf("Height : "); scanf(" %u%*c", &stht[i].height);
    }
    putchar('\n');

    puts("Writing to file...");
    fwrite(stht, sizeof(*stht), n, fp);

    fflush(fp);
    rewind(fp);

    puts("Reading from file...");
    fread(stht, sizeof(*stht), n, fp);

    for(i = 0; i < n; ++i){
        printf("\nStudent %zu\n", i + 1);
        printf("Name   : %s", stht[i].name);
        printf("Height : %u", stht[i].height);
        putchar('\n');
    }

    fclose(fp);
    return 0;
}
/* end of struct_file.c */

/* OUTPUT

Number of Students? 2

Student 1
Name   : Ankit Pati
Height : 170

Student 2
Name   : Tiashaa Chatterjee
Height : 168

Writing to file...
Reading from file...

Student 1
Name   : Ankit Pati
Height : 170

Student 2
Name   : Tiashaa Chatterjee
Height : 168

*/
