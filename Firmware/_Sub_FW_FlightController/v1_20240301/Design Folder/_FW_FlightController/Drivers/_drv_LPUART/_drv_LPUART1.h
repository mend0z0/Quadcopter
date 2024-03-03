/****************************************************************************************************
*
*   	Project Name:       Quadcopter._FW_FlightController
*   	@Brief Description:
*   	File Status:	    DRAFT   (DRAFT , PRELIMINARY, CHECKED, RELEASED)
*
*	File Name:	_drv_LPUART1.h
*	Version:	01
*	Revision:	00
*	Date:		2024/03/01
*	License:	Open-source
********************************* Project Description *******************************************
*	@Detailed Description:
*
*
********************************* File Description *******************************************
*	@Detailed Description:
*
*
*
**********************************  Hardware Info  **********************************************
*   	Name:       _HW_FlightController
*   	Version:    v1.0
**********************************  Processor Info **********************************************
*	Processor:          STM32U575ZIT6QU (Cortex�-M33) 32-Bits
*	Clock Frequency:    160.00	MHz
*	RAM Size:           784.00	KBytes
*	Flash Size:         2.00	MBytes
*   	SRAM1 Size:         192.00   	KBytes
*   	SRAM2 Size:         64.00   	KBytes
*   	SRAM3 Size:         512.00   	KBytes
*   	SRAM4 Size:         16.00   	KBytes
************************************  Case Style  ***********************************************
*	Local Variables = camelCase			Global Variables = g_camelCase
*	Headers = SCREAMIN_SNAKE_CASE
*   	Macros = SCREAMING_SNAKE_CASE
*   	Const Variables = SCREAMING_SNAKE_CASE
*	Functions = PascalCase				Initialize Functions = _lower_case
*	Struct = lower_case				Struct.members = camelCase
*	Enum = lower_case				Enum Members = SNAKE_CASE
*	Pointer Variables = p_camelCase
************************************ Contact Info ***********************************************
*	Author: Siavash Taher Parvar
*	GitHub: www.github.com/Mend0z0
****************************************************************************************************/
#ifndef _DRV_LPUART1_H_
#define _DRV_LPUART1_H_
/****************************************************************************************************
****************************       HEADERS DECLARATION       ****************************************
*****************************************************************************************************/
#include "main.h"

/****************************************************************************************************
****************************        MACRO DECLARATION         ***************************************
*****************************************************************************************************/

/****************************************************************************************************
****************************   DEFINED VARIABLES DECLARATION    *************************************
*****************************************************************************************************/

#define	LPDMA_CH_LPUART_RX	0U	// The channel that is dedicated to receiver part of LPUART
#define	LPDMA_CH_LPUART_TX	1U	// The channel that is dedicated to transmitter part of LPUART

#define	LPUART1_BUFFER_SIZE 	1024UL	// The size of buffer that is dedicated to each rx & tx.


/****************************************************************************************************
****************************   		STRUCT DECLARATION  		*****************************
*****************************************************************************************************/
struct lpuart_buffer{
  uint8_t rxBuffer[LPUART_BUFFER_SIZE];
  uint8_t txBuffer[LPUART_BUFFER_SIZE];
  __IO bool rxTransferCompleteFlag;		// Once the receiving completes this flag will set to true otherwise it's false.
  __IO bool txTransferCompleteFlag;		// Once the transfer completes this flag will set to true otherwise it's false.
};

/****************************************************************************************************
**************************     GLOBAL FUNCTIONS DECLARATION      ************************************
*****************************************************************************************************/

/****************************************************************************************************
*   	@Brief Description:	Receive data from LPUART
*   	Function Status: 	DRAFT   (DRAFT , PRILIMINARY, CHECKED, RELEASED)
*
*************************************************************************************************
*	Function Name:		LPUART1DataRead()
*	Function Scope:		Global
*	Function Parameters:	uint8_t *receivedData
*	Function Return Type:	uint16_t
*************************************************************************************************
*   	Function Parameters Description:  Pointer where the received data want to be downloaded
*  	Function Return Type Description: The number of received bytes, or 0 as of error
*************************************************************************************************/
uint16_t LPUART1DataRead( uint8_t *receivedData );

/****************************************************************************************************
*   	@Brief Description:	Transfer data via LPUART
*   	Function Status: 	PRILIMINARY   (DRAFT , PRILIMINARY, CHECKED, RELEASED)
*
*************************************************************************************************
*	Function Name:		LPUART1DataSend()
*	Function Scope:		Global
*	Function Parameters:	uint8_t *data, uint16_t size
*	Function Return Type:	uint16_t
*************************************************************************************************
*   	Function Parameters Description:  pointer to the memory space date is about to be uploaded, number of bytes to be uploaded
*  	Function Return Type Description: The number of transfered data, or 0 as of indicating an error.
*************************************************************************************************/
uint16_t LPUART1DataSend( uint8_t *data, uint16_t size);

#endif /* _DRV_LPUART1_H_  */

/****************************************************************************************************
*	Revision History (Description (author, date: yyyy/mm/dd))
*
****************************************************************************************************/

/*                                 FUNCTION DECLARATION TEMPLATE                                   */
/****************************************************************************************************
*   @Brief Description:
*
*	************************************************************************************************
*	Function Name:
*	Function Parameters:
*	Function Return Type:
****************************************************************************************************/

/************************************     END OF THE FILE      *************************************/
