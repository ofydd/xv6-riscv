#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"


#define DIRSIZ 14

//Code copied from ls.c
char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}


void find(char* path, char* file_name){
    char buf[512], *p;
    int fd;

    struct dirent de;
    struct stat st;
    
    fd = open(path, 0);
    char ok = fstat(fd, &st);

    if(ok >= 0){
        switch(st.type){
        case T_DIR:
            strcpy(buf, path);
            p = buf+strlen(buf);
            *p++ = '/';

            while(read(fd, &de, sizeof(de)) == sizeof(de)){
                char* current_file_name = de.name;

                if(de.inum == 0)
                    continue;

                memmove(p, de.name, DIRSIZ);
                p[DIRSIZ] = 0;
                
                //Cannot get file metadata:
                if(stat(buf, &st) < 0){
                    printf("ls: cannot stat %s\n", buf);
                    continue;
                }

                //In order to prevent recursive calls into ./ or ../
                if((strcmp(current_file_name, ".") == 0 ) || (strcmp(current_file_name, "..") == 0)){   
                    continue;
                }

                if(strcmp(current_file_name, file_name) == 0){
                        printf("%s\n", buf);
                }

                if(st.type == T_DIR){
                    find(buf, file_name);
                }
            }
            break;
        }
    }
    
    
}

int main(int argc, char* argv[]){
    if(argc < 2){
        printf("No argv provided");
    }
    else if(argc == 2){
        find(".", argv[1]);
    }
    else{
        find(argv[1], argv[2]);
    }
}