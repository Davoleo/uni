FROM nginx

RUN apt-get update -y
RUN apt-get install -y net-tools iptables iproute2 nmap traceroute dnsutils iputils-ping
RUN apt-get install -y tcpdump openssh-server nano python2 rsyslog

RUN useradd debian -p $(openssl passwd -1 debian) -m

RUN echo "ListenAddress 0.0.0.0" >> /etc/ssh/sshd_config

