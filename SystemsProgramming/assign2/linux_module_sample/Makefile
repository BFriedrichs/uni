obj-m  := module_test.o

KDIR   := /lib/modules/$(shell uname -r)/build
PWD    := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	rm Module.symvers  module_test.ko  module_test.mod.c  module_test.mod.o  module_test.o  modules.order
