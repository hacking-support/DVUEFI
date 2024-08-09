FROM debian:bookworm-slim

RUN set -eu && \
    apt update && \
    apt --no-install-recommends -y install \
        build-essential=12.9 \
        qtbase5-dev=5.15.8+dfsg-11+deb12u2 \
        qt5-qmake=5.15.8+dfsg-11+deb12u2 \
        cmake=3.25.1-1 \
        zip=3.0-13


WORKDIR /home

VOLUME vuln-edk2

CMD ["bash"]
