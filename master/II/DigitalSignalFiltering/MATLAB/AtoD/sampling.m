function[vins,vins2,vinsh]=sampling(t,vin,fs,fo,plotf)

global nstart nstep Nsample indexsh indexs nfig;

N=length(vin);

nstep=round(N/(fs/fo));
nstart=round(nstep/2);

vins=0*ones(1,length(vin));
vins(nstart:nstep:length(vin)+nstart-1)=vin(nstart:nstep:length(vin)+nstart-1);
vins2(1:1:fs/fo)=vin(nstart:nstep:length(vin)+nstart-1);


for i=1:1:Nsample

    for j=1:1:nstep
       
        indexsh=(i-1)*nstep+j;
        indexs=nstart+(i-1)*nstep;
        vinsh(indexsh)=vins(indexs);
        
    end
    
end
if plotf
    figure(nfig);
    plot(t,vins,'-ro','LineWidth',2);
    hold on;
    plot(t,vinsh,'m','LineWidth',2);
    plot(t,vin-vinsh,'b','LineWidth',2);
    hold on;
    plot(t,vin,'k','LineWidth',2);
    grid on;
    xlabel('Time - [sec]');ylabel('Amplitude - [V]');
    legend('vins','vinsh','vin-vinsh','vin');
    nfig=nfig+1;
end