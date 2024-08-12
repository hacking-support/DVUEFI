# Level 1: Exploiting EFI Applications

In this stage, we're going to be running some intentionally vulnerable UEFI applications (source in `/vuln-edk2/VulnerableCode/Stage1Apps`).

## Building Vulnerable Firmware
To start, make sure you have a fresh build of the firmware.
You can reference the instructions at [edk2-toolchain](../../edk2-build-toolchain/README.md).

We also need to build the vulnerable firmware itself, by running `build --conf ConfStage1`

Altogether, to refresh all builds we can run (in docker):

```console
build --conf ConfEDK2/
build --conf ConfStage1/
```

## Running the Challenges
Outside of docker and inside the `vuln-edk2` directory, run `./level-scripts/run_level1.sh`.

QEMU should launch and you should see something like:

```
UEFI v2.70 (EDK II, 0x00010000)
Mapping table
      FS0: Alias(s):HD0a1:;BLK1:
          PciRoot(0x0)/Pci(0x1,0x1)/Ata(0x0)/HD(1,MBR,0xBE1AFDFA,0x3F,0xFBFC1)
     BLK0: Alias(s):
          PciRoot(0x0)/Pci(0x1,0x1)/Ata(0x0)
     BLK2: Alias(s):
          PciRoot(0x0)/Pci(0x1,0x1)/Ata(0x0)
Press ESC in 5 seconds to skip startup.nsh or any other key to continue.
Shell>
```

We have a shell!
All the Vulnerable Apps live in the `FS0:` drive.
You can mount it by entering `FS0:`.

If you run the `ls` command, you should see the first challenge, `Unhexlify.efi`: a little command-line application that tries to turn hex digits to ascii.

Take a look at the [source code](../../../../../VulnerableCode/tree/main/Stage1Apps/Unhexlify/Unhexlify.c): can you see the vulnerability? What happens if you enter a very long string?

Note: when QEMU is launched, it creates a pipe that allows you to interact in QEMU by sending data into the `/tmp/guest.in`: you can use this to generate long inputs by using a scripting language (e.g. Python) and piping the output to `/tmp/guest.in`!

Once you found a crash, you can begin working on the exploit.
We're leaving this open for now, but may provide additional guidance in the future!
