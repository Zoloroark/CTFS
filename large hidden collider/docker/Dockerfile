FROM python:3.11-slim

# Install socat for network connection handling
RUN apt-get update && \
    apt-get install -y socat && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Create a non-root user for security
RUN useradd -m -u 1000 ctfuser

# Set working directory
WORKDIR /app

# Copy application files
COPY app.py /app/
COPY flag.txt /app/

# Set permissions
RUN chown -R ctfuser:ctfuser /app && \
    chmod 444 /app/flag.txt

# Switch to non-root user
USER ctfuser

# Expose port
EXPOSE 51673

# Run the application with socat
# This will listen on port 51673 and spawn a new Python process for each connection
CMD ["socat", "TCP-LISTEN:51673,reuseaddr,fork", "EXEC:'python3 -u /app/app.py',pty,stderr,setsid,sigint,sane"]
