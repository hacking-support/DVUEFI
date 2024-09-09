# Debian Container: Build Tools and QEMU

We provide a docker image that can be used to build the (vulnerable) firmware and run it using QEMU virtualisation.

## Obtaining Image
There are two ways to obtain the docker image:

1. Pull it directly from the GitHub container registry (coming soon)
2. Build it yourself

To build the container image, run the following command at the root of the project:

```console
docker build --tag dvuefi-build edk2-build-toolchain
```

This will build a new image named `dvuefi-build` (feel free to use any other name you'd like).
Now if you run `docker images dvuefi-build` you should see something like the following:

```
REPOSITORY         TAG       IMAGE ID       CREATED         SIZE
dvuefi-build       latest    ...        ... seconds ago     ...
```

## Run container interactively
The container we built is very simple: it contains a minimal Debian image with OVMF firmware build tools and QEMU pre-installed.

We can run the container and give it access to the `vuln-edk2` directory so that it can build the firmware and run it.
We do that using `--volume`

```console
docker run --volume ./vuln-edk2:/home/vuln-edk2 --rm -it dvuefi-build

user@docker:/home#
```

You should find yourself in the `home` directory, which should contain the `vuln-edk2` directory inside of it:

```console
user@docker:/home# pwd
/home

user@docker:/home# ls
vuln-edk2
```

## Compiling Vulnerable Firmware
Run `cd vuln-edk2` to enter the directory where we will be compiling the firmware.

You will see a large number of files and directories: most of them come unmodified from the [EDK II](https://github.com/tianocore/edk2/tree/edk2-stable202402) project.
Notice the `VulnerableCode` directory: this directory contains some of the vulnerable modules that serve as challenges in DVUEFI.

To compile EDK II, we must first compile the `BaseTools` package which bootstraps the build tools that we'll use to build the rest of the firmware.
This will also run a testsuite to make sure everything was compiled correctly.

```console
user@docker:/home/vuln-edk2# make -C BaseTools

gcc ...

...

OK

make[1]: Leaving directory '/home/vuln-edk2/BaseTools/Tests'
make: Leaving directory '/home/vuln-edk2/BaseTools'
```

Now it's time to compile the rest of the firmware.
First we need to tell the toolchain to use the `BaseTools` we just compiled:

```console
user@docker:/home/vuln-edk2# source edksetup.sh

Loading previous configuration from /home/vuln-edk2/Conf/BuildEnv.sh
Using EDK2 in-source Basetools
WORKSPACE: /home/vuln-edk2
EDK_TOOLS_PATH: /home/vuln-edk2/BaseTools
CONF_PATH: /home/vuln-edk2/Conf
```

Now if we run the `build` command, it will compile the firmware according to the configuration specified in `Conf/target.txt`--feel free to take a look by opening that file using your favorite editor (you can open it outside of docker).

Some important fields are listed below (more information about each field in `Conf/target.txt`):
- `ACTIVE_PLATFORM = OvmfPkg/OvmfPkgX64.dsc`: what we want to build is the `OVMF` (Open Virtual Machine Firmware) package, since we'll be running it inside a virtualised environment
- `TARGET = DEBUG`: to ease debugging with GDB we create a debug build
- `TARGET_ARCH = X64`: We want to build firmware for X86_64
- `TOOL_CHAIN_TAG = GCC5`: Use the GCC toolchain for the build (pre-installed in the container)

Now to compile OVMF, run `build`:

```console
user@docker:/home/vuln-edk2# build
Build environment: Linux-6.5.0-35-generic-x86_64-with-glibc2.36

...

FV Space Information
SECFV [27%Full] 212992 (0x34000) total, 57600 (0xe100) used, 155392 (0x25f00) free
PEIFV [31%Full] 917504 (0xe0000) total, 284904 (0x458e8) used, 632600 (0x9a718) free
DXEFV [39%Full] 15204352 (0xe80000) total, 5985896 (0x5b5668) used, 9218456 (0x8ca998) free
FVMAIN_COMPACT [52%Full] 3440640 (0x348000) total, 1806080 (0x1b8f00) used, 1634560 (0x18f100) free

- Done -
```
