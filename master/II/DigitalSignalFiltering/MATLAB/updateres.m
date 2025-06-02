function[res]=updateres(Nb,tclk,NFIFO,SNRdB,FS,pnoise,A0,T0,f0,fs,OVR,Mperiods,Nsamples_tot)

res.Nb=Nb;
res.tclk=tclk;
res.NFIFO=NFIFO;
res.SNRdB=SNRdB;
res.FS=FS;
res.pnoise=pnoise;
res.A0=A0;
res.T0=T0;
res.f0=f0;
res.fs=fs;
res.fcutoff=0.5*fs/NFIFO;
res.OVR=OVR;
res.Mperiods=Mperiods;
res.Nsamples_tot=Nsamples_tot;
res.TOTAL_SIM_TIME=Nsamples_tot*tclk;
