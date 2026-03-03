FROM ubuntu:22.04

# Install required packages
RUN apt update && apt install -y \
    socat \
    gcc \
    && rm -rf /var/lib/apt/lists/*

# Add user and create challenge directory
RUN useradd -ms /bin/sh golfer

WORKDIR /home/golfer/

# Copy files into container, except dockerignore
COPY . ./

# Setup docker env
RUN \
    # Command to rebuild the binary. Not needed if binary has already been buit and is in the directory. 
    #gcc -g -rdynamic -fno-stack-protector golf.c -o golf &&\
    chown -R root:golfer /home/golfer &&\
    chmod 750 /home/golfer &&\
    chmod 550 /home/golfer/golf &&\
    chown root:golfer /home/golfer/flag.txt && \
    chmod 440 /home/golfer/flag.txt


# Expose port
EXPOSE 15590

# Run socat to handle connections
CMD ["socat", "-T60", "TCP-LISTEN:15590,reuseaddr,fork,su=golfer","EXEC:/home/golfer/golf"]

