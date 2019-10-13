#include <ftw.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>

 static int dirNumber, regularFileNum;
 static int callback(const char *fpath, const struct stat *sb, int typeflag) {
   if(typeflag == FTW_F) {
     regularFileNum++;
   }
   if(typeflag == FTW_D){
     dirNumber++;
   }

       return 0;

   
}

#define MAX_FTW_DEPTH 16



int main(int argc, char** argv) {
    // Check arguments and set things up
   if( argc !=2) {
     printf("Usage: %s <path>\n", argv[0]);
     return 1;
   }

    dirNumber = 0;
    regularFileNum=0;
    ftw(argv[1], callback, MAX_FTW_DEPTH);

    // Print out the results
       printf("There were %d directories.\n", dirNumber);
      printf("There were %d regular files.\n", regularFileNum);
     return 0;
}
