function [Ak,Bk,HF,Fd,hn,n, maximum]= show_filter_responses_pz(poles,zeros,K,fsample,num_of_f_points, num_of_n_points,figure_num)
% This function takes multiple arguments: the poles and zeros of the
% system, the DC gain (K), the sampling frequency, the number of f and n
% points for which to plot, and the figure number. The function returns
% a pole zero plot, digital and analog frequency responses, and a unit
% sample response.

%create tf (in Z domain) from poles and zeros
numerator = poly(zeros);
denominator = poly(poles);
HZ = K*filt(numerator, denominator)
Ak = denominator
Bk = K*numerator

%create pole/zero diagram 
figure(figure_num)
zplane(Bk, Ak);
grid
title('Pole Zero Diagram')

%plot the frequency response
HF = freqz(Bk, Ak, num_of_f_points);
Fd = linspace(0, 0.5, num_of_f_points);
plot_freq_responses(Fd, HF, fsample, figure_num + 1);

%obtain critical values from the frequency response
HF_mag = abs(HF);
Fd_max_index = find(HF_mag == max(HF_mag), 1, 'first');  
Fd_max = Fd(Fd_max_index)
HF_max = HF_mag(Fd_max_index)
maximum = HF_max;

Fd_min_index = find(HF_mag == min(HF_mag), 1, 'first');
Fd_min = Fd(Fd_min_index)
HF_min = HF_mag(Fd_min_index)

%Find maximum attenuation (in dB)
max_atten = 20*log10(HF_max/HF_min)

%Determine the 3dB cut off frequency
cut_off_dB = 20*log10(HF_max) - 3
cut_off_magn = 10^(cut_off_dB/20)

%Determine filter type
if (HF_mag(1) < (cut_off_magn) && HF_mag(500) > (cut_off_magn))
    disp('Filter type = HPF')
    Filter = 1;
elseif (HF_mag(1) > (cut_off_magn) && HF_mag(500) < (cut_off_magn))
    disp('Filter type = LPF')
    Filter = 2;
elseif (HF_mag(1) > (cut_off_magn) && HF_mag(500) > (cut_off_magn))
    disp('Filter type = Notch Filter')
    Filter = 3;
elseif (HF_mag(1) < (cut_off_magn) && HF_mag(500) < (cut_off_magn))
    disp('Filter type = BPF')
    Filter = 4;
end

if (Filter == 1)
    hp_cutoff = Fd(find( HF_mag > (cut_off_magn) , 1 , 'first'));
    disp('Cut off frequency:')
    disp(hp_cutoff)
    disp('BW:')
    disp(0.5-hp_cutoff)
elseif (Filter == 2)
    lp_cutoff = Fd(find( HF_mag > (cut_off_magn) , 1 , 'last'));
    disp('Cut off frequency:')
    disp(lp_cutoff)
    disp('BW:')
    disp(lp_cutoff)
elseif (Filter == 3)
    notch_cutoff_low = Fd(find( HF_mag < (cut_off_magn) , 1 , 'first'));
    notch_cutoff_high = Fd(find( HF_mag < (cut_off_magn) , 1 , 'last'));
    disp('Cut off frequencies:')
    disp(notch_cutoff_low)
    disp(notch_cutoff_high)
    disp('BW:')
    disp(notch_cutoff_high - notch_cutoff_low)
else
    bp_cutoff_low = Fd(find( HF_mag > (cut_off_magn) , 1 , 'first'));
    bp_cutoff_high = Fd(find( HF_mag > (cut_off_magn) , 1 , 'last'));
    disp('Cut off frequencies:')
    disp(bp_cutoff_low)
    disp(bp_cutoff_high)
    disp('BW:')
    disp(bp_cutoff_high - bp_cutoff_low)
end

%plot the unit sample response
[hn, n] = unit_sample_response(Bk, Ak, num_of_n_points, figure_num + 3);

end

