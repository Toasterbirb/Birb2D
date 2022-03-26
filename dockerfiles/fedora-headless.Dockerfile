FROM fedora

RUN dnf -y update &&       \
    dnf -y install gcc     \
    gcc-c++                \
    git                    \
    make                   \
    vim                    \
    SDL2-devel             \
    SDL2_image-devel       \
    SDL2_ttf-devel         \
    SDL2_mixer-devel       \
    SDL2_gfx-devel

# Setup rootless env
ARG USER=birb

RUN useradd -m ${USER} && \
    chown -R ${USER}:${USER} /home/${USER}

WORKDIR /home/${USER}
COPY --chown=${USER} . workspace
USER ${USER}
