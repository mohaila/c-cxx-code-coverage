FROM alpine:latest

ARG USER=vscode
ARG GROUP=vscode
ARG UID=1000
ARG GID=1000

RUN apk update \
    && apk add \
    autoconf \
    bash \
    boost-dev \
    build-base \
    cmake \
    curl \
    git \
    gzip \
    lcov \
    libtool \
    pkgconf \
    poco-dev \
    python3-dev \
    samurai \
    starship \
    unzip \
    wget \
    zip \
    && addgroup -g ${GID} ${GROUP} \
    && adduser -D -u ${UID} -G ${GROUP} -s /bin/bash -h /home/${USER} ${USER}

COPY --chown=${UID}:${GID} --chmod=644 .bashrc /home/${USER}
COPY --chown=${UID}:${GID} --chmod=644 .profile /home/${USER}

USER ${USER}
