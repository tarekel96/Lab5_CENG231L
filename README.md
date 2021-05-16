# Lab5_CENG231L

## Collaboration project between Tavid Terzian and Tarek El-Hajjaoui.

## Description of Program:
  - NOTE: Program is incomplete because the RPC functionality is not working.
  - This is a C/C++ program that creates an RPC Server. The server creates an RPC socket in which 5 clients can connect to
  - Once connected, the clients are presented with options menu
  - They have 5 options: 1 - get temperature of sense hat, 2 - get pressure of sense hat, 3 - get humidity of sense hat, 4 - send message to sense hat, 5 - exit socket connection
  - The program uses which allows C++ to interface with Python code that does the desired functionality mentioned above
  - Console arguments [ip address, port number]
  
## Instructions to run the program:
- **Compile the server with gcc/g++ using these commands:**
- **gcc -c sense_svc.c**
  -  Generates sense_svc.o
-  **gcc -c sense_sif.c** <-- server interface
  - Generates sense_sif.o
- **gcc -c sense_srp.cpp -I /usr/include/python2.7/ $(/usr/bin/python2.7-config --ldflags) -w**
  - Generates sense_srp.o
- **gcc -o Server sense_svc.o sense_sif.o sense_srp.o -I /usr/include/python2.7/ $(/usr/bin/python2.7-config --ldflags) -w**
  - Should make the RPC Server in a file called Server but get undefined reference error

  - **Compile the client with gcc/g++ using these commands:**
- **gcc -c sense_clnt.c**
  -  Generates sense_clnt.o
-  **gcc -c sense_cif.c** <-- client interface
  - Generates sense_cif.o
- **gcc SenseHatClient.cpp –o Client sense_cif.o rdict_clnt.o**
  - Should make the RPC Client in a file called Client but get undefined reference error
  
## Sources:
  - C Bind: https://man7.org/linux/man-pages/man2/bind.2.html
  - C Accept: https://man7.org/linux/man-pages/man2/accept.2.html
  - C Send: https://man7.org/linux/man-pages/man2/send.2.html
  - C Recv: https://man7.org/linux/man-pages/man2/recv.2.html
  - C c_str: https://www.cplusplus.com/reference/string/string/c_str/
  - C strdup: https://man7.org/linux/man-pages/man3/strdup.3.html
  - Python2.7 Object Protocol for C/C++: https://docs.python.org/2.7/c-api/object.html
  - Linux Man page: https://linux.die.net/man/3/syslog  
  - GNU: https://www.gnu.org/software/libc/manual/html_node/Syslog-Example.html
  
 ## Relevant Source Files:
  - sense.x
  - sense_cif.c/o
  - sense_sif.c/o
  - sense.h
  - sense_svc.c/o
  - sense_srp.cpp/o
  - sense_clnt.c/o
  - senseHatServer.cpp
  - SenseHatClient.cpp/o
  - senseHatModules.py
  - senseHatModules.pyc
