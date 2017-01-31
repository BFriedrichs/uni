#include <stdio.h>
#include <stdlib.h>

#include "libusb-1.0/libusb.h"

#define V_ID 0x04d8
#define P_ID 0x020c

int main(int argc, char *argv[]) {
  int r;
  libusb_context *context;
  libusb_device_handle *device_handle;

	if (libusb_init(&context) < 0) {
      perror("cant init");
      exit(1);
  }

  device_handle = libusb_open_device_with_vid_pid(context, V_ID, P_ID);
  if(device_handle == NULL) {
    perror("can't open");
    exit(1);
  }

  int transferred = 0;

  char my_data[1];
  my_data[0] = 0x01;
  int x = libusb_bulk_transfer(device_handle, 0x02, my_data, sizeof(my_data), &transferred, 0);
  /*
  if( == 0) {
    printf("sent %i\n", transferred);
  } else {
    perror("can't transfer");
    exit(1);
  }
  */

  printf("%i\n", x);


	libusb_exit(context);
	return 0;
}
