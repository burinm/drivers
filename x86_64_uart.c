#include "x86_64_uart.h"
#include "util.h"

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

#define BAUDRATE B19200
#define MODEMDEVICE "/dev/ttyACM0"

//Interface, implementation 

static int uart_fd;
struct termios oldtio,newtio;

void uart_open() {
        
        uart_fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY ); 
        if (uart_fd <0) {
            LOG0("Error opening" MODEMDEVICE "\n");
        }
        
        tcgetattr(uart_fd,&oldtio); /* save current port settings */
        
        bzero(&newtio, sizeof(newtio));
        newtio.c_cflag = BAUDRATE |  CS8 | CLOCAL | CREAD;
        newtio.c_iflag = IGNPAR;
        newtio.c_oflag = 0;
        
        /* set input mode (non-canonical, no echo,...) */
        newtio.c_lflag = 0;
         
        newtio.c_cc[VTIME]    = 0;   /* inter-character timer unused */
        newtio.c_cc[VMIN]     = 1;   /* blocking read until 1 chars received */
        
        tcflush(uart_fd, TCIFLUSH);
        tcsetattr(uart_fd,TCSANOW,&newtio);

}

void uart_close() {
    tcsetattr(uart_fd,TCSANOW,&oldtio);
    close(uart_fd);
}

void uart_send_byte(uint8_t b) {
    write(uart_fd, &b,1);
}

uint8_t uart_get_byte() {
uint8_t b=0;
uint8_t err=0;
err = read(uart_fd,&b,1);

return b;
}


