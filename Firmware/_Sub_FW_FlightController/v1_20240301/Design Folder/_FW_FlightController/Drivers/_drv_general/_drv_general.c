/****************************************************************************************************
*
*   	Project Name:       Quadcopter._FW_FlightController
*   	@Brief Description:
*   	File Status:	    DRAFT   (DRAFT , PRELIMINARY, CHECKED, RELEASED)
*
*	File Name:	_drv_general.c
*	Version:	01
*	Revision:	00
*	Date:		2024/03/01
*	License:	Open-source
********************************* Project Description *******************************************
*	@Detailed Description:
*
*
*
********************************* File Description *******************************************
*	@Detailed Description:
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
*	Author:	Siavash Taher Parvar
*	GitHub: github.com/Mend0z0
****************************************************************************************************/

/****************************************************************************************************
****************************       HEADERS DECLARATION       ****************************************
*****************************************************************************************************/
#include "_drv_general.h"

/****************************************************************************************************
****************************   CONST VARIABLES DECLARATION    ***************************************
*****************************************************************************************************/

/****************************************************************************************************
****************************   GLOB. VARIABLES DECLARATION    ***************************************
*****************************************************************************************************/

/****************************************************************************************************
***********************     STATIC/LOCAL FUNCTIONS DECLARATION      *********************************
*****************************************************************************************************/
void _init_RCC( void );
void _init_Systick( void );

/****************************************************************************************************
****************************         GLOBAL FUNTIONS         ****************************************
*****************************************************************************************************/

/****************************************************************************************************
*   	@Brief Description:	Configuring general peripherals like RCC and so on...
*   	Function Status: 	PRILIMINARY   (DRAFT , PRILIMINARY, CHECKED, RELEASED)
*
*************************************************************************************************
*	Function Name:			_init_General()
*	Function Scope:			Global
*	Function Parameters:	void
*	Function Return Type:	void
*************************************************************************************************
*   	Function Parameters Description:
*   	Function Return Type Description:
*************************************************************************************************
*	Revision History (Description, author, date: yyyy/mm/dd)
*
****************************************************************************************************/
void _init_General( void )
{
	_init_RCC();
	_init_Systick(160000000); // Configure systick clock with 160MHz input clock
}

/****************************************************************************************************
*   	@Brief Description:	This function will fill an array with defined input value
*   	Function Status: 	PRILIMINARY   (DRAFT , PRILIMINARY, CHECKED, RELEASED)
*
*************************************************************************************************
*	Function Name:		ArrayFill()
*	Function Scope:		Global
*	Function Parameters:	uint8_t *array, uint16_t bufferSize, uint8_t value
*	Function Return Type:	void
*************************************************************************************************
*   	Function Parameters Description:  pointer to array, buffer size, and the desire value you want fill the array with.
*   	Function Return Type Description: void
*************************************************************************************************
*	Revision History (Description, author, date: yyyy/mm/dd)
*
****************************************************************************************************/
void ArrayFill( uint8_t *array, uint16_t bufferSize, uint8_t value)
{
  while(--bufferSize)
    {
      *(array + bufferSize) = value;
    }
}

/****************************************************************************************************
****************************         STATIC FUNTIONS         ****************************************
*****************************************************************************************************/

/****************************************************************************************************
*   @Brief Description: Initialize RCC peripheral
*   Function Status: 	PRELIMINARY   (DRAFT , PRELIMINARY, CHECKED, RELEASED)
*
*	************************************************************************************************
*	Function Name:			_init_RCC()
*	Function Scope:         Local(static)
*	Function Parameters:	void
*	Function Return Type:	void
*	************************************************************************************************
*	@Detailed Description: (Do numbering and tag the number to each part of code)
*   Function Parameters Description:	void
*   Function Return Type Description:	void
*	************************************************************************************************
*	Revision History (Description (author, date: yyyy/mm/dd))
*
****************************************************************************************************/
void _init_RCC( void )
{
	RCC->CR |= RCC_CR_HSION;												// HSI16 oscillator ON
	while(!(RCC->CR & RCC_CR_HSIRDY));										// Wait until HSI16 oscillator ready

	RCC->PLL1CFGR |=	RCC_PLL1CFGR_PLL1REN	|							// pll1_r_ck output enabled
						RCC_PLL1CFGR_PLL1M_1	| RCC_PLL1CFGR_PLL1M_0	|	// division by 4
						RCC_PLL1CFGR_PLL1SRC_1								// HSI16 clock selected as PLL1 clock entry
						;

	RCC->PLL1DIVR |= 80U;													// Multiplication factor for PLL1 VCO

	RCC->CR |= RCC_CR_PLL1ON;												// PLL1 ON
	while(!(RCC->CR & RCC_CR_PLL1RDY));										// Wait until PLL1 locked

	// PLL output = ((16MHz(HSI) / 4(M)) * 80(N)) / 2(R) = 160 MHz

	// Switch to PLL source
	RCC->CFGR1 |= RCC_CFGR1_SW_1 | RCC_CFGR1_SW_0;							// PLL pll1_r_ck selected as system clock
	while(!(RCC->CFGR1 & (RCC_CFGR1_SWS_1 | RCC_CFGR1_SWS_0)));				// Wait until PLL pll1_r_ck used as system clock
}

/****************************************************************************************************
*   @Brief Description: Init Systick peripheral and enabling its interrupt
*   Function Status: 	PRELIMINARY   (DRAFT , PRELIMINARY, CHECKED, RELEASED)
*
*	************************************************************************************************
*	Function Name:			_init_Systick()
*	Function Scope:         Local(static)
*	Function Parameters:	uint32_t inputClock
*	Function Return Type:	void
*	************************************************************************************************
*	@Detailed Description: (Do numbering and tag the number to each part of code)
*   Function Parameters Description:	void
*   Function Return Type Description:	void
*	************************************************************************************************
*	Revision History (Description (author, date: yyyy/mm/dd))
*
****************************************************************************************************/
void _init_Systick( uint32_t inputClock )
{
	SysTick_Config( inputClock / 8000 );	// Update the input clock value
	NVIC_EnableIRQ(SysTick_IRQn);			// Enable the IRQ
}


/***************************************************************************************************/
/**********************************                             ************************************/
/********************                     END OF THE CODE                         ******************/
/**********************************                             ************************************/
/***************************************************************************************************/

/*                                   GLOBAL FUNCTION TEMPLATE                                      */

/****************************************************************************************************
*   	@Brief Description:
*   	Function Status: 	DRAFT   (DRAFT , PRILIMINARY, CHECKED, RELEASED)
*
*************************************************************************************************
*	Function Name:
*	Function Scope:			Global
*	Function Parameters:
*	Function Return Type:
*************************************************************************************************
*   	Function Parameters Description:
*   	Function Return Type Description:
*************************************************************************************************
*	Revision History (Description, author, date: yyyy/mm/dd)
*
****************************************************************************************************/

/*                               STATIC/LOCAL FUNCTION TEMPLATE                                    */

/****************************************************************************************************
*   	@Brief Description:
*   	Function Status: 	DRAFT   (DRAFT , PRELIMINARY, CHECKED, RELEASED)
*
*************************************************************************************************
*	Function Name:
*	Function Scope:         Local(static)
*	Function Parameters:
*	Function Return Type:
*************************************************************************************************
*	@Detailed Description: (Do numbering and tag the number to each part of code)
*   	Function Parameters Description:
*   	Function Return Type Description:
*************************************************************************************************
*	Revision History (Description (author, date: yyyy/mm/dd))
*
****************************************************************************************************/

/************************************     END OF THE FILE      *************************************/
