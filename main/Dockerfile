FROM ubuntu:16.04
#ENV TZ=Europe/Paris \
#    DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y \
  sudo bash zsh\
  vim nano\
  gcc gcc-multilib build-essential gdb\
  curl

WORKDIR /opt
COPY su_user.sh su_user.sh

WORKDIR /home/user

# Copy and compile stack program
COPY stack.c stack.c
RUN gcc -ggdb -m32 -O0 -z execstack -fno-stack-protector -o stack stack.c
RUN chmod 4755 stack

# Defining default non-root user UID, GID, and name
ARG USER_UID="1000"
ARG USER_GID="1000"
ARG USER_NAME="user"

# Creating default non-user
RUN groupadd -g $USER_GID $USER_NAME\
    && useradd -m -g $USER_GID -u $USER_UID $USER_NAME

# Change home directory ownership
RUN chown user:user /home/user

COPY exploit.c exploit.c
COPY shellcode.c shellcode.c
RUN gcc -ggdb -m32 -O0 -z execstack -o shellcode shellcode.c
USER root
RUN chown user:user \
  exploit.c \
  shellcode.c shellcode

# Generate secret
RUN curl -L https://github.com/rloic/docktical-secret-public/raw/eb184fb39b467b5a52c292cc1c638c877c7c3721/ubuntu-18.04/secret -o secret
RUN chmod u=x,g=,o= secret
RUN ./secret key -s 512
RUN chmod o= key
RUN chmod o=r key.pub

SHELL [ "/bin/bash", "-c" ]
RUN rm -f /bin/sh
RUN ln -s /bin/zsh /bin/sh
USER user

ENTRYPOINT [ "sleep", "infinity" ]