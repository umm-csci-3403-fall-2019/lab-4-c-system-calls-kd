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
     stat(path, &buf);
  	return S_ISDIR(buf.st_mode);  //retutn non-zero if the file is a directory


    /*
     * Use the stat() function (try "man 2 stat") to determine if the file
     * referenced by path is a directory or not. Call stat, and then use
     * S_ISDIR to see if the file is a directory. Make sure you check the
     * return value from stat in case there is a problem, e.g., maybe the
     * the file doesn't actually exist.
     *
     * You'll need to allocate memory for a buffer you pass to stat(); make
     * sure you free up that space before you return from this function or
     * you'll have a substantial memory leak (think of how many times this
     * will be called!).
     */

}

/*
 * This is necessary this because the multiple recursion means there's no way to
 * order them so that all the functions are defined before they're called.
 */
void process_path(const char*);


    /*
     * Update the number of directories seen, use opendir() to open the
     * directory, and then use readdir() to loop through the entries
     * and process them. You have to be careful not to process the
     * "." and ".." directory entries, or you'll end up spinning in
     * (infinite) loops. Also make sure you closedir() when you're done.
     *
     * You'll also want to use chdir() to move into this new directory,
     * with a matching call to chdir() to move back out of it when you're
     * done.
     */
void process_directory(const char* path) {
  /*
   * Update the number of directories seen, use opendir() to open the
   * directory, and then use readdir() to loop through the entries
   * and process them. You have to be careful not to process the
   * "." and ".." directory entries, or you'll end up spinning in
   * (infinite) loops. Also make sure you closedir() when you're done.
   *
   * You'll also want to use chdir() to move into this new directory,
   * with a matching call to chdir() to move back out of it when you're
   * done.
   */
    num_dirs++; //update the number of directories
    struct dirent *cur_dir;
    DIR *dir;
    int errnum; //this int will be used to store the errno value for error messages
    if((dir = opendir(path))==NULL){  //open the directory and checks for error
      errnum = errno;
      printf("Error opening directory: %s, the directory name: %s\n", strerror(errnum), path);
      exit(1);
    }
    if(chdir(path)==-1){ //go to this directory and checks for error
      errnum = errno;
      printf("Error changing directory: %s, the directory name: %s\n", strerror(errnum), path);
      exit(1);
    }
    while((cur_dir = readdir(dir))!=NULL){ //loop through the entries in the directory

      // skip if the entries are ".." or "."
      if((strcmp((cur_dir->d_name),"..")==0)||(strcmp((cur_dir->d_name),".")==0)){
        continue;
      }

      //recursive call to check the entry
      process_path(cur_dir->d_name);

    }

    if(chdir("..")==-1){ //go to the parent directory and checks for error
      errnum = errno;
      printf("Error changing directory: %s, the directory name: %s\n", strerror(errnum), "..");
      exit(1);
    }

    if(closedir(dir)==-1){ //closes directory and checks for error
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
    if (argc = 2) {
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
