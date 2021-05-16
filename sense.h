/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _SENSE_H_RPCGEN
#define _SENSE_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


#define RSENSEPROG 0x30090949
#define RSENSEVERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define GET_TEMPERATURE 1
extern  void * get_temperature_1(void *, CLIENT *);
extern  void * get_temperature_1_svc(void *, struct svc_req *);
#define GET_PRESSURE 2
extern  void * get_pressure_1(void *, CLIENT *);
extern  void * get_pressure_1_svc(void *, struct svc_req *);
#define GET_HUMIDITY 3
extern  void * get_humidity_1(void *, CLIENT *);
extern  void * get_humidity_1_svc(void *, struct svc_req *);
#define SEND_MESSAGE 4
extern  void * send_message_1(char **, CLIENT *);
extern  void * send_message_1_svc(char **, struct svc_req *);
#define EMU_CLIENTHANDLER 5
extern  void * emu_clienthandler_1(void *, CLIENT *);
extern  void * emu_clienthandler_1_svc(void *, struct svc_req *);
extern int rsenseprog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define GET_TEMPERATURE 1
extern  void * get_temperature_1();
extern  void * get_temperature_1_svc();
#define GET_PRESSURE 2
extern  void * get_pressure_1();
extern  void * get_pressure_1_svc();
#define GET_HUMIDITY 3
extern  void * get_humidity_1();
extern  void * get_humidity_1_svc();
#define SEND_MESSAGE 4
extern  void * send_message_1();
extern  void * send_message_1_svc();
#define EMU_CLIENTHANDLER 5
extern  void * emu_clienthandler_1();
extern  void * emu_clienthandler_1_svc();
extern int rsenseprog_1_freeresult ();
#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_SENSE_H_RPCGEN */
