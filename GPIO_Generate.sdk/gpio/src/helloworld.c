#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xgpiops.h"

XGpioPs gpio;
XGpioPs_Config *gpio_cfg;

int main()
{
    init_platform();

	gpio_cfg = XGpioPs_LookupConfig(XPAR_XGPIOPS_0_DEVICE_ID);
	XGpioPs_CfgInitialize(&gpio, gpio_cfg,gpio_cfg->BaseAddr);

//	for(u8 Pin=0; Pin<130; Pin++){
	u8	Pin = 48;
		u8 Bank=254, PinNumber=254, PinNumberTemp;
		u32 RegOffset, Value0, Value1;
		XGpioPs_GetBankPin(Pin, &Bank, &PinNumber);
		u32 DIR=gpio.GpioConfig.BaseAddr+((u32)(Bank)*XGPIOPS_REG_MASK_OFFSET)+XGPIOPS_DIRM_OFFSET;
		u32 DIR__EN=gpio.GpioConfig.BaseAddr+((u32)(Bank)*XGPIOPS_REG_MASK_OFFSET)+XGPIOPS_OUTEN_OFFSET;
		if (PinNumber>15){PinNumberTemp=PinNumber-16; RegOffset = XGPIOPS_DATA_MSW_OFFSET;}else{PinNumberTemp=PinNumber; RegOffset = XGPIOPS_DATA_LSW_OFFSET;}
		Value0 = ~((u32)1 << (PinNumberTemp + 16U)) & ((0 << PinNumberTemp) | 0xFFFF0000U);
		Value1 = ~((u32)1 << (PinNumberTemp + 16U)) & ((1 << PinNumberTemp) | 0xFFFF0000U);
		u32 Read_Pin=gpio.GpioConfig.BaseAddr+((u32)(Bank)*XGPIOPS_DATA_BANK_OFFSET)+XGPIOPS_DATA_RO_OFFSET;
		u32 PORT=gpio.GpioConfig.BaseAddr+((u32)(Bank)*XGPIOPS_DATA_MASK_OFFSET)+RegOffset;
		xil_printf("%d,%d,%x,%x,%x,%d,%x,%x,%x,\r\n", Pin,Bank, DIR ,DIR__EN,PORT,PinNumber, Value0, Value1,Read_Pin);
//	}

    cleanup_platform();
    return 0;
}
