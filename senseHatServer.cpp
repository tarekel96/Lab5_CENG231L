  
/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <string>
#include <pthread.h>
#include <Python.h>
using namespace std; // so can use string 

// global variables
PyObject *pModule;
int new_sock_fd;

// method prototypes
void *emu_clientHandler(void* arg);
void get_temperature();
void get_pressure();
void get_humidity();
void send_message();

int main(int argc, char * argv[])
{
    Py_Initialize();
    
    PyObject *sys;
    PyObject *path;
    PyObject *pName;
    
    sys = PyImport_ImportModule("sys");
    path = PyObject_GetAttrString(sys, "path");
    PyList_Append(path, PyUnicode_FromString("."));
    pName = PyUnicode_FromString("senseHatModules");
    
    if (pName == NULL) {
        PyErr_Print();
    }

    pModule = PyImport_Import(pName);
    if (pModule == NULL) {
        PyErr_Print();
    }
    
    char* ip_address = "192.168.1.14";
    int PORT_NUMBER = 5000;
    
    int server_sockfd;
    int client_sockfd;
    int new_sockfd; // file descriptor vars
    int server_len, client_len;
    // server and client addresses
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    pthread_t a_thread;
    // size of client address - must be socklen_t data type
    socklen_t client_address_size;
    char buffer[1024] = {0};
    //int sense_hat_choice = 1;
    
    /* Remove any old socket and create an unnamed socket for the server. */
    unlink("server_socket");
    
    // init socket: [AF_INET - IPv4 protocols, SOCK_STREAM - socket type, 0 (default val) - protocol type]
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero((char*) &server_address, sizeof(server_address)); 

    // assign socket addr fields to server addr
    server_address.sin_family = AF_INET;
    server_address.sin_port = (unsigned short)htons(PORT_NUMBER);
    inet_pton(AF_INET, ip_address, &server_address.sin_addr);
    server_len = sizeof(server_address);
    // bind server addr to socket

    int n_bind = bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
    if(n_bind < 0) {
        cerr << "Err with binding\n";
    }
    /*  Create a connection queue and wait for clients.  */
    listen(server_sockfd, 5);   // second arg is backlog - max num of connections to allow on socket
    while(1) {
        int id;
        printf("server waiting\n");

        /*  Accept a connection.  */
        client_len = sizeof(client_address);
        client_address_size = sizeof(client_address);
        
        // server socket accepts client connection
        new_sockfd = accept(server_sockfd, 
            (struct sockaddr *)&client_address, &client_address_size);
            
        if(new_sockfd < 0)
            break;
        
        id = pthread_create(&a_thread, NULL, emu_clientHandler, &new_sockfd);
        
        /*  We can now read/write to client on client_sockfd.  */
    }
    Py_Finalize();
}

void *emu_clientHandler(void *arg)
{    
	int newSock = *((int*)arg);
    new_sock_fd = *((int*)arg);
    
	char* optionsMenu = "Sense Hat Menu\n---------\n1. Get Temperature\n2. Get Pressure\n3. Get Humidity\n4. Set Message\n5. Exit\n";
	char clientMessage[1024] = {0};

	while(1){
        const int sense_hat_choice = 1;
        
        send(newSock, optionsMenu, strlen(optionsMenu), 0);
        // read input from client
        char exampleRes = '1';
        int sizeBuff = sizeof(exampleRes);
		int n_recv = recv(newSock, clientMessage, 1024, 0);
        if(n_recv != sizeBuff) {
            break;
        }
		cout << "Client Response: ";
		cout << clientMessage << endl;
		bool end = false;
        
        switch(clientMessage[0]) {
            case '1': 
            {
                get_temperature();    
            } break;
            case '2': 
            {
                get_pressure();
            } break;
            case '3': 
            {
                get_humidity();
            } break;
            case '4': 
            {
                send_message();
            } break;
            case '5': 
            {
                end = true;
                const char* title = "Terminated Program. Goodbye.\n";
                send(new_sock_fd, title, strlen(title), 0);
                sleep(1.5);
                pthread_exit(NULL);
            } break;
            default:
            {
                cerr << "Invalid input" << endl;
            } break;
        }
        if(end)
            break;
	}
}

