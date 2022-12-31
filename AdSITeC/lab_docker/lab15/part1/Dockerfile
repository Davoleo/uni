FROM fedora

# Install HTTPD service
RUN yum install -y httpd

# Default Env
ENV DOCUMENTROOT /srv/www/http PORT 80

# Make sure the serve directory exists and give permission to the apache daemon on it
RUN mkdir -p $DOCUMENTROOT && chown -R apache:apache $DOCUMENTROOT

# Expose HTTP port
EXPOSE $PORT

COPY httpd.template.conf /etc/httpd/conf/httpd.template.conf
COPY entrypoint.sh /entrypoint.sh