FROM ubuntu:22.10

LABEL maintainer="Marcus"
LABEL version="0.1"
LABEL description="Environment for Moonlander with qmk"

ARG DEBIAN_FRONTEND=noninteractive
SHELL ["/bin/bash", "-c"]

RUN apt-get update && apt-get install --no-install-recommends -y \
    avrdude \
    binutils-arm-none-eabi \
    binutils-riscv64-unknown-elf \
    build-essential \
    ca-certificates \
    clang-format-11 \
    dfu-programmer \
    dfu-util \
    dos2unix \
    ca-certificates \
    gcc \
    gcc-arm-none-eabi \
    gcc-riscv64-unknown-elf \
    git \
    libfl2 \
    libnewlib-arm-none-eabi \
    picolibc-riscv64-unknown-elf \
    python3 \
    python3-pip \
    software-properties-common \
    tar \
    teensy-loader-cli \
    unzip \
    tar \
    wget \
    zip \
    && rm -rf /var/lib/apt/lists/*


RUN python3 -m pip install --upgrade pip setuptools wheel
RUN python3 -m pip install nose2 yapf
RUN python3 -m pip install qmk

# Fix ubuntu path bug
RUN echo 'PATH="$HOME/.local/bin:$PATH"' >> $HOME/.bashrc && source $HOME/.bashrc

RUN qmk setup zsa/qmk_firmware -b firmware21 -y
