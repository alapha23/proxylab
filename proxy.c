/*------------------------------------------------------------------------------
 * M1522.000800              System Programming                       Fall 2017
 *
 *                             HTTP & Proxy Lab
 *
 * Author: Barend Harris <barend@csap.snu.ac.kr>
 * Change Log:
 * 2017/11/23 Barend Harris created based on csapp book
 *
 * Copyright (c) 2012-2017, Computer Systems and Platforms Laboratory, SNU
 * All rights reserved.
 *
 *  Redistribution and use in source and binary forms,  with or without modifi-
 *  cation, are permitted provided that the following conditions are met:
 *
 *  - Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,  BUT NOT LIMITED TO,  THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY  AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER  OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT,  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSE-
 *  QUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF  SUBSTITUTE
 *  GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT
 *  LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY WAY
 *  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 *  DAMAGE.
 *----------------------------------------------------------------------------*/
/*
 * proxy.c - A simple, iterative HTTP proxy server
 */
#include "csapp.h"

void doit(int fd);
void print_requesthdrs(rio_t *rp);

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
/*
 * main:
 *  listens for connections on the given port number, handles HTTP requests
 *  with the doit function then closes the connection
 */
  /*
  int listenfd, connfd, port, clientlen;
  struct sockaddr_in clientaddr;
  */
  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(1);
  }

  // listen for connections
  // if a client connects, accept the connection, handle the requests
  // (call the do it function), then close the connection
}

//-----------------------------------------------------------------------------
void doit(int fd)
{
/*
 * doit: reads HTTP request from connection socket, forwards the request to the
 *  requested host. Reads the response from the host server, and writes the
 *  response back to the client
 * params:
 *    - fd (int): file descriptor of the connection socket.
 */
  /*
  char line1[MAXLINE], line2[MAXLINE], host[MAXLINE];
  int serverfd, port;
  */
  rio_t rio;

  Rio_readinitb(&rio, fd);

  //read line 1, format: method uri version

  //read and parse line 2, format:  host:port


  // be sure to call this only after you have read out all the information
  // you need from the request
  print_requesthdrs(&rio);

  // Send the first line of the client request to the server
  // (only the first line is needed), add a break '\r\n' so the server knows
  // the request has ended

  /*
  char responseBuffer[MAXLINE], response[MAXLINE];
  char *contentBuffer;
  int contentLength;
  rio_t serverResponse;

  responseBuffer[0] = '\0';
  response[0] = '\0';
  */

  // Read the response header from the server and build the proxy's response
  // header by repeatedly adding the responseBuffer (server response)

  // we must parse the Content-Length header from the server response in order
  // to know how much content to read from the server and write to the client

  // Using the contentLength read from the server response header,
  // we must allocate and read that many bytes to our buffer

  // We now write the response heading and the content back to the client

  // Close the connection to the server
}

//-----------------------------------------------------------------------------
void print_requesthdrs(rio_t *rp)
{
/**** DO NOT MODIFY ****/
/**** WARNING: This will read out everything remaining until a line break ****/
/*
 * print_requesthdrs:
 *        reads out and prints all request lines sent to the server
 * params:
 *    - rp: Rio pointer for reading from file
 *
 */
  char buf[MAXLINE];
  Rio_readlineb(rp, buf, MAXLINE);
  while(strcmp(buf, "\r\n")) {
    printf("%s", buf);
    Rio_readlineb(rp, buf, MAXLINE);
  }
  printf("\n");
  return;
}
