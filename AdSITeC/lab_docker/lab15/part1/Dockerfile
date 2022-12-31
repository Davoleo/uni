FROM fedora

# Install HTTPD service
RUN yum install -y httpd

# Make sure the serve directory exists and give permission to the apache daemon on it
RUN mkdir -p /srv/www/http && chown -R apache:apache /srv/www/http

# Default Env
ENV DOCUMENTROOT /srv/www/http PORT 80

# Expose HTTP port
EXPOSE $PORT

COPY httpd.template.conf /etc/httpd/conf/httpd.template.conf
COPY entrypoint.sh /entrypoint.sh