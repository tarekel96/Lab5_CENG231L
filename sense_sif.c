/* rdict_sif.c - init_1, insert_1, delete_1, lookup_1_svc */

#include <rpc/rpc.h>

#define	RPC_SVC
#include "sense.h"

/* Server-side stub inteface routines written by hand */

static	int retcode;

void get_temperature(void), get_pressure(void), get_humidity(void), send_message(void), emu_clientHandler(void);

/*------------------------------------------------------------------------
 * insertw_1_svc -  server side interface to remote procedure insertw
 *------------------------------------------------------------------------
 */
void * 
get_temperature_1_svc(void * n, struct svc_req * b)
{
	get_temperature();
}

/*------------------------------------------------------------------------
 * initw_1_svc -  server side interface to remote procedure initw
 *------------------------------------------------------------------------
 */
void * 
get_pressure_1_svc(void * n, struct svc_req * b)
{
	get_pressure();
}

/*------------------------------------------------------------------------
 * deletew_1_svc -  server side interface to remote procedure deletew
 *------------------------------------------------------------------------
 */
void * 
get_humidity_1_svc(void * n, struct svc_req * b)
{
	get_humidity();
}

/*------------------------------------------------------------------------
 * lookupw_1_svc -  server side interface to remote procedure lookupw
 *------------------------------------------------------------------------
 */
void * 
send_message_1_svc(char ** n, struct svc_req * b)
{
	send_message();
}

/*------------------------------------------------------------------------
 * lookupw_1_svc -  server side interface to remote procedure lookupw
 *------------------------------------------------------------------------
 */
void * 
emu_clienthandler_1_svc_1(void * n, struct svc_req * b)
{
	emu_clientHandler();
}
