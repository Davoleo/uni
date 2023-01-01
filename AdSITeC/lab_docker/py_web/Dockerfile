# Python Ver 3.7 image
FROM python:3.7-alpine

# set the current WD to /code
WORKDIR /code

# Environments variables used by the flask command
ENV FLASK_APP=app.py
ENV FLASK_RUN_HOST=0.0.0.0

# Install other dependencies
RUN apk add --no-cache gcc musl-dev linux-headers

# Copy dependencies file and install python packages dependencies
COPY requirements.txt requirements.txt
RUN pip install -r requirements.txt

# Service Port
EXPOSE 5000

# Copy other project files in this directory to the WD in the container
COPY . .

# On startup the container should run the flask app
CMD ["flask", "run"]