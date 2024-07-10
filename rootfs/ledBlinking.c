#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int fd = -1;

#define         LED_PIN             "538"
#define         LED_DIRECTION       "OUT"
#define         LED_ON              "1"
#define         LED_OFF             "0"
#define         ONE_SECOND           1


void KeyboradInt()
{
    close(fd);
    fd = open("/sys/class/gpio/unexport",O_WRONLY);
    write(fd,LED_PIN,strlen(LED_PIN));
    close(fd);
    printf("Led APP closed");
    
    exit(0);
}

int main()
{

    signal(SIGINT,KeyboradInt);

    fd = open("/sys/class/gpio/export",O_WRONLY);

    if(fd == -1)
    {
        printf("Failed to open export file\n");
    }
    else
    {
       int r_byte = write(fd,LED_PIN,strlen(LED_PIN));
       if(r_byte == -1)
       {
            printf("failed to write\n");
       }
       close(fd);
    }

    sleep(ONE_SECOND);

    fd = open("/sys/class/gpio/gpio538/direction",O_WRONLY);

    if(fd == -1)
    {
        printf("Failed to open direction file\n");
    }
    else
    {
        write(fd,LED_DIRECTION,strlen(LED_DIRECTION));
        close(fd);
    }

    
    fd = open("/sys/class/gpio/gpio538/value",O_WRONLY);

    if(fd == -1)
    {
        printf("Failed to open value file\n");
    }


    while(fd != -1)
    {
        write(fd,LED_ON,strlen(LED_ON));
        sleep(ONE_SECOND);
        write(fd,LED_OFF,strlen(LED_OFF));
        sleep(ONE_SECOND);
    }
    return 0;
}