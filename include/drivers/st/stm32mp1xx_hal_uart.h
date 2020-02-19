/**
  ******************************************************************************
  * @file    stm32mp1xx_hal_uart.h
  * @author  MCD Application Team
  * @version V0.3.0
  * @date    14-January-2015
  * @brief   Header file of UART HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * SPDX-License-Identifier: BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32MP1xx_HAL_UART_H
#define __STM32MP1xx_HAL_UART_H

#ifdef __cplusplus
 extern "C" {
#endif

#define HAL_UART_MODULE_ENABLED

/* Includes ------------------------------------------------------------------*/
#include <stm32mp1xx_hal.h>
#include <stm32_uart_regs.h>

/**
  * @brief UART Init Structure definition
  */
typedef struct
{
	uint32_t BaudRate;                  /*!< This member configures the UART communication baud rate.
					      The baud rate register is computed using the following formula:
					      - If oversampling is 16 or in LIN mode,
					      Baud Rate Register = ((PCLKx) / ((huart->Init.BaudRate)))
					      - If oversampling is 8,
					      Baud Rate Register[15:4] = ((2 * PCLKx) / ((huart->Init.BaudRate)))[15:4]
					      Baud Rate Register[3] =  0
					      Baud Rate Register[2:0] =  (((2 * PCLKx) / ((huart->Init.BaudRate)))[3:0]) >> 1      */

	uint32_t WordLength;                /*!< Specifies the number of data bits transmitted or received in a frame.
					      This parameter can be a value of @ref UARTEx_Word_Length. */

	uint32_t StopBits;                  /*!< Specifies the number of stop bits transmitted.
					      This parameter can be a value of @ref UART_Stop_Bits. */

	uint32_t Parity;                    /*!< Specifies the parity mode.
					      This parameter can be a value of @ref UART_Parity
					      @note When parity is enabled, the computed parity is inserted
					      at the MSB position of the transmitted data (9th bit when
					      the word length is set to 9 data bits; 8th bit when the
					      word length is set to 8 data bits). */

	uint32_t Mode;                      /*!< Specifies whether the Receive or Transmit mode is enabled or disabled.
					      This parameter can be a value of @ref UART_Mode. */

	uint32_t HwFlowCtl;                 /*!< Specifies whether the hardware flow control mode is enabled
					      or disabled.
					      This parameter can be a value of @ref UART_Hardware_Flow_Control. */

	uint32_t OverSampling;              /*!< Specifies whether the Over sampling 8 is enabled or disabled, to achieve higher speed (up to f_PCLK/8).
					      This parameter can be a value of @ref UART_Over_Sampling. */

	uint32_t OneBitSampling;            /*!< Specifies whether a single sample or three samples' majority vote is selected.
					      Selecting the single sample method increases the receiver tolerance to clock
					      deviations. This parameter can be a value of @ref UART_OneBit_Sampling. */

	uint32_t Prescaler;                 /*!< Specifies the prescaler value used to divide the UART clock source.
					      This parameter can be a value of @ref UART_Prescaler. */

	uint32_t FIFOMode;                  /*!< Specifies if the FIFO mode will be used. This parameter can be a value
					      of @ref UART_FIFO_mode. */

	uint32_t TXFIFOThreshold;           /*!< Specifies the TXFIFO threshold level.
					      This parameter can be a value of @ref UART_TXFIFO_threshold_level. */

	uint32_t RXFIFOThreshold;           /*!< Specifies the RXFIFO threshold level.
					      This parameter can be a value of @ref UART_RXFIFO_threshold_level. */

} UART_InitTypeDef;

/**
  * @brief  UART Advanced Features initalization structure definition
  */
typedef struct
{
	uint32_t AdvFeatureInit;        /*!< Specifies which advanced UART features is initialized. Several
					  Advanced Features may be initialized at the same time .
					  This parameter can be a value of @ref UART_Advanced_Features_Initialization_Type. */

	uint32_t TxPinLevelInvert;      /*!< Specifies whether the TX pin active level is inverted.
					  This parameter can be a value of @ref UART_Tx_Inv.  */

	uint32_t RxPinLevelInvert;      /*!< Specifies whether the RX pin active level is inverted.
					  This parameter can be a value of @ref UART_Rx_Inv.  */

	uint32_t DataInvert;            /*!< Specifies whether data are inverted (positive/direct logic
					  vs negative/inverted logic).
					  This parameter can be a value of @ref UART_Data_Inv. */

	uint32_t Swap;                  /*!< Specifies whether TX and RX pins are swapped.
					  This parameter can be a value of @ref UART_Rx_Tx_Swap. */

	uint32_t OverrunDisable;        /*!< Specifies whether the reception overrun detection is disabled.
					  This parameter can be a value of @ref UART_Overrun_Disable. */

	uint32_t DMADisableonRxError;   /*!< Specifies whether the DMA is disabled in case of reception error.
					  This parameter can be a value of @ref UART_DMA_Disable_on_Rx_Error. */

	uint32_t AutoBaudRateEnable;    /*!< Specifies whether auto Baud rate detection is enabled.
					  This parameter can be a value of @ref UART_AutoBaudRate_Enable */

	uint32_t AutoBaudRateMode;      /*!< If auto Baud rate detection is enabled, specifies how the rate
					  detection is carried out.
					  This parameter can be a value of @ref UART_AutoBaud_Rate_Mode. */

	uint32_t MSBFirst;              /*!< Specifies whether MSB is sent first on UART line.
					  This parameter can be a value of @ref UART_MSB_First. */
} UART_AdvFeatureInitTypeDef;



/**
  * @brief HAL UART State structures definition
  * @note  HAL UART State value is a combination of 2 different substates: gState and RxState.
  *        - gState contains UART state information related to global Handle management
  *          and also information related to Tx operations.
  *          gState value coding follow below described bitmap :
  *          b7-b6  Error information
  *             00 : No Error
  *             01 : (Not Used)
  *             10 : Timeout
  *             11 : Error
  *          b5     IP initilisation status
  *             0  : Reset (IP not initialized)
  *             1  : Init done (IP not initialized. HAL UART Init function already called)
  *          b4-b3  (not used)
  *             xx : Should be set to 00
  *          b2     Intrinsic process state
  *             0  : Ready
  *             1  : Busy (IP busy with some configuration or internal operations)
  *          b1     (not used)
  *             x  : Should be set to 0
  *          b0     Tx state
  *             0  : Ready (no Tx operation ongoing)
  *             1  : Busy (Tx operation ongoing)
  *        - RxState contains information related to Rx operations.
  *          RxState value coding follow below described bitmap :
  *          b7-b6  (not used)
  *             xx : Should be set to 00
  *          b5     IP initilisation status
  *             0  : Reset (IP not initialized)
  *             1  : Init done (IP not initialized)
  *          b4-b2  (not used)
  *            xxx : Should be set to 000
  *          b1     Rx state
  *             0  : Ready (no Rx operation ongoing)
  *             1  : Busy (Rx operation ongoing)
  *          b0     (not used)
  *             x  : Should be set to 0.
  */
typedef enum {
	HAL_UART_STATE_RESET             = 0x00U,   /*!< Peripheral is not initialized
						      Value is allowed for gState and RxState */
	HAL_UART_STATE_READY             = 0x20U,   /*!< Peripheral Initialized and ready for use
						      Value is allowed for gState and RxState */
	HAL_UART_STATE_BUSY              = 0x24U,   /*!< an internal process is ongoing
						      Value is allowed for gState only */
	HAL_UART_STATE_BUSY_TX           = 0x21U,   /*!< Data Transmission process is ongoing
						      Value is allowed for gState only */
	HAL_UART_STATE_BUSY_RX           = 0x22U,   /*!< Data Reception process is ongoing
						      Value is allowed for RxState only */
	HAL_UART_STATE_BUSY_TX_RX        = 0x23U,   /*!< Data Transmission and Reception process is ongoing
						      Not to be used for neither gState nor RxState.
						      Value is result of combination (Or) between gState and RxState values */
	HAL_UART_STATE_TIMEOUT           = 0xA0U,   /*!< Timeout state
						      Value is allowed for gState only */
	HAL_UART_STATE_ERROR             = 0xE0U    /*!< Error
						      Value is allowed for gState only */
} HAL_UART_StateTypeDef;

/**
  * @brief  HAL UART Error Code structure definition
  */
typedef enum
{
	HAL_UART_ERROR_NONE      = 0x00U,    /*!< No error            */
	HAL_UART_ERROR_PE        = 0x01U,    /*!< Parity error        */
	HAL_UART_ERROR_NE        = 0x02U,    /*!< Noise error         */
	HAL_UART_ERROR_FE        = 0x04U,    /*!< frame error         */
	HAL_UART_ERROR_ORE       = 0x08U,    /*!< Overrun error       */
	HAL_UART_ERROR_DMA       = 0x10U     /*!< DMA transfer error  */
} HAL_UART_ErrorTypeDef;

/**
  * @brief UART clock sources definition
  */
typedef enum {
	UART_CLOCKSOURCE_PCLK1      = 0x00U,    /*!< PCLK1 clock source  */
	UART_CLOCKSOURCE_PCLK2      = 0x01U,    /*!< PCLK2 clock source  */
	UART_CLOCKSOURCE_PCLK5      = 0x02U,    /*!< PCLK5 clock source  (only used by UART1) */
	UART_CLOCKSOURCE_PLL3Q      = 0x04U,    /*!< PLL3Q clock source  (only used by UART1) */
	UART_CLOCKSOURCE_PLL4Q      = 0x08U,    /*!< PLL4Q clock source  */
	UART_CLOCKSOURCE_HSI        = 0x10U,    /*!< HSI clock source    */
	UART_CLOCKSOURCE_CSI        = 0x20U,    /*!< CSI clock source    */
	UART_CLOCKSOURCE_HSE        = 0x40U,    /*!< HSE clock source    */
	UART_CLOCKSOURCE_UNDEFINED  = 0x80U     /*!< Undefined clock source */
} UART_ClockSourceTypeDef;

/**
  * @brief  UART handle Structure definition
  */
