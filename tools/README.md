# Analyzing and Manipulating UEFI Images

## Background
We include two versions of the same tool, UEFITool, as it is widely useful for firmware analysis and image modification.

`UEFITool` represents the latest and great version of UEFITool that works best for analyzing images.
It automatically resolves many GUIDs making it easy to narrow down what we want to analyze. 

`UEFITool28` uses an outdated engine, but it is capable of modifying the UEFI images and not just analyzing them.
We can insert, replace, and remove files from the image with just a few clicks.

Outside of the GUI tool, there are a number of command line tools included in each.
For `UEFITool` those are focused on image analysis (e.g. `UEFIExtract` allows you to extract a driver from the image without having to use a GUI),
whereas `UEFITool28` has more tools for image modification (e.g. `UEFIReplace` can be used to replace a file with another).


## Our Goal: Stage 3
Outside of general analysis, we needed to build some automation to insert drivers constructed from source by EKDII into the UEFI firmware image provided by VMWare (whose source we don't have access to).
We could use a GUI version of `UEFITool28` to do so, but that would be very time consuming and inconvenient.

We break down the task into 4 distinct parts:
0. Compile our drivers alongside the firmware image using EDKII
1. Given a GUID of the (vulnerable) driver we built, extract it from the rest of the firmware image
2. Find a point at which to insert the driver inside the VMware image, such that it is loaded during boot
3. Insert the driver into the VMWare image

## UEFIInsert and install_driver.sh
While `UEFITool28` has a commandline utility to replace files, there is no way to use it to *insert* another file into the image.
To resolve this, we create a simple extension, `UEFIInsert`, that lets us do just that.

Then, we link together `UEFIExtract` from `UEFITool` with our `UEFIInsert` (that uses the `UEFITool28` toolchain) to complete steps 1-3.

### Container with Toolchain
To help with compiling the toolchain, we provide a container, which can be built by running:

```console
docker build uefitool-build-toolchain -t uefitool-build
```

The container can  be launched by running `launch_toolchain.sh`.

### Compiling UEFITools
After launching the container (optional), build `UEFIExtract`:

```console
cd UEFITool
cmake UEFIExtract
make
cd ..
```

Then build `UEFITool28`:
```console
cd UEFITool28
./unixbuild.sh
cd ..
```

### Usage:
`./install_driver.sh "EDK-Image" "GUID" "VMware-Image" "OutputImage"`

For example:
```
./install_driver.sh OVMF_CODE.fd 3A28FDA1-3F06-11EA-8BB9-54E1ADE5F305 vmware/uefi.rom vmware/new_uefi.rom
```
