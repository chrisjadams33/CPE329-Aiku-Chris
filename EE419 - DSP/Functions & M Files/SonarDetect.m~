function SonarDetect(xn)

load('SubSonar', '-mat')
%xn_envelope = abs(hilbert(xn));


[LAsub, LAindex] = NormCrossCorrelate(xn, LosAngelesSubEcho);
[Akulasub, Akulaindex] = NormCrossCorrelate(xn, AkulaSubEcho);
[Typhoonsub, Typhoonindex] = NormCrossCorrelate(xn, TyphoonSubEcho);

LA_envelope = abs(hilbert(LAsub));
Akula_envelope = abs(hilbert(Akulasub));
Typhoon_envelope = abs(hilbert(Typhoonsub));

LA_i = find(LA_envelope, LA_envelope == max(LA_envelope));
Akula_i = find(Akula_envelope, Akula_envelope == max(Akula_envelope));
Typhoon_i = find(Typhoon_envelope, Typhoon_envelope == max(Typhoon_envelope));

peaks = [LA_envelope(LA_i) Akula_envelope(Akula_i) Typhoon_envelope(Typhoon_i)];

peak_i = find(peaks, peaks == max(peaks));

    if (peaks(peak_i) > mean(peaks) - 0.01)
        if (peak_i == 1)
            sub_type = 'LosAngeles Sub';
        elseif (peak_i == 2)
            sub_type = 'Akula Sub';
        elseif (peak_i == 3)
            sub_type = 'Typhoon Sub';
        end
    end
end