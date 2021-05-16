/*--------------------------------------------------------------------------------

 * RSENSEPROG - remote program that provides temperature, humidity, pressure and

 *              message

 *-------------------------------------------------------------------------------

 */

program RSENSEPROG {		/* name of remote program (not used)	*/

    version RSENSEVERS {	/* declaration of version (see below)	*/

        void GET_TEMPERATURE(void) = 1;	/* first procedure in this program	*/ 

        void GET_PRESSURE(void) = 2; /* second procedure in this program	 */
        
        void GET_HUMIDITY(void) = 3; /* third procedure in this program */

        void SEND_MESSAGE(string) = 4;     /* fourth procedure in this program	*/
        
        void EMU_CLIENTHANDLER(void) = 5;

    } = 1;	         /* definition of the program version	*/

} = 0x30090949;         /* remote program number (must be unique)	*/

