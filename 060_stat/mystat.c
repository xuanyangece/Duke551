#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

// function: print data in step 1
void printStat1(const char * filename, struct stat * buffer) {
  if (buffer == NULL) {
    perror("NULL buffer!");
    exit(EXIT_FAILURE);
  }

  // step 7 revised
  if (S_ISLNK(buffer->st_mode)) {
    char linktarget[256];
    ssize_t len = readlink(filename, linktarget, 256);
    linktarget[len] = '\0';

    printf("  File: %s -> %s\n", filename, linktarget);
  }
  else {
    printf("  File: %s\n", filename);
  }

  const char * desc_file_type = NULL;
  switch (buffer->st_mode & S_IFMT) {
    case S_IFBLK:
      desc_file_type = "block special file";
      break;
    case S_IFCHR:
      desc_file_type = "character special file";
      break;
    case S_IFDIR:
      desc_file_type = "directory";
      break;
    case S_IFIFO:
      desc_file_type = "fifo";
      break;
    case S_IFLNK:
      desc_file_type = "symbolic link";
      break;
    case S_IFREG:
      desc_file_type = "regular file";
      break;
    case S_IFSOCK:
      desc_file_type = "socket";
      break;
    default:
      desc_file_type = "unknown";
      break;
  }
  printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",
         buffer->st_size,
         buffer->st_blocks,
         buffer->st_blksize,
         desc_file_type);

  // step 6: check Device property
  if (S_ISCHR(buffer->st_mode) || S_ISBLK(buffer->st_mode)) {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %d,%d\n",
           buffer->st_dev,
           buffer->st_dev,
           buffer->st_ino,
           buffer->st_nlink,
           major(buffer->st_rdev),
           minor(buffer->st_rdev));
  }
  else {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
           buffer->st_dev,
           buffer->st_dev,
           buffer->st_ino,
           buffer->st_nlink);
  }
}

// help set character in step 2
char stat2Helper(struct stat * buffer, mode_t input, char output) {
  if ((buffer->st_mode & input) != 0) {
    return output;
  }
  else {
    return '-';
  }
}

// function: print Access data in step 2 & 3
void printStat2(struct stat * buffer) {
  if (buffer == NULL) {
    perror("NULL buffer!");
    exit(EXIT_FAILURE);
  }

  // make up the readable description - 10 characters
  char desc[11] = {' '};
  desc[10] = '\0';
  // design each character in order
  switch (buffer->st_mode & S_IFMT) {
    case S_IFBLK:
      desc[0] = 'b';
      break;
    case S_IFCHR:
      desc[0] = 'c';
      break;
    case S_IFDIR:
      desc[0] = 'd';
      break;
    case S_IFIFO:
      desc[0] = 'p';
      break;
    case S_IFLNK:
      desc[0] = 'l';
      break;
    case S_IFREG:
      desc[0] = '-';
      break;
    case S_IFSOCK:
      desc[0] = 's';
      break;
    default:
      desc[0] = 'X';
      break;
  }

  desc[1] = stat2Helper(buffer, S_IRUSR, 'r');
  desc[2] = stat2Helper(buffer, S_IWUSR, 'w');
  desc[3] = stat2Helper(buffer, S_IXUSR, 'x');
  desc[4] = stat2Helper(buffer, S_IRGRP, 'r');
  desc[5] = stat2Helper(buffer, S_IWGRP, 'w');
  desc[6] = stat2Helper(buffer, S_IXGRP, 'x');
  desc[7] = stat2Helper(buffer, S_IROTH, 'r');
  desc[8] = stat2Helper(buffer, S_IWOTH, 'w');
  desc[9] = stat2Helper(buffer, S_IXOTH, 'x');

  //get user and group id&name
  const char * name1 = getpwuid(buffer->st_uid)->pw_name;
  const char * name2 = getgrgid(buffer->st_gid)->gr_name;

  printf("Access: (%04o/%s)  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",
         buffer->st_mode & ~S_IFMT,
         desc,
         buffer->st_uid,
         name1,
         buffer->st_gid,
         name2);
}

//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t = localtime(when);
  strftime(temp1, 512, "%Y-%m-%d %H:%M:%S", t);
  strftime(temp2, 32, "%z", t);
  snprintf(ans, 128, "%s.%09ld %s", temp1, ns, temp2);
  return ans;
}

// function: print time data in step 4
void printStat4(struct stat * buffer) {
  char * timeA = time2str(&buffer->st_atime, buffer->st_atim.tv_nsec);
  char * timeM = time2str(&buffer->st_mtime, buffer->st_mtim.tv_nsec);
  char * timeC = time2str(&buffer->st_ctime, buffer->st_ctim.tv_nsec);

  printf("Access: %s\n", timeA);
  printf("Modify: %s\n", timeM);
  printf("Change: %s\n", timeC);
  printf(" Birth: -\n");
  free(timeA);
  free(timeM);
  free(timeC);
}

int main(int argc, char ** argv) {
  // accept command line argument
  if (argc < 2 || argv == NULL) {
    perror("Invalid command line arg");
    exit(EXIT_FAILURE);
  }

  for (int i = 1; i < argc; i++) {
    // step 1: get the data from first 3 lines;
    struct stat buffer;  // uninitialized

    lstat(argv[i], &buffer);
    printStat1(argv[i], &buffer);

    // step 2&3
    printStat2(&buffer);

    // step 4
    printStat4(&buffer);
  }

  return EXIT_SUCCESS;
}
