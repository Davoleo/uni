FROM fedora

# Install HTTPD service
RUN yum install -y httpd

# Make sure the serve directory exists and give permission to the apache daemon on it
RUN mkdir -p /srv/www/http && chown -R apache:apache /srv/www/http

# Default Env
ENV DOCUMENTROOT /srv/www/http PORT 80

# Expose HTTP port
EXPOSE 80

COPY httpd.conf /etc/httpd/conf/httpd.conf

CMD [ "/usr/sbin/httpd", "-D", "FOREGROUND" ]