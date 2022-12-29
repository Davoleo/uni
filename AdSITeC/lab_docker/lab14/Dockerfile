FROM fedora

RUN yum -y install httpd gettext

WORKDIR /var/www/html
COPY Hello_docker.html /var/www/html

ENV AUTHOR="Luca"
EXPOSE 80

CMD envsubst < Hello_docker.html > index.html ; /usr/sbin/httpd -D FOREGROUND;
