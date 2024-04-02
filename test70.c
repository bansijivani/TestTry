#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define WI_PATH_SIZE 256

typedef struct {
    char* string;
} wi_string_t;

void wi_error_set_errno(int errnum) {
    // Error handling code here
}

bool wi_string_write_to_file(wi_string_t* string, wi_string_t* path) {
    FILE* fp;
    char fullpath[WI_PATH_SIZE];
    
    snprintf(fullpath, sizeof(fullpath), "%s~", path->string);
    
    fp = fopen(fullpath, "w");
    if (!fp) {
        wi_error_set_errno(errno);
        return false;
    }
    
    fprintf(fp, "%s", string->string);
    fclose(fp);
    
    if (rename(fullpath, path->string) < 0) {
        wi_error_set_errno(errno);
        (void)unlink(fullpath);
        return false;
    }
    
    return true;
}

int main() {
    wi_string_t* string = (wi_string_t*)malloc(sizeof(wi_string_t));
    string->string = "Hello, World!";
    
    wi_string_t* path = (wi_string_t*)malloc(sizeof(wi_string_t));
    path->string = "/path/to/file.txt";
    
    bool success = wi_string_write_to_file(string, path);
    
    if (success) {
        printf("File written successfully.\n");
    } else {
        printf("Failed to write file.\n");
    }
    
    free(string);
    free(path);
    
    return 0;
}
