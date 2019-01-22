% EE419_HF_exp1_proto
% COMPUTE AND PLOT THE FREQUENCY RESPONSE OF AN IIR FILTER
% H(z) = z / (z-0.9)

% Make a digital frequency variable with 1001 points 
% for Principle Range F =-1/2 to +1/2, with spacing .001 cycles/sample

%Freq=[-0.5 -0.499 -0.498 ......... 0.499  0.5];  % 1001 values?! YIKES!!

%Freq=linspace(first_val, last_val, Num_of_points); 
% For LINSPACE: Increment =(last_val - first_val) / (Num_of_points-1) 
%Freq=linspace(-.5, .5, 1001); % 1001 points, from -1/2 to +1/2, Incr=.001

%Freq=[first_val : increment : last_val]; 
% NOTE: # of Points =[(last_val-first_val) / increment]+1 
                    % 1001 points, from -1/2 to +1/2, increment=.001
Freq = linspace(-0.5, 0.5, 1001);

% Compute the values of the COMPLEX DTFT frequency response at these frequencies
z = exp(j*2*pi*Freq);
HF = z./(z - 0.9);

% LINEAR FREQUENCY RESPONSE PLOT
% Plot the magnitude and phase responses on a linear freq scaleOp

% Open a new Figure #1:
figure(1)
% Plot the Magnitude Response 
subplot(2,1,1)  % Display plots in 2 rows / 1 column; This is the 1st plot.

% Plot the magnitude of HF on a linear scale
plot(Freq, abs(HF));

grid on
xlabel('Digital Frequency  F (cycles/sample)')
ylabel('Magnitude Response')
title('Frequency Response of Filter')

% Plot the Phase Response below the Magnitude Response
subplot(2,1,2) % Display plots in 2 rows / 1 column; This is the 2nd plot.

% Plot the Phase Angle vs Frequency     
                    % Normalize angle radian values by pi radians
plot(Freq, angle(HF));
                    
grid on
xlabel('Digital Frequency  F (cycles/sample)')
ylabel('Phase Response /pi')


% PLOT dB (LOG AMPLITUDE) SCALE FREQUENCY RESPONSE PLOT in a new figure
% copy, paste, modify plot commands from above

figure(2)
subplot(1,1,1) % Display plots in 3 rows / 1 column; This is the 3rd plot.

% Plot the Phase Angle vs Frequency     
                    % Normalize angle radian values by pi radians
plot(Freq, 20.*log10(abs(HF)));
                    
grid on
xlabel('Digital Frequency  F (cycles/sample)')
ylabel('Magnitude Response [dB]')

[HFFreqz, W] = freqz(1, [1, -0.9], 500);

% Open a new Figure #3:
figure(3)
% Plot the Magnitude Response 
subplot(2,1,1)  % Display plots in 2 rows / 1 column; This is the 1st plot.

% Plot the magnitude of HF on a linear scale
plot(W./(2*pi), abs(HFFreqz));

grid on
xlabel('Digital Frequency  F (cycles/sample)')
ylabel('Magnitude Response')
title('Frequency Response of Filter')

% Plot the Phase Response below the Magnitude Response
subplot(2,1,2) % Display plots in 2 rows / 1 column; This is the 2nd plot.

% Plot the Phase Angle vs Frequency     
                    % Normalize angle radian values by pi radians
plot(W./(2*pi), angle(HFFreqz));

% Use Matlab freqz() function to plot frequency response
% [H,W] = freqz(B,A,N) 
%   B = H(z) numberator coefficients
%   A = H(z) denominator coefficients
%   N = # of complex H(F) data points to compute 
%   H = complex H(F) values
%   W = radian digital frequency = 2*pi*F
% Get 500 points for the plot
 

% Plot the magnitude and phase response (copy, paste, modify)



% Find the peak response and peak response frequency
[peak_response, peak_response_index] = max(abs(HF))
% No ';' at end so answers print to screen
peak_response_freq = Freq(peak_response_index)

% Find the minimum magnitude response and min response frequency
[min_response, min_response_index] = min(abs(HF))
% No ';' so answers print to screen
min_response_freq = Freq(min_response_index)

% Interrogate Figure 1 to check the results

% COPY FIGURES TO A WORD DOCUMENT WHEN DONE

