/* SoC support for ESP8266/ESP32*.
 *
 * Provide a unified interface where possible, from ESP8266 Non-OS SDK & esp-idf
 * headers.
 *
 */
#pragma once

#ifdef ESP8266
#define SPI_IDX 0

#include "ets_sys.h"
#include "eagle_soc.h"
#include "driver_lib/include/driver/uart_register.h"
#include "driver_lib/include/driver/spi_register.h"

/* Harmonise register names between ESP8266 & -32 */
#define SPI_CMD_REG(X) SPI_CMD(X)
#define SPI_W0_REG(X) SPI_W0(X)
#define SPI_ADDR_REG(X) SPI_ADDR(X)
#define SPI_EXT2_REG(X) SPI_EXT2(X)
#define SPI_RD_STATUS_REG(X) SPI_RD_STATUS(X)

#define UART_CLKDIV_REG(X) UART_CLKDIV(X)
#define UART_CLKDIV_M (UART_CLKDIV_CNT << UART_CLKDIV_S)

#define SPI_ST 0x7 /* field in SPI_EXT2_REG */

#define REG_READ READ_PERI_REG
#define REG_WRITE WRITE_PERI_REG

#define ETS_UART0_INUM ETS_UART_INUM

#define UART_RXFIFO_CNT_M (0xFF)

#else /* ESP32/ESP32S2 */
#define SPI_IDX 1

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "soc/soc.h"
#include "soc/uart_reg.h"
#include "soc/gpio_reg.h"
#ifdef ESP32
// ESP32 registers no present on ESP32S2

#include "soc/spi_reg.h"

#else
// ESP32S2 renamed SPI flash controller to SPI_MEM
//
// for now, defined the registers we use back to the same
// names that are used in ESP32
#include "soc/spi_mem_reg.h"

#define SPI_EXT2_REG(X) SPI_MEM_FSM_REG(X)
#define SPI_ST SPI_MEM_ST

#define SPI_RD_STATUS_REG(X) SPI_MEM_RD_STATUS_REG(X)
#define SPI_CMD_REG(X) SPI_MEM_CMD_REG(X)
#define SPI_CTRL_REG(X) SPI_MEM_CTRL_REG(X)
#define SPI_ADDR_REG(X) SPI_MEM_ADDR_REG(X)

// CMD fields
#define SPI_FLASH_RDSR SPI_MEM_FLASH_RDSR
#define SPI_FLASH_WREN SPI_MEM_FLASH_WREN
#define SPI_FLASH_SE   SPI_MEM_FLASH_SE
#define SPI_FLASH_BE   SPI_MEM_FLASH_BE

// CTRL_REG fields
#define SPI_WRSR_2B SPI_MEM_WRSR_2B

#endif  // ESP32S2

/* ESP32 & S2 UART register naming is a bit more consistent */
#define UART_INT_CLR(X) UART_INT_CLR_REG(X)
#define UART_INT_ST(X) UART_INT_ST_REG(X)
#define UART_INT_ENA(X) UART_INT_ENA_REG(X)
#define UART_STATUS(X) UART_STATUS_REG(X)
#ifndef ESP32S2
#define UART_FIFO(X) UART_FIFO_REG(X)
#else
#define UART_FIFO(X) UART_FIFO_AHB_REG(X)
#endif

#endif // ESP32/S2
