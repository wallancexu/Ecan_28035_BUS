/*
 * bsp_ecan.c
 *
 *  Created on: 2020年12月30日
 *      Author: sea
 */
#include "DSP28x_Project.h"     // DSP28x Headerfile

void ConfigureEcan(void)
{
    struct ECAN_REGS ECanaShadow;
    // Step 4. Initialize all the Device Peripherals:
    // This function is found in DSP2833x_InitPeripherals.c
    // InitPeripherals(); // Not required for this example

    // In this case just initalize eCAN-A and eCAN-B
    // This function is in DSP2833x_ECan.c
    InitECan();
    //ErrorCount = 0;
    //PassCount = 0;

    /* Write to the MSGID field  */

    ECanaMboxes.MBOX16.MSGID.all = 0x95555554; // Extended Identifier
    ECanaMboxes.MBOX25.MSGID.all = 0x95555555; // Extended Identifier

    /* Configure Mailbox under test as a Re/Transmit mailbox */
    EALLOW;
    ECanaShadow.CANMD.all = ECanaRegs.CANMD.all;
    ECanaShadow.CANMD.bit.MD16 = 1; //rx
    ECanaShadow.CANMD.bit.MD25 = 0;//tx
    ECanaRegs.CANMD.all = ECanaShadow.CANMD.all;


    //without considering id and the data can be received
    ECanaMboxes.MBOX16.MSGID.bit.AME = 1;
    ECanaLAMRegs.LAM16.all = 0xFFFFFFFF;

    /* Enable Mailbox under test */

    ECanaShadow.CANME.all = ECanaRegs.CANME.all;
    ECanaShadow.CANME.bit.ME16 = 1;
    ECanaShadow.CANME.bit.ME25 = 1;
    ECanaRegs.CANME.all = ECanaShadow.CANME.all;


    /* Write to DLC field in Master Control reg */
    //ECanaMboxes.MBOX16.MSGCTRL.bit.DLC = 8;
    ECanaMboxes.MBOX25.MSGCTRL.bit.DLC = 8;



    ECanaRegs.CANRMP.all = 0xFFFFFC00;

    /* Write to the mailbox RAM field */

//    ECanaMboxes.MBOX16.MDL.all = 0x555;
//    ECanaMboxes.MBOX16.MDH.all = 0x555;

    ECanaMboxes.MBOX25.MDL.all = 0x55555555;
    ECanaMboxes.MBOX25.MDH.all = 0xAAAAAAAA;

    EDIS;

    EALLOW;

    ECanaShadow.CANMIM.all=ECanaRegs.CANMIM.all;
    ECanaShadow.CANMIM.bit.MIM16=1;
    ECanaRegs.CANMIM.all=ECanaShadow.CANMIM.all;

    ECanaShadow.CANMIL.all = ECanaRegs.CANMIL.all;
    ECanaShadow.CANMIL.all = 0;              // 1-32号邮箱中断在中断线0上产生
    ECanaRegs.CANMIL.all = ECanaShadow.CANMIL.all;

    ECanaShadow.CANGIM.all = ECanaRegs.CANGIM.all;
    ECanaShadow.CANGIM.bit.I0EN = 1 ;              //  中断线0使能
    ECanaRegs.CANGIM.all = ECanaShadow.CANGIM.all;

    ECanaShadow.CANMC.all = ECanaRegs.CANMC.all;
    ECanaShadow.CANMC.bit.STM = 0;    // 0-Normal
    ECanaRegs.CANMC.all = ECanaShadow.CANMC.all;

    EDIS;

}
