#include "msp.h"

//define clock frequency values
#define FREQ_1_5MHz  1500000
#define FREQ_3MHz    3000000
#define FREQ_6MHz    6000000
#define FREQ_12MHz   12000000
#define FREQ_24MHz   24000000
#define FREQ_48MHz   48000000

int set_DCO(int clk_freq)
{
    CS -> KEY = CS_KEY_VAL;
    CS -> CTL0 = 0;
    if (clk_freq == FREQ_1_5MHz)
    {
        CS->CTL0 = CS_CTL0_DCORSEL_0;       // 1.5MHz
        CS->CTL1 = CS_CTL1_SELA_2 | CS_CTL1_SELS_3 | CS_CTL1_SELM_3;
    }
    else if (clk_freq == FREQ_3MHz)
    {
        CS -> CTL0 = CS_CTL0_DCORSEL_1;     // 3MHz
        CS->CTL1 = CS_CTL1_SELA_2 | CS_CTL1_SELS_3 | CS_CTL1_SELM_3;
    }
    else if (clk_freq == FREQ_6MHz)
    {
        CS -> CTL0 = CS_CTL0_DCORSEL_2;     // 6MHz
        CS->CTL1 = CS_CTL1_SELA_2 | CS_CTL1_SELS_3 | CS_CTL1_SELM_3;
    }
    else if (clk_freq == FREQ_12MHz)
    {
        CS -> CTL0 = CS_CTL0_DCORSEL_3;     // 12MHz
        CS->CTL1 = CS_CTL1_SELA_2 | CS_CTL1_SELS_3 | CS_CTL1_SELM_3;
    }
    else if (clk_freq == FREQ_24MHz)
    {
        CS -> CTL0 = CS_CTL0_DCORSEL_4;     // 24MHz
        CS->CTL1 = CS_CTL1_SELA_2 | CS_CTL1_SELS_3 | CS_CTL1_SELM_3 | CS_CTL1_DIVS_4;
    }    
    else if (clk_freq == FREQ_48MHz)
    {
    		/* Transition to VCORE Level 1: AM0_LDO --> AM1_LDO */
		while ((PCM->CTL1 & PCM_CTL1_PMR_BUSY));
			PCM->CTL0 = PCM_CTL0_KEY_VAL | PCM_CTL0_AMR_1;
		while ((PCM->CTL1 & PCM_CTL1_PMR_BUSY));
		
		/* Configure Flash wait-state to 1 for both banks 0 & 1 */
		FLCTL->BANK0_RDCTL = (FLCTL->BANK0_RDCTL & ~(FLCTL_BANK0_RDCTL_WAIT_MASK)) | FLCTL_BANK0_RDCTL_WAIT_1;
		FLCTL->BANK1_RDCTL = (FLCTL->BANK0_RDCTL & ~(FLCTL_BANK1_RDCTL_WAIT_MASK)) | FLCTL_BANK1_RDCTL_WAIT_1;
		
        CS -> CTL0 = CS_CTL0_DCORSEL_5;     // 48MHz
		CS->CTL1 = CS->CTL1 & ~(CS_CTL1_SELM_MASK | CS_CTL1_DIVM_MASK) |
		CS_CTL1_SELM_3;
	}
    else
        return -1;
    CS->KEY = 0;                            // lock CS register
}
