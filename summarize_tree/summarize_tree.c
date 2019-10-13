#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

static int num_dirs, num_regular;

bool is_dir(const char* path) {
     struct stat buf;  // checks if the path is a directory
     if(stat(path, &buf) == 0)  //stat return zero if path is a path
      { if(S_ISDIR(buf.st_mode)) {
         return true;
       }
        else {
          return false;
          }
      }
     else{
       return false;
     }
      }


void process_path(const char*);

   
void process_directory(const char* path) {

    num_dirs++; s
    struct dirent *cur_dir;
    DIR *dir;
    int errnum; 
    if((dir = opendir(path))==NULL){ 
      errnum = errno;
      printf("Error opening directory: %s, the directory name: %s\n", strerror(errnum), path);
      exit(1);
    }
    if(chdir(path)==-1){ 
      errnum = errno;
      printf("Error changing directory: %s, the directory name: %s\n", strerror(errnum), path);
      exit(1);
    }
    while((cur_dir = readdir(dir))!=NULL){ 

      
      if((strcmp((cur_dir->d_name),"..")==0)||(strcmp((cur_dir->d_name),".")==0)){
        continue;
      }

      process_path(cur_dir->d_name);
    }
    if(chdir("..")==-1){ 
      errnum = errno;
      printf("Error changing directory: %s, the directory name: %s\n", strerror(errnum), "..");
      exit(1);
    }

    if(closedir(dir)==-1){ 
      errnum = errno;
      printf("Error closing directory: %s, the directory name: %s\n", strerror(errnum), path);
      exit(1);
    }
  }

void process_file(const char* path) {
   num_regular++;  //Update the number of regular files.
}

void process_path(const char* path) {
    if (is_dir(path)) {
        process_directory(path);
    } else {
        process_file(path);
    }
}

int main (int argc, char *argv[]) {
    // Ensure an argument was provided.
    if (argc != 2) {
        printf ("Usage: %s <path>\n", argv[0]);
        printf ("       where <path> is the file or root of the tree you want to summarize.\n");
        return 1;
    }

    num_dirs = 0;
    num_regular = 0;

    process_path(argv[1]);

    printf("There were %d directories.\n", num_dirs);
    printf("There were %d regular files.\n", num_regular);

    return 0;
}
