FROM alpine:latest

# Install PIP on Alpine dist
RUN apk add --update py3-pip

# Copy requirements files and install the dependencies
COPY requirements.txt /usr/src/app/
RUN pip install --no-cache-dir -r /usr/src/app/requirements.txt

# Sauce Files [heh]
COPY app.py /usr/src/app/
COPY templates/index.html /usr/src/app/templates/

# Port
EXPOSE 5000

# Run the app
CMD [ "python3", "/usr/src/app/app.py" ]

