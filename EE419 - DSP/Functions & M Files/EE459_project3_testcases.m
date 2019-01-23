n1 = 0:100-1;

x1 = 1*cos(8*2*pi*n1/20);
x2 = 1*cos(10*2*pi*n1/20);
x3 = 1*cos(12*2*pi*n1/20);
x4 = 1*cos(7.05*2*pi*n1/20);
x5 = 1*cos(7.05*2*pi*n1/20) + 0.25*cos(8.17*2*pi*n1/20);
x6 = x5.*blackman(100).';

n2 = 0:200-1;

x7 = 1*cos(7.05*2*pi*n2/20) + 0.25*cos(8.17*2*pi*n2/20);
x8 = x7.*blackman(200).';
x9 = 1*cos(7.05*2*pi*n2/20) + 1*cos(7.25*2*pi*n2/20);
x10 = x9.*blackman(200).';
x11 = unit_sample(40);
[hn] = unit_sample_response([0.2 0.2 0.2 0.2 0.2], [1 0 0 0 0], 40, 1);
x12 = hn;