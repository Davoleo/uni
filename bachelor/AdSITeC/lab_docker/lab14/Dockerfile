FROM fedora

RUN yum -y install httpd which gettext

WORKDIR /var/www/html
COPY Hello_docker.html /var/www/html
COPY entrypoint.sh /entrypoint.sh

ENV AUTHOR="Luca"
EXPOSE 80

ENTRYPOINT [ "/entrypoint.sh" ]
# CMD envsubst < Hello_docker.html > index.html ; /usr/sbin/httpd -D FOREGROUND;