void get_temperature() {
    PyObject *pFunc = PyObject_GetAttrString(pModule, "emu_getTemperature");

    pFunc = PyObject_GetAttrString(pModule, "emu_getTemperature");
    double temperature = 0;
    if (pFunc && PyCallable_Check(pFunc)) 
    {
        PyObject *pValue = PyObject_CallObject(pFunc, NULL);
        temperature = PyFloat_AsDouble(pValue);
        Py_DECREF(pValue);
    } 
    else 
    {
        PyErr_Print();
    }

    Py_DECREF(pFunc);
    
    string tempString = "Temperature: " + std::to_string(temperature);
    const char* message = tempString.c_str();
    char* mod_message = strdup(message);
    if(send(new_sock_fd, mod_message, strlen(mod_message), 0) < 0) {
        cerr << "Error in sending to client option 1" << endl;
       printf("Value of errno: %d\n", errno);
    }
    sleep(0.5);
}

void get_pressure() {
    PyObject *pFunc = PyObject_GetAttrString(pModule, "emu_getPressure");

    pFunc = PyObject_GetAttrString(pModule, "emu_getPressure");
    double pressure = 0;
    if (pFunc && PyCallable_Check(pFunc)) 
    {
        PyObject *pValue = PyObject_CallObject(pFunc, NULL);
        pressure = PyFloat_AsDouble(pValue);
        Py_DECREF(pValue);
    } 
    else 
    {
        PyErr_Print();
    }

    Py_DECREF(pFunc);
    
    string pressureString = "Pressure: " + std::to_string(pressure);
    const char* message = pressureString.c_str();
    char* mod_message = strdup(message);
    if(send(new_sock_fd, mod_message, strlen(mod_message), 0) < 0) {
        cerr << "Error in sending to client option 1" << endl;
       printf("Value of errno: %d\n", errno);
    }
    sleep(0.5);
}

void get_humidity(){
    PyObject *pFunc = PyObject_GetAttrString(pModule, "emu_getHumidity");

    pFunc = PyObject_GetAttrString(pModule, "emu_getHumidity");
    double humidity = 0;
    if (pFunc && PyCallable_Check(pFunc)) 
    {
        PyObject *pValue = PyObject_CallObject(pFunc, NULL);
        humidity = PyFloat_AsDouble(pValue);
        Py_DECREF(pValue);
    } 
    else 
    {
        PyErr_Print();
    }

    Py_DECREF(pFunc);
    
    string humidityString = "Humidity: " + std::to_string(humidity);
    const char* message = humidityString.c_str();
    char* mod_message = strdup(message);
    if(send(new_sock_fd, mod_message, strlen(mod_message), 0) < 0) {
        cerr << "Error in sending to client option 1" << endl;
       printf("Value of errno: %d\n", errno);
    }
    sleep(0.5);
}

void send_message(){
    char bigBuffer[3000] = {0};
    const char* title = "Enter your message.";
    send(new_sock_fd, title, strlen(title), 0);
    read(new_sock_fd, bigBuffer, 3000);
    cout << "Debug: Message from client = " << bigBuffer << endl;
    
    double worked;
    PyObject *pFunc = PyObject_GetAttrString(pModule, "emu_sendMsg");

    // attr - temp static argument to pass to Python sendMessage
    PyObject *stringObjectArg = PyBytes_FromStringAndSize(bigBuffer, sizeof(bigBuffer) * 2);
    if (pFunc && PyCallable_Check(pFunc)) {
        // pass the Python object as a 2nd argument
        PyObject *pValue = PyObject_CallObject(pFunc, stringObjectArg);
        worked = PyFloat_AsDouble(pValue);
        if(worked = 1){
            cout << "Sense show message called\nMessage was: " << bigBuffer << endl;
        }
    } 
    else {
        PyErr_Print();
    }

    Py_DECREF(pFunc);
    
    sleep(0.5);
}
