/*******************************************************************************************
 * Author:	Ussash Arafat
 * Project:	wave_generator
 * File:	wave-generator_app.c
 * Tools:  	Vivado 2019.1
 * 		  	Xilinx SDK 2019.1
 * Device: 	Zedboard
 ********************************************************************************************/

//include libraries
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xil_io.h"
#include "xparameters.h"

int main()
{
    init_platform();

    short memoryValue;

    //16 bit input parameters
    short finalValue = 20;
	short dropValue = 15;
	short hValue = 2;
	short vValue = 1;
	short period = 40;

	short totalStep;
	int finalAddress;
	int baseAddress = XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR;
	int memoryAddress= baseAddress;
	int memoryRead;
	int sample = 1;

	totalStep = period/hValue;
	memoryValue = finalValue - dropValue;

	//writing to block ram
	for (int i=0; i<totalStep; i++){
		for (int j=0; j<hValue; j++){
			memoryValue = memoryValue;
			Xil_Out16(memoryAddress, memoryValue);
			memoryAddress = memoryAddress + 0x2;
		}
		if(memoryValue<finalValue) memoryValue = memoryValue + vValue;
		else memoryValue = finalValue;
	}
	finalAddress = memoryAddress;

	//reading from block ram
	for(int i=baseAddress ; i<finalAddress; i+=0x2){
		memoryRead = Xil_In16(i);
		printf("Sample: %d, Address: %x, Data: %d \n\r",sample, i, memoryRead);
		sample= sample + 1;
	}
    cleanup_platform();
    return 0;
}
