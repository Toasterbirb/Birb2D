FROM debian

RUN apt-get -y update &&   \
    apt-get -y install gcc \
    g++                    \
    git                    \
    make                   \
    vim                    \
    libsdl2-dev            \
    libsdl2-image-dev      \
    libsdl2-ttf-dev        \
    libsdl2-mixer-dev      \
    libsdl2-gfx-dev

# Setup rootless env
ARG USER=birb

RUN useradd -m ${USER} && \
    chown -R ${USER}:${USER} /home/${USER}

WORKDIR /home/${USER}
COPY --chown=${USER} . workspace
USER ${USER}
