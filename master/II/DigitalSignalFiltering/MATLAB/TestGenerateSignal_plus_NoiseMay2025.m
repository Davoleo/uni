clear all;
close all;

set(0,'DefaultAxesFontName','arial');
set(0,'DefaultAxesFontSize',24);
global k T nfig;
k=13.8e-24;
T=300;
nfig=1;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
mypath='C:\Dev\uni\master\II\DigitalSignalFiltering\DigitalSignalFiltering.sim\sim_1\behav\xsim\';
myfilename='mysignal.txt';
writemyfile=1;

%%% Data Resolution
Nb=8;
tclk=20e-9;
N=Nb;
NFIFO=64;

%%% SINUSOIDAL SIGNAL and NOISE to fit FS
SNRdB=-6;
FS=256;
SNR=10^(SNRdB/20);
% Noise Power
pnoise=FS/(2*SNR*sqrt(2) + 3);
A0=pnoise*SNR*sqrt(2);
A0off=A0;

%%% Signal Period(s)/freq., OVR and Time Axis
T0=(2^Nb)*tclk;
f0=1/T0;
fs=1/tclk;
fcutoff=0.5*fs/NFIFO;
OVR=fs/(2*f0);
% Numero di periodi per il segnale
Mperiods=10;
Nsamples_tot=Mperiods*2^Nb;

t=1:1:Mperiods*(2^Nb);
t=t/length(t);
t=t*T0*Mperiods;

%%% ysignal is the pure signal
%%% ynoise is the noise signal
%%% yns=ysignal+ynoise
ysignal=0*(A0off+A0*sin(2*pi*f0*t));
ynoise=pnoise*(1+randn(1,length(t))); % Rumore generato con funzione randn
yns=ynoise+ysignal;

%%% A-to-D Conversion (ynsq is the quantized version of yns)
[ynsq,eq]=quantization(t,yns,FS,Nb);
% Segnale più rumore quantizzato

%%% Filtering by Matlab
ynsq_f=movmean(ynsq,NFIFO);

%%% WRITE OUTPUT FILE for VIVADO
if writemyfile
    ynsqb=dec2bin(ynsq);
    writematrix(ynsqb,strcat(mypath,myfilename));
end

%%% Noise power
pnoise_power_rms = rms(ynoise-mean(ynoise));
% Ricalcolo L'RMS sulla traccia che ho generato del rumore (segnale generato potrebbe essere leggermente diverso)

%%% res
res=updateres(Nb,tclk,NFIFO,SNRdB,FS,pnoise,A0,T0,f0,fs,OVR,Mperiods,Nsamples_tot);

%%% Frequency Domain
b=fir1(NFIFO,fcutoff/(0.5*fs),'low');
freqz(b,1,512);
[hf,w] = freqz(b,1,512);

nfig=nfig+1;
f=0.5*fs*w/(pi);
figure(nfig+1);
subplot(2,1,1);
semilogx(f,20*log10(abs(hf)),'-k','LineWidth',2);
hold on;
ylabel('[dB]');
grid on;
subplot(2,1,2);
semilogx(f,(180/pi)*angle(hf),'-k','LineWidth',2);
hold on;
xlabel('Frequency - [Hz]');ylabel('[dB]');
grid on;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
%%% PLOT in Time Domain
nfig=nfig+2;
figure(nfig);
plot(t,ynoise,'-r','LineWidth',2);
hold on;
plot(t,ysignal,'-k','LineWidth',5);
plot(t,FS*ones(1,length(t)),'--k');
plot(t,0*ones(1,length(t)),'--k');
grid on;
xlabel('Time - [s]');ylabel('Values - [-]');
legend('yn','ys','FS');
axis([0 Nsamples_tot*tclk -100 300]);

nfig=nfig+1;
figure(nfig);
plot(t,ysignal+ynoise,'-b','LineWidth',1);
hold on;
plot(t,FS*ones(1,length(t)));
plot(t,0*ones(1,length(t)));
legend('yns');
xlabel('Time - [s]');ylabel('Values - [-]');
grid on;
legend('yns','FS');
axis([0 Nsamples_tot*tclk -100 300]);

nfig=nfig+1;
figure(nfig);
plot(t,ysignal+ynoise,'-b','LineWidth',1);
hold on;
plot(t,ynsq,'-g','LineWidth',3);
plot(t,ynsq_f,'-m','LineWidth',4);
xlabel('Time - [s]');ylabel('Values - [-]');
grid on;
legend('yns','ynsq','ynsqf');
axis([0 Nsamples_tot*tclk -100 300]);

nfig=nfig+1;
figure(nfig);
plot(t,ynsq_f,'-m','LineWidth',6);
hold on;
plot(t,ysignal+mean(ynoise),':k','LineWidth',4)
xlabel('Time - [s]');ylabel('Values - [-]');
grid on;
legend('ynsqf','ysignal');
axis([0 Nsamples_tot*tclk -100 300]);