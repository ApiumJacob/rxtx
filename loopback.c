// Code derived from: https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp/
// C library headers

//char port_name[] = "/dev/ttySC2";
//char port_name[] = "/dev/ttyAMA0";
char port_name[] = "/dev/ttyUSB0";

#include "serial.h"

int main() {
  int serial_port = serial_open(port_name);
  
  // Allocate memory for read buffer, set size according to your needs
  unsigned char read_buf [512];
  unsigned int total_bytes = 0;
  int num_bytes = 0;

  // flush the buffer
  printf("flushing receive buffer...\n");
  do
  {
    num_bytes = read(serial_port, &read_buf, sizeof(read_buf));
  } while( num_bytes > 0 );


  // Write to serial port
  unsigned char msg[256];
  for(int i = 0; i < sizeof(msg); i++)
  {
    msg[i] = i;
    write(serial_port, &msg[i], 1);
    nanosleep((const struct timespec[]){{0, 5000000L}}, NULL);
    num_bytes = read(serial_port, &read_buf, sizeof(read_buf));

    for(int i = 0; i < num_bytes; i++)
    {
      if(total_bytes % 0x10 == 0)
      {
        printf("\nTotal read 0x%04x:", total_bytes);
      }

      printf("[%02x]", (unsigned int)(read_buf[i]));
      if(total_bytes != read_buf[i])
        printf("\nbyte %02x incorrect, found %02x\n", total_bytes, (unsigned int)(read_buf[i]));
      
      total_bytes++;
    }
  }
  
  // Normally you wouldn't do this memset() call, but since we will just receive
  // ASCII data for this example, we'll set everything to 0 so we can
  // call printf() easily.
  memset(&read_buf, '\0', sizeof(read_buf));

  // Read bytes. The behaviour of read() (e.g. does it block?,
  // how long does it block for?) depends on the configuration
  // settings above, specifically VMIN and VTIME
  while( total_bytes < sizeof(msg) )
  {
    int num_bytes = read(serial_port, &read_buf, sizeof(read_buf));
    
    // n is the number of bytes read. n may be 0 if no bytes were received, and can also be -1 to signal an error.
    if (num_bytes < 0) {
        printf("Error reading: %s", strerror(errno));
        return 1;
    }

    // Here we assume we received ASCII data, but you might be sending raw bytes (in that case, don't try and
    // print it to the screen like this!)
    //printf("Total %i, Read %i bytes. Received message: %s\n", total_bytes, num_bytes, read_buf);
    for(int i = 0; i < num_bytes; i++)
    {
      if(total_bytes % 0x10 == 0)
      {
        printf("\nTotal read 0x%04x:", total_bytes);
      }

      printf("[%02x]", (unsigned int)(read_buf[i]));
      if(total_bytes != read_buf[i])
        printf("\nbyte %02x incorrect, found %02x\n", total_bytes, (unsigned int)(read_buf[i]));
      
      total_bytes++;
    }
  }
  printf("\n");
  printf("\nTotal bytes read %i.\n", total_bytes);

  serial_close(serial_port);
  return 0; // success
}

