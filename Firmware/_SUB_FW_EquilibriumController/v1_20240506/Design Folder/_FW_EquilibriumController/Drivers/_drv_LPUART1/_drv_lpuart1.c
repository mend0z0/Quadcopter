/****************************************************************************************************
*
*   Project Name:       Drone - _SUB_FW_EquilibriumController._drv_lpuart1
*   @Brief Description: This file contain the driver for Sending/Receiving data through LPUART peripheral
*   File Status:	    DRAFT   (DRAFT , PRELIMINARY, CHECKED, RELEASED)
*
*	File Name:	_drv_lpuart1.c
*	Version:	01
*	Revision:	01
*	Date:		2024/05/23
*	License:	Open-source
*	******************************** Project Description *******************************************
*	@Detailed Description: This controller is supposed to read environmental sensors such as temperature,
*   humidity, pressure, 3-Axis gyroscope, 3-Axis accelerometer, 3-Axis compass, and GPS. Once the data is
*   read, it'll be filtered and be used for equilibrium calculation.
*
*	******************************** File Description *******************************************
*	@Detailed Description: This file contains necessary functions to make a serial connection by LPUART
*   that can work in RTOS environment. To do so, we are using LPDMA, LPTIM1, LPUART peripherals in
*   connection with each other so we can send & receive data without constantly involving the main process.
*
*	*********************************  Hardware Info  **********************************************
*   Name:       _SUB_HW_EquilibriumController
*   Version:    v1.0
*	*********************************  Processor Info **********************************************
*	Processor:          STM32U575CIU6Q 32-Bits
*	Clock Frequency:    160.0	MHz
*	RAM/SRAM Size:      0.784	MBytes
*	Flash Size:         02.00	MBytes
*	***********************************  Case Style  ***********************************************
*	Local Variables = camelCase			Global Variables = g_camelCase
*	Headers = SCREAMIN_SNAKE_CASE
*   Macros = SCREAMING_SNAKE_CASE
*   Const Variables = SCREAMING_SNAKE_CASE
*	Functions = PascalCase				Initialize Functions = _lower_case
*	Struct = lower_case					Struct.members = camelCase
*	Enum = lower_case					Enum Members = SNAKE_CASE
*	Pointer Variables = p_camelCase
*	*********************************** Contact Info ***********************************************
*	Author:	Siavash Taher Parvar
*	GitHub: github.com/Mend0z0
****************************************************************************************************/

/****************************************************************************************************
****************************       HEADERS DECLARATION       ****************************************
*****************************************************************************************************/
#include "_drv_lpuart1.h"

/****************************************************************************************************
****************************   CONST VARIABLES DECLARATION    ***************************************
*****************************************************************************************************/

const uint16_t LPUART_BUFF_SIZE_RX = 254;		//it's 256 bytes
const uint16_t LPUART_BUFF_SIZE_TX = 1024;		//it's 1024 bytes

/****************************************************************************************************
****************************   GLOB. VARIABLES DECLARATION    ***************************************
*****************************************************************************************************/

struct {
	uint8_t buff_tx[LPUART_BUFF_SIZE_TX];		//
	uint8_t buff_rx[LPUART_BUFF_SIZE_RX];		//
	uint16_t currentDataSize;					//
	uint16_t nextDataSize;						//
	bool awaitingOngoingData;					//
	bool readReady;								//
}lpuart;

/****************************************************************************************************
****************************        ISR DECLARATION           ***************************************
*****************************************************************************************************/

/****************************************************************************************************
*   @Brief Description:
*   Function Status: 	DRAFT   (DRAFT , PRELIMINARY, CHECKED, RELEASED)
*
*	************************************************************************************************
*	Function Name:
*	Function Scope:         Local(static)
*	Function Parameters:
*	Function Return Type:
*	************************************************************************************************
*	@Detailed Description: (Do numbering and tag the number to each part of code)
*   Function Parameters Description:
*   Function Return Type Description:
*   Comments should be added in front of each line. (This line should be deleted)
*	************************************************************************************************
*	Revision History (Description (author, date: yyyy/mm/dd))
*
****************************************************************************************************/
void LPTIM1_IRQHandler( void )
{
	LPTIM1->ICR |= LPTIM_ICR_UECF;	//clear the UE flag
}

