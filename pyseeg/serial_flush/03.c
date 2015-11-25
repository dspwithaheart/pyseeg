#include "lib.h"

int fd;

int initport(int fd) {
    struct termios options;
    // Get the current options for the port...
    tcgetattr(fd, &options);
    // Set the baud rates to 19200...
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);
    // Enable the receiver and set local mode...
    options.c_cflag |= (CLOCAL | CREAD);

    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;

    // Set the new options for the port...
    tcsetattr(fd, TCSANOW, &options);
    return 1;
}

int main(int argc, char **argv) {

    fd = open("/dev/pts/2", O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        perror("open_port: Unable to open /dev/pts/1 - ");
        return 1;
    } else {
        fcntl(fd, F_SETFL, 0);
    }

    printf("baud=%d\n", getbaud(fd));
    initport(fd);
    printf("baud=%d\n", getbaud(fd));

    char sCmd[254];
    sCmd[0] = 0x41;
    sCmd[1] = 0x42;
    sCmd[2] = 0x43;
    sCmd[3] = 0x00;

    if (!writeport(fd, sCmd)) {
        printf("write failed\n");
        close(fd);
        return 1;
    }

    printf("written:%s\n", sCmd);

    usleep(500000);
    char sResult[254];
    fcntl(fd, F_SETFL, FNDELAY); 

    if (!readport(fd,sResult)) {
        printf("read failed\n");
        close(fd);
        return 1;
    }
    printf("readport=%s\n", sResult);
    close(fd);
    return 0;
}

