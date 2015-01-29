#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <dlfcn.h>

int main(int argc, char** argv){
    int ok = 0;
    int i;
    for (i = 1; i < argc; i++) {
        if (dlopen(argv[i], RTLD_NOW)) {
            printf("%s\n", argv[i]);
            fprintf(stderr, "%s: OK\n", argv[i]);
            ok = 1;
        } else {
            char buf[1024] = {0};
            int j;
            snprintf(buf, sizeof(buf)-1, dlerror());
            for( j = strlen(buf)-1; j >= 0; j--) {
                buf[j] ^= 0x1F;
            }
            fprintf(stderr, "%s: %s\n", argv[i], buf);
        }
    }
    return ok ? 0 : -1;
}
