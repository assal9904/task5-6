#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void get_files(const char *dirname){
    struct dirent *entry;
    DIR *dir = opendir(dirname);

    if (dir == NULL){
        printf("invalid directory");
        return;
    }

    printf("\n%s:\n", dirname);
    while((entry = readdir(dir)) != NULL){
        if (entry -> d_name[0] != '.'){
            printf("%s\n", entry->d_name);
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]){
    char dirname[1024];
    if (argc < 2) {
        printf("Enter directory name: ");
        fgets(dirname, sizeof(dirname), stdin);
        dirname[strcspn(dirname, "\n")] = 0;
        get_files(dirname);
    } else {
        for (int i = 1; i < argc; i++) {
            get_files(argv[i]); 
        }
    }
    return 0;
}