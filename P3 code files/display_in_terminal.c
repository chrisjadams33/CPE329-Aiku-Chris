//******************************************************************************
//
//   - The display_in_terminal.c program serves the primary purpose of displaying
//   waveform attributes that the digital multimeter is required to sample
//   - These attributes are displayed on a Serial Terminal via inspiration from
//   VT100 protocol
//   - The serial terminal displays the RMS voltage, DC voltage, peak-to-peak
//   voltage, and frequencies of the waveforms
//   - The terminal also displays the RMS and DC values via a bar graph
//
//   Aiku Shintani & Chris Adams
//   Cal Poly San Luis Obispo EE
//   May 17 (updated)
//******************************************************************************


#include "msp.h"
#include "stdio.h"


void display_in_terminal(char *pointer);

//takes float variable inputs from the main and sets the appropriate settings of the bar graph and terminal display
void string_to_terminal(float RMS_voltage, float peak_to_peak, float DC_voltage, float frequency, int mode){

    //statements[x] fits x number of characters in it
    static char statements[1000];
    int data;
    float DC_bar_graph_ticks = 0;
    float RMS_bar_graph_ticks = 0;
    int display = 0;
    char DC3_30 = ' ', DC3_08 = ' ', DC2_86 = ' ', DC2_64 = ' ', DC2_42 = ' ', DC2_20 = ' ',
         DC1_98 = ' ', DC1_76 = ' ', DC1_54 = ' ', DC1_32 = ' ', DC1_10 = ' ', DC0_88 = ' ',
         DC0_66 = ' ', DC0_44 = ' ', DC0_22 = ' ', DC0_00 = '*';
    char RMS3_30 = ' ', RMS3_08 = ' ', RMS2_86 = ' ', RMS2_64 = ' ', RMS2_42 = ' ', RMS2_20 = ' ',
         RMS1_98 = ' ', RMS1_76 = ' ', RMS1_54 = ' ', RMS1_32 = ' ', RMS1_10 = ' ', RMS0_88 = ' ',
         RMS0_66 = ' ', RMS0_44 = ' ', RMS0_22 = ' ', RMS0_00 = '*';
    char first_letter = ' ', second_letter = ' ';
    char thousands = " ";

    //char wave_display;
    //char Sinusoid = "Sinusoid";
    //char Square   = "Square";
    //char Triangle = "Triangle";
    //categorize waveforms
       /* if (wave_type == 1)
            wave_display = Sinusoid;
        else if (wave_type == 2)
            wave_display = Square;
        else if (wave_type == 3)
            wave_display = Triangle;*/

    //the DC voltage divided by the resolution of 0.22V to see how many asterisks are displayed on the bar graph
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

    //the RMS voltage divided by the resolution of 0.22V to see how many asterisks are displayed on the bar graph
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

    //Display appropriate Mode of operation, 0 for AC, 1 for DC, and 2 to not display
    if (mode == 0)
    {
        first_letter = 'A';
        second_letter = 'C';
        display = 1;
    }
    else if (mode == 1)
    {
        first_letter = 'D';
        second_letter = 'C';
        display = 1;
    }
    else if (mode == 2)
    {
        display = 0;
    }

    if (frequency >= 1000)
        thousands = " ";
    else if (frequency >= 100)
        thousands = "  ";
    else if (frequency >= 10)
        thousands = "   ";
    else if (frequency < 10)
        thousands = "    ";


    if(display == 1)
    {
        //place the characters in the statements argument in the order to use it in the display_in_terminal function
        data = sprintf(statements," -------------------------        ---------------------------\r\n"
                                  " |      CPE329 - P3       |      |   3.30-  %c       %c       |\r\n"
                                  " |                        |      |   3.08-  %c       %c       |\r\n"
                                  " |                        |      |   2.86-  %c       %c       |\r\n"
                                  " |   DIGITAL MULTIMETER   |      |   2.64-  %c       %c       |\r\n"
                                  " |------------------------|      |   2.42-  %c       %c       |\r\n"
                                  " |Mode:        %c%c       |      |   2.20-  %c       %c       |\r\n"
                                  " |                        |      |   1.98-  %c       %c       |\r\n"
                                  " |                        |      |   1.76-  %c       %c       |\r\n"
                                  " |RMS Voltage: %.2fV      |      |   1.54-  %c       %c       |\r\n"
                                  " |                        |      |   1.32-  %c       %c       |\r\n"
                                  " |                        |      |   1.10-  %c       %c       |\r\n"
                                  " |Peak-to-Peak: %.2fV     |      |   0.88-  %c       %c       |\r\n"
                                  " |                        |      |   0.66-  %c       %c       |\r\n"
                                  " |                        |      |   0.44-  %c       %c       |\r\n"
                                  " |DC Voltages:  %.2fV     |      |   0.22-  %c       %c       |\r\n"
                                  " |                        |      |   0.00-  %c       %c       |\r\n"
                                  " |                        |      |--------------------------|\r\n"
                                  " |Frequency:   %s%.2fHz     |      |          DC      RMS     |\r\n"
                                  " -------------------------       ---------------------------|",   DC3_30, RMS3_30, DC3_08, RMS3_08, DC2_86, RMS2_86, DC2_64, RMS2_64, DC2_42, RMS2_42,first_letter,
                                                                                                     second_letter, DC2_20, RMS2_20,DC1_98, RMS1_98, DC1_76, RMS1_76, RMS_voltage, DC1_54,RMS1_54,  DC1_32,
                                                                                                     RMS1_32, DC1_10, RMS1_10, peak_to_peak, DC0_88, RMS0_88, DC0_66,  RMS0_66, DC0_44,  RMS0_44,  DC_voltage,
                                                                                                     DC0_22,  RMS0_22, DC0_00, RMS0_00, thousands, frequency);

        //data = sprintf(statements, "Digital Multimeter %.2f:%d", 5.00, 2);  //float with two decimal places, d= decimal
        display_in_terminal(statements);
    }

}

//increment pointer and address the characters in the sprintf statement above and send to the terminal
void display_in_terminal(char *pointer){

    //while the *pointer still has addresses to index through
    while(*pointer){
        // Check if the TX buffer is empty first
        while(!(EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG));
        //send characters on the TXBUF
        EUSCI_A0->TXBUF = *pointer;
        pointer ++;
    }
}


