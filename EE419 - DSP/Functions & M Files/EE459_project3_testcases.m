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


%Plot Analog and Digital DFTs
fsample1 = 20;

%create array of input sequences for the loop
x1_x10 = {x1, x2, x3, x4, x5, x6, x7, x8, x9, x10};

for k= 1:10
    %input_seq = strcat('x', sprintf('%d', k));
    plot_DFT_mag(x1_x10{k}, fsample1, k);
    savefig(sprintf('Figure%d.fig',k));
    Figure_to_img = openfig(sprintf('Figure%d.fig', k));
    saveas(Figure_to_img, sprintf('Test Case %d.png',k))
end

fsample2 = 1000;
x11_x12 = {x11, x12};

for k= 11:12
    %input_seq = strcat('x', sprintf('%d', k));
    plot_DFT_mag(x11_x12{k-10}, fsample2, k);   % sub. 10 to number consistent
    savefig(sprintf('Figure%d.fig',k));
    Figure_to_img = openfig(sprintf('Figure%d.fig', k));
    saveas(Figure_to_img, sprintf('Test Case %d.png',k))
end

