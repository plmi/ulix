FROM debian/eol:squeeze-slim@sha256:0b0555951023232dde17db8b7d88f654791e949c3f21285e497ce4fbc136606c

ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/Berlin
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update \
  && apt-get install -y gcc make vim gcc noweb python nasm mtools qemu sudo

WORKDIR /root
RUN mkdir ulix
WORKDIR /root/ulix
RUN chmod +x /root/ulix/bin-build/assembler-parser.py
