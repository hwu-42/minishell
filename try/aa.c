#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <arg1> <arg2>\n", argv[0]);
        return 1;
    }

    printf("Argument 1: %s\n", argv[1]);
    printf("Argument 2: %s\n", argv[2]);

    char input[100];
    if (fgets(input, sizeof(input), stdin) != NULL) {
        printf("Standard input: %s", input);
    }

    return 0;
}
