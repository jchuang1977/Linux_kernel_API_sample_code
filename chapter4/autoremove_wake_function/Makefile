ifneq ($(KERNELRELEASE),)
obj-m += autoremove_wake_function.o 
else
PWD  := $(shell pwd)
KVER ?= $(shell uname -r)
KDIR := /lib/modules/$(KVER)/build
all:
	$(MAKE) -C $(KDIR) M=$(PWD) 
clean:
	rm -rf  *.o *.mod.c *.ko *.symvers *~ *.order *.markers
endif
