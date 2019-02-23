ScaleFactor = 512;

[Ak1, Bk1] = show_filter_responses_pz([0.95*exp(j*pi*7.5/180), 0.95*exp(-j*pi*7.5/180)],[1*exp(j*pi*7.5/180), 1*exp(-j*pi*7.5/180)], 0.9037008, 48e3,100e3, 40, 1);

scaled_A0 = round(Ak1(1)*ScaleFactor); 
scaled_A1 = round(Ak1(2)*ScaleFactor); 
scaled_A2 = round(Ak1(3)*ScaleFactor); 

unscaled_A0 = scaled_A0/ScaleFactor;
unscaled_A1 = scaled_A1/ScaleFactor;
unscaled_A2 = scaled_A2/ScaleFactor;

scaled_B0 = round(Bk1(1)*ScaleFactor); 
scaled_B1 = round(Bk1(2)*ScaleFactor); 
scaled_B2 = round(Bk1(3)*ScaleFactor); 

unscaled_B0 = scaled_B0/ScaleFactor;
unscaled_B1 = scaled_B1/ScaleFactor;
unscaled_B2 = scaled_B2/ScaleFactor;

scaled_Ak1 = [scaled_A0, scaled_A1, scaled_A2];
scaled_Bk1 = [scaled_B0, scaled_B1, scaled_B2];

unscaled_Ak1 = [unscaled_A0, unscaled_A1, unscaled_A2];
unscaled_Bk1 = [unscaled_B0, unscaled_B1, unscaled_B2];

[poles, zeros, HF1, Fd] = show_filter_response(unscaled_Ak1, unscaled_Bk1, 48e3, 100e3, 40, 1);

[Ak2, Bk2] = show_filter_responses_pz([0.95*exp(j*pi*15/180), 0.95*exp(-j*pi*15/180)],[1*exp(j*pi*15/180), 1*exp(-j*pi*15/180)], 0.9037008, 48e3,100e3, 40, 1);

scaled_A0 = round(Ak2(1)*ScaleFactor); 
scaled_A1 = round(Ak2(2)*ScaleFactor); 
scaled_A2 = round(Ak2(3)*ScaleFactor); 

unscaled_A0 = scaled_A0/ScaleFactor;
unscaled_A1 = scaled_A1/ScaleFactor;
unscaled_A2 = scaled_A2/ScaleFactor;

scaled_B0 = round(Bk2(1)*ScaleFactor); 
scaled_B1 = round(Bk2(2)*ScaleFactor); 
scaled_B2 = round(Bk2(3)*ScaleFactor); 

unscaled_B0 = scaled_B0/ScaleFactor;
unscaled_B1 = scaled_B1/ScaleFactor;
unscaled_B2 = scaled_B2/ScaleFactor;

scaled_Ak2 = [scaled_A0, scaled_A1, scaled_A2];
scaled_Bk2 = [scaled_B0, scaled_B1, scaled_B2];

unscaled_Ak2 = [unscaled_A0, unscaled_A1, unscaled_A2];
unscaled_Bk2 = [unscaled_B0, unscaled_B1, unscaled_B2];

[poles, zeros, HF2, Fd] = show_filter_response(unscaled_Ak2, unscaled_Bk2, 48e3, 100e3, 40, 1);

Hcascade = HF1.*HF2;
plot_freq_responses(Fd, Hcascade, 48e3, 9)


