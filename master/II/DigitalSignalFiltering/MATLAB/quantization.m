function[vinq,eq]=quantization(tsh,vinsh,FS,Nb);

global nfig;

LSB=FS/(2^Nb);
dr=[0:LSB:FS-LSB];

for i=1:1:length(vinsh)
   
       [y,x]=min(abs( vinsh(i) - dr ));
       vinq(i)=dr(x);
       eq(i)=vinsh(i)-vinq(i); 
       
end



% figure(nfig);
% plot(tsh,vinq,'b+','LineWidth',2);
% plot(tsh,eq,'-m','LineWidth',2);
% xlabel('Time - [sec]');ylabel('Amplitude - [V]');
% legend('vin','vinsh','vinq','Quantization Error');