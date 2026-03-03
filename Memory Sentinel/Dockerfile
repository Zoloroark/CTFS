FROM ubuntu:22.04

# Install required packages
RUN apt update && apt install -y \
    socat \
    gcc \
    && rm -rf /var/lib/apt/lists/*

# Add user and create challenge directory
RUN useradd -ms /bin/sh miner

WORKDIR /home/miner/

# Copy files into container, except dockerignore
COPY . ./

# Compile the challenge binary
RUN \
    gcc -g -rdynamic -fstack-protector-strong canarytesting3.c -o mine &&\
    chown -R root:miner /home/miner &&\
    chmod 750 /home/miner &&\
    chmod 550 /home/miner/mine &&\
    chown root:miner /home/miner/flag.txt && \
    chmod 440 /home/miner/flag.txt && \
    rm -rf *.c


# Expose port
EXPOSE 1337

CMD ["socat", "-T60", "TCP-LISTEN:1337,reuseaddr,fork,su=miner","EXEC:/home/miner/mine,stderr"]

