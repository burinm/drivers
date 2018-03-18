/* x86_64_uart.c - (c) 2016 - burin */

#include "x86_64_uart.h"
#include "../mylib/util.h"

/* x86_64_uart.c
 *
 *  Code Modified from Linux Serial How To
 *   http://tldp.org/HOWTO/Serial-Programming-HOWTO/x115.html
 *
 * All source code in Linux Installation and Getting Started is
 *  placed under the *GNU* General Public License.
 * 
 * https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html
 */


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <strings.h>

#include <sys/time.h>

#define BAUDRATE B19200

#define MODEMDEVICE "/dev/ttyACM0"


//Interface, implementation 

static int uart_fd;
struct termios oldtio,newtio;
struct termios stdin_orig;

void uart_open() {
        
        uart_fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY ); 
        if (uart_fd <0) {
            LOG0("Error opening" MODEMDEVICE "\n");
        }
        
        tcgetattr(uart_fd,&oldtio); /* save current port settings */
        
        bzero(&newtio, sizeof(newtio));

        //raw mode - from man page: tcgetattr
        newtio.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
                           | INLCR | IGNCR | ICRNL | IXON);
        newtio.c_oflag &= ~OPOST;
        newtio.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
        newtio.c_cflag &= ~(CSIZE | PARENB);
        newtio.c_cflag |=  BAUDRATE | CS8; 
        
        /* set input mode (non-canonical, no echo,...) */
        newtio.c_lflag = 0;
         
        newtio.c_cc[VTIME]    = 0;   /* inter-character timer unused */
        newtio.c_cc[VMIN]     = 1;   /* blocking read until 1 chars received */
        
        tcflush(uart_fd, TCIFLUSH);
        tcflush(uart_fd, TCIOFLUSH);
        tcsetattr(uart_fd,TCSANOW,&newtio);
}

void stdin_canonical() {
    struct termios t;
    bzero(&t,sizeof(t));
    tcgetattr(STDIN_FILENO,&stdin_orig);
    t=stdin_orig;
    t.c_lflag &= ~(ICANON | ECHO);
//    t.c_lflag &= ~(ICANON);
    t.c_cc[VTIME] = 0;
    t.c_cc[VMIN] = 1;
    tcsetattr(STDIN_FILENO,TCSANOW,&t);
}

void stdin_restore() {
    tcsetattr(STDIN_FILENO,TCSANOW,&stdin_orig);
}

void uart_close() {
    tcsetattr(uart_fd,TCSANOW,&oldtio);
    close(uart_fd);
}

void uart_send_byte(uint8_t b) {
    struct timespec t;
    t.tv_sec=0;
    t.tv_nsec=70000;
    nanosleep(&t,NULL); 
    write(uart_fd, &b,1);
}

uint8_t uart_get_byte() {
uint8_t b=0;
    read(uart_fd,&b,1);

return b;
}

//Mine
uint8_t getchar_blocking() {
uint8_t b=0;
        read(STDIN_FILENO,&b,1);
//    tcflush(uart_fd, TCIFLUSH);
return b;

}

uint8_t putchar2(uint8_t b) {
        write(uart_fd, &b,1);
return b;

}


void uart_flush_rx() {
    tcflush(uart_fd, TCIFLUSH);
}

void uart_flush_tx() {
    tcflush(uart_fd, TCOFLUSH);
}
