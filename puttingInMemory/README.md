# Borrowed from Callum's return to sender setup 

## Setup

- Theres a docker-compose.yml and Dockerfile, the Dockerfile is what does the
    building of the docker image to be used by docker-compose.yml.
- You will likely need to install docker on the host, if not already on it. Im
    not gonna tell you how to install docker 0_0

To run the image, do:
```shell
docker compose up -d --build --force-recreate
```
USE THIS ANYTIME YOU NEED TO RESTART THE CONTAINER TOO

If you need to access the image for whatever reason, you can do so with:
```shell
docker exec -it puttinginmemory-golfing-1 bash
```

If you need to check the logs, to *maybe* debug(?), do so with this:
```shell
docker logs -f puttinginmemory-golfing-1
```
> i do not remember if any logs show up ever...

IF you need to recompile the executable, there is a gcc command in the Dockerfile. 
```shell
gcc -g -rdynamic -fno-stack-protector golf.c -o golf &&\
```
WILL BREAK IF NOT COMPILED ON 22.04

- flag.txt is the flag value that the user will grab to submit, people are
    will get the shell as the user return, so should not be able to modify the
    flag, if they do manage to do something to it... idk give them extra points
    or something lol, idk of any privs escs on this chall, it does use ubuntu
    22.04 tho so who knows.....
- you can change flag.txt. if you wish to do so, do it then relaunch the
    container, or before you launch it initially..


### Testing

solve.py should provide shell access.
