FROM dorowu/ubuntu-desktop-lxde-vnc
ENV DEBIAN_FRONTEND=noninteractive

ARG USERNAME=ubuntu
ARG USER_UID=1005
ARG USER_GID=$USER_UID

ENV HOME /home/ubuntu

SHELL ["/bin/bash", "-l", "-c"]

RUN apt-get install -y wget
RUN wget -q -O - https://dl.google.com/linux/linux_signing_key.pub | sudo apt-key add - 

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
            visualboyadvance \
            vbaexpress \ 
 && rm -rf /var/lib/apt/lists/* \
 && rm -rf /tmp/*

ENV TZ=Asia/Tokyo
RUN apt update && \
  apt install -yq wget curl libarchive13 xz-utils make gpg pkg-config && \
  wget https://wii.leseratte10.de/devkitPro/pacman/devkitpro-pacman-1.0.2.amd64.deb && \
  dpkg -i devkitpro-pacman-1.0.2.amd64.deb && \
  rm /etc/mtab && \
  ln -s /proc/self/mounts /etc/mtab && \
  all | dkp-pacman --noconfirm -S gba-dev 

ENV DEVKITARM=/opt/devkitpro/devkitARM
ENV DEVKITPRO=/opt/devkitpro
ENV DEVKITPPC=/opt/devkitpro/devkitPPC
ENV PATH="${DEVKITPRO}/tools/bin:${PATH}"

WORKDIR ${HOME}
RUN git clone https://github.com/devkitPro/gba-examples