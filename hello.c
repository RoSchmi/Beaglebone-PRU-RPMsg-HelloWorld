/*
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the
 * distribution.
 *
 * * Neither the name of Texas Instruments Incorporated nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/poll.h>


#define MAX_BUFFER_SIZE 512
char readBuf[MAX_BUFFER_SIZE];
#define DEVICE_NAME0 "/dev/rpmsg_pru30"
#define DEVICE_NAME1 "/dev/rpmsg_pru31"
int main(void)
{
 struct pollfd pollfds[2];
 int result = 0;
 
 int pru_data;
 
 /* Open the rpmsg_pru character device file */
 pollfds[0].fd = open(DEVICE_NAME0, O_RDWR);
 pollfds[1].fd = open(DEVICE_NAME1, O_RDWR);
 /*
 * If the RPMsg channel doesn't exist yet the character device
 * won't either.
 * Make sure the PRU firmware is loaded and that the rpmsg_pru
 * module is inserted.
 */
 if (pollfds[0].fd < 0) {
 printf("Failed to open %s\n", DEVICE_NAME0);
 return -1;
 }
 
 if (pollfds[1].fd < 0) {
 printf("Failed to open %s\n",DEVICE_NAME1);
 return -1;
 }
 
 /* Send 'hello world!' to the PRU through the RPMsg channel */
 result = write(pollfds[0].fd, "hello world_0!", 13);

 result = write(pollfds[1].fd, "hello world_1!",13);

 /* Poll until we receive a message from the PRU and then print it */
 result = read(pollfds[0].fd, readBuf, MAX_BUFFER_SIZE);
 if (result > 0)
 printf("Message received from PRU_0: %s\n\n",readBuf);

 /* Close the rpmsg_pru character device file */
 close(pollfds[0].fd);
 result = read(pollfds[1].fd,readBuf,MAX_BUFFER_SIZE);
 if(result > 0) printf("Message received from PRU_1: %s\n",readBuf);
 close(pollfds[1].fd);
 return 0;
}