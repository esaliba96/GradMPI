#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef DEBUG
#define INITIAL_ALLOC 2
#else
#define INITIAL_ALLOC 512
#endif

char *
read_line(FILE *fin) {
    char *buffer;
    char *tmp;
    int read_chars = 0;
    int bufsize = INITIAL_ALLOC;
    char *line = malloc(bufsize);

    if ( !line ) {
        return NULL;
    }

    buffer = line;

    while ( fgets(buffer, bufsize - read_chars, fin) ) {
        read_chars = strlen(line);

        if ( line[read_chars - 1] == '\n' ) {
            line[read_chars - 1] = '\0';
            return line;
        }

        else {
            bufsize = 2 * bufsize;
            tmp = realloc(line, bufsize);
            if ( tmp ) {
                line = tmp;
                buffer = line + read_chars;
            }
            else {
                free(line);
                return NULL;
            }
        }
    }
    return NULL;
}

int
main(int argc, char *argv[]) {
    FILE *fin;
    char *line;

    if ( argc != 3 ) {
        return EXIT_FAILURE;
    }

    fin = fopen(argv[1], "r");

    if ( fin ) {
        while ( line = read_line(fin) ) {
            if ( strstr(line, argv[2]) ){
                printf("%s\n", argv[1]);
            }
            free(line);
        }
    }

    fclose(fin);
    return 0;
}
