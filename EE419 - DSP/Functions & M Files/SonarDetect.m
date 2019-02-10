function [sub_type, disp_dist] = SonarDetect(xn)

load('SubSonar', '-mat')
%xn_envelope = abs(hilbert(xn));

%compute cross correlatation the received echo signal with each of the 
%echos from subs
[LAsub, LAindex] = NormCrossCorrelate(xn, LosAngelesSubEcho);
[Akulasub, Akulaindex] = NormCrossCorrelate(xn, AkulaSubEcho);
[Typhoonsub, Typhoonindex] = NormCrossCorrelate(xn, TyphoonSubEcho);
%compute cross correlation b/w received echo signal with the Txpulse to see
%if echo is caused by rock/wall 
[Rock, Rockindex] = NormCrossCorrelate(xn, TxPulse);

%take the Hilbert Transform to accurately find the absolute peak of the
%cross-correlation results 
LA_envelope = abs(hilbert(LAsub));
Akula_envelope = abs(hilbert(Akulasub));
Typhoon_envelope = abs(hilbert(Typhoonsub));
Rock_envelope = abs(hilbert(Rock));

%find the index where the cross-correlation is at its max
LA_i = find(LA_envelope == max(LA_envelope), 1, 'first');
Akula_i = find(Akula_envelope == max(Akula_envelope), 1, 'first');
Typhoon_i = find(Typhoon_envelope == max(Typhoon_envelope), 1, 'first');
Rock_i = find(Rock_envelope == max(Rock_envelope), 1, 'first');

%organize the magnitude values of the max peaks into an array
peaks_i = [LA_envelope(LA_i) Akula_envelope(Akula_i) Typhoon_envelope(Typhoon_i) Rock_envelope(Rock_i)];
peak_hil = find(peaks_i == max(peaks_i), 1);       %find the index of greatest peak corresponding to cross corr w one of the subs

%find the index of the secons peak of the cross-correlation result
LA_envelope_temp = LA_envelope; Akula_envelope_temp = Akula_envelope; 
Typhoon_envelope_temp = Typhoon_envelope; Rock_envelope_temp = Rock_envelope;

if (peak_hil == 1)
    LA_envelope_temp(LA_i - 500: LA_i + 500) = 0;  %set max of col to 0
elseif (peak_hil == 2)
    Akula_envelope_temp(Akula_i - 500: Akula_i + 500) = 0;  %set max of col to 0
elseif (peak_hil == 3)
    Typhoon_envelope_temp(Typhoon_i - 500: Typhoon_i + 500) = 0;  %set max of col to 0
else
    Rock_envelope_temp(Rock_i - 500: Rock_i + 500) = 0;  %set max of col to 0

LA_ii = find(LA_envelope_temp == max(LA_envelope_temp), 1, 'first');
Akula_ii = find(Akula_envelope_temp == max(Akula_envelope_temp), 1, 'first');
Typhoon_ii = find(Typhoon_envelope_temp == max(Typhoon_envelope_temp), 1, 'first');
Rock_ii = find(Rock_envelope_temp == max(Rock_envelope_temp), 1, 'first');

%organize the magnitude values of the second peaks into an array
peaks_ii = [LA_envelope(LA_ii) Akula_envelope(Akula_ii) Typhoon_envelope(Typhoon_ii) Rock_envelope(Rock_ii)];
peak_hil_2 = find(peaks_ii == max(peaks_ii), 1);       %find the index of greatest peak corresponding to cross corr w one of the subs

% peaks_temp = peaks; peaks_temp(:,peak_hil) = 0;
% peak_hil_2 = find(peaks_temp == max(peaks_temp), 1);

    % check if the highest value of cross correlation result is valid    
    if (peaks_i(peak_hil) > mean(peaks_i) + 0.002)
        if (peak_hil == 1)
            sub_type = 'LosAngeles Sub';
            peak_i = LAindex(LA_i);
        elseif (peak_hil == 2)
            sub_type = 'Akula Sub';
            peak_i = Akulaindex(Akula_i);
        elseif (peak_hil == 3)
            sub_type = 'Typhoon Sub';
            peak_i = Typhoonindex(Typhoon_i);
        elseif (peak_hil == 4)
            sub_type = 'Rock/Wall';
            peak_i = Rockindex(Rock_i);
        end
    else
        sub_type = 'Nothing in path';
    end
    
    if (peaks_ii(peak_hil_2) > mean(peaks_ii) + 0.001)
        if (peak_hil_2 == 1)
            sub_type_2 = 'LosAngeles Sub';
            peak_ii = LAindex(LA_i);
        elseif (peak_hil_2 == 2)
            sub_type_2 = 'Akula Sub';
            peak_ii = Akulaindex(Akula_i);
        elseif (peak_hil_2 == 3)
            sub_type_2 = 'Typhoon Sub';
            peak_ii = Typhoonindex(Typhoon_i);
        elseif (peak_hil_2 == 4)
            sub_type_2 = 'Rock/Wall';
            peak_ii = Rockindex(Rock_i);
        end
    else
        sub_type_2 = 'Nothing in path';
    end
    
%determine the distance to the detected sub or the rock/wall 
fs = 50000; %sampling frequency 
vs = 1500;  %speed of sound under water in m/s 

if (~strcmp('Nothing in path', sub_type))
    time_tx_rx = (peak_i/fs); %calculate time for tx and rx based off of the peak_i index
    dist = (time_tx_rx/2)*vs; %dist. to object is only half of time_tx_rx

    %display distance
    disp_dist = num2str(dist);
    disp(sub_type)
    disp(strcat(disp_dist, 'm'))
end

if (~strcmp('Nothing in path', sub_type_2))
    time_tx_rx_2 = (peak_ii/fs); %calculate time for tx and rx based off of the peak_i index
    dist_2 = (time_tx_rx_2/2)*vs; %dist. to object is only half of time_tx_rx

    %display distance
    disp_dist_2 = num2str(dist_2);
    disp(sub_type_2)
    disp(strcat(disp_dist_2, 'm'))
end

end