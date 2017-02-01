#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include "libusb-1.0/libusb.h"

#define V_ID 0x04d8
#define P_ID 0x020c

// 0x81, Remaining Entries, ID, flags, LengthServiceName, LengthOfPassword, ServiceName*, Password*
typedef struct Password {
  uint8_t x;
  uint8_t remaining;
  uint8_t id;
  uint8_t flags;
  uint8_t lengthService;
  uint8_t lengthPassword;
  uint8_t *serviceName;
  uint8_t *passwordName;
} password_t;

int main(int argc, char *argv[]) {

  int sflag = 0;
  int dflag = 0;
  char error[]  = "No parameters for password list or use -s <ID> <password> to change a password.\n";

  if(argc == 1) {
    dflag = 1;
  } else {
    int c = getopt(argc, argv, "s:");
    if(c == 's' && argc == 4) {
      dflag = sflag = 1;
    }
  }

  if(!dflag && !sflag) {
    printf("%s", error);
  }

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
  int x = 0;

  if(dflag) {
    char my_data[1];
    my_data[0] = 0x01;

    x = libusb_bulk_transfer(device_handle, 0x02, my_data, sizeof(my_data), &transferred, 0);

    int size = 1280;
    uint8_t *pwMeta = malloc(size);
    x = libusb_bulk_transfer(device_handle, 0x82, pwMeta, size, &transferred, 0);

    int entries = pwMeta[1] + 1;
    password_t password_list[entries];

    for(int i = 0; i < entries; i++) {
      int curr = 64 * i;

      memcpy(&password_list[i], &pwMeta[curr], 6);
      int serviceNameLength = pwMeta[curr + 4];
      int passwordNameLength = pwMeta[curr + 5];

      password_list[i].serviceName = malloc(serviceNameLength + 1);
      password_list[i].passwordName = malloc(passwordNameLength + 1);

      memcpy(password_list[i].serviceName, &pwMeta[curr + 6], serviceNameLength);
      memcpy(password_list[i].passwordName, &pwMeta[curr + 6 + serviceNameLength], passwordNameLength);
    }

    if(sflag) {
      int id = atoi(argv[2]);
      if(id < 0 || id > 19) {
        printf("id has to be in set of 0-19.");
        exit(1);
      }
      password_t *currPW = &password_list[id];

      int length = strlen(argv[3]);

      memset(currPW->passwordName, '\0', currPW->lengthPassword);
      memcpy(currPW->passwordName, argv[3], length);

      int size = 5 + currPW->lengthService + length;
      unsigned char *data = malloc(size);

      //0x02, ID, flags+, LengthOfServiceName, LengthOfPassword, ServiceName*, Password*
      data[0] = 0x02;
      data[1] = currPW->id;
      data[2] = 0;
      data[3] = currPW->lengthService;
      data[4] = length;
      memcpy(&data[5], currPW->serviceName, data[3]);
      memcpy(&data[5 + data[3]], currPW->passwordName, length);

      x = libusb_bulk_transfer(device_handle, 0x02, data, 64, &transferred, 0);
      printf("out: %i\n", x);
    }

    for(int i = 0; i < entries; i++) {
      printf("%i: %s\n", i, password_list[i].passwordName );
    }
  }

	libusb_exit(context);
	return 0;
}
