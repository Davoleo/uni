FROM busybox:latest

# Copy start script into root dir
COPY start.sh /start.sh

# Exec Permission
RUN chmod +x /start.sh

# Setup Environment Variables
ENV \
AUTHOR=Docker

CMD [ "/start.sh" ]