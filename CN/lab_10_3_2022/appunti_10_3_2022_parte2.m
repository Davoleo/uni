%% Scheda 2

% Es 3
% per n -> \infty
test_vec = [0:1000]
test_vec2 = [1:10^3:10^4]

an = (1 + 1./test_vec).^test_vec
bn = (4.*test_vec) ./ (test_vec + 2)
cn = log(1 + sqrt(test_vec ./ (test_vec + 1)))

% Funzione per visualizzare i valori graficamente
%plot(?n)


% Es 4
lim_vec0 = linspace(0, 1, 1000);
lim_vecinf = test_vec;

% tutti e tre analiticasmente equivalenti però i numeri macchina sballano 
% quando molto alti (vedi somma malcondizionata)
a0 = lim_vec0.*(sqrt(lim_vec0.^2 + 1) - lim_vec0)
ainf = lim_vecinf.*(sqrt(lim_vecinf.^2 + 1) - lim_vecinf)

b0 = lim_vec0.*sqrt(lim_vec0.^2 + 1)-lim_vec0.^2
binf = lim_vecinf.*sqrt(lim_vecinf.^2 + 1)-lim_vecinf.^2

c0 = lim_vec0./(sqrt(lim_vec0.^2 + 1) + lim_vec0)
cinf = lim_vecinf./(sqrt(lim_vecinf.^2 + 1) + lim_vecinf)