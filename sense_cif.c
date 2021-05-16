/* rdict_cif.c - initw, insertw, deletew, lookupw */

#include <rpc/rpc.h>

#include <stdio.h>

#define RPC_CLNT
#include "sense.h"

/* Client-side stub interface routines written by programmer */

extern	CLIENT	*handle;		/* handle for remote procedure	*/
static	int	*ret;			/* tmp storage for return code	*/

/*------------------------------------------------------------------------
 * initw - client interface routine that calls initw_1
 *------------------------------------------------------------------------
 */
void
get_temperature()
{
	get_temperature_1(0, handle);
}

/*------------------------------------------------------------------------
 * insertw - client interface routine that calls insertw_1
 *------------------------------------------------------------------------
 */
void
get_pressure()
{
	get_pressure_1(0, handle);
}

/*------------------------------------------------------------------------
 * deletew - client interface routine that calls deletew_1
 *------------------------------------------------------------------------
 */
void
get_humidity()
{
	get_humidity_1(0, handle);
}

/*------------------------------------------------------------------------
 * lookupw - client interface routine that calls lookupw_1
 *------------------------------------------------------------------------
 */
void 
send_message()
{
	send_message_1(0, handle);
}
