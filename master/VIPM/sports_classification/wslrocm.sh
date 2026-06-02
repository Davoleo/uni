#!/bin/bash

sudo apt update
wget https://repo.radeon.com/amdgpu-install/7.2/ubuntu/noble/amdgpu-install_7.2.70200-1_all.deb
sudo apt install ./amdgpu-install_7.2.70200-1_all.deb

amdgpu-install -y --usecase=wsl,rocm --no-dkms

rocminfo
PAUSE