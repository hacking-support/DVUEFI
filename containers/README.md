# Debian Container: Build Tools and QEMU

We provide a docker image that can be used to build the (vulnerable) firmware and run it using QEMU virtualisation.

## Obtaining Image
There are two ways to obtain the docker image:

1. Pull it directly from the GitHub container registry (coming soon)
2. Build it yourself

To build the container image, run the following command at the root of the project:

```
docker build --tag debian-qemu-uefi containers
```

This will build a new image named `debian-qemu-uefi` (feel free to use any other name you'd like).
Now if you run `docker images debian-qemu-uefi` you should see something like the following:

```
REPOSITORY         TAG       IMAGE ID       CREATED         SIZE
debian-qemu-uefi   latest    ...        ... seconds ago     ...
```

## Run container interactively
The container we built is very simple: it contains a minimal Debian image with OVMF firmware build tools and QEMU pre-installed.

We can run the container and give it access to the `vuln-edk2` directory so that it can build the firmware and run it.
We do that using `--volume`

```
docker run --volume ./vuln-edk2:/home/edk2 --rm -it debian-qemu-uefi
```

You should find yourself in the `home` directory

```
> ls 

edk2/
```


## Compiling Vulnerable Firmware

TODO: elaborate

```
cd edk2/
make -C BaseTools
```

## Running with QEMU
```
qemu-system-x86_64 -name "Vuln OVMF" -drive file=${OVMF_CODE},if=pflash,format=raw,unit=0,readonly=on -drive file=${OVMF_VARS_COPY},if=pflash,format=raw,unit=1 -net none -nographic
```
