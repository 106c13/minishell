#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    const char *text = "Hello, clipboard!\n";
    FILE *pipe = popen("xclip -selection clipboard", "w");
    if (!pipe) {
        perror("popen");
        return 1;
    }
    fwrite(text, 1, strlen(text), pipe);
    pclose(pipe);
    return 0;
}