/****************************************************************************************************
*   @Brief Description:
*   Function Status: 	DRAFT   (DRAFT , PRELIMINARY, CHECKED, RELEASED)
*
*	************************************************************************************************
*	Function Name:
*	Function Scope:         Local(static)
*	Function Parameters:
*	Function Return Type:
*	************************************************************************************************
*	@Detailed Description: (Do numbering and tag the number to each part of code)
*   Function Parameters Description:
*   Function Return Type Description:
*   Comments should be added in front of each line. (This line should be deleted)
*	************************************************************************************************
*	Revision History (Description (author, date: yyyy/mm/dd))
*
****************************************************************************************************/
void LPUART1_IRQHandler( void )
{

}

/****************************************************************************************************
*   @Brief Description:
*   Function Status: 	DRAFT   (DRAFT , PRELIMINARY, CHECKED, RELEASED)
*
*	************************************************************************************************
*	Function Name:
*	Function Scope:         Local(static)
*	Function Parameters:
*	Function Return Type:
*	************************************************************************************************
*	@Detailed Description: (Do numbering and tag the number to each part of code)
*   Function Parameters Description:
*   Function Return Type Description:
*   Comments should be added in front of each line. (This line should be deleted)
*	************************************************************************************************
*	Revision History (Description (author, date: yyyy/mm/dd))
*
****************************************************************************************************/
void LPDMA1_Channel0_IRQHandler( void )
{

}

/****************************************************************************************************
*   @Brief Description:
*   Function Status: 	DRAFT   (DRAFT , PRELIMINARY, CHECKED, RELEASED)
*
*	************************************************************************************************
*	Function Name:
*	Function Scope:         Local(static)
*	Function Parameters:
*	Function Return Type:
*	************************************************************************************************
*	@Detailed Description: (Do numbering and tag the number to each part of code)
*   Function Parameters Description:
*   Function Return Type Description:
*   Comments should be added in front of each line. (This line should be deleted)
*	************************************************************************************************
*	Revision History (Description (author, date: yyyy/mm/dd))
*
****************************************************************************************************/
void LPDMA1_Channel1_IRQHandler( void )
{

}

/****************************************************************************************************
***********************     STATIC/LOCAL FUNCTIONS DECLARATION      *********************************
*****************************************************************************************************/

void _init_Clock( void );
void _init_LPGPIO( void );
void _init_LPTIM1( void );
void _init_LPDMA1( void );

/****************************************************************************************************
****************************         GLOBAL FUNTIONS         ****************************************
*****************************************************************************************************/

/****************************************************************************************************
*   @Brief Description:
*   Function Status: 	DRAFT   (DRAFT , PRILIMINARY, CHECKED, RELEASED)
*
*	************************************************************************************************
*	Function Name:
*	Function Scope:			Global
*	Function Parameters:
*	Function Return Type:
*	************************************************************************************************
*   Function Parameters Description:
*   Function Return Type Description:
*   Comments should be added in front of each line. (This line should be deleted)
*	************************************************************************************************
*	Revision History (Description, author, date: yyyy/mm/dd)
*
****************************************************************************************************/
void _init_lpuart1( void )
{
	_init_Clock();
	_init_LPGPIO();
	_init_LPTIM1();
	_init_LPDMA1();

	//init the LPUART1
}

/****************************************************************************************************
*   @Brief Description:
*   Function Status: 	DRAFT   (DRAFT , PRILIMINARY, CHECKED, RELEASED)
*
*	************************************************************************************************
*	Function Name:
*	Function Scope:			Global
*	Function Parameters:
*	Function Return Type:
*	************************************************************************************************
*   Function Parameters Description:
*   Function Return Type Description:
*   Comments should be added in front of each line. (This line should be deleted)
*	************************************************************************************************
*	Revision History (Description, author, date: yyyy/mm/dd)
*
****************************************************************************************************/
bool LPUARTAvailable( void )
{

}

