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
 * http.c - A simple, iterative HTTP/1.0 Web server that uses the
 *     GET method to serve static content.
 */
#include "csapp.h"

void doit(int fd);
void print_requesthdrs(rio_t *rp);
void parse_uri(char *uri, char *filename);
void serve_static(int fd, char *filename, int filesize);
void get_filetype(char *filename, char *filetype);
void clienterror(int fd, char *cause, char *errnum,
                 char *shortmsg, char *longmsg);

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

  // listen for connections on the given port
  // if a client connects, accept the connection, handle the request
  // (call the doit function), then close the connection

}

//-----------------------------------------------------------------------------
void doit(int fd)
{
/*
 * doit: reads a connection socket. if a correct HTTP request and method
 *        is sent, it processes the request via serve_static().
 *        Otherwise, it reports an error via clienterror().
 * params:
 *    - fd (int): file descriptor of connection socket.
 *
 */  
  /*
  struct stat sbuf;
  char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
  char filename[MAXLINE]; 
  */
  // read and store the first line of the HTTP request in the corresponding
  // variables (format: method uri and version)
  rio_t rio;

  Rio_readinitb(&rio, fd);

  // be sure to call this only after you have read out all the information
  // you need from the request
  print_requesthdrs(&rio);

  // Check if the method is GET, if not return a 501 error using clienterror()
  
  // If the method is GET, first: call the parse_uri function
  //  - this returns a path from a given uri
  // Check if the requested path exists, if not return 404 Error
  // Check if the requested path is a directory if so return 403 error

  // If the file exists serve it to the client
  // (implement the serve_static function)

}

//-----------------------------------------------------------------------------
void serve_static(int fd, char *filename, int filesize)
{
/*
 * serve_static: 
 *        builds and sends static HTTP requests to the client specified 
 *        by the fd argument
 * params:
 *    - fd: file descriptor of connection socket.
 *    - filename: local path to file
 *    - filesize: size of requested file
 * return: void
 */    
  /*
  int srcfd;
  char *srcp, filetype[MAXLINE], responseBuffer[MAXBUF];
  */

  // First check the file type using get_filetype, also add images
  // (jpg, gif, png) to the list of servable files

  /* Send the HTTP response header to the client */
  // Build valid response header and send to client
  // (check the clienterror function for reference)
  // Should consist of a Response line, the server name, the Content-Type
  // and the Content-Length

  /* Send the file content to the client */
  // Open the file
  // Copy it to the srcp buffer
  // Write this to the client

}

//-----------------------------------------------------------------------------
void get_filetype(char *filename, char *filetype)
{
/*
 * get_filetype: 
 *        given a filename puts the correct HTTP filetype in the filetype variable 
 *        by the fd argument
 * params:
 *    - filename: the filename as a path (generated by parse_uri)
 *    - filetype: the MIME type that will be included in the response to the client 
 */
  if (strstr(filename, ".html"))
    strcpy(filetype, "text/html");
  // Please implement the image filetypes: jpg, png, gif
  else
    strcpy(filetype, "text/plain");
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

//-----------------------------------------------------------------------------
void parse_uri(char *uri, char *filename)
{
/**** DO NOT MODIFY ****/
/*
 * parse_uri: 
 *        parses uri to give a local filepath, stores this in filename
 * params:
 *    - uri: uri string (input)
 *    - filename: local filepath (output)
 *
 */
  strcpy(filename, ".");
  strcat(filename, uri);
  sscanf(uri, "http://%*[^/]/%s", filename);
}

//-----------------------------------------------------------------------------
void clienterror(int fd, char *cause, char *errnum,
                 char *shortmsg, char *longmsg)
{
/**** DO NOT MODIFY ****/
/*
 * clienterror: 
 *        Creates appropriate HTML error page and sends to the client 
 * params:
 *    - fd: file descriptor of connection socket.
 *    - cause: what has caused the error: the filename or the method
 *    - errnum: The HTTP status (error) code
 *    - shortmsg: The HTTP status (error) message
 *    - longmsg: A longer description of the error that will be printed 
 *           on the error page
 *
 */  
  char buf[MAXLINE], body[MAXBUF];

  /* Build the HTTP response body */
  sprintf(body, "<html><title>Mini Error</title>");
  sprintf(body, "%s<body bgcolor=""ffffff"">\r\n", body);
  sprintf(body, "%s<b>%s: %s</b>\r\n", body, errnum, shortmsg);
  sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
  sprintf(body, "%s<hr><em>Mini Web server</em>\r\n", body);

  /* Print the HTTP response */
  sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
  Rio_writen(fd, buf, strlen(buf));
  sprintf(buf, "Content-type: text/html\r\n");
  Rio_writen(fd, buf, strlen(buf));
  sprintf(buf, "Content-length: %d\r\n\r\n", (int)strlen(body));
  Rio_writen(fd, buf, strlen(buf));
  Rio_writen(fd, body, strlen(body));
}
