#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

struct stat stat1, stat2;
struct tm time1, time2;  // 구조체 자체로 선언해서 localtime 덮어쓰기 방지

void filestat1();
void filestat2();
void filetime1();
void filetime2();
void sizecmp();
void blockcmp();
void datecmp();
void timecmp();

int main() {
  filestat1();
  filestat2();
  filetime1();
  filetime2();
  sizecmp();
  blockcmp();
  datecmp();
  timecmp();

  return 0;
}

//파일 1의 정보를 가져오는 함수 작성
void filestat1(){
    if (stat("text1", &stat1) == -1){
        printf("text1 stat error!\n");
        exit(1);
    }
}

//파일 2의 정보를 가져오는 함수 작성
void filestat2(){
    if (stat("text2", &stat2) == -1){
        printf("text2 stat error!\n");
        exit(1);
    }
}

//파일 1의 시간 정보를 가져오는 함수 작성
void filetime1(){
    struct tm *tmp = localtime(&stat1.st_mtime);
    if (tmp == NULL) { printf("localtime error\n"); exit(1); }
    
    time1 = *tmp;
}

//파일 2의 시간 정보를 가져오는 함수 작성
void filetime2(){
    struct tm *tmp = localtime(&stat2.st_mtime);
    if (tmp == NULL) { printf("localtime error\n"); exit(1); }
    
    time2 = *tmp;
}

// 두 개의 파일 크기를 비교하는 함수 작성
void sizecmp() {
    printf("size compare\n");
    if (stat1.st_size > stat2.st_size) {
        printf("text1 is bigger\n");
    }
    else if (stat1.st_size < stat2.st_size) {
        printf("text2 is bigger\n");
    }
    else {
        printf("sizes are equal\n");
    }
    printf("\n");
}

// 두 개의 파일 블락 수를 비교하는 함수 작성
void blockcmp() {
    printf("block compare\n");
    if (stat1.st_blocks > stat2.st_blocks) {
        printf("text1 is bigger\n");
    }
    else if (stat1.st_blocks < stat2.st_blocks) {
        printf("text2 is bigger\n");
    }
    else {
        printf("sizes are equal\n");
    }
    printf("\n");
}

// 두 개의 파일 수정 날짜를 비교하는 함수 작성
void datecmp() {
    printf("date compare\n");
    if (time1.tm_year > time2.tm_year)
        printf("text2 is early\n\n");
    else if (time1.tm_year < time2.tm_year)
        printf("text1 is early\n\n");
    else {
        if (time1.tm_mon > time2.tm_mon)
            printf("text2 is early\n\n");
        else if (time1.tm_mon < time2.tm_mon)
            printf("text1 is early\n\n");
        else {
            if (time1.tm_mday > time2.tm_mday)
                printf("text2 is early\n\n");
            else if (time1.tm_mday < time2.tm_mday)
                printf("text1 is early\n\n");
            else
                printf("same date\n\n");
        }
    }
}

//두 개의 파일 수정 시간을 비교하는 함수 작성
void timecmp(){
    printf("time compare\n");

    if (time1.tm_hour == time2.tm_hour && time1.tm_min == time2.tm_min) {
        printf("same time\n\n");
    } else if (
        time1.tm_hour < time2.tm_hour ||
        (time1.tm_hour == time2.tm_hour && time1.tm_min < time2.tm_min)
    ) {
        printf("text1 is early\n\n");
    } else {
        printf("text2 is early\n\n");
    }
}