/****************************************************************************************************
*   @Brief Description:
*   Function Status: 	DRAFT   (DRAFT , PRILIMINARY, CHECKED, RELEASED)
*
*	************************************************************************************************
*	Function Name:
*	Function Scope:			Global
*	Function Parameters:
*	Function Return Type:
*	************************************************************************************************
*   Function Parameters Description:
*   Function Return Type Description:
*   Comments should be added in front of each line. (This line should be deleted)
*	************************************************************************************************
*	Revision History (Description, author, date: yyyy/mm/dd)
*
****************************************************************************************************/
uint16_t LPUARTRead( uint8_t *data, uint16_t buffSize)
{

}

/****************************************************************************************************
*   @Brief Description:
*   Function Status: 	DRAFT   (DRAFT , PRILIMINARY, CHECKED, RELEASED)
*
*	************************************************************************************************
*	Function Name:
*	Function Scope:			Global
*	Function Parameters:
*	Function Return Type:
*	************************************************************************************************
*   Function Parameters Description:
*   Function Return Type Description:
*   Comments should be added in front of each line. (This line should be deleted)
*	************************************************************************************************
*	Revision History (Description, author, date: yyyy/mm/dd)
*
****************************************************************************************************/
void LPUARTFlushRx( void )
{

}

/****************************************************************************************************
*   @Brief Description:
*   Function Status: 	DRAFT   (DRAFT , PRILIMINARY, CHECKED, RELEASED)
*
*	************************************************************************************************
*	Function Name:
*	Function Scope:			Global
*	Function Parameters:
*	Function Return Type:
*	************************************************************************************************
*   Function Parameters Description:
*   Function Return Type Description:
*   Comments should be added in front of each line. (This line should be deleted)
*	************************************************************************************************
*	Revision History (Description, author, date: yyyy/mm/dd)
*
****************************************************************************************************/
void LPUARTWrite( uint8_t *data, uint16_t buffSize )
{

}

/****************************************************************************************************
*   @Brief Description:
*   Function Status: 	DRAFT   (DRAFT , PRILIMINARY, CHECKED, RELEASED)
*
*	************************************************************************************************
*	Function Name:
*	Function Scope:			Global
*	Function Parameters:
*	Function Return Type:
*	************************************************************************************************
*   Function Parameters Description:
*   Function Return Type Description:
*   Comments should be added in front of each line. (This line should be deleted)
*	************************************************************************************************
*	Revision History (Description, author, date: yyyy/mm/dd)
*
****************************************************************************************************/
void LPUARTFlushTx( void )
{

}

/****************************************************************************************************
****************************         STATIC FUNTIONS         ****************************************
*****************************************************************************************************/

/****************************************************************************************************
*   @Brief Description:
*   Function Status: 	DRAFT   (DRAFT , PRELIMINARY, CHECKED, RELEASED)
*
*	************************************************************************************************
*	Function Name:
*	Function Scope:         Local(static)
*	Function Parameters:
*	Function Return Type:
*	************************************************************************************************
*	@Detailed Description: (Do numbering and tag the number to each part of code)
*   Function Parameters Description:
*   Function Return Type Description:
*   Comments should be added in front of each line. (This line should be deleted)
*	************************************************************************************************
*	Revision History (Description (author, date: yyyy/mm/dd))
*
****************************************************************************************************/
void _init_Clock( void )
{

}

/****************************************************************************************************
*   @Brief Description:
*   Function Status: 	DRAFT   (DRAFT , PRELIMINARY, CHECKED, RELEASED)
*
*	************************************************************************************************
*	Function Name:
*	Function Scope:         Local(static)
*	Function Parameters:
*	Function Return Type:
*	************************************************************************************************
*	@Detailed Description: (Do numbering and tag the number to each part of code)
*   Function Parameters Description:
*   Function Return Type Description:
*   Comments should be added in front of each line. (This line should be deleted)
*	************************************************************************************************
*	Revision History (Description (author, date: yyyy/mm/dd))
*
****************************************************************************************************/
void _init_GPIO( void )
{
	//PA2 = LPUART1_TX & IT'S AF8
	//PA3 = LPUART1_RX & IT'S AF8
	GPIOA->MODER |= GPIO_MODER_MODE2_1 | GPIO_MODER_MODE3_1;			//Set the GPIO mode as Alternate function
	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT2 | GPIO_OTYPER_OT3);				//Set the output push-pull
	GPIOA->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED2 | GPIO_OSPEEDR_OSPEED3);	//Set the speed as low speed
	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD2 | GPIO_PUPDR_PUPD3);				//No pull-up, pull-down

	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL2_3 | GPIO_AFRL_AFSEL3_3;			//Set the Alternate function to AF8.

	//Locking the port bits
	GPIOA->LCKR |= GPIO_LCKR_LCK2 | GPIO_LCKR_LCK3 | GPIO_LCKR_LCKK;	//1
	GPIOA->LCKR |= GPIO_LCKR_LCK2 | GPIO_LCKR_LCK3;						//2
	GPIOA->LCKR |= GPIO_LCKR_LCK2 | GPIO_LCKR_LCK3 | GPIO_LCKR_LCKK;	//3
}

