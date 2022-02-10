// Code derived from: https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp/
// C library headers

//char port_name[] = "/dev/ttySC2";
//char port_name[] = "/dev/ttyAMA0";
char port_name[] = "/dev/ttyUSB0";

#include "serial.h"
const int packet_size = 256;

int main() {
  int serial_port = serial_open(port_name);
  

while(1)
{
  // Allocate memory for read buffer, set size according to your needs
  unsigned char read_buf [512];
  unsigned int total_bytes = 0;
  int num_bytes = 0;

  // flush the buffer
  printf("flushing receive buffer...\n");
  do
  {
    num_bytes = read(serial_port, &read_buf, sizeof(read_buf));
    total_bytes += num_bytes;
  } while( num_bytes > 0 );
  printf("\nTotal bytes flushed: %i.\n", total_bytes);
  total_bytes = 0;

  // Normally you wouldn't do this memset() call, but since we will just receive
  // ASCII data for this example, we'll set everything to 0 so we can
  // call printf() easily.
  memset(&read_buf, '\0', sizeof(read_buf));

  // Read bytes. The behaviour of read() (e.g. does it block?,
  // how long does it block for?) depends on the configuration
  // settings above, specifically VMIN and VTIME
  int expected_byte = 0;
  while( total_bytes < packet_size && expected_byte != 0x100 )
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
//      while(( total_bytes != read_buf[i]) && total_bytes < packet_size)
//      {
//        if(total_bytes % 0x10 == 0)
//          printf("\nTotal read 0x%04x:", total_bytes);
//        printf("{%02x}", (unsigned int)(read_buf[i]));
//        total_bytes++;
//      }
      if(total_bytes % 0x10 == 0)
        printf("\nTotal read 0x%04x:", total_bytes);

      if( expected_byte != read_buf[i] )
      {
        printf("{%02x}", (unsigned int)(read_buf[i]));
        //expected_byte = read_buf[i];
      }
      else
        printf(" %02x ", (unsigned int)(read_buf[i]));
      
      expected_byte++;
      total_bytes++;
    }
  }
  printf("\n");
  printf("\nTotal bytes received: %i.\n", total_bytes);
}
  serial_close(serial_port);
  return 0; // success
}

