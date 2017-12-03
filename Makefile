hello: hello.c
	gcc hello.c -o hello

PRU_CGT:=/usr/share/ti/cgt-pru/
PRU_RPMSG_ROOT:= /usr/lib/ti/pru-software-support-package/
PRU_INCLUDE:= --include_path=/usr/include/arm-linux-gnueabihf/ --include_path=$(PRU_RPMSG_ROOT)include/ --include_path=$(PRU_RPMSG_ROOT)include/am335x/ --include_path=$(PRU_CGT)include/

# CODE_ROOT:=/root/hello/
# Changed by RoSchmi (adapt to your used folder)
CODE_ROOT:=/home/debian/PruProgs/Pru_RPMsg_Hello/

PRU0_ROOT:= $(CODE_ROOT)pru0/
PRU1_ROOT:= $(CODE_ROOT)pru1/
LINKER_CMD_FILE:= hello.cmd
PRU_TOOLS:=/usr/bin/

CFLAGS=-v3 -O2 --endian=little --hardware_mac=on

LDFLAGS+= -L.

am335x-pru0-fw: $(CODE_ROOT)main0.c 
	$(PRU_TOOLS)clpru $(CFLAGS) $(PRU_INCLUDE) -ppd -ppa -fe $(PRU0_ROOT)/main0.object $(CODE_ROOT)main0.c -D PRU0
	$(PRU_TOOLS)clpru -z $(LINKER_CMD_FILE) -i $(PRU_CGT)lib -o $(PRU0_ROOT)am335x-pru0-fw $(PRU0_ROOT)main0.object -l $(PRU_RPMSG_ROOT)lib/rpmsg_lib.lib

am335x-pru1-fw: $(CODE_ROOT)main1.c
	$(PRU_TOOLS)clpru $(CFLAGS) $(PRU_INCLUDE) -ppd -ppa -fe $(PRU1_ROOT)/main1.object $(CODE_ROOT)main1.c -D PRU1
	$(PRU_TOOLS)clpru -z $(LINKER_CMD_FILE) -i $(PRU_CGT)lib -o $(PRU1_ROOT)am335x-pru1-fw $(PRU1_ROOT)main1.object -l$(PRU_RPMSG_ROOT)lib/rpmsg_lib.lib

install: am335x-pru0-fw am335x-pru1-fw
	cp $(PRU0_ROOT)/am335x-pru0-fw /lib/firmware
	cp $(PRU1_ROOT)/am335x-pru1-fw /lib/firmware
	rmmod -f pru_rproc
	modprobe pru_rproc

clean:
	rm $(PRU0_ROOT)/am335x-pru0-fw
	rm $(PRU1_ROOT)/am335x-pru1-fw
	rm $(PRU0_ROOT)/*.object
	rm $(PRU1_ROOT)/*.object
	rm *.pp

