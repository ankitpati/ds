/* cpy.c */
/* Date  : 18 April 2016
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 4096

int main(int argc, char **argv)
{
    char buf[BUFFER];
    FILE *fin, *fout;

    if(argc != 3){
        fprintf(stderr, "Usage:\n\tcpy <source> <destination>\n");
        exit(1);
    }

    if(!strcmp(argv[1], argv[2])){
        fprintf(stderr, "Source and destination files cannot be same!\n");
        exit(2);
    }

    if(!(fin = fopen(argv[1], "rb")) || !(fout = fopen(argv[2], "wb"))){
        fprintf(stderr, "File(s) could not be opened!\n");
        exit(5);
    }

    while(!feof(fin)) fwrite(buf, 1, fread(buf, 1, BUFFER, fin), fout);

    fclose(fout);
    fclose(fin);
    return 0;
}
/* end of cpy.c */
