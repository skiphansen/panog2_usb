#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "gpio_defs.h"
#include "timer.h"
#include "pano_io.h"
#include "usb_core.h"

#define DEBUG_LOGGING         1
#define VERBOSE_DEBUG_LOGGING 1
#include "log.h"

#define REG_WR(reg, wr_data)       *((volatile uint32_t *)(reg)) = (wr_data)
#define REG_RD(reg)                *((volatile uint32_t *)(reg))

struct usb_device gRootHubDev;

void DumpUsbRegs(void);

static uint32_t usbhw_reg_read(uint32_t addr)
{
    return *((volatile uint32_t*)(CONFIG_USB_BASE + addr));
}

//-----------------------------------------------------------------
// main
//-----------------------------------------------------------------
int main(int argc, char *argv[])
{
    int i;
    unsigned char Buf[256];
    int Id = 0;
    uint32_t Temp;
    uint32_t Led;
    int Fast = 0;
    int Err;

    LOG("usb_test compiled " __DATE__ " " __TIME__ "\n");

    usbhw_init(CONFIG_USB_BASE);

// Set LED GPIO's to output
    Temp = REG_RD(GPIO_BASE + GPIO_DIRECTION);
    Temp |= GPIO_BIT_RED_LED | GPIO_BIT_GREEN_LED |GPIO_BIT_BLUE_LED | GPIO_BIT_USB_RESET;
    REG_WR(GPIO_BASE + GPIO_DIRECTION,Temp);
 // reset USB subsystem
#if 0
    LOG("USB registers before reset:\n");
    DumpUsbRegs();
#endif

    REG_WR(GPIO_BASE + GPIO_OUTPUT_SET,GPIO_BIT_USB_RESET);
    LOG("USB reset\n");
    REG_WR(GPIO_BASE + GPIO_OUTPUT_CLR,GPIO_BIT_USB_RESET);
    LOG("Calling usbhw_reset()\n");
    usbhw_reset();

#if 0
    LOG("USB registers after reset:\n");
    DumpUsbRegs();
#endif

    LOG("calling usb_configure_device()\n");
    Err = usb_configure_device(&gRootHubDev,1);
    LOG("usb_configure_device returned %d\n",Err);

    Led = GPIO_BIT_RED_LED;
    for(; ; ) {
       REG_WR(GPIO_BASE + GPIO_OUTPUT,Led);
       for(i = 0; i < (Fast ? 3 : 10); i++) {
          timer_sleep(50);
       }
       REG_WR(GPIO_BASE + GPIO_OUTPUT,0);
       for(i = 0; i < (Fast ? 3 : 10); i++) {
          timer_sleep(50);
       }
       switch(Led) {
          case GPIO_BIT_RED_LED:
             Led = GPIO_BIT_GREEN_LED;
             break;

          case GPIO_BIT_GREEN_LED:
             Led = GPIO_BIT_BLUE_LED;
             break;

          case GPIO_BIT_BLUE_LED:
             Led = GPIO_BIT_RED_LED;
             break;
       }
    }

    return 0;
}

void DumpUsbRegs()
{
   LOG("USB_CTRL: 0x%x\n",usbhw_reg_read(0));
   LOG("USB_STATUS: 0x%x\n",usbhw_reg_read(4));
   LOG("USB_IRQ_ACK: 0x%x\n",usbhw_reg_read(8));
   LOG("USB_IRQ_STS: 0x%x\n",usbhw_reg_read(0xc));
   LOG("USB_IRQ_MASK: 0x%x\n",usbhw_reg_read(0x10));
   LOG("USB_RX_STAT: 0x%x\n",usbhw_reg_read(0x1c));
}
