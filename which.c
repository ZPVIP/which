// source from: http://stackoverflow.com/a/3454538
#include <io.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char *extensions[] = { "com", "exe", "bat", "cmd", NULL };

int is_exe(char *ext) {

    int i;

    for ( i = 0; extensions[i]; i++)
        if ( 0 == stricmp(ext, extensions[i] ) )
            return 1;
    return 0;
}

void print_path(char *buffer) {
    time_t t;
    time(&t);
    srand((unsigned int)t);
    switch (rand() % 6) {
        case 0: printf("\n\n |  | |__| | /  ` |__|\n |/\\| |  | | \\__, |  |\n\n\n%s\n\n", buffer);break;
        case 1: printf("\n\n \\    / |_  o  _ |_ \n  \\/\\/  | | | (_ | |\n\n\n%s\n\n", buffer);break;
        case 2: printf("\n\n   _       _  _                _ \n  ( )  _  ( )( )     _        ( )\n  | | ( ) | || |__  (_)   ___ | |__\n  | | | | | ||  _ `\\| | /'___)|  _ `\\\n  | (_/ \\_) || | | || |( (___ | | | |\n  `\\___x___/'(_) (_)(_)`\\____)(_) (_)\n\n\n%s\n\n", buffer);break;
        case 3: printf("\n\n        .__    .__       .__ \n__  _  _|  |__ |__| ____ |  |__\n\\ \\/ \\/ /  |  \\|  |/ ___\\|  |  \\\n \\     /|   Y  \\  \\  \\___|   Y  \\\n  \\/\\_/ |___|  /__|\\___  >___|  /\n             \\/        \\/     \\/\n\n\n%s\n\n", buffer);break;
        case 4: printf("\n\n __          ___     _      _ \n \\ \\        / / |   (_)    | |\n  \\ \\  /\\  / /| |__  _  ___| |__ \n   \\ \\/  \\/ / | '_ \\| |/ __| '_ \\ \n    \\  /\\  /  | | | | | (__| | | |\n     \\/  \\/   |_| |_|_|\\___|_| |_|\n\n\n%s\n\n", buffer);break;
        case 5: printf("\n\n _    _ _     _      _ \n| |  | | |   (_)    | |\n| |  | | |__  _  ___| |__\n| |/\\| | '_ \\| |/ __| '_ \\ \n\\  /\\  / | | | | (__| | | |\n \\/  \\/|_| |_|_|\\___|_| |_|\n\n\n%s\n\n", buffer);break;
    }

}

int main(int argc, char **argv) {

    char path[FILENAME_MAX];
    char buffer[FILENAME_MAX];
    char *path_var;
    char *ext;
    char *dir;
    int i;

    if (argc != 2) { 
        fprintf(stderr, "Usage: which <filename>\n");
        return 1;
    }

/* First try to find file name as-is.
 */
    if ( 0 == access(argv[1], 0)) {
        print_path(argv[1]);
        return 0;
    }

/* Okay, it wasn't found.  See if it had an extension, and if not, try
 * adding the usual ones...
 */

    ext = strrchr(argv[1], '.' );

    if ( 0 == ext++ || !is_exe(ext) ) {
        for ( i = 0; extensions[i]; i++) {

            sprintf(buffer, "%s.%s", argv[1], extensions[i]);

            if ( 0 == access(buffer, 0)) {
                print_path(buffer);
                return 0;
            }
        }

        if ( NULL == (path_var=getenv("PATH")))
            return 1;

        dir = strtok(path_var, ";");
        do {
            for ( i = 0; extensions[i]; i++) {

                sprintf(buffer, "%s\\%s.%s", dir, argv[1], extensions[i]);

                if ( 0 == access( buffer, 0)) {
                    print_path(buffer);
                    return 0;
                }
            }
        } while ( NULL != ( dir = strtok(NULL, ";")));
    }

    else {
        if ( NULL == (path_var=getenv("PATH")))
            return 1;

        dir = strtok(path_var, ";");
        do {
            sprintf(buffer, "%s\\%s", dir, argv[1]);

            if ( 0 == access( buffer, 0)) {
                print_path(buffer);
                return 0;
            }
        } while ( NULL != ( dir = strtok(NULL, ";")));
    }
    return 1;
}
