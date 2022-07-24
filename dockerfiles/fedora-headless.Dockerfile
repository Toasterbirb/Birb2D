FROM fedora

RUN dnf -y update &&       \
    dnf -y install gcc     \
    gcc-c++                \
    git                    \
    cmake                  \
	valgrind               \
    vim                    \
	fluidsynth-devel       \
	libxmp-devel           \
	flac-devel             \
	freetype-devel         \
	opusfile-devel


# Setup rootless env
ARG USER=birb

RUN useradd -m ${USER} && \
    chown -R ${USER}:${USER} /home/${USER}

WORKDIR /home/${USER}
COPY --chown=${USER} . workspace
USER ${USER}

# Remove any build files
RUN rm -rf workspace/build
