clear all;
close all;

global nstart nstep Nsample LSB indexsh indexs;
global vin vins vinsh;
global nfig;

% nfig=33;
nfig=1;
%%% - Sistemare il param FS in modo indipendente dal valore 0P della
%%% sinusoide
%%% - Non mi piace -0.5 +0.5
%%% - Aggiungere un noise
%%% - Fare la FFT del segnale quantizzato
%%%

%%%%%%%%% Parameters %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
k=13.8e-24;
T=300;

%%% Full-scale
FS=1;

%%% Input Signal and Sampling frequency, Bits Resolution
f0=1e3;
fs=64e3;
Nb=4;
LSB=FS/2^Nb;

%%%%%%%%%%%% Input signal %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
A=FS/2;

Nperiod=1;
N=128*fs/f0;
Nsample=round(fs/f0);

%%% Time Axis
T=Nperiod/f0;
t=1:1:N;
t=t/N;
t=t*T;
vin=A*sin(2*pi*f0*t);

%%%%%%%%%%%%%%%%%%% Sampling %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
[vins,vins2,vinsh]=sampling(t,vin,fs,f0,0);

%%%%%%%%%%%%%%%%%%% Quantization %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
[vinq,vinq2,eq]=quantization(t,vin,vins2,fs,f0,FS,Nb,0);
vinq_dft(1:1:fs/f0)=vinq(1:128:length(vinq));

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% PLOT in Time Domain
%%% Sampling Plots
figure(nfig);
plot(t,vin,'-k','LineWidth',4);
hold on;
grid on;
xlabel('Time - [sec]');ylabel('Amplitude - [V]');
legend('vin');
nfig=nfig+1;

figure(nfig);
plot(t,vin,'-k','LineWidth',4);
hold on;
plot(t,vins,'-ro','LineWidth',1,'MarkerSize',8);
grid on;
xlabel('Time - [sec]');ylabel('Amplitude - [V]');
legend('vin','vins');
nfig=nfig+1;

figure(nfig);
plot(t,vin,'-k','LineWidth',4);
hold on;
plot(t,vins,'-ro','LineWidth',1,'MarkerSize',8);
plot(t,vinsh,'m','LineWidth',2);
grid on;
xlabel('Time - [sec]');ylabel('Amplitude - [V]');
legend('vin','vins','vinsh');
nfig=nfig+1;

figure(nfig);
plot(t,vin,'-k','LineWidth',4);
hold on;
plot(t,vins,'-ro','LineWidth',1,'MarkerSize',8);
plot(t,vinsh,'m','LineWidth',2);
plot(t,vin-vinsh,'b','LineWidth',2);
grid on;
xlabel('Time - [sec]');ylabel('Amplitude - [V]');
legend('vin','vins','vinsh','error');
nfig=nfig+1;

%%% Quantization Plots
figure(nfig);
plot(t,vin,'-k','LineWidth',4);
hold on;
plot(t,vinsh,'m','LineWidth',2);
plot(t,vinq,'b','LineWidth',2);
grid on;
xlabel('Time - [sec]');ylabel('Amplitude - [V]');
legend('vin','vinsh','vinshq');
nfig=nfig+1;

figure(nfig);
plot(t,vin,'-k','LineWidth',4);
hold on;
plot(t,vinsh,'m','LineWidth',2);
plot(t,vinq,'b','LineWidth',2);
plot(t,eq,'r','LineWidth',2);
grid on;
xlabel('Time - [sec]');ylabel('Amplitude - [V]');
legend('vin','vinsh','vinshq','eq');
nfig=nfig+1;

figure(nfig);
plot(t,vin,'-k','LineWidth',4);
hold on;
plot(t,vins,'m','LineWidth',2);
plot(t,vinq,'b','LineWidth',2);
plot(t,eq,'r','LineWidth',2);
grid on;
xlabel('Time - [sec]');ylabel('Amplitude - [V]');
legend('vin','vins','vinshq','eq');
nfig=nfig+1;

% figure(nfig);
% plot(t,vin,'-k','LineWidth',2);
% grid on;
% hold on;
% %plot(t,vinrms,'-k','LineWidth',2);
% xlabel('Time - [sec]');ylabel('Amplitude - [V]');
% 
% nfig=nfig+1;
% % 
% % my_fft(t,vinq_dft,fo,Nperiod);
% % 
% % YqdB=my_fft(t,vins2,fo,Nperiod);
% YqdB=my_fft(fo,Nb,vinq2,1);
% figure;
% plot(YqdB);