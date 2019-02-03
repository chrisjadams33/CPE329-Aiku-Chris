function [key_num] = DTMF_signal_decoder(test_tone, fs, figure_num)
%This function takes a time domain signal in '.mat' format and the sampling
%frequency as inputs. The function takes the FFT of the signal and creates
%a plot of the magnitude response. The function finds the presence of two
%particular frequencies correponding to the row and col. of a keypad press.
%The function ultimately returns the which key was pressed on the keypad.

str = 0;

xn = test_tone;                                  %time domain test tone
[DFTx, Fd] = plot_DFT_mag(xn, fs, figure_num);   %plot the DFT magn.

%find the col peak
Tacq = 0.5;
Mx = length(xn);
DFTx_mag  = abs(DFTx); 
fa_max_1_index = find(DFTx_mag == max(DFTx_mag)); %returns indexes for two peaks (array) of col
DFTx_max_1 = DFTx_mag(fa_max_1_index(1))/(fs*Tacq); %mag. divided by M 
fa_val(1) = fa_max_1_index(1)/Mx*fs;% index doesn't provide enough info
                                    % to get fa value, quantify the index #
                                    
%find the row peak 
DFTx_mag([fa_max_1_index(1) - 5: fa_max_1_index(1) + 5]) = 0;  %set max of col to 0
DFTx_mag([fa_max_1_index(2) - 5: fa_max_1_index(2) + 5]) = 0;  %set max of col to 0

fa_max_2_index = find(DFTx_mag == max(DFTx_mag)); %returns indexes for two peaks (array) of row
DFTx_max_2 = DFTx_mag(fa_max_2_index(1))/(fs*Tacq); %mag. divided by M 
fa_val(2) = fa_max_2_index(1)/Mx*fs;% index doesn't provide enough info
                                    % to get fa value, quantify the index #

fa_val = sort(fa_val, 'descend');   % in case the row and col peak height 
                                    % is not consistent
                                        
%determine which key was pressed
fc1 = 1209; fc2 = 1336; fc3 = 1477; fc4 = 1633;
fr1 = 697; fr2 = 770; fr3 = 852; fr4 = 941;
thresh = 30;

%row 1
if ((fc1 - thresh < fa_val(1) && fa_val(1) < fc1 + thresh) && (fr1 - thresh < fa_val(2) && fa_val(2) < fr1 + thresh))
    key_num = 1;
elseif ((fc2 - thresh < fa_val(1) && fa_val(1) < fc2 + thresh) && (fr1 - thresh < fa_val(2) && fa_val(2) < fr1 + thresh))
   key_num = 2;
elseif ((fc3 - thresh < fa_val(1) && fa_val(1) < fc3 + thresh) && (fr1 - thresh < fa_val(2) && fa_val(2) < fr1 + thresh))
   key_num = 3;
elseif ((fc4 - thresh < fa_val(1) && fa_val(1) < fc4 + thresh) && (fr1 - thresh < fa_val(2) && fa_val(2) < fr1 + thresh))
   key_num = 'A';
   str = 1;
%row 2
elseif ((fc1 - thresh < fa_val(1) && fa_val(1) < fc1 + thresh) && (fr2 - thresh < fa_val(2) && fa_val(2) < fr2 + thresh))
    key_num = 4;
elseif ((fc2 - thresh < fa_val(1) && fa_val(1) < fc2 + thresh) && (fr2 - thresh < fa_val(2) && fa_val(2) < fr2 + thresh))
   key_num = 5;
elseif ((fc3 - thresh < fa_val(1) && fa_val(1) < fc3 + thresh) && (fr2 - thresh < fa_val(2) && fa_val(2) < fr2 + thresh))
   key_num = 6;
elseif ((fc4 - thresh < fa_val(1) && fa_val(1) < fc4 + thresh) && (fr2 - thresh < fa_val(2) && fa_val(2) < fr2 + thresh))
   key_num = 'B';
   str = 1;
%row 3
elseif ((fc1 - thresh < fa_val(1) && fa_val(1) < fc1 + thresh) && (fr3 - thresh < fa_val(2) && fa_val(2) < fr3 + thresh))
    key_num = 7;
elseif ((fc2 - thresh < fa_val(1) && fa_val(1) < fc2 + thresh) && (fr3 - thresh < fa_val(2) && fa_val(2) < fr3 + thresh))
   key_num = 8;
elseif ((fc3 - thresh < fa_val(1) && fa_val(1) < fc3 + thresh) && (fr3 - thresh < fa_val(2) && fa_val(2) < fr3 + thresh))
   key_num = 9;
elseif ((fc4 - thresh < fa_val(1) && fa_val(1) < fc4 + thresh) && (fr3 - thresh < fa_val(2) && fa_val(2) < fr3 + thresh))
   key_num = 'C'; 
   str = 1;
%row 4
elseif((fc1 - thresh < fa_val(1) && fa_val(1) < fc1 + thresh) && (fr4 - thresh < fa_val(2) && fa_val(2) < fr4 + thresh))
    key_num = '*';
    str = 1;
elseif ((fc2 - thresh < fa_val(1) && fa_val(1) < fc2 + thresh) && (fr4 - thresh < fa_val(2) && fa_val(2) < fr4 + thresh))
   key_num = 0;
elseif ((fc3 - thresh < fa_val(1) && fa_val(1) < fc3 + thresh) && (fr4 - thresh < fa_val(2) && fa_val(2) < fr4 + thresh))
   key_num = '#';
   str = 1;
elseif ((fc4 - thresh < fa_val(1) && fa_val(1) < fc4 + thresh) && (fr4 - thresh < fa_val(2) && fa_val(2) < fr4 + thresh))
   key_num = 'D';
   str = 1;
else
    key_num = 'N/A';
    str = 1;

end
  
%display pressed key on figure 
if (str == 1)
    text(3850, 0.9, key_num, 'FontSize',14)
else
    text(3850, 0.9, num2str(key_num), 'FontSize',14)
end

end