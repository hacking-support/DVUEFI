<img src="docs/media/DVUEFILogo.png" width="125">

# Damn Vulnerable UEFI (DVUEFI)

An Exploitation Toolkit and Learning Platform for Unveiling and Fixing UEFI Firmware Vulnerabilities
Presented at [Black Hat USA 2024 Arsenal](https://www.blackhat.com/us-24/arsenal/schedule/index.html#damn-vulnerable-uefi-dvuefi-an-exploitation-toolkit-and-learning-platform-for-unveiling-and-fixing-uefi-firmware-vulnerabilities-39058)

![](./docs/img/dvuefi.png)

# Introduction
Inspired by projects such as Damn Vulnerable Web Application and OWASP's Damn Vulnerable Web Sockets, Damn Vulnerable UEFI (DVUEFI) is designed to help guide ethical hackers, security researchers, and firmware enthusiasts in getting started with UEFI firmware security, by facilitating the exploration of vulnerabilities by example.

The DVUEFI project is engineered to simulate real-world firmware attacks, offering an environment for practicing and refining exploitation techniques.

DVUEFI is accompanied by a robust, continuously evolving catalog of documented UEFI vulnerabilities.
Each entry is detailed with exploitation methods, potential impacts, and strategic mitigation recommendations, serving as both a learning tool and a reference for security practitioners.


## OS Support
DEVUEFI's exploitation environment is designed to be deployable on both Windows and Linux using either [QEMU](https://www.qemu.org/) for the first two stages and [VMWare Workstation Player](https://www.vmware.com/products/workstation-player/workstation-player-evaluation.html) for the final stage (the free version, VMWare Workstation Player, will suffice).

## Tools
We extend and combine different engines of [UEFITool](https://github.com/LongSoft/UEFITool) to help with automation for the third stage.
For more information on the tool, see [Tools](./tools/README.md).

# Getting Started
Clone this repository using

```console
git clone --recursive git@github.com:hacking-support/DVUEFI.git # ssh
```

or 

```console
git clone --recursive https://github.com/hacking-support/DVUEFI.git # https
```

To start setting up your exploitation environment, head over to [Level 0: Setup](./docs/0-environment-setup/README.md)

# Acknowledgements
DVUEFI would not exist without the previous contributions of many members of the UEFI community.

* UEFI image analysis and modification: https://github.com/LongSoft/UEFITool
* Inspiration for Apps to make Vulnerable: https://github.com/fpmurphy/UEFI-Utilities-2019
