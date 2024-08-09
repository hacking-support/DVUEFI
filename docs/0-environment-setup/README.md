# Stage 0: Setting up DVUEFI Environment

Welcome to DVUEFI!

Before we can begin exploring UEFI vulnerabilities, we must setup our environment.
While the environment differs slightly from stage to stage, some elements remain the same.

## Compiling EDK II
EDK II is the firmware reference implementation that forms a base for the first two stages (and is used in the last stage also).

We recommend using our docker image to set up the toolchain.
See [here](../../edk2-build-toolchain/README.md) for instructions on how to build the image and use it to compile the firmware.
To use this method, you have to have [docker](https://docs.docker.com/engine/install/) installed on your system.

If you would prefer not to use docker, you can try to install the dependencies that the docker image uses directly on your system, and follow the rest of the instructions as if you were using docker.

## Installing QEMU
[QEMU](https://www.qemu.org/download/) can be installed with your package manager, from pre-existing binaries (hosted [here](https://qemu.weilnetz.de/w64/2024/) for windows), or by compiling it from source.

See also:
- Compilation instructions for [Linux](https://wiki.qemu.org/Hosts/Linux)
- Compilation instructions for [Windows](https://wiki.qemu.org/Hosts/W32) (not recommended)

Note: when compiling for Linux, you can configure the build with `./configure --enable-slirp` to enable networking, which will be useful for future DVUEFI challenges.


## Installing VMware (Only for Stage3: work in progress)
Recently, VMware workstation PRO was made [free](https://blogs.vmware.com/workstation/2024/05/vmware-workstation-pro-now-available-free-for-personal-use.html) for personal use.

Unfortunately, we found it quite tricky to obtain the build from the Broadcom website, so we continue using the free VMWare Workstation Player, which can be downloaded for both Windows and Linux from [here](https://softwareupdate.vmware.com/cds/vmw-desktop/player/17.5.2/23775571/).

On some Linux installations, we've found that VMWare Player was failing to build some of its required drivers.
To fix this, we've used the [vmware-host-modules](https://github.com/nan0desu/vmware-host-modules/wiki) repository.
