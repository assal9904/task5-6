#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void direct_handling(const char *path, int bin_width, int *bins, int max_bins){
    struct dirent *entry;
    struct stat file_stat;
    char full_path[1024];

    DIR *dir = opendir(path);
     while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry ->d_name, ".") == 0 || strcmp(entry -> d_name, "..") == 0)
        continue;

        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry -> d_name);

        if (stat(full_path , &file_stat) == 0){
            if (S_ISDIR(file_stat.st_mode)){
                direct_handling(full_path, bin_width, bins, max_bins);
            } else if (S_ISREG(file_stat.st_mode)){
                int bin_index = file_stat.st_size / bin_width;
                if (bin_index < 100){
                    bins[bin_index] ++;
                }
            }
        }
     }
     closedir(dir);
     
}

int main() {
    char directory[1024];
    int bin_width;
    printf("enter directory to search: ");
    fgets(directory, sizeof(directory), stdin);
    directory[strcspn(directory, "\n")] = 0;

    printf ("enter bin width in bytes: ");
    scanf("%d", &bin_width);
    int bins[100] = {0};
    direct_handling(directory, bin_width, bins, 100);

    for (int i = 0; i < 100; i++) {
        if (bins[i] > 0) {
            printf("%d - %d: ", i * bin_width, (i + 1) * bin_width - 1);
            for (int j = 0; j < bins[i]; j++)
                printf("#");
            printf(" (%d files)\n", bins[i]);
        }
    }
}