FROM devkitpro/devkitarm
ENV DEBIAN_FRONTEND=noninteractive

ARG USERNAME=ubuntu
ARG USER_UID=1005
ARG USER_GID=$USER_UID

ENV HOME /home/ubuntu

SHELL ["/bin/bash", "-l", "-c"]

# # Create the user
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    #
    # [Optional] Add sudo support. Omit if you don't need to install software after connecting.
    && apt-get update \
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

RUN DEBIAN_FRONTEND=noninteractive apt-get update \
 && apt-get install -qq -y --no-install-recommends \
            build-essential \
            cmake \
            git \
            ca-certificates \
            vim \
            libssl-dev \
            libeigen3-dev \
            clang \
            curl \
            ninja-build \
            libgtk-3-dev \
            lcov \
            locales-all \ 
            gdb \
 && rm -rf /var/lib/apt/lists/* \
 && rm -rf /tmp/*


ENV DEVKITARM=/opt/devkitpro/devkitARM
ENV DEVKITPRO=/opt/devkitpro
ENV DEVKITPPC=/opt/devkitpro/devkitPPC
ENV PATH="${DEVKITPRO}/tools/bin:${PATH}"