typedef struct {
	USART_TypeDef            *Instance;        /*!< UART registers base address        */

	UART_InitTypeDef         Init;             /*!< UART communication parameters      */

	UART_AdvFeatureInitTypeDef AdvancedInit;   /*!< UART Advanced Features initialization parameters */

	uint8_t                  *pTxBuffPtr;      /*!< Pointer to UART Tx transfer Buffer */

	uint16_t                 TxXferSize;       /*!< UART Tx Transfer size              */

	__IO uint16_t            TxXferCount;      /*!< UART Tx Transfer Counter           */

	uint8_t                  *pRxBuffPtr;      /*!< Pointer to UART Rx transfer Buffer */

	uint16_t                 RxXferSize;       /*!< UART Rx Transfer size              */

	__IO uint16_t            RxXferCount;      /*!< UART Rx Transfer Counter           */

	uint16_t                 Mask;             /*!< UART Rx RDR register mask          */

#if defined(HAL_DMA_MODULE_ENABLED)
	DMA_HandleTypeDef        *hdmatx;          /*!< UART Tx DMA Handle parameters      */

	DMA_HandleTypeDef        *hdmarx;          /*!< UART Rx DMA Handle parameters      */
#endif
#if defined(HAL_MDMA_MODULE_ENABLED)
	MDMA_HandleTypeDef        *hmdmatx;        /*!< UART Tx MDMA Handle parameters      */

	MDMA_HandleTypeDef        *hmdmarx;        /*!< UART Rx MDMA Handle parameters      */
#endif /* HAL_MDMA_MODULE_ENABLED */

	HAL_LockTypeDef           Lock;            /*!< Locking object                     */

	__IO HAL_UART_StateTypeDef    gState;      /*!< UART state information related to global Handle management
						     and also related to Tx operations.
						     This parameter can be a value of @ref HAL_UART_StateTypeDef */

	__IO HAL_UART_StateTypeDef    RxState;     /*!< UART state information related to Rx operations.
						     This parameter can be a value of @ref HAL_UART_StateTypeDef */

	__IO uint32_t             ErrorCode;       /*!< UART Error code                    */

} UART_HandleTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup UART_Exported_Constants UART Exported Constants
  * @{
  */

/** @defgroup UART_Stop_Bits   UART Number of Stop Bits
  * @{
  */
#define UART_STOPBITS_0_5                    USART_CR2_STOP_0                     /*!< UART frame with 0.5 stop bit  */
#define UART_STOPBITS_1                     ((uint32_t)0x00000000U)               /*!< UART frame with 1 stop bit    */
#define UART_STOPBITS_1_5                   (USART_CR2_STOP_0 | USART_CR2_STOP_1) /*!< UART frame with 1.5 stop bits */
#define UART_STOPBITS_2                      USART_CR2_STOP_1                     /*!< UART frame with 2 stop bits   */
/**
  * @}
  */

/** @defgroup UART_Parity  UART Parity
  * @{
  */
#define UART_PARITY_NONE                    ((uint32_t)0x00000000U)                        /*!< No parity   */
#define UART_PARITY_EVEN                    ((uint32_t)USART_CR1_PCE)                      /*!< Even parity */
#define UART_PARITY_ODD                     ((uint32_t)(USART_CR1_PCE | USART_CR1_PS))     /*!< Odd parity  */
/**
  * @}
  */

/** @defgroup UART_Hardware_Flow_Control UART Hardware Flow Control
  * @{
  */
#define UART_HWCONTROL_NONE                  ((uint32_t)0x00000000U)                          /*!< No hardware control       */
#define UART_HWCONTROL_RTS                   ((uint32_t)USART_CR3_RTSE)                       /*!< Request To Send           */
#define UART_HWCONTROL_CTS                   ((uint32_t)USART_CR3_CTSE)                       /*!< Clear To Send             */
#define UART_HWCONTROL_RTS_CTS               ((uint32_t)(USART_CR3_RTSE | USART_CR3_CTSE))    /*!< Request and Clear To Send */
/**
  * @}
  */

/** @defgroup UART_Mode UART Transfer Mode
  * @{
  */
#define UART_MODE_RX                        ((uint32_t)USART_CR1_RE)                    /*!< RX mode        */
#define UART_MODE_TX                        ((uint32_t)USART_CR1_TE)                    /*!< TX mode        */
#define UART_MODE_TX_RX                     ((uint32_t)(USART_CR1_TE | USART_CR1_RE))   /*!< RX and TX mode */
/**
  * @}
  */

/** @defgroup UART_State  UART State
  * @{
  */
#define UART_STATE_DISABLE                  ((uint32_t)0x00000000U)         /*!< UART disabled  */
#define UART_STATE_ENABLE                   ((uint32_t)USART_CR1_UE)        /*!< UART enabled   */
/**
  * @}
  */

/** @defgroup UART_Over_Sampling UART Over Sampling
  * @{
  */
#define UART_OVERSAMPLING_16                ((uint32_t)0x00000000U)         /*!< Oversampling by 16 */
#define UART_OVERSAMPLING_8                 ((uint32_t)USART_CR1_OVER8)     /*!< Oversampling by 8  */
/**
  * @}
  */

/** @defgroup UART_OneBit_Sampling UART One Bit Sampling Method
  * @{
  */
#define UART_ONE_BIT_SAMPLE_DISABLE         ((uint32_t)0x00000000U)         /*!< One-bit sampling disable */
#define UART_ONE_BIT_SAMPLE_ENABLE          ((uint32_t)USART_CR3_ONEBIT)    /*!< One-bit sampling enable  */
/**
  * @}
  */

/** @defgroup UART_Prescaler  UART Prescaler
  * @{
  */
#define UART_PRESCALER_DIV1    ((uint32_t)0x00000000U)  /*!< UART clock /1   */
#define UART_PRESCALER_DIV2    ((uint32_t)0x00000001U)  /*!< UART clock /2   */
#define UART_PRESCALER_DIV4    ((uint32_t)0x00000002U)  /*!< UART clock /4   */
#define UART_PRESCALER_DIV6    ((uint32_t)0x00000003U)  /*!< UART clock /6   */
#define UART_PRESCALER_DIV8    ((uint32_t)0x00000004U)  /*!< UART clock /8   */
#define UART_PRESCALER_DIV10   ((uint32_t)0x00000005U)  /*!< UART clock /10  */
#define UART_PRESCALER_DIV12   ((uint32_t)0x00000006U)  /*!< UART clock /12  */
#define UART_PRESCALER_DIV16   ((uint32_t)0x00000007U)  /*!< UART clock /16  */
#define UART_PRESCALER_DIV32   ((uint32_t)0x00000008U)  /*!< UART clock /32  */
#define UART_PRESCALER_DIV64   ((uint32_t)0x00000009U)  /*!< UART clock /64  */
#define UART_PRESCALER_DIV128  ((uint32_t)0x0000000AU)  /*!< UART clock /128 */
#define UART_PRESCALER_DIV256  ((uint32_t)0x0000000BU)  /*!< UART clock /256 */

/**
  * @}
  */

/** @defgroup UART_FIFO_mode UART FIFO mode
  * @brief    UART FIFO  mode
  * @{
  */
#define UART_FIFOMODE_DISABLE        ((uint32_t)0x00000000U)       /*!< FIFO mode disable */
#define UART_FIFOMODE_ENABLE         ((uint32_t)USART_CR1_FIFOEN)  /*!< FIFO mode enable  */
/**
  * @}
  */

/** @defgroup UART_TXFIFO_threshold_level UART TXFIFO threshold level
  * @brief    UART TXFIFO level
  * @{
  */
#define UART_TXFIFO_THRESHOLD_1EIGHTHFULL    ((uint32_t)0x00000000U)                               /*!< TXFIFO reaches 1/8 of its depth */
#define UART_TXFIFO_THRESHOLD_1QUARTERFULL   ((uint32_t)USART_CR3_TXFTCFG_0)                       /*!< TXFIFO reaches 1/4 of its depth */
#define UART_TXFIFO_THRESHOLD_HALFFULL       ((uint32_t)USART_CR3_TXFTCFG_1)                       /*!< TXFIFO reaches 1/2 of its depth */
#define UART_TXFIFO_THRESHOLD_3QUARTERSFULL  ((uint32_t)(USART_CR3_TXFTCFG_0 | USART_CR3_TXFTCFG_1)) /*!< TXFIFO reaches 3/4 of its depth */
#define UART_TXFIFO_THRESHOLD_7EIGHTHFULL    ((uint32_t)USART_CR3_TXFTCFG_2)                       /*!< TXFIFO reaches 7/8 of its depth */
#define UART_TXFIFO_THRESHOLD_EMPTY          ((uint32_t)(USART_CR3_TXFTCFG_2 | USART_CR3_TXFTCFG_0)) /*!< TXFIFO becomes empty            */
/**
  * @}
  */

/** @defgroup UART_RXFIFO_threshold_level UART RXFIFO threshold level
  * @brief    UART RXFIFO level
  * @{
  */
#define UART_RXFIFO_THRESHOLD_1EIGHTHFULL    ((uint32_t)0x00000000U)                               /*!< RXFIFO reaches 1/8 of its depth */
#define UART_RXFIFO_THRESHOLD_1QUARTERFULL   ((uint32_t)USART_CR3_RXFTCFG_0)                       /*!< RXFIFO reaches 1/4 of its depth */
#define UART_RXFIFO_THRESHOLD_HALFFULL       ((uint32_t)USART_CR3_RXFTCFG_1)                       /*!< RXFIFO reaches 1/2 of its depth */
#define UART_RXFIFO_THRESHOLD_3QUARTERSFULL  ((uint32_t)(USART_CR3_RXFTCFG_0 | USART_CR3_RXFTCFG_1)) /*!< RXFIFO reaches 3/4 of its depth */
#define UART_RXFIFO_THRESHOLD_7EIGHTHFULL    ((uint32_t)USART_CR3_RXFTCFG_2)                       /*!< RXFIFO reaches 7/8 of its depth */
#define UART_RXFIFO_THRESHOLD_FULL           ((uint32_t)(USART_CR3_RXFTCFG_2 | USART_CR3_RXFTCFG_0)) /*!< RXFIFO becomes full             */
/**
  * @}
  */

/** @defgroup UART_AutoBaud_Rate_Mode    UART Advanced Feature AutoBaud Rate Mode
  * @{
  */
#define UART_ADVFEATURE_AUTOBAUDRATE_ONSTARTBIT    ((uint32_t)0x00000000U)           /*!< Auto Baud rate detection on start bit            */
#define UART_ADVFEATURE_AUTOBAUDRATE_ONFALLINGEDGE ((uint32_t)USART_CR2_ABRMODE_0)   /*!< Auto Baud rate detection on falling edge         */
#define UART_ADVFEATURE_AUTOBAUDRATE_ON0X7FFRAME   ((uint32_t)USART_CR2_ABRMODE_1)   /*!< Auto Baud rate detection on 0x7F frame detection */
#define UART_ADVFEATURE_AUTOBAUDRATE_ON0X55FRAME   ((uint32_t)USART_CR2_ABRMODE)     /*!< Auto Baud rate detection on 0x55 frame detection */
/**
  * @}
  */

/** @defgroup UART_Receiver_TimeOut UART Receiver TimeOut
  * @{
  */
#define UART_RECEIVER_TIMEOUT_DISABLE       ((uint32_t)0x00000000U)                 /*!< UART receiver timeout disable */
#define UART_RECEIVER_TIMEOUT_ENABLE        ((uint32_t)USART_CR2_RTOEN)             /*!< UART receiver timeout enable  */
/**
  * @}
  */

/** @defgroup UART_LIN    UART Local Interconnection Network mode
  * @{
  */
#define UART_LIN_DISABLE                    ((uint32_t)0x00000000U)                /*!< Local Interconnect Network disable */
#define UART_LIN_ENABLE                     ((uint32_t)USART_CR2_LINEN)            /*!< Local Interconnect Network enable  */
/**
  * @}
  */

/** @defgroup UART_LIN_Break_Detection  UART LIN Break Detection
  * @{
  */
#define UART_LINBREAKDETECTLENGTH_10B       ((uint32_t)0x00000000U)               /*!< LIN 10-bit break detection length */
#define UART_LINBREAKDETECTLENGTH_11B       ((uint32_t)USART_CR2_LBDL)            /*!< LIN 11-bit break detection length  */
/**
  * @}
  */

/** @defgroup UART_DMA_Tx    UART DMA Tx
  * @{
  */
#define UART_DMA_TX_DISABLE                 ((uint32_t)0x00000000U)               /*!< UART DMA TX disabled */
#define UART_DMA_TX_ENABLE                  ((uint32_t)USART_CR3_DMAT)            /*!< UART DMA TX enabled  */
/**
  * @}
  */

/** @defgroup UART_DMA_Rx   UART DMA Rx
  * @{
  */
#define UART_DMA_RX_DISABLE                 ((uint32_t)0x00000000U)                 /*!< UART DMA RX disabled */
#define UART_DMA_RX_ENABLE                  ((uint32_t)USART_CR3_DMAR)              /*!< UART DMA RX enabled  */
/**
  * @}
  */

/** @defgroup UART_Half_Duplex_Selection  UART Half Duplex Selection
  * @{
  */
#define UART_HALF_DUPLEX_DISABLE            ((uint32_t)0x00000000U)                 /*!< UART half-duplex disabled */
#define UART_HALF_DUPLEX_ENABLE             ((uint32_t)USART_CR3_HDSEL)             /*!< UART half-duplex enabled  */
/**
  * @}
  */

/** @defgroup UART_WakeUp_Methods   UART WakeUp Methods
  * @{
  */
#define UART_WAKEUPMETHOD_IDLELINE          ((uint32_t)0x00000000U)                 /*!< UART wake-up on idle line    */
#define UART_WAKEUPMETHOD_ADDRESSMARK       ((uint32_t)USART_CR1_WAKE)              /*!< UART wake-up on address mark */
/**
  * @}
  */

/** @defgroup UART_Request_Parameters UART Request Parameters
  * @{
  */
#define UART_AUTOBAUD_REQUEST               ((uint32_t)USART_RQR_ABRRQ)        /*!< Auto-Baud Rate Request      */
#define UART_SENDBREAK_REQUEST              ((uint32_t)USART_RQR_SBKRQ)        /*!< Send Break Request          */
#define UART_MUTE_MODE_REQUEST              ((uint32_t)USART_RQR_MMRQ)         /*!< Mute Mode Request           */
#define UART_RXDATA_FLUSH_REQUEST           ((uint32_t)USART_RQR_RXFRQ)        /*!< Receive Data flush Request  */
#define UART_TXDATA_FLUSH_REQUEST           ((uint32_t)USART_RQR_TXFRQ)        /*!< Transmit data flush Request */
/**
  * @}
  */

/** @defgroup UART_Advanced_Features_Initialization_Type  UART Advanced Feature Initialization Type
  * @{
  */
#define UART_ADVFEATURE_NO_INIT                 ((uint32_t)0x00000000U)        /*!< No advanced feature initialization       */
#define UART_ADVFEATURE_TXINVERT_INIT           ((uint32_t)0x00000001U)        /*!< TX pin active level inversion            */
#define UART_ADVFEATURE_RXINVERT_INIT           ((uint32_t)0x00000002U)        /*!< RX pin active level inversion            */
#define UART_ADVFEATURE_DATAINVERT_INIT         ((uint32_t)0x00000004U)        /*!< Binary data inversion                    */
#define UART_ADVFEATURE_SWAP_INIT               ((uint32_t)0x00000008U)        /*!< TX/RX pins swap                          */
#define UART_ADVFEATURE_RXOVERRUNDISABLE_INIT   ((uint32_t)0x00000010U)        /*!< RX overrun disable                       */
#define UART_ADVFEATURE_DMADISABLEONERROR_INIT  ((uint32_t)0x00000020U)        /*!< DMA disable on Reception Error           */
#define UART_ADVFEATURE_AUTOBAUDRATE_INIT       ((uint32_t)0x00000040U)        /*!< Auto Baud rate detection initialization  */
#define UART_ADVFEATURE_MSBFIRST_INIT           ((uint32_t)0x00000080U)        /*!< Most significant bit sent/received first */
/**
  * @}
  */

/** @defgroup UART_Tx_Inv UART Advanced Feature TX Pin Active Level Inversion
  * @{
  */
#define UART_ADVFEATURE_TXINV_DISABLE       ((uint32_t)0x00000000U)            /*!< TX pin active level inversion disable */
#define UART_ADVFEATURE_TXINV_ENABLE        ((uint32_t)USART_CR2_TXINV)        /*!< TX pin active level inversion enable  */
/**
  * @}
  */

/** @defgroup UART_Rx_Inv UART Advanced Feature RX Pin Active Level Inversion
  * @{
  */
#define UART_ADVFEATURE_RXINV_DISABLE       ((uint32_t)0x00000000U)             /*!< RX pin active level inversion disable */
#define UART_ADVFEATURE_RXINV_ENABLE        ((uint32_t)USART_CR2_RXINV)         /*!< RX pin active level inversion enable  */
/**
  * @}
  */

/** @defgroup UART_Data_Inv  UART Advanced Feature Binary Data Inversion
  * @{
  */
#define UART_ADVFEATURE_DATAINV_DISABLE     ((uint32_t)0x00000000U)             /*!< Binary data inversion disable */
#define UART_ADVFEATURE_DATAINV_ENABLE      ((uint32_t)USART_CR2_DATAINV)       /*!< Binary data inversion enable  */
/**
  * @}
  */

/** @defgroup UART_Rx_Tx_Swap UART Advanced Feature RX TX Pins Swap
  * @{
  */
#define UART_ADVFEATURE_SWAP_DISABLE        ((uint32_t)0x00000000U)             /*!< TX/RX pins swap disable */
#define UART_ADVFEATURE_SWAP_ENABLE         ((uint32_t)USART_CR2_SWAP)          /*!< TX/RX pins swap enable  */
/**
  * @}
  */

/** @defgroup UART_Overrun_Disable  UART Advanced Feature Overrun Disable
  * @{
  */
#define UART_ADVFEATURE_OVERRUN_ENABLE      ((uint32_t)0x00000000U)             /*!< RX overrun enable  */
#define UART_ADVFEATURE_OVERRUN_DISABLE     ((uint32_t)USART_CR3_OVRDIS)        /*!< RX overrun disable */
/**
  * @}
  */

/** @defgroup UART_AutoBaudRate_Enable  UART Advanced Feature Auto BaudRate Enable
  * @{
  */
#define UART_ADVFEATURE_AUTOBAUDRATE_DISABLE   ((uint32_t)0x00000000U)          /*!< RX Auto Baud rate detection enable  */
#define UART_ADVFEATURE_AUTOBAUDRATE_ENABLE    ((uint32_t)USART_CR2_ABREN)      /*!< RX Auto Baud rate detection disable */
/**
  * @}
  */

/** @defgroup UART_DMA_Disable_on_Rx_Error   UART Advanced Feature DMA Disable On Rx Error
  * @{
  */
#define UART_ADVFEATURE_DMA_ENABLEONRXERROR    ((uint32_t)0x00000000U)          /*!< DMA enable on Reception Error  */
#define UART_ADVFEATURE_DMA_DISABLEONRXERROR   ((uint32_t)USART_CR3_DDRE)       /*!< DMA disable on Reception Error */
/**
  * @}
  */

/** @defgroup UART_MSB_First   UART Advanced Feature MSB First
  * @{
  */
#define UART_ADVFEATURE_MSBFIRST_DISABLE    ((uint32_t)0x00000000U)             /*!< Most significant bit sent/received first disable */
#define UART_ADVFEATURE_MSBFIRST_ENABLE     ((uint32_t)USART_CR2_MSBFIRST)      /*!< Most significant bit sent/received first enable  */
/**
  * @}
  */

/** @defgroup UART_Stop_Mode_Enable   UART Advanced Feature Stop Mode Enable
  * @{
  */
#define UART_ADVFEATURE_STOPMODE_DISABLE    ((uint32_t)0x00000000U)             /*!< UART stop mode disable */
#define UART_ADVFEATURE_STOPMODE_ENABLE     ((uint32_t)USART_CR1_UESM)          /*!< UART stop mode enable  */
/**
  * @}
  */

/** @defgroup UART_Mute_Mode   UART Advanced Feature Mute Mode Enable
  * @{
  */
#define UART_ADVFEATURE_MUTEMODE_DISABLE    ((uint32_t)0x00000000U)             /*!< UART mute mode disable */
#define UART_ADVFEATURE_MUTEMODE_ENABLE     ((uint32_t)USART_CR1_MME)           /*!< UART mute mode enable  */
/**
  * @}
  */

/** @defgroup UART_CR2_ADDRESS_LSB_POS    UART Address-matching LSB Position In CR2 Register
  * @{
  */
#define UART_CR2_ADDRESS_LSB_POS            ((uint32_t)24U)                    /*!< UART address-matching LSB position in CR2 register */
/**
  * @}
  */

/** @defgroup UART_WakeUp_from_Stop_Selection   UART WakeUp From Stop Selection
  * @{
  */
#define UART_WAKEUP_ON_ADDRESS              ((uint32_t)0x00000000U)             /*!< UART wake-up on address                         */
#define UART_WAKEUP_ON_STARTBIT             ((uint32_t)USART_CR3_WUS_1)         /*!< UART wake-up on start bit                       */
#define UART_WAKEUP_ON_READDATA_NONEMPTY    ((uint32_t)USART_CR3_WUS)           /*!< UART wake-up on receive data register not empty */
#define UART_WAKEUP_ON_RXFIFO_THRESHOLD     ((uint32_t)USART_CR3_RXFTIE)        /*!< UART wake-up when the RXFIFO reaches threshold  */
#define UART_WAKEUP_ON_RXFIFO_FULL          ((uint32_t)USART_CR1_RXFFIE)        /*!< UART wake-up when the RXFIFO is full            */
#define UART_WAKEUP_ON_TXFIFO_THRESHOLD     ((uint32_t)USART_CR3_TXFTIE)        /*!< UART wake-up when the TXFIFO reaches threshold  */
#define UART_WAKEUP_ON_TXFIFO_EMPTY         ((uint32_t)USART_CR1_TXFEIE)        /*!< UART wake-up when the TXFIFO is  empty          */
/**
  * @}
  */

/** @defgroup UART_DriverEnable_Polarity      UART DriverEnable Polarity
  * @{
  */
#define UART_DE_POLARITY_HIGH               ((uint32_t)0x00000000U)             /*!< Driver enable signal is active high */
#define UART_DE_POLARITY_LOW                ((uint32_t)USART_CR3_DEP)           /*!< Driver enable signal is active low  */
/**
  * @}
  */

/** @defgroup UART_CR1_DEAT_ADDRESS_LSB_POS    UART Driver Enable Assertion Time LSB Position In CR1 Register
  * @{
  */
#define UART_CR1_DEAT_ADDRESS_LSB_POS       ((uint32_t)21U)                    /*!< UART Driver Enable assertion time LSB position in CR1 register */
/**
  * @}
  */

/** @defgroup UART_CR1_DEDT_ADDRESS_LSB_POS    UART Driver Enable DeAssertion Time LSB Position In CR1 Register
  * @{
  */
#define UART_CR1_DEDT_ADDRESS_LSB_POS       ((uint32_t)16U)                    /*!< UART Driver Enable de-assertion time LSB position in CR1 register */
/**
  * @}
  */

/** @defgroup UART_Interruption_Mask    UART Interruptions Flag Mask
  * @{
  */
#define UART_IT_MASK                        ((uint32_t)0x001FU)                 /*!< UART interruptions flags mask */
/**
  * @}
  */

/** @defgroup UART_TimeOut_Value    UART polling-based communications time-out value
  * @{
  */
#define HAL_UART_TIMEOUT_VALUE              0x1FFFFFFU                          /*!< UART polling-based communications time-out value */
/**
  * @}
  */

/** @defgroup UART_Flags     UART Status Flags
  *        Elements values convention: 0xXXXX
  *           - 0xXXXX  : Flag mask in the ISR register
  * @{
  */
#define UART_FLAG_TXFT                      USART_ISR_TXFT   /*!< UART TXFIFO threshold flag                */
#define UART_FLAG_RXFT                      USART_ISR_RXFT   /*!< UART RXFIFO threshold flag                */
#define UART_FLAG_RXFF                      USART_ISR_RXFF   /*!< UART RXFIFO Full flag                     */
#define UART_FLAG_TXFE                      USART_ISR_TXFE   /*!< UART TXFIFO Empty flag                    */
#define UART_FLAG_REACK                     USART_ISR_REACK  /*!< UART receive enable acknowledge flag      */
#define UART_FLAG_TEACK                     USART_ISR_TEACK  /*!< UART transmit enable acknowledge flag     */
#define UART_FLAG_WUF                       USART_ISR_WUF    /*!< UART wake-up from stop mode flag          */
#define UART_FLAG_RWU                       USART_ISR_RWU    /*!< UART receiver wake-up from mute mode flag */
#define UART_FLAG_SBKF                      USART_ISR_SBKF   /*!< UART send break flag                      */
#define UART_FLAG_CMF                       USART_ISR_CMF    /*!< UART character match flag                 */
#define UART_FLAG_BUSY                      USART_ISR_BUSY   /*!< UART busy flag                            */
#define UART_FLAG_ABRF                      USART_ISR_ABRF   /*!< UART auto Baud rate flag                  */
#define UART_FLAG_ABRE                      USART_ISR_ABRE   /*!< UART uto Baud rate error                  */
#define UART_FLAG_RTOF                      USART_ISR_RTOF   /*!< UART receiver timeout flag                */
#define UART_FLAG_CTS                       USART_ISR_CTS    /*!< UART clear to send flag                   */
#define UART_FLAG_CTSIF                     USART_ISR_CTSIF  /*!< UART clear to send interrupt flag         */
#define UART_FLAG_LBDF                      USART_ISR_LBDF   /*!< UART LIN break detection flag             */
#define UART_FLAG_TXE                       USART_ISR_TXE    /*!< UART transmit data register empty         */
#define UART_FLAG_TXFNF                     USART_ISR_TXE    /*!< UART TXFIFO not full                      */
#define UART_FLAG_TC                        USART_ISR_TC     /*!< UART transmission complete                */
#define UART_FLAG_RXNE                      USART_ISR_RXNE   /*!< UART read data register not empty         */
#define UART_FLAG_RXFNE                     USART_ISR_RXNE   /*!< UART RXFIFO not empty                     */
#define UART_FLAG_IDLE                      USART_ISR_IDLE   /*!< UART idle flag                            */
#define UART_FLAG_ORE                       USART_ISR_ORE    /*!< UART overrun error                        */
#define UART_FLAG_NE                        USART_ISR_NE     /*!< UART noise error                          */
#define UART_FLAG_FE                        USART_ISR_FE     /*!< UART frame error                          */
#define UART_FLAG_PE                        USART_ISR_PE     /*!< UART parity error                         */
/**
  * @}
  */

/** @defgroup UART_Interrupt_definition   UART Interrupts Definition
  *        Elements values convention: 000ZZZZZ0XXYYYYYb
  *           - YYYYY  : Interrupt source position in the XX register (5bits)
  *           - XX  : Interrupt source register (2bits)
  *                 - 01: CR1 register
  *                 - 10: CR2 register
  *                 - 11: CR3 register
  *           - ZZZZZ  : Flag position in the ISR register(5bits)
  * @{
  */
#define UART_IT_PE                          ((uint32_t)0x0028U)                  /*!< UART parity error interruption                 */
#define UART_IT_TXE                         ((uint32_t)0x0727U)                  /*!< UART transmit data register empty interruption */
#define UART_IT_TC                          ((uint32_t)0x0626U)                  /*!< UART transmission complete interruption        */
#define UART_IT_RXNE                        ((uint32_t)0x0525U)                  /*!< UART read data register not empty interruption */
#define UART_IT_LBD                         ((uint32_t)0x0846U)                  /*!< UART LIN break detection interruption          */
#define UART_IT_CTS                         ((uint32_t)0x096AU)                  /*!< UART CTS interruption                          */
#define UART_IT_CM                          ((uint32_t)0x112EU)                  /*!< UART character match interruption              */
#define UART_IT_WUF                         ((uint32_t)0x1476U)                  /*!< UART wake-up from stop mode interruption       */
#define UART_IT_RXFF                        ((uint16_t)0x183FU)
#define UART_IT_TXFE                        ((uint16_t)0x173EU)
#define UART_IT_RXFT                        ((uint16_t)0x1A7CU)
#define UART_IT_TXFT                        ((uint16_t)0x1B77U)


/**       Elements values convention: 000000000XXYYYYYb
  *           - YYYYY  : Interrupt source position in the XX register (5bits)
  *           - XX  : Interrupt source register (2bits)
  *                 - 01: CR1 register
  *                 - 10: CR2 register
  *                 - 11: CR3 register
  */
#define UART_IT_ERR                         ((uint32_t)0x0060U)                  /*!< UART error interruption         */

/**       Elements values convention: 0000ZZZZ00000000b
  *           - ZZZZ  : Flag position in the ISR register(4bits)
  */
#define UART_IT_ORE                         ((uint32_t)0x0300U)                  /*!< UART overrun error interruption */
#define UART_IT_NE                          ((uint32_t)0x0200U)                  /*!< UART noise error interruption   */
#define UART_IT_FE                          ((uint32_t)0x0100U)                  /*!< UART frame error interruption   */
/**
  * @}
  */

/** @defgroup UART_IT_CLEAR_Flags  UART Interruption Clear Flags
  * @{
  */
#define UART_CLEAR_PEF                       USART_ICR_PECF            /*!< Parity Error Clear Flag           */
#define UART_CLEAR_FEF                       USART_ICR_FECF            /*!< Framing Error Clear Flag          */
#define UART_CLEAR_NEF                       USART_ICR_NCF             /*!< Noise detected Clear Flag         */
#define UART_CLEAR_OREF                      USART_ICR_ORECF           /*!< OverRun Error Clear Flag          */
#define UART_CLEAR_IDLEF                     USART_ICR_IDLECF          /*!< IDLE line detected Clear Flag     */
#define UART_CLEAR_TXFECF                    USART_ICR_TXFECF          /*!< TXFIFO empty clear flag           */
#define UART_CLEAR_TCF                       USART_ICR_TCCF            /*!< Transmission Complete Clear Flag  */
#define UART_CLEAR_LBDF                      USART_ICR_LBDCF           /*!< LIN Break Detection Clear Flag    */
#define UART_CLEAR_CTSF                      USART_ICR_CTSCF           /*!< CTS Interrupt Clear Flag          */
#define UART_CLEAR_RTOF                      USART_ICR_RTOCF           /*!< Receiver Time Out Clear Flag      */
#define UART_CLEAR_CMF                       USART_ICR_CMCF            /*!< Character Match Clear Flag        */
#define UART_CLEAR_WUF                       USART_ICR_WUCF            /*!< Wake Up from stop mode Clear Flag */
/**
  * @}
  */


/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup UART_Exported_Macros UART Exported Macros
  * @{
  */

/** @brief  Reset UART handle states.
 * @param  __HANDLE__: UART handle.
 * @retval None
 */
#define __HAL_UART_RESET_HANDLE_STATE(__HANDLE__)  \
	do {                                                  \
		(__HANDLE__)->gState = HAL_UART_STATE_RESET;  \
		(__HANDLE__)->RxState = HAL_UART_STATE_RESET; \
	} while (0)

/** @brief  Flush the UART Data registers.
 * @param  __HANDLE__: specifies the UART Handle.
 * @retval None
 */
#define __HAL_UART_FLUSH_DRREGISTER(__HANDLE__)      \
	do {                                         \
		SET_BIT((__HANDLE__)->Instance->RQR, \
			UART_RXDATA_FLUSH_REQUEST);  \
		SET_BIT((__HANDLE__)->Instance->RQR, \
			UART_TXDATA_FLUSH_REQUEST);  \
	}  while (0)

/** @brief  Clear the specified UART pending flag.
 * @param  __HANDLE__: specifies the UART Handle.
 * @param  __FLAG__: specifies the flag to check.
 *          This parameter can be any combination of the following values:
 *            @arg UART_FLAG_WUF:   Wake up from stop mode flag
 *            @arg UART_FLAG_CMF:   Character match flag
 *            @arg UART_FLAG_RTOF:  Receiver timeout flag
 *            @arg UART_FLAG_CTS:   CTS Change flag (not available for UART4 and UART5)
 *            @arg UART_FLAG_LBD:   LIN Break detection flag
 *            @arg UART_FLAG_TC:    Transmission Complete flag
 *            @arg UART_FLAG_TXFE:  TXFIFO Empty flag
 *            @arg UART_FLAG_IDLE:  Idle Line detection flag
 *            @arg UART_FLAG_ORE:   OverRun Error flag
 *            @arg UART_FLAG_NE:    Noise Error flag
 *            @arg UART_FLAG_FE:    Framing Error flag
 *            @arg UART_FLAG_PE:    Parity Error flag
 * @retval The new state of __FLAG__ (TRUE or FALSE).
 */
#define __HAL_UART_CLEAR_FLAG(__HANDLE__, __FLAG__) \
	((__HANDLE__)->Instance->ICR = (__FLAG__))

/** @brief  Clear the UART PE pending flag.
 * @param  __HANDLE__: specifies the UART Handle.
 * @retval None
 */
#define __HAL_UART_CLEAR_PEFLAG(__HANDLE__) \
	__HAL_UART_CLEAR_FLAG((__HANDLE__), UART_CLEAR_PEF)

/** @brief  Clear the UART FE pending flag.
 * @param  __HANDLE__: specifies the UART Handle.
 * @retval None
 */
#define __HAL_UART_CLEAR_FEFLAG(__HANDLE__) \
	__HAL_UART_CLEAR_FLAG((__HANDLE__), UART_CLEAR_FEF)

/** @brief  Clear the UART NE pending flag.
 * @param  __HANDLE__: specifies the UART Handle.
 * @retval None
 */
#define __HAL_UART_CLEAR_NEFLAG(__HANDLE__) \
	__HAL_UART_CLEAR_FLAG((__HANDLE__), UART_CLEAR_NEF)

/** @brief  Clear the UART ORE pending flag.
 * @param  __HANDLE__: specifies the UART Handle.
 * @retval None
 */
#define __HAL_UART_CLEAR_OREFLAG(__HANDLE__) \
	__HAL_UART_CLEAR_FLAG((__HANDLE__), UART_CLEAR_OREF)

/** @brief  Clear the UART IDLE pending flag.
 * @param  __HANDLE__: specifies the UART Handle.
 * @retval None
 */
#define __HAL_UART_CLEAR_IDLEFLAG(__HANDLE__) \
	__HAL_UART_CLEAR_FLAG((__HANDLE__), UART_CLEAR_IDLEF)

/** @brief  Clear the UART TX FIFO empty clear flag.
 * @param  __HANDLE__: specifies the UART Handle.
 * @retval None
 */
#define __HAL_UART_CLEAR_TXFECF(__HANDLE__) \
	__HAL_UART_CLEAR_FLAG((__HANDLE__), UART_CLEAR_TXFECF)

/** @brief  Check whether the specified UART flag is set or not.
 * @param  __HANDLE__: specifies the UART Handle.
 * @param  __FLAG__: specifies the flag to check.
 *        This parameter can be one of the following values:
 *            @arg UART_FLAG_TXFT: TXFIFO threshold flag
 *            @arg UART_FLAG_RXFT: RXFIFO threshold flag
 *            @arg UART_FLAG_RXFF:  RXFIFO Full flag
 *            @arg UART_FLAG_TXFE:  TXFIFO Empty flag
 *            @arg UART_FLAG_REACK: Receive enable acknowledge flag
 *            @arg UART_FLAG_TEACK: Transmit enable acknowledge flag
 *            @arg UART_FLAG_WUF:   Wake up from stop mode flag
 *            @arg UART_FLAG_RWU:   Receiver wake up flag (if the UART in mute mode)
 *            @arg UART_FLAG_SBKF:  Send Break flag
 *            @arg UART_FLAG_CMF:   Character match flag
 *            @arg UART_FLAG_BUSY:  Busy flag
 *            @arg UART_FLAG_ABRF:  Auto Baud rate detection flag
 *            @arg UART_FLAG_ABRE:  Auto Baud rate detection error flag
 *            @arg UART_FLAG_RTOF:  Receiver timeout flag
 *            @arg UART_FLAG_CTS:   CTS Change flag
 *            @arg UART_FLAG_LBD:   LIN Break detection flag
 *            @arg UART_FLAG_TXE:   Transmit data register empty flag
 *            @arg UART_FLAG_TC:    Transmission Complete flag
 *            @arg UART_FLAG_RXNE:  Receive data register not empty flag
 *            @arg UART_FLAG_IDLE:  Idle Line detection flag
 *            @arg UART_FLAG_ORE:   OverRun Error flag
 *            @arg.UART_FLAG_NE:    Noise Error flag
 *            @arg UART_FLAG_FE:    Framing Error flag
 *            @arg UART_FLAG_PE:    Parity Error flag
 * @retval The new state of __FLAG__ (TRUE or FALSE).
 */
#define __HAL_UART_GET_FLAG(__HANDLE__, __FLAG__) \
	(((__HANDLE__)->Instance->ISReg & (__FLAG__)) == (__FLAG__))

/** @brief  Enable the specified UART interrupt.
 * @param  __HANDLE__: specifies the UART Handle.
 * @param  __INTERRUPT__: specifies the UART interrupt source to enable.
 *          This parameter can be one of the following values:
 *            @arg UART_IT_RXFF :  RXFIFO Full interrupt
 *            @arg UART_IT_TXFE :  TXFIFO Empty interrupt
 *            @arg UART_IT_RXFT :  RXFIFO threshold interrupt
 *            @arg UART_IT_TXFT :  TXFIFO threshold interrupt
 *            @arg UART_IT_WUF:  Wakeup from stop mode interrupt
 *            @arg UART_IT_CM:   Character match interrupt
 *            @arg UART_IT_CTS:  CTS change interrupt
 *            @arg UART_IT_LBD:  LIN Break detection interrupt
 *            @arg UART_IT_TXE:  Transmit Data Register empty interrupt
 *            @arg UART_IT_TC:   Transmission complete interrupt
 *            @arg UART_IT_RXNE: Receive Data register not empty interrupt
 *            @arg UART_IT_IDLE: Idle line detection interrupt
 *            @arg UART_IT_PE:   Parity Error interrupt
 *            @arg UART_IT_ERR:  Error interrupt (Frame error, noise error, overrun error)
 * @retval None
 */
#define __HAL_UART_ENABLE_IT(__HANDLE__, __INTERRUPT__) \
	(((((uint8_t)((__INTERRUPT__) & 0xFF)) >> 5U) == 1) ? \
	 ((__HANDLE__)->Instance->CR1 |= \
	  (1U << ((__INTERRUPT__) & UART_IT_MASK))) : \
	 ((((uint8_t)((__INTERRUPT__) & 0xFF)) >> 5U) == 2) ? \
	 ((__HANDLE__)->Instance->CR2 |= \
	  (1U << ((__INTERRUPT__) & UART_IT_MASK))) : \
	 ((__HANDLE__)->Instance->CR3 |= \
	  (1U << ((__INTERRUPT__) & UART_IT_MASK))))


/** @brief  Disable the specified UART interrupt.
 * @param  __HANDLE__: specifies the UART Handle.
 * @param  __INTERRUPT__: specifies the UART interrupt source to disable.
 *          This parameter can be one of the following values:
 *            @arg UART_IT_RXFF :  RXFIFO Full interrupt
 *            @arg UART_IT_TXFE :  TXFIFO Empty interrupt
 *            @arg UART_IT_RXFT :  RXFIFO threshold interrupt
 *            @arg UART_IT_TXFT :  TXFIFO threshold interrupt
 *            @arg UART_IT_WUF:  Wakeup from stop mode interrupt
 *            @arg UART_IT_CM:   Character match interrupt
 *            @arg UART_IT_CTS:  CTS change interrupt
 *            @arg UART_IT_LBD:  LIN Break detection interrupt
 *            @arg UART_IT_TXE:  Transmit Data Register empty interrupt
 *            @arg UART_IT_TC:   Transmission complete interrupt
 *            @arg UART_IT_RXNE: Receive Data register not empty interrupt
 *            @arg UART_IT_IDLE: Idle line detection interrupt
 *            @arg UART_IT_PE:   Parity Error interrupt
 *            @arg UART_IT_ERR:  Error interrupt (Frame error, noise error, overrun error)
 * @retval None
 */
#define __HAL_UART_DISABLE_IT(__HANDLE__, __INTERRUPT__)  \
	(((((uint8_t)((__INTERRUPT__) & 0xFF)) >> 5U) == 1) ? \
	 ((__HANDLE__)->Instance->CR1 &= \
	  ~(1U << ((__INTERRUPT__) & UART_IT_MASK))) : \
	 ((((uint8_t)((__INTERRUPT__) & 0xFF)) >> 5U) == 2) ? \
	 ((__HANDLE__)->Instance->CR2 &= \
	  ~(1U << ((__INTERRUPT__) & UART_IT_MASK))) : \
	 ((__HANDLE__)->Instance->CR3 &= \
	  ~(1U << ((__INTERRUPT__) & UART_IT_MASK))))

/** @brief  Check whether the specified UART interrupt has occurred or not.
 * @param  __HANDLE__: specifies the UART Handle.
 * @param  __IT__: specifies the UART interrupt to check.
 *          This parameter can be one of the following values:
 *            @arg UART_IT_RXFF :  RXFIFO Full interrupt
 *            @arg UART_IT_TXFE :  TXFIFO Empty interrupt
 *            @arg UART_IT_RXFT :  RXFIFO threshold interrupt
 *            @arg UART_IT_TXFT :  TXFIFO threshold interrupt
 *            @arg UART_IT_WUF:  Wakeup from stop mode interrupt
 *            @arg UART_IT_CM:   Character match interrupt
 *            @arg UART_IT_CTS:  CTS change interrupt
 *            @arg UART_IT_LBD:  LIN Break detection interrupt
 *            @arg UART_IT_TXE:  Transmit Data Register empty interrupt
 *            @arg UART_IT_TC:   Transmission complete interrupt
 *            @arg UART_IT_RXNE: Receive Data register not empty interrupt
 *            @arg UART_IT_IDLE: Idle line detection interrupt
 *            @arg UART_IT_ORE:  OverRun Error interrupt
 *            @arg UART_IT_NE:   Noise Error interrupt
 *            @arg UART_IT_FE:   Framing Error interrupt
 *            @arg UART_IT_PE:   Parity Error interrupt
 * @retval The new state of __IT__ (TRUE or FALSE).
 */
#define __HAL_UART_GET_IT(__HANDLE__, __IT__) \
	((__HANDLE__)->Instance->ISReg & ((uint32_t)1 << ((__IT__) >> 0x08)))

/** @brief  Check whether the specified UART interrupt source is enabled or not.
 * @param  __HANDLE__: specifies the UART Handle.
 * @param  __IT__: specifies the UART interrupt source to check.
 *          This parameter can be one of the following values:
 *            @arg UART_IT_RXFF :  RXFIFO Full interrupt
 *            @arg UART_IT_TXFE :  TXFIFO Empty interrupt
 *            @arg UART_IT_RXFT :  RXFIFO threshold interrupt
 *            @arg UART_IT_TXFT :  TXFIFO threshold interrupt
 *            @arg UART_IT_CTS: CTS change interrupt (not available for UART4 and UART5)
 *            @arg UART_IT_LBD: LIN Break detection interrupt
 *            @arg UART_IT_TXE: Transmit Data Register empty interrupt
 *            @arg UART_IT_TC:  Transmission complete interrupt
 *            @arg UART_IT_RXNE: Receive Data register not empty interrupt
 *            @arg UART_IT_IDLE: Idle line detection interrupt
 *            @arg UART_IT_ORE: OverRun Error interrupt
 *            @arg UART_IT_NE: Noise Error interrupt
 *            @arg UART_IT_FE: Framing Error interrupt
 *            @arg UART_IT_PE: Parity Error interrupt
 * @retval The new state of __IT__ (TRUE or FALSE).
 */
#define __HAL_UART_GET_IT_SOURCE(__HANDLE__, __IT__) \
	((((((uint8_t)(__IT__)) >> 5U) == 1) ? \
	  (__HANDLE__)->Instance->CR1 : \
	  (((((uint8_t)(__IT__)) >> 5U) == 2) ? \
	   (__HANDLE__)->Instance->CR2 : \
	   (__HANDLE__)->Instance->CR3)) & \
	 ((uint32_t)1 << (((uint16_t)(__IT__)) & UART_IT_MASK)))

/** @brief  Clear the specified UART ISR flag, in setting the proper ICR register flag.
 * @param  __HANDLE__: specifies the UART Handle.
 * @param  __IT_CLEAR__: specifies the interrupt clear register flag that needs to be set
 *                       to clear the corresponding interrupt
 *          This parameter can be one of the following values:
 *            @arg UART_CLEAR_PEF: Parity Error Clear Flag
 *            @arg UART_CLEAR_FEF: Framing Error Clear Flag
 *            @arg UART_CLEAR_NEF: Noise detected Clear Flag
 *            @arg UART_CLEAR_OREF: OverRun Error Clear Flag
 *            @arg UART_CLEAR_IDLEF: IDLE line detected Clear Flag
 *            @arg UART_CLEAR_TCF: Transmission Complete Clear Flag
 *            @arg UART_CLEAR_LBDF: LIN Break Detection Clear Flag
 *            @arg UART_CLEAR_CTSF: CTS Interrupt Clear Flag
 *            @arg UART_CLEAR_RTOF: Receiver Time Out Clear Flag
 *            @arg UART_CLEAR_CMF: Character Match Clear Flag
 *            @arg UART_CLEAR_WUF:  Wake Up from stop mode Clear Flag
 *            @arg UART_CLEAR_TXFECF: TXFIFO empty Clear Flag
 * @retval None
 */
#define __HAL_UART_CLEAR_IT(__HANDLE__, __IT_CLEAR__) \
	((__HANDLE__)->Instance->ICR = (uint32_t)(__IT_CLEAR__))

/** @brief  Set a specific UART request flag.
 * @param  __HANDLE__: specifies the UART Handle.
 * @param  __REQ__: specifies the request flag to set
 *          This parameter can be one of the following values:
 *            @arg UART_AUTOBAUD_REQUEST: Auto-Baud Rate Request
 *            @arg UART_SENDBREAK_REQUEST: Send Break Request
 *            @arg UART_MUTE_MODE_REQUEST: Mute Mode Request
 *            @arg UART_RXDATA_FLUSH_REQUEST: Receive Data flush Request
 *            @arg UART_TXDATA_FLUSH_REQUEST: Transmit data flush Request
 * @retval None
 */
#define __HAL_UART_SEND_REQ(__HANDLE__, __REQ__) \
	((__HANDLE__)->Instance->RQR |= (uint32_t)(__REQ__))

/** @brief  Enable the UART one bit sample method.
 * @param  __HANDLE__: specifies the UART Handle.
 * @retval None
 */
#define __HAL_UART_ONE_BIT_SAMPLE_ENABLE(__HANDLE__) \
	((__HANDLE__)->Instance->CR3 |= USART_CR3_ONEBIT)

/** @brief  Disable the UART one bit sample method.
 * @param  __HANDLE__: specifies the UART Handle.
 * @retval None
 */
#define __HAL_UART_ONE_BIT_SAMPLE_DISABLE(__HANDLE__) \
	((__HANDLE__)->Instance->CR3 &= (uint32_t)~((uint32_t)USART_CR3_ONEBIT))

/** @brief  Enable UART.
 * @param  __HANDLE__: specifies the UART Handle.
 * @retval None
 */
#define __HAL_UART_ENABLE(__HANDLE__) \
	((__HANDLE__)->Instance->CR1 |=  USART_CR1_UE)

/** @brief  Disable UART.
 * @param  __HANDLE__: specifies the UART Handle.
 * @retval None
 */
#define __HAL_UART_DISABLE(__HANDLE__) \
	((__HANDLE__)->Instance->CR1 &=  ~USART_CR1_UE)

/** @brief  Enable TX UART
 * @param  __HANDLE__: specifies the UART Handle.
 * @retval None
 */
#define __HAL_UART_ENABLE_TX(__HANDLE__) \
	((__HANDLE__)->Instance->CR1 |=  USART_CR1_TE)

/** @brief  Disable TX UART
 * @param  __HANDLE__: specifies the UART Handle.
 * @retval None
 */
#define __HAL_UART_DISABLE_TX(__HANDLE__) \
	((__HANDLE__)->Instance->CR1 &=  ~USART_CR1_TE)

/** @brief  Enable CTS flow control
 *         This macro allows to enable CTS hardware flow control for a given UART instance,
 *         without need to call HAL_UART_Init() function.
 *         As involving direct access to UART registers, usage of this macro should be fully endorsed by user.
 * @note   As macro is expected to be used for modifying CTS Hw flow control feature activation, without need
 *         for USART instance Deinit/Init, following conditions for macro call should be fulfilled :
 *           - UART instance should have already been initialised (through call of HAL_UART_Init() )
 *           - macro could only be called when corresponding UART instance is disabled (i.e. __HAL_UART_DISABLE(__HANDLE__))
 *             and should be followed by an Enable macro (i.e. __HAL_UART_ENABLE(__HANDLE__)).
 * @param  __HANDLE__: specifies the UART Handle.
 * @retval None
 */
#define __HAL_UART_HWCONTROL_CTS_ENABLE(__HANDLE__)                    \
	do {                                                           \
		SET_BIT((__HANDLE__)->Instance->CR3, USART_CR3_CTSE);  \
		(__HANDLE__)->Init.HwFlowCtl |= USART_CR3_CTSE;        \
	} while (0)

/** @brief  Disable CTS flow control.
 * @note   This macro allows to disable CTS hardware flow control for a given UART instance,
 *         without need to call HAL_UART_Init() function.
 *         As involving direct access to UART registers, usage of this macro should be fully endorsed by user.
 * @note   As macro is expected to be used for modifying CTS Hw flow control feature activation, without need
 *         for USART instance Deinit/Init, following conditions for macro call should be fulfilled :
 *           - UART instance should have already been initialised (through call of HAL_UART_Init() )
 *           - macro could only be called when corresponding UART instance is disabled (i.e. __HAL_UART_DISABLE(__HANDLE__))
 *             and should be followed by an Enable macro (i.e. __HAL_UART_ENABLE(__HANDLE__)).
 * @param  __HANDLE__: specifies the UART Handle.
 * @retval None
 */
#define __HAL_UART_HWCONTROL_CTS_DISABLE(__HANDLE__)                    \
	do {                                                            \
		CLEAR_BIT((__HANDLE__)->Instance->CR3, USART_CR3_CTSE); \
		(__HANDLE__)->Init.HwFlowCtl &= ~(USART_CR3_CTSE);      \
	} while (0)

/** @brief  Enable RTS flow control.
 * @note   This macro allows to enable RTS hardware flow control for a given UART instance,
 *         without need to call HAL_UART_Init() function.
 *         As involving direct access to UART registers, usage of this macro should be fully endorsed by user.
 * @note   As macro is expected to be used for modifying RTS Hw flow control feature activation, without need
 *         for USART instance Deinit/Init, following conditions for macro call should be fulfilled :
 *           - UART instance should have already been initialised (through call of HAL_UART_Init() )
 *           - macro could only be called when corresponding UART instance is disabled (i.e. __HAL_UART_DISABLE(__HANDLE__))
 *             and should be followed by an Enable macro (i.e. __HAL_UART_ENABLE(__HANDLE__)).
 * @param  __HANDLE__: specifies the UART Handle.
 * @retval None
 */
#define __HAL_UART_HWCONTROL_RTS_ENABLE(__HANDLE__)                   \
	do {                                                          \
		SET_BIT((__HANDLE__)->Instance->CR3, USART_CR3_RTSE); \
		(__HANDLE__)->Init.HwFlowCtl |= USART_CR3_RTSE;       \
	} while (0)

/** @brief  Disable RTS flow control.
 * @note   This macro allows to disable RTS hardware flow control for a given UART instance,
 *         without need to call HAL_UART_Init() function.
 *         As involving direct access to UART registers, usage of this macro should be fully endorsed by user.
 * @note   As macro is expected to be used for modifying RTS Hw flow control feature activation, without need
 *         for USART instance Deinit/Init, following conditions for macro call should be fulfilled :
 *           - UART instance should have already been initialised (through call of HAL_UART_Init() )
 *           - macro could only be called when corresponding UART instance is disabled (i.e. __HAL_UART_DISABLE(__HANDLE__))
 *             and should be followed by an Enable macro (i.e. __HAL_UART_ENABLE(__HANDLE__)).
 * @param  __HANDLE__: specifies the UART Handle.
 * @retval None
 */
#define __HAL_UART_HWCONTROL_RTS_DISABLE(__HANDLE__)                   \
	do {                                                           \
		CLEAR_BIT((__HANDLE__)->Instance->CR3, USART_CR3_RTSE);\
		(__HANDLE__)->Init.HwFlowCtl &= ~(USART_CR3_RTSE);     \
	} while (0)

/**
 * @}
  */

/* Private variables -----------------------------------------------------*/
/** @defgroup UART_Private_Variables   UART Private Variables
  * @{
  */
static const uint16_t presc_table[12] = {
	1, 2, 4, 6, 8, 10, 12, 16, 32, 64, 128, 256
};

/** @brief  BRR division operation to set BRR register in 8-bit oversampling
 * mode.
 * @param  clockfreq: UART clock.
 * @param  baud_rate: Baud rate set by the user.
 * @param  prescaler: UART prescaler value.
 * @retval Division result
 */
static inline uint32_t uart_div_sampling8(unsigned long clockfreq,
					  uint32_t baud_rate,
					  uint32_t prescaler)
{
	uint32_t scaled_freq = clockfreq / presc_table[prescaler];

	return ((scaled_freq * 2) + (baud_rate / 2)) / baud_rate;

}

/** @brief  BRR division operation to set BRR register in 16-bit oversampling
 * mode.
 * @param  clockfreq: UART clock.
 * @param  baud_rate: Baud rate set by the user.
 * @param  prescaler: UART prescaler value.
 * @retval Division result
 */
static inline uint32_t uart_div_sampling16(unsigned long clockfreq,
					   uint32_t baud_rate,
					   uint32_t prescaler)
{
	uint32_t scaled_freq = clockfreq / presc_table[prescaler];

	return (scaled_freq + (baud_rate / 2)) / baud_rate;

}

/* Private macros --------------------------------------------------------*/
/** @defgroup UART_Private_Macros   UART Private Macros
  * @{
  */
/** @brief  Check UART Baud rate.
  * @param  __BAUDRATE__: Baudrate specified by the user.
  *         The maximum Baud Rate is derived from the maximum clock on MP1 (i.e. 100 MHz)
  *         divided by the smallest oversampling used on the USART (i.e. 8)
  * @retval SET (__BAUDRATE__ is valid) or RESET (__BAUDRATE__ is invalid)
  */
#define IS_UART_BAUDRATE(__BAUDRATE__) ((__BAUDRATE__) < 12500001U)

/** @brief  Check UART assertion time.
  * @param  __TIME__: 5-bit value assertion time.
  * @retval Test result (TRUE or FALSE).
  */
#define IS_UART_ASSERTIONTIME(__TIME__)    ((__TIME__) <= 0x1FU)

/** @brief  Check UART deassertion time.
  * @param  __TIME__: 5-bit value deassertion time.
  * @retval Test result (TRUE or FALSE).
  */
#define IS_UART_DEASSERTIONTIME(__TIME__) ((__TIME__) <= 0x1FU)

/**
  * @brief Ensure that UART frame number of stop bits is valid.
  * @param __STOPBITS__: UART frame number of stop bits.
  * @retval SET (__STOPBITS__ is valid) or RESET (__STOPBITS__ is invalid)
  */
#define IS_UART_STOPBITS(__STOPBITS__) \
	(((__STOPBITS__) == UART_STOPBITS_0_5) || \
	 ((__STOPBITS__) == UART_STOPBITS_1)   || \
	 ((__STOPBITS__) == UART_STOPBITS_1_5) || \
	 ((__STOPBITS__) == UART_STOPBITS_2))

/**
  * @brief Ensure that UART frame parity is valid.
  * @param __PARITY__: UART frame parity.
  * @retval SET (__PARITY__ is valid) or RESET (__PARITY__ is invalid)
  */
#define IS_UART_PARITY(__PARITY__) \
	(((__PARITY__) == UART_PARITY_NONE) || \
	 ((__PARITY__) == UART_PARITY_EVEN) || \
	 ((__PARITY__) == UART_PARITY_ODD))

/**
  * @brief Ensure that UART hardware flow control is valid.
  * @param __CONTROL__: UART hardware flow control.
  * @retval SET (__CONTROL__ is valid) or RESET (__CONTROL__ is invalid)
  */
#define IS_UART_HARDWARE_FLOW_CONTROL(__CONTROL__) \
	(((__CONTROL__) == UART_HWCONTROL_NONE) || \
	 ((__CONTROL__) == UART_HWCONTROL_RTS)  || \
	 ((__CONTROL__) == UART_HWCONTROL_CTS)  || \
	 ((__CONTROL__) == UART_HWCONTROL_RTS_CTS))

/**
  * @brief Ensure that UART communication mode is valid.
  * @param __MODE__: UART communication mode.
  * @retval SET (__MODE__ is valid) or RESET (__MODE__ is invalid)
  */
#define IS_UART_MODE(__MODE__) \
	((((__MODE__) & (~((uint32_t)(UART_MODE_TX_RX)))) == \
	  (uint32_t)0x00) && \
	 ((__MODE__) != (uint32_t)0x00))

/**
  * @brief Ensure that UART state is valid.
  * @param __STATE__: UART state.
  * @retval SET (__STATE__ is valid) or RESET (__STATE__ is invalid)
  */
#define IS_UART_STATE(__STATE__) (((__STATE__) == UART_STATE_DISABLE) || \
				  ((__STATE__) == UART_STATE_ENABLE))

/**
  * @brief Ensure that UART oversampling is valid.
  * @param __SAMPLING__: UART oversampling.
  * @retval SET (__SAMPLING__ is valid) or RESET (__SAMPLING__ is invalid)
  */
#define IS_UART_OVERSAMPLING(__SAMPLING__) \
	(((__SAMPLING__) == UART_OVERSAMPLING_16) || \
	 ((__SAMPLING__) == UART_OVERSAMPLING_8))

/**
  * @brief Ensure that UART frame sampling is valid.
  * @param __ONEBIT__: UART frame sampling.
  * @retval SET (__ONEBIT__ is valid) or RESET (__ONEBIT__ is invalid)
  */
#define IS_UART_ONE_BIT_SAMPLE(__ONEBIT__) \
	(((__ONEBIT__) == UART_ONE_BIT_SAMPLE_DISABLE) || \
	 ((__ONEBIT__) == UART_ONE_BIT_SAMPLE_ENABLE))

/**
  * @brief Ensure that UART auto Baud rate detection mode is valid.
  * @param __MODE__: UART auto Baud rate detection mode.
  * @retval SET (__MODE__ is valid) or RESET (__MODE__ is invalid)
  */
#define IS_UART_ADVFEATURE_AUTOBAUDRATEMODE(__MODE__) \
	(((__MODE__) == UART_ADVFEATURE_AUTOBAUDRATE_ONSTARTBIT)    || \
	 ((__MODE__) == UART_ADVFEATURE_AUTOBAUDRATE_ONFALLINGEDGE) || \
	 ((__MODE__) == UART_ADVFEATURE_AUTOBAUDRATE_ON0X7FFRAME)   || \
	 ((__MODE__) == UART_ADVFEATURE_AUTOBAUDRATE_ON0X55FRAME))

/**
  * @brief Ensure that UART receiver timeout setting is valid.
  * @param __TIMEOUT__: UART receiver timeout setting.
  * @retval SET (__TIMEOUT__ is valid) or RESET (__TIMEOUT__ is invalid)
  */
#define IS_UART_RECEIVER_TIMEOUT(__TIMEOUT__) \
	(((__TIMEOUT__) == UART_RECEIVER_TIMEOUT_DISABLE) || \
	 ((__TIMEOUT__) == UART_RECEIVER_TIMEOUT_ENABLE))

/**
  * @brief Ensure that UART LIN state is valid.
  * @param __LIN__: UART LIN state.
  * @retval SET (__LIN__ is valid) or RESET (__LIN__ is invalid)
  */
#define IS_UART_LIN(__LIN__) \
	(((__LIN__) == UART_LIN_DISABLE) || \
	 ((__LIN__) == UART_LIN_ENABLE))

/**
  * @brief Ensure that UART LIN break detection length is valid.
  * @param __LENGTH__: UART LIN break detection length.
  * @retval SET (__LENGTH__ is valid) or RESET (__LENGTH__ is invalid)
  */
#define IS_UART_LIN_BREAK_DETECT_LENGTH(__LENGTH__) \
	(((__LENGTH__) == UART_LINBREAKDETECTLENGTH_10B) || \
	 ((__LENGTH__) == UART_LINBREAKDETECTLENGTH_11B))

/**
  * @brief Ensure that UART DMA TX state is valid.
  * @param __DMATX__: UART DMA TX state.
  * @retval SET (__DMATX__ is valid) or RESET (__DMATX__ is invalid)
  */
#define IS_UART_DMA_TX(__DMATX__) \
	(((__DMATX__) == UART_DMA_TX_DISABLE) || \
	 ((__DMATX__) == UART_DMA_TX_ENABLE))

/**
  * @brief Ensure that UART DMA RX state is valid.
  * @param __DMARX__: UART DMA RX state.
  * @retval SET (__DMARX__ is valid) or RESET (__DMARX__ is invalid)
  */
#define IS_UART_DMA_RX(__DMARX__) \
	(((__DMARX__) == UART_DMA_RX_DISABLE) || \
	 ((__DMARX__) == UART_DMA_RX_ENABLE))

/**
  * @brief Ensure that UART half-duplex state is valid.
  * @param __HDSEL__: UART half-duplex state.
  * @retval SET (__HDSEL__ is valid) or RESET (__HDSEL__ is invalid)
  */
#define IS_UART_HALF_DUPLEX(__HDSEL__) \
	(((__HDSEL__) == UART_HALF_DUPLEX_DISABLE) || \
	 ((__HDSEL__) == UART_HALF_DUPLEX_ENABLE))

/**
  * @brief Ensure that UART wake-up method is valid.
  * @param __WAKEUP__: UART wake-up method .
  * @retval SET (__WAKEUP__ is valid) or RESET (__WAKEUP__ is invalid)
  */
#define IS_UART_WAKEUPMETHOD(__WAKEUP__) \
	(((__WAKEUP__) == UART_WAKEUPMETHOD_IDLELINE) || \
	 ((__WAKEUP__) == UART_WAKEUPMETHOD_ADDRESSMARK))

/**
  * @brief Ensure that UART request parameter is valid.
  * @param __PARAM__: UART request parameter.
  * @retval SET (__PARAM__ is valid) or RESET (__PARAM__ is invalid)
  */
#define IS_UART_REQUEST_PARAMETER(__PARAM__) \
	(((__PARAM__) == UART_AUTOBAUD_REQUEST)     || \
	 ((__PARAM__) == UART_SENDBREAK_REQUEST)    || \
	 ((__PARAM__) == UART_MUTE_MODE_REQUEST)    || \
	 ((__PARAM__) == UART_RXDATA_FLUSH_REQUEST) || \
	 ((__PARAM__) == UART_TXDATA_FLUSH_REQUEST))

/**
  * @brief Ensure that UART advanced features initialization is valid.
  * @param __INIT__: UART advanced features initialization.
  * @retval SET (__INIT__ is valid) or RESET (__INIT__ is invalid)
  */
#define IS_UART_ADVFEATURE_INIT(__INIT__) \
	((__INIT__) <= (UART_ADVFEATURE_NO_INIT                | \
			UART_ADVFEATURE_TXINVERT_INIT          | \
			UART_ADVFEATURE_RXINVERT_INIT          | \
			UART_ADVFEATURE_DATAINVERT_INIT        | \
			UART_ADVFEATURE_SWAP_INIT              | \
			UART_ADVFEATURE_RXOVERRUNDISABLE_INIT  | \
			UART_ADVFEATURE_DMADISABLEONERROR_INIT | \
			UART_ADVFEATURE_AUTOBAUDRATE_INIT      | \
			UART_ADVFEATURE_MSBFIRST_INIT))

/**
  * @brief Ensure that UART frame TX inversion setting is valid.
  * @param __TXINV__: UART frame TX inversion setting.
  * @retval SET (__TXINV__ is valid) or RESET (__TXINV__ is invalid)
  */
#define IS_UART_ADVFEATURE_TXINV(__TXINV__) \
	(((__TXINV__) == UART_ADVFEATURE_TXINV_DISABLE) || \
	 ((__TXINV__) == UART_ADVFEATURE_TXINV_ENABLE))

/**
  * @brief Ensure that UART frame RX inversion setting is valid.
  * @param __RXINV__: UART frame RX inversion setting.
  * @retval SET (__RXINV__ is valid) or RESET (__RXINV__ is invalid)
  */
#define IS_UART_ADVFEATURE_RXINV(__RXINV__) \
	(((__RXINV__) == UART_ADVFEATURE_RXINV_DISABLE) || \
	 ((__RXINV__) == UART_ADVFEATURE_RXINV_ENABLE))

/**
  * @brief Ensure that UART frame data inversion setting is valid.
  * @param __DATAINV__: UART frame data inversion setting.
  * @retval SET (__DATAINV__ is valid) or RESET (__DATAINV__ is invalid)
  */
#define IS_UART_ADVFEATURE_DATAINV(__DATAINV__) \
	(((__DATAINV__) == UART_ADVFEATURE_DATAINV_DISABLE) || \
	 ((__DATAINV__) == UART_ADVFEATURE_DATAINV_ENABLE))

/**
  * @brief Ensure that UART frame RX/TX pins swap setting is valid.
  * @param __SWAP__: UART frame RX/TX pins swap setting.
  * @retval SET (__SWAP__ is valid) or RESET (__SWAP__ is invalid)
  */
#define IS_UART_ADVFEATURE_SWAP(__SWAP__) \
	(((__SWAP__) == UART_ADVFEATURE_SWAP_DISABLE) || \
	 ((__SWAP__) == UART_ADVFEATURE_SWAP_ENABLE))

/**
  * @brief Ensure that UART frame overrun setting is valid.
  * @param __OVERRUN__: UART frame overrun setting.
  * @retval SET (__OVERRUN__ is valid) or RESET (__OVERRUN__ is invalid)
  */
#define IS_UART_OVERRUN(__OVERRUN__) \
	(((__OVERRUN__) == UART_ADVFEATURE_OVERRUN_ENABLE) || \
	 ((__OVERRUN__) == UART_ADVFEATURE_OVERRUN_DISABLE))

/**
  * @brief Ensure that UART auto Baud rate state is valid.
  * @param __AUTOBAUDRATE__: UART auto Baud rate state.
  * @retval SET (__AUTOBAUDRATE__ is valid) or RESET (__AUTOBAUDRATE__ is invalid)
  */
#define IS_UART_ADVFEATURE_AUTOBAUDRATE(__AUTOBAUDRATE__) \
	(((__AUTOBAUDRATE__) == UART_ADVFEATURE_AUTOBAUDRATE_DISABLE) || \
	 ((__AUTOBAUDRATE__) == UART_ADVFEATURE_AUTOBAUDRATE_ENABLE))

/**
  * @brief Ensure that UART DMA enabling or disabling on error setting is valid.
  * @param __DMA__: UART DMA enabling or disabling on error setting.
  * @retval SET (__DMA__ is valid) or RESET (__DMA__ is invalid)
  */
#define IS_UART_ADVFEATURE_DMAONRXERROR(__DMA__) \
	(((__DMA__) == UART_ADVFEATURE_DMA_ENABLEONRXERROR) || \
	 ((__DMA__) == UART_ADVFEATURE_DMA_DISABLEONRXERROR))

/**
  * @brief Ensure that UART frame MSB first setting is valid.
  * @param __MSBFIRST__: UART frame MSB first setting.
  * @retval SET (__MSBFIRST__ is valid) or RESET (__MSBFIRST__ is invalid)
  */
#define IS_UART_ADVFEATURE_MSBFIRST(__MSBFIRST__) \
	(((__MSBFIRST__) == UART_ADVFEATURE_MSBFIRST_DISABLE) || \
	 ((__MSBFIRST__) == UART_ADVFEATURE_MSBFIRST_ENABLE))

/**
  * @brief Ensure that UART stop mode state is valid.
  * @param __STOPMODE__: UART stop mode state.
  * @retval SET (__STOPMODE__ is valid) or RESET (__STOPMODE__ is invalid)
  */
#define IS_UART_ADVFEATURE_STOPMODE(__STOPMODE__) \
	(((__STOPMODE__) == UART_ADVFEATURE_STOPMODE_DISABLE) || \
	 ((__STOPMODE__) == UART_ADVFEATURE_STOPMODE_ENABLE))

/**
  * @brief Ensure that UART mute mode state is valid.
  * @param __MUTE__: UART mute mode state.
  * @retval SET (__MUTE__ is valid) or RESET (__MUTE__ is invalid)
  */
#define IS_UART_MUTE_MODE(__MUTE__) \
	(((__MUTE__) == UART_ADVFEATURE_MUTEMODE_DISABLE) || \
	 ((__MUTE__) == UART_ADVFEATURE_MUTEMODE_ENABLE))

/**
  * @brief Ensure that UART wake-up selection is valid.
  * @param __WAKE__: UART wake-up selection.
  * @retval SET (__WAKE__ is valid) or RESET (__WAKE__ is invalid)
  */
#define IS_UART_WAKEUP_SELECTION(__WAKE__) \
	(((__WAKE__) == UART_WAKEUP_ON_ADDRESS)            || \
	 ((__WAKE__) == UART_WAKEUP_ON_STARTBIT)           || \
	 ((__WAKE__) == UART_WAKEUP_ON_READDATA_NONEMPTY)  || \
	 ((__WAKE__) == UART_WAKEUP_ON_RXFIFO_THRESHOLD)   || \
	 ((__WAKE__) == UART_WAKEUP_ON_RXFIFO_FULL)        || \
	 ((__WAKE__) == UART_WAKEUP_ON_TXFIFO_THRESHOLD)   || \
	 ((__WAKE__) == UART_WAKEUP_ON_TXFIFO_EMPTY))

/**
  * @brief Ensure that UART driver enable polarity is valid.
  * @param __POLARITY__: UART driver enable polarity.
  * @retval SET (__POLARITY__ is valid) or RESET (__POLARITY__ is invalid)
  */
#define IS_UART_DE_POLARITY(__POLARITY__) \
	(((__POLARITY__) == UART_DE_POLARITY_HIGH) || \
	 ((__POLARITY__) == UART_DE_POLARITY_LOW))

/**
  * @brief Ensure that UART Prescaler is valid.
  * @param __PRESCALER__: UART Prescaler value.
  * @retval SET (__PRESCALER__ is valid) or RESET (__PRESCALER__ is invalid)
  */
#define IS_UART_PRESCALER(__PRESCALER__) \
	(((__PRESCALER__) == UART_PRESCALER_DIV1)   || \
	 ((__PRESCALER__) == UART_PRESCALER_DIV2)   || \
	 ((__PRESCALER__) == UART_PRESCALER_DIV4)   || \
	 ((__PRESCALER__) == UART_PRESCALER_DIV6)   || \
	 ((__PRESCALER__) == UART_PRESCALER_DIV8)   || \
	 ((__PRESCALER__) == UART_PRESCALER_DIV10)  || \
	 ((__PRESCALER__) == UART_PRESCALER_DIV12)  || \
	 ((__PRESCALER__) == UART_PRESCALER_DIV16)  || \
	 ((__PRESCALER__) == UART_PRESCALER_DIV32)  || \
	 ((__PRESCALER__) == UART_PRESCALER_DIV64)  || \
	 ((__PRESCALER__) == UART_PRESCALER_DIV128) || \
	 ((__PRESCALER__) == UART_PRESCALER_DIV256))

/**
  * @brief Ensure that UART FIFO mode is valid.
  * @param __STATE__: UART FIFO mode.
  * @retval SET (__STATE__ is valid) or RESET (__STATE__ is invalid)
  */
#define IS_UART_FIFO_MODE_STATE(__STATE__) \
	(((__STATE__) == UART_FIFOMODE_DISABLE) || \
	 ((__STATE__) == UART_FIFOMODE_ENABLE))

/**
  * @brief Ensure that UART TXFIFO threshold level is valid.
  * @param __THRESHOLD__: UART TXFIFO threshold level.
  * @retval SET (__THRESHOLD__ is valid) or RESET (__THRESHOLD__ is invalid)
  */
#define IS_UART_TXFIFO_THRESHOLD(__THRESHOLD__) \
	((((__THRESHOLD__) == UART_TXFIFO_THRESHOLD_1EIGHTHFULL)   || \
	  ((__THRESHOLD__) == UART_TXFIFO_THRESHOLD_1QUARTERFULL) || \
	  ((__THRESHOLD__) == UART_TXFIFO_THRESHOLD_HALFFULL)      || \
	  ((__THRESHOLD__) == UART_TXFIFO_THRESHOLD_3QUARTERSFULL) || \
	  ((__THRESHOLD__) == UART_TXFIFO_THRESHOLD_7EIGHTHFULL))  || \
	 ((__THRESHOLD__) == UART_TXFIFO_THRESHOLD_EMPTY))

/**
  * @brief Ensure that UART RXFIFO threshold level is valid.
  * @param __THRESHOLD__: UART RXFIFO threshold level.
  * @retval SET (__THRESHOLD__ is valid) or RESET (__THRESHOLD__ is invalid)
  */
#define IS_UART_RXFIFO_THRESHOLD(__THRESHOLD__) \
	((((__THRESHOLD__) == UART_RXFIFO_THRESHOLD_1EIGHTHFULL)   || \
	  ((__THRESHOLD__) == UART_RXFIFO_THRESHOLD_1QUARTERFULL)  || \
	  ((__THRESHOLD__) == UART_RXFIFO_THRESHOLD_HALFFULL)      || \
	  ((__THRESHOLD__) == UART_RXFIFO_THRESHOLD_3QUARTERSFULL) || \
	  ((__THRESHOLD__) == UART_RXFIFO_THRESHOLD_7EIGHTHFULL))  || \
	 ((__THRESHOLD__) == UART_RXFIFO_THRESHOLD_FULL))

/* Include UART HAL Extension module */
#include "stm32mp1xx_hal_uart_ex.h"

/* Initialization and de-initialization functions  ****************************/
HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart);

/* IO operation functions *****************************************************/
HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData,
				    uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData,
				   uint16_t Size, uint32_t Timeout);

/* Peripheral State and Errors functions  **************************************************/
HAL_UART_StateTypeDef HAL_UART_GetState(UART_HandleTypeDef *huart);
uint32_t              HAL_UART_GetError(UART_HandleTypeDef *huart);

/* Private functions -----------------------------------------------------------*/
/** @addtogroup UART_Private_Functions UART Private Functions
  * @{
  */

HAL_StatusTypeDef UART_SetConfig(UART_HandleTypeDef *huart);
HAL_StatusTypeDef UART_CheckIdleState(UART_HandleTypeDef *huart);
HAL_StatusTypeDef UART_WaitOnFlagUntilTimeout(UART_HandleTypeDef *huart,
					      uint32_t Flag, FlagStatus Status,
					      uint32_t Tickstart,
					      uint32_t Timeout);
void UART_AdvFeatureConfig(UART_HandleTypeDef *huart);

#ifdef __cplusplus
}
#endif

#endif /* __STM32MP1xx_HAL_UART_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
