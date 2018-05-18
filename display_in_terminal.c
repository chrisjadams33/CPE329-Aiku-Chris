#include "msp.h"
#include "stdio.h"
/*
 * display_in_terminal.c
 *
 *  Created on: May 16, 2018
 *      Author: Aiku
 */
void display_in_terminal(char *pointer);

//add the frequency, rms voltage, dc offset, and mode as inputs to this function
void string_to_terminal(float RMS_voltage, float DC_voltage, float frequency){
    static char statements[1000];
    int data;
    float DC_bar_graph_ticks = 0;
    float RMS_bar_graph_ticks = 0;
    char DC3_30 = ' ', DC3_08 = ' ', DC2_86 = ' ', DC2_64 = ' ', DC2_42 = ' ', DC2_20 = ' ',
         DC1_98 = ' ', DC1_76 = ' ', DC1_54 = ' ', DC1_32 = ' ', DC1_10 = ' ', DC0_88 = ' ',
         DC0_66 = ' ', DC0_44 = ' ', DC0_22 = ' ';
    char RMS3_30 = ' ', RMS3_08 = ' ', RMS2_86 = ' ', RMS2_64 = ' ', RMS2_42 = ' ', RMS2_20 = ' ',
         RMS1_98 = ' ', RMS1_76 = ' ', RMS1_54 = ' ', RMS1_32 = ' ', RMS1_10 = ' ', RMS0_88 = ' ',
         RMS0_66 = ' ', RMS0_44 = ' ', RMS0_22 = ' ';


    if (DC_voltage > 0.22)
    {
        DC_bar_graph_ticks = DC_voltage/(0.22);

        if (DC_bar_graph_ticks >= 15)
            DC0_22 = '*', DC0_44 = '*', DC0_66 = '*', DC0_88 = '*', DC1_10 = '*', DC1_32 = '*',
            DC1_54 = '*', DC1_76 = '*', DC1_98 = '*', DC2_20 = '*', DC2_42 = '*', DC2_64 = '*', DC2_86 = '*', DC3_08 = '*', DC3_30 = '*';
        else if (DC_bar_graph_ticks >= 14)
            DC0_22 = '*', DC0_44 = '*', DC0_66 = '*', DC0_88 = '*', DC1_10 = '*', DC1_32 = '*',
            DC1_54 = '*', DC1_76 = '*', DC1_98 = '*', DC2_20 = '*', DC2_42 = '*', DC2_64 = '*', DC2_86 = '*', DC3_08 = '*';
        else if (DC_bar_graph_ticks >= 13)
            DC0_22 = '*', DC0_44 = '*', DC0_66 = '*', DC0_88 = '*', DC1_10 = '*', DC1_32 = '*',
            DC1_54 = '*', DC1_76 = '*', DC1_98 = '*', DC2_20 = '*', DC2_42 = '*', DC2_64 = '*', DC2_86 = '*';
        else if (DC_bar_graph_ticks >= 12)
            DC0_22 = '*', DC0_44 = '*', DC0_66 = '*', DC0_88 = '*', DC1_10 = '*', DC1_32 = '*',
            DC1_54 = '*', DC1_76 = '*', DC1_98 = '*', DC2_20 = '*', DC2_42 = '*', DC2_64 = '*';
        else if (DC_bar_graph_ticks >= 11)
            DC0_22 = '*', DC0_44 = '*', DC0_66 = '*', DC0_88 = '*', DC1_10 = '*', DC1_32 = '*',
            DC1_54 = '*', DC1_76 = '*', DC1_98 = '*', DC2_20 = '*', DC2_42 = '*';
        else if (DC_bar_graph_ticks >= 10)
            DC0_22 = '*', DC0_44 = '*', DC0_66 = '*', DC0_88 = '*', DC1_10 = '*', DC1_32 = '*',
            DC1_54 = '*', DC1_76 = '*', DC1_98 = '*', DC2_20 = '*';
        else if (DC_bar_graph_ticks >= 9)
            DC0_22 = '*', DC0_44 = '*', DC0_66 = '*', DC0_88 = '*', DC1_10 = '*', DC1_32 = '*',
            DC1_54 = '*', DC1_76 = '*', DC1_98 = '*';
        else if (DC_bar_graph_ticks >= 8)
            DC0_22 = '*', DC0_44 = '*', DC0_66 = '*', DC0_88 = '*', DC1_10 = '*', DC1_32 = '*',
            DC1_54 = '*', DC1_76 = '*';
        else if (DC_bar_graph_ticks >= 7)
            DC0_22 = '*', DC0_44 = '*', DC0_66 = '*', DC0_88 = '*', DC1_10 = '*', DC1_32 = '*',
            DC1_54 = '*';
        else if (DC_bar_graph_ticks >= 6)
            DC0_22 = '*', DC0_44 = '*', DC0_66 = '*', DC0_88 = '*', DC1_10 = '*', DC1_32 = '*';
        else if (DC_bar_graph_ticks >= 5)
            DC0_22 = '*', DC0_44 = '*', DC0_66 = '*', DC0_88 = '*', DC1_10 = '*';
        else if (DC_bar_graph_ticks >= 4)
            DC0_22 = '*', DC0_44 = '*', DC0_66 = '*', DC0_88 = '*';
        else if (DC_bar_graph_ticks >= 3)
            DC0_22 = '*', DC0_44 = '*', DC0_66 = '*';
        else if (DC_bar_graph_ticks >= 2)
            DC0_22 = '*', DC0_44 = '*';
        else if (DC_bar_graph_ticks >= 1)
            DC0_22 = '*';
    }

    if (RMS_voltage > 0.22)
    {
        RMS_bar_graph_ticks = RMS_voltage/(0.22);

        if (RMS_bar_graph_ticks >= 15)
            RMS0_22 = '*', RMS0_44 = '*', RMS0_66 = '*', RMS0_88 = '*', RMS1_10 = '*', RMS1_32 = '*',
            RMS1_54 = '*', RMS1_76 = '*', RMS1_98 = '*', RMS2_20 = '*', RMS2_42 = '*', RMS2_64 = '*', RMS2_86 = '*', RMS3_08 = '*', RMS3_30 = '*';
        else if (RMS_bar_graph_ticks >= 14)
            RMS0_22 = '*', RMS0_44 = '*', RMS0_66 = '*', RMS0_88 = '*', RMS1_10 = '*', RMS1_32 = '*',
            RMS1_54 = '*', RMS1_76 = '*', RMS1_98 = '*', RMS2_20 = '*', RMS2_42 = '*', RMS2_64 = '*', RMS2_86 = '*', RMS3_08 = '*';
        else if (RMS_bar_graph_ticks >= 13)
            RMS0_22 = '*', RMS0_44 = '*', RMS0_66 = '*', RMS0_88 = '*', RMS1_10 = '*', RMS1_32 = '*',
            RMS1_54 = '*', RMS1_76 = '*', RMS1_98 = '*', RMS2_20 = '*', RMS2_42 = '*', RMS2_64 = '*', RMS2_86 = '*';
        else if (RMS_bar_graph_ticks >= 12)
            RMS0_22 = '*', RMS0_44 = '*', RMS0_66 = '*', RMS0_88 = '*', RMS1_10 = '*', RMS1_32 = '*',
            RMS1_54 = '*', RMS1_76 = '*', RMS1_98 = '*', RMS2_20 = '*', RMS2_42 = '*', RMS2_64 = '*';
        else if (RMS_bar_graph_ticks >= 11)
            RMS0_22 = '*', RMS0_44 = '*', RMS0_66 = '*', RMS0_88 = '*', RMS1_10 = '*', RMS1_32 = '*',
            RMS1_54 = '*', RMS1_76 = '*', RMS1_98 = '*', RMS2_20 = '*', RMS2_42 = '*';
        else if (RMS_bar_graph_ticks >= 10)
            RMS0_22 = '*', RMS0_44 = '*', RMS0_66 = '*', RMS0_88 = '*', RMS1_10 = '*', RMS1_32 = '*',
            RMS1_54 = '*', RMS1_76 = '*', RMS1_98 = '*', RMS2_20 = '*';
        else if (RMS_bar_graph_ticks >= 9)
            RMS0_22 = '*', RMS0_44 = '*', RMS0_66 = '*', RMS0_88 = '*', RMS1_10 = '*', RMS1_32 = '*',
            RMS1_54 = '*', RMS1_76 = '*', RMS1_98 = '*';
        else if (RMS_bar_graph_ticks >= 8)
            RMS0_22 = '*', RMS0_44 = '*', RMS0_66 = '*', RMS0_88 = '*', RMS1_10 = '*', RMS1_32 = '*',
            RMS1_54 = '*', RMS1_76 = '*';
        else if (RMS_bar_graph_ticks >= 7)
            RMS0_22 = '*', RMS0_44 = '*', RMS0_66 = '*', RMS0_88 = '*', RMS1_10 = '*', RMS1_32 = '*',
            RMS1_54 = '*';
        else if (RMS_bar_graph_ticks >= 6)
            RMS0_22 = '*', RMS0_44 = '*', RMS0_66 = '*', RMS0_88 = '*', RMS1_10 = '*', RMS1_32 = '*';
        else if (RMS_bar_graph_ticks >= 5)
            RMS0_22 = '*', RMS0_44 = '*', RMS0_66 = '*', RMS0_88 = '*', RMS1_10 = '*';
        else if (RMS_bar_graph_ticks >= 4)
            RMS0_22 = '*', RMS0_44 = '*', RMS0_66 = '*', RMS0_88 = '*';
        else if (RMS_bar_graph_ticks >= 3)
            RMS0_22 = '*', RMS0_44 = '*', RMS0_66 = '*';
        else if (RMS_bar_graph_ticks >= 2)
            RMS0_22 = '*', RMS0_44 = '*';
        else if (RMS_bar_graph_ticks >= 1)
            RMS0_22 = '*';
    }


    data = sprintf(statements," -------------------------        ---------------------------\r\n"
                              " |      CPE329 - P3       |      |   3.30-  %c       %c       |\r\n"
                              " |                        |      |   3.08-  %c       %c       |\r\n"
                              " |                        |      |   2.86-  %c       %c       |\r\n"
                              " |   DIGITAL MULTIMETER   |      |   2.64-  %c       %c       |\r\n"
                              " |------------------------|      |   2.42-  %c       %c       |\r\n"
                              " |Mode:                   |      |   2.20-  %c       %c       |\r\n"
                              " |                        |      |   1.98-  %c       %c       |\r\n"
                              " |                        |      |   1.76-  %c       %c       |\r\n"
                              " |RMS Voltage: %.2fV      |      |   1.54-  %c       %c       |\r\n"
                              " |                        |      |   1.32-  %c       %c       |\r\n"
                              " |                        |      |   1.10-  %c       %c       |\r\n"
                              " |DC Voltage:  %.2fV      |      |   0.88-  %c       %c       |\r\n"
                              " |                        |      |   0.66-  %c       %c       |\r\n"
                              " |                        |      |   0.44-  %c       %c       |\r\n"
                              " |Frequency:   %.2fHz  |      |   0.22-  %c       %c       |\r\n"
                              " |                        |      |   0.00-                  |\r\n"
                              " |                        |      |--------------------------|\r\n"
                              " |                        |      |          DC      RMS     |\r\n"
                              " -------------------------       ---------------------------|",   DC3_30, RMS3_30, DC3_08, RMS3_08, DC2_86, RMS2_86, DC2_64, RMS2_64, DC2_42, RMS2_42,DC2_20, RMS2_20,
                                                                                                 DC1_98, RMS1_98, DC1_76, RMS1_76, RMS_voltage, DC1_54,RMS1_54,  DC1_32, RMS1_32, DC1_10, RMS1_10,
                                                                                                 DC_voltage, DC0_88,  RMS0_88, DC0_66,  RMS0_66,DC0_44,  RMS0_44, frequency, DC0_22,  RMS0_22);

    //data = sprintf(statements, "Digital Multimeter %.2f:%d", 5.00, 2);  //float with two decimal places, d= decimal
    display_in_terminal(statements);

}

void display_in_terminal(char *pointer){

    while(*pointer){

        while(!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG));
        EUSCI_A0->TXBUF = *pointer;
        pointer ++;

    }

}


