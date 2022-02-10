// Code derived from: https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp/
// C library headers

char port_name[] = "/dev/ttySC2";
//char port_name[] = "/dev/ttyAMA0";
//char port_name[] = "/dev/ttyUSB0";

#include "serial.h"

const int packet_size = 256;

int main() {
  int serial_port = serial_open(port_name);
  
  // Allocate memory for read buffer, set size according to your needs
  unsigned int total_bytes = 0;
  int num_bytes = 0;

  // Write to serial port
  unsigned char msg[1];
  for(int i = 0; i < packet_size; i++)
  {
    if(total_bytes % 0x10 == 0)
    printf("\nTotal written 0x%04x:", total_bytes);

    msg[0] = i & 0xff;
    write(serial_port, &msg, sizeof(msg));
    printf("[%02x]", msg[0]);

    //nanosleep((const struct timespec[]){{0, 2000000L}}, NULL);
    total_bytes++;
  }
  
  printf("\n");
  printf("\nTotal bytes transmitted: %i.\n", total_bytes);

  serial_close(serial_port);
  return 0; // success
}

