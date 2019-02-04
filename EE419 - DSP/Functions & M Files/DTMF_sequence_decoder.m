function [sequence] = DTMF_sequence_decoder(audio_file, fs)
% __function description__
%
%
    
    chop = fs/10;                               %chunk of data (0.1 sec of data)
    interval = chop/fs;
    chop_num = floor(length(audio_file)/chop);  %number of total chunks of data
    total_keys = 0;                             %counter for keys received
    ready = 1;                                  %variable to receive new key
    invalid_count = 0;                          %counter for number of pause chunks
    n = 0;                                      %loop counter
    key_hold = 0;
    %cycle through data
    while(n <= chop_num-1)
        section = audio_file((n*chop +1):(n+1)*chop);   %chunk of data to look at
        [key] = DTMF_signal_decoder(section, fs, 1);    %get key
        if (key ~= 'N/A')                               %if key received
            key_hold = key_hold +1;
            if (ready == 1)                             %ready to receive new key
                total_keys = total_keys + 1;            %increment key counter
                sequence(total_keys) = key;             %add to key sequence
                ready = 0;                              %not ready to receive
                disp('pause time:')
                disp(invalid_count*interval)
                invalid_count = 0;                      %reset pause count
            end

        else                                            %pause received
            if (invalid_count > 0)
                ready = 1;                              %ready to receive new count
                if (key_hold ~= 0)
                    disp('key time:')
                    disp(key_hold*interval)
                    key_hold = 0;
                end
            end
            invalid_count = invalid_count + 1;          %increment pause count
            if (total_keys == 10)                       
                n = chop_num-1;                         %end loop if 10 keys
            end
        end
        if (invalid_count == 10*fs/chop + 1)            %if pauses equal 10s
            n = chop_num-1;                             %end loop
            if (total_keys ~=7)                         
               disp('Error - Invalid Sequence')         %invalid bc not 10 or 7 keys
            end
        end
        n = n + 1;
    end
    disp(sequence)                                      %print key sequence
    if (total_keys ~=7 && total_keys ~=10)
        disp('Error - Invalid Sequence')                %invalid bc not 10 or 7 keys
    end
    
    %plot spectrogram
    figure
    window = 128; nonoverlap = 120;
    M = length(audio_file)/fs;
    spectrogram(audio_file, window, nonoverlap, 1024, fs)
end