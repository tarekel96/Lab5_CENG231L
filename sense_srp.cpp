/* rdict_srp.c - initw, insertw, deletew, lookupw */



#include <rpc/rpc.h>



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

#include "sense.h"

using namespace std;

/* Server-side remote procedures and the global data they use */



//char	dict[DICTSIZ][MAXWORD+1];/* storage for a dictionary of words	*/

int	nwords = 0;		/* number of words in the dictionary	*/

// global variables
PyObject *pModule;
int new_sock_fd;



/*------------------------------------------------------------------------

 * initw - initialize the dictionary to contain no words at all

 *------------------------------------------------------------------------

 */

void

get_temperature()

{
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



/*------------------------------------------------------------------------

 * insertw - insert  a word in the dictionary

 *------------------------------------------------------------------------

 */

void

get_pressure()

{
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



/*------------------------------------------------------------------------

 * deletew - delete  a word from the dictionary

 *------------------------------------------------------------------------

 */

void

get_humidity()

{
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



/*------------------------------------------------------------------------

 * lookupw - look up a word in the dictionary

 *------------------------------------------------------------------------

 */

void

send_message()

{
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
