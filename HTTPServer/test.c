#include <time.h>
#include <string.h>
#define PORT 8080

int main() {
    time_t raw_time; 
    struct tm* time_info; //localtime returns this data type struct

    time(&raw_time);
    time_info = localtime(&raw_time);

    char* time_str = asctime(time_info);

    printf("Current local time: %s", time_str);

    return 0;
}