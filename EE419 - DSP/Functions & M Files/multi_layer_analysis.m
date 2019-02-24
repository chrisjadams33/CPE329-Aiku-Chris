function [ref_coef, amp_plus, amp_minus] = multi_layer_analysis(layers, mu, ep, sig, f, thickness, incident)

ep = ep * 8.85e-12;
mu = mu*4*pi*10e-8;
amp_plus(1) = incident;
ref_plus = ones(1,layers-1);
ref_coef = ones(1,layers-1);
trans = zeros(1,layers-1);
z = ones(1,layers-1);
amp_minus = zeros(1,layers);

for n = 1:layers
    alpha(n) = 2*pi*f*sqrt(mu(n)*ep(n)/2)*sqrt(sqrt(1+(sig(n)/(2*pi*f*ep(n)))^2) - 1);
    beta(n) = 2*pi*f*sqrt(mu(n)*ep(n)/2)*sqrt(sqrt(1+(sig(n)/(2*pi*f*ep(n)))^2) + 1)/10;
    eta(n) = sqrt((1i*2*pi*f*mu(n))/(sig(n) + 1i*2*pi*f*ep(n)));
end

z(layers-1) = eta(layers);

ref_coef(layers-1) = (z(layers-1) - eta(layers-1))/(z(layers-1) + eta(layers-1));
trans(layers-1) = 1+ref_coef(layers-1);
ref_plus(layers-1) = 0;

for n = 1:layers-2
    ref_plus(layers-n-1) = ref_coef(layers-n)*exp(2*(alpha(layers-n)+1i*beta(layers-n))*(-1*thickness));
    z(layers-n-1) = eta(layers-n)*(1+ref_plus(layers-n-1))/(1-ref_plus(layers-n-1));
    ref_coef(layers-n-1) = (z(layers-n-1) - eta(layers-n-1))/(z(layers-n-1) + eta(layers-n-1));
    trans(layers-n-1) = (1+ref_coef(layers-n-1))/(1+ref_plus(layers-n-1))/exp(2*1i*beta(layers-n)*(-1*thickness));
end

amp_minus(1) = amp_plus(1)*ref_coef(1);

for n = 2:layers
    amp_plus(n) = trans(n-1)*amp_plus(n-1);
    amp_minus(n-1) = amp_plus(n-1)*ref_coef(n-1);
end
    

disp(strcat('E_1 plus =', num2str(abs(amp_plus(1)))))
disp(strcat('angle =', num2str(180/pi*angle(amp_plus(1))), ' degrees'))

disp(strcat('E_2 plus =', num2str(abs(amp_plus(2)))))
disp(strcat('angle =', num2str(180/pi*angle(amp_plus(2))), ' degrees'))

disp(strcat('E_3 plus =', num2str(abs(amp_plus(3)))))
disp(strcat('angle =', num2str(180/pi*angle(amp_plus(3))), ' degrees'))

disp(strcat('E_1 minus =', num2str(abs(amp_minus(1)))))
disp(strcat('angle =', num2str(180/pi*angle(amp_minus(1))), ' degrees'))

disp(strcat('E_2 minus =', num2str(abs(amp_minus(2)))))
disp(strcat('angle =', num2str(180/pi*angle(amp_minus(2))), ' degrees'))

disp(strcat('E_3 minus =', num2str(abs(amp_minus(3)))))
disp(strcat('angle =', num2str(180/pi*angle(amp_minus(3))), ' degrees'))

end