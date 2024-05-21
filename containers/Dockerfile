FROM debian:bookworm-slim

RUN set -eu && \
    apt update && \
    apt --no-install-recommends -y install \
        build-essential \
        uuid-dev \
        iasl \
        git \
        nasm \
        python-is-python3 \
        qemu-system-x86
