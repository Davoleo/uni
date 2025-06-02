clear all;
% close all;

set(0,'DefaultAxesFontName','arial');
set(0,'DefaultAxesFontSize',24);

global k T nfig;
k=13.8e-24;
T=300;
Nb=8;

nfig=11;

%%%
mypath='C:\Dev\uni\master\II\DigitalSignalFiltering\DigitalSignalFiltering.sim\sim_1\behav\xsim\';
myfilename='output_results_mdm.txt';

d=importdata(strcat(mypath,myfilename));
ysignal=bin2dec(num2str(d));
ysignalFS=ysignal/(2^Nb);
ysignalFS_f=movmean(ysignalFS,64);

%%% Time Axis
tclk=20e-9;
N=length(ysignal);

Tperiod=(2^(Nb))*tclk;
fperiod=1/Tperiod;
fs=1/tclk;

TSTOP=tclk*N;
t=1:1:N;
t=(t/N)*TSTOP;

%%% Noise power
pnoise_power_rms = rms(ysignal-mean(ysignal));

%%%
%%% Time Domain
figure(nfig);
plot(t,ysignal,'-y','LineWidth',4);
hold on;
grid on;
xlabel('Time - [s]');ylabel('Digital - [-]');

%%% Scaled to 1V
nfig=nfig+1;
figure(nfig);
plot(t,ysignalFS,'-y','LineWidth',4);
hold on;
grid on;
xlabel('Time - [s]');ylabel('Digital - [-]');
% axis([1e-6 5e-6+(2^Nb)*2*tclk -0.1 1.1]);

