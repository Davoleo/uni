FROM fedora

# Install HTTPD service
RUN yum install -y httpd

# Expose HTTP port
EXPOSE 80

COPY httpd.conf /etc/httpd/conf/httpd.conf

CMD [ "/usr/sbin/httpd", "-D", "FOREGROUND" ]