#!/bin/bash

sudo apt update
wget https://repo.radeon.com/amdgpu-install/7.2/ubuntu/noble/amdgpu-install_7.2.70200-1_all.deb
sudo apt install ./amdgpu-install_7.2.70200-1_all.deb

sudo usermod -a -G render,video $LOGNAME

rocminfo

echo "after checking rocm installation info press enter to reboot the system..."
PAUSE

sudo reboot