FROM debian:bookworm-slim

RUN set -eu && \
    apt update && \
    apt --no-install-recommends -y install \
        build-essential=12.9 \
        uuid-dev=2.38.1-5+deb12u1 \
        acpica-tools=20200925-8 \
        git \
        nasm=2.16.01-1 \
        python-is-python3

WORKDIR /home

VOLUME vuln-edk2

CMD ["bash"]
