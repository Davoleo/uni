function[vinq,vinq2,eq]=quantization(t,vin,vins2,fs,fo,FS,Nb,plotf)

global nstart nstep Nsample LSB;
global vin vins vinsh;
global nfig;

Nb
LSB=FS/2^Nb;
dr=[-FS/2+LSB/2:LSB:FS/2-LSB/2];

for i=1:1:length(vinsh)
   
       [y,x]=min(abs( vinsh(i) - dr ));
       vinq(i)=dr(x);
       eq(i)=vin(i)-vinq(i);   
end

for i=1:1:length(vins2)
   
       [y,x]=min(abs( vins2(i) - dr ));
       vinq2(i)=dr(x);
       eq2(i)=vin(i)-vinq(i);   
end

if plotf
    figure(nfig);
    plot(t,vin,'k','LineWidth',2);
    hold on;
    plot(t,vinq,'b','LineWidth',2);
    plot(t,eq,'r','LineWidth',2);
    grid on;
    xlabel('Time - [sec]');ylabel('Amplitude - [V]');
    legend('vin','vinq','Eq');
end