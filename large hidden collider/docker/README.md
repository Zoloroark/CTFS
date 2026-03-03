# CTF Challenge Docker Container

This Docker container serves a Python application over a network connection accessible via netcat.

## Files

- `app.py` - The main Python challenge application
- `flag.txt` - The flag file (customize this with your actual flag)
- `Dockerfile` - Container configuration
- `docker-compose.yml` - Docker Compose configuration for easy deployment

## Building and Running

### Option 1: Using Docker Compose (Recommended)

```bash
docker-compose up -d
```

### Option 2: Using Docker directly

Build the image:
```bash
docker build -t ctf-challenge .
```

Run the container:
```bash
docker run -d -p 51673:51673 --name ctf-challenge ctf-challenge
```

## Connecting

Once the container is running, users can connect using netcat:

```bash
nc localhost 51673
```

Or from a remote machine:
```bash
nc <your-server-ip> 51673
```

## Stopping the Container

### Docker Compose:
```bash
docker-compose down
```

### Docker:
```bash
docker stop ctf-challenge
docker rm ctf-challenge
```

## Configuration

- **Port**: The service runs on port 51673 by default. You can change this in `docker-compose.yml` or the `docker run` command.
- **Flag**: Edit `flag.txt` to set your custom flag.
- **Resource Limits**: Adjust CPU and memory limits in `docker-compose.yml` if needed.

## Security Features

- Runs as a non-root user (`ctfuser`)
- Flag file is read-only
- Each connection spawns an isolated Python process
- Resource limits can be configured to prevent abuse

## Notes

This is an MD5 collision challenge. The application checks if a password hash matches but the actual password differs - a classic hash collision scenario.
