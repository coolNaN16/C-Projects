#include <stdio.h>
#include <string.h>
#include <dirent.h>

long int totaldir = 0;
long int totalfile = 0;

void print_file(const char *file, int is_dir, int indent) {
    printf("%*c", indent * 4, " ");
    if (is_dir) {
        printf("\e[0;36m▶ %s\n", file);
    } else {
        printf("\e[0;37m▹ %s\n", file);
    }
}

int walk(const char *path, int indent, const char* query, int is_checking) {
    int totalquery = 0;
    int totaldirect = 0;

    DIR *dir = opendir(path);
    struct dirent *dp;
    while ((dp = readdir(dir)) != NULL) {
        const char *dirname = dp->d_name;

        if (strcmp(dirname, ".") == 0 || strcmp(dirname, "..") == 0) {
            continue;
        }

        size_t len = strlen(path) + strlen(dirname) + 2;
        char sub_path[len];
        snprintf(sub_path, len, "%s/%s", path, dirname);

        if (dp->d_type == DT_DIR) { 
            // is a directory
            
            if (strcmp(query, "") == 0) {
                print_file(dirname, 1, indent);
                walk(sub_path, indent + 1, query, 0);
                totaldir++;                
            } else {
                print_file(dirname, 1, indent);
                int foundquery = walk(sub_path, indent + 1, query, 1);
                if (foundquery > 0) {
                    // print_file(dirname, 1, indent);
                    walk(sub_path, indent + 1, query, 0);
                    if (is_checking == 0) {
                        totaldir++;
                    }
                    
                    // totalquery++;
                }
            }
        } else {
            // is a file

            if (strcmp(query, "") == 0) {
                print_file(dirname, 0, indent);
                totalfile++;
            } else {
                if (strstr(dirname, query) != NULL) {
                    // printf("File: %s, Query: %s\n", dirname, query);
                    if (is_checking == 0) {
                        print_file(dirname, 0, indent);
                        totalfile++;
                    } else {
                       totalquery++; 
                       break;
                    }
                }
            }
        }
        
    }
    closedir(dir);

    return totalquery;
}

int main(int argc, char **argv) {
    const char *path = ".";
    const char *query = "";
    if (argc > 1) {
        path = argv[1];
    } 
    if (argc > 2) {
        query = argv[2];
    }

    // printf("\nargv[2]: %s\n", argv[2]);
    // printf("Path: %s\n", path);

    int err = walk(path, 0, query, 0);
    char totdir[64];
    snprintf(totdir, sizeof(totaldir), "%d", totaldir);

    char totfile[64];
    snprintf(totfile, sizeof(totaldir), "%d", totalfile);

    printf("\n%s directories, %s files\n", totdir, totfile);

    return err;
}