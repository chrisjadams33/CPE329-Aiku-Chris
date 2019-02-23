ScaleFactor = 2^13;

[Ak, Bk] = show_filter_responses_pz([0.95*exp(j*pi*15/180), 0.95*exp(-j*pi*15/180), 0.95*exp(j*pi*7.5/180), 0.95*exp(-j*pi*7.5/180)],[1*exp(j*pi*15/180), 1*exp(-j*pi*15/180), 1*exp(j*pi*7.5/180), 1*exp(-j*pi*7.5/180)], 0.9037008, 48e3,100e3, 40, 1);

scaled_A0 = round(Ak(1)*ScaleFactor); 
scaled_A1 = round(Ak(2)*ScaleFactor); 
scaled_A2 = round(Ak(3)*ScaleFactor); 
scaled_A3 = round(Ak(4)*ScaleFactor); 
scaled_A4 = round(Ak(5)*ScaleFactor); 

unscaled_A0 = scaled_A0/ScaleFactor;
unscaled_A1 = scaled_A1/ScaleFactor;
unscaled_A2 = scaled_A2/ScaleFactor;
unscaled_A3 = scaled_A3/ScaleFactor;
unscaled_A4 = scaled_A4/ScaleFactor;

scaled_B0 = round(Bk(1)*ScaleFactor); 
scaled_B1 = round(Bk(2)*ScaleFactor); 
scaled_B2 = round(Bk(3)*ScaleFactor); 
scaled_B3 = round(Bk(4)*ScaleFactor); 
scaled_B4 = round(Bk(5)*ScaleFactor);

unscaled_B0 = scaled_B0/ScaleFactor;
unscaled_B1 = scaled_B1/ScaleFactor;
unscaled_B2 = scaled_B2/ScaleFactor;
unscaled_B3 = scaled_B3/ScaleFactor;
unscaled_B4 = scaled_B4/ScaleFactor;

scaled_Ak = [scaled_A0, scaled_A1, scaled_A2, scaled_A3, scaled_A4];
scaled_Bk = [scaled_B0, scaled_B1, scaled_B2, scaled_B3, scaled_B4];

unscaled_Ak = [unscaled_A0, unscaled_A1, unscaled_A2, unscaled_A3, unscaled_A4];
unscaled_Bk = [unscaled_B0, unscaled_B1, unscaled_B2, unscaled_B3, unscaled_B4];

[poles, zeros] = show_filter_response(unscaled_Ak, unscaled_Bk, 48e3, 1000, 40, 1);

%display
scaled_Ak
scaled_Bk
unscaled_Ak
unscaled_Bk

error_Ak = (abs(Ak - unscaled_Ak)./Ak)*100; 
error_Bk = (abs(Bk - unscaled_Bk)./Bk)*100;

poles_magn = abs(poles);
poles_theta = angle(poles)*180/pi; 

zeros_magn = abs(zeros);
zeros_theta = angle(zeros)*180/pi; 