/****************************************************************************************************
*   @Brief Description:
*   Function Status: 	DRAFT   (DRAFT , PRELIMINARY, CHECKED, RELEASED)
*
*	************************************************************************************************
*	Function Name:
*	Function Scope:         Local(static)
*	Function Parameters:
*	Function Return Type:
*	************************************************************************************************
*	@Detailed Description: (Do numbering and tag the number to each part of code)
*   Function Parameters Description:
*   Function Return Type Description:
*   Comments should be added in front of each line. (This line should be deleted)
*	************************************************************************************************
*	Revision History (Description (author, date: yyyy/mm/dd))
*
****************************************************************************************************/
void _init_LPTIM1( void )
{
	LPTIM1->CFGR |= LPTIM_CFGR_PRESC;	// Config the prescaler...

	LPTIM1->CFGR |= LPTIM_CFGR_PRELOAD;	// Registers are updated at the end of the current LPTIM period

	LPTIM1->ARR = 0XFFFF;				// Value for this bit should be set later...

	LPTIM1->CR |= LPTIM_CR_ENABLE | LPTIM_CR_SNGSTRT;		// LPTIM is enabled + LPTIM start in Single mode

	LPTIM1->DIER |= LPTIM_DIER_UEIE;	//Enable Update Event Interrupt. This line should be placed after the LPTIM is enabled...
}

/****************************************************************************************************
*   @Brief Description:
*   Function Status: 	DRAFT   (DRAFT , PRELIMINARY, CHECKED, RELEASED)
*
*	************************************************************************************************
*	Function Name:
*	Function Scope:         Local(static)
*	Function Parameters:
*	Function Return Type:
*	************************************************************************************************
*	@Detailed Description: (Do numbering and tag the number to each part of code)
*   Function Parameters Description:
*   Function Return Type Description:
*   Comments should be added in front of each line. (This line should be deleted)
*	************************************************************************************************
*	Revision History (Description (author, date: yyyy/mm/dd))
*
****************************************************************************************************/
void _init_LPDMA1( void )
{

}

/***************************************************************************************************/
/**********************************                             ************************************/
/********************                     END OF THE CODE                         ******************/
/**********************************                             ************************************/
/***************************************************************************************************/

/*                                   GLOBAL FUNCTION TEMPLATE                                      */

/****************************************************************************************************
*   @Brief Description:
*   Function Status: 	DRAFT   (DRAFT , PRILIMINARY, CHECKED, RELEASED)
*
*	************************************************************************************************
*	Function Name:
*	Function Scope:			Global
*	Function Parameters:
*	Function Return Type:
*	************************************************************************************************
*   Function Parameters Description:
*   Function Return Type Description:
*   Comments should be added in front of each line. (This line should be deleted)
*	************************************************************************************************
*	Revision History (Description, author, date: yyyy/mm/dd)
*
****************************************************************************************************/

/*                               STATIC/LOCAL FUNCTION TEMPLATE                                    */

/****************************************************************************************************
*   @Brief Description:
*   Function Status: 	DRAFT   (DRAFT , PRELIMINARY, CHECKED, RELEASED)
*
*	************************************************************************************************
*	Function Name:
*	Function Scope:         Local(static)
*	Function Parameters:
*	Function Return Type:
*	************************************************************************************************
*	@Detailed Description: (Do numbering and tag the number to each part of code)
*   Function Parameters Description:
*   Function Return Type Description:
*   Comments should be added in front of each line. (This line should be deleted)
*	************************************************************************************************
*	Revision History (Description (author, date: yyyy/mm/dd))
*
****************************************************************************************************/

/************************************     END OF THE FILE      *************************************/
