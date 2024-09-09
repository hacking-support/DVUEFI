# Level 2: Exploiting with SecureBoot
While this stage resembles the [previous one](../1-efi-apps/README.md), we've added an additional challenge: SecureBoot is enabled, meaning that only binaries signed by an allowed certificate will be executed by the firmware: the rest will be rejected.

## Building Firmware
To work with secure boot, we'll have to recompile EDKII with secure boot enabled.
Inside your build environment (i.e. docker container) run

```console
build --conf ConfEDK2 -DSECURE_BOOT_ENABLE
```

Note that the `SECURE_BOOT_ENABLE` flag provides support for secure boot: it does not automatically enable it (more on this later).

## Running the Challenges
First, navigate over to the [Stage2](../../../../../VulnerableCode/tree/main/Stage2SecureBoot/) directory.

Start by running `setup.sh` (on your laptop; make sure you're not inside QEMU).
This will copy over the firmware you built into the correct directories.

Then run `./run_shell.sh`: just like for Stage 1, you'll be provided with a shell in QEMU, and you can mount the binaries in `FS0:`.

Run the `display_smiley.efi` binary.
Even though it is unsigned, you are able to run it because secure boot hasn't been enabled yet!

To enable secure boot run: 
```console
FS0:\> EnrollDefaultKeys.efi --no-default   
info: SetupMode=1 SecureBoot=0 SecureBootEnable=0 CustomMode=0 VendorKeys=1
info: SetupMode=0 SecureBoot=1 SecureBootEnable=1 CustomMode=0 VendorKeys=0
info: success
```

Now if you try to run `display_smiley.efi` you should get an error, since secure boot has activated
```console
FS0:\> display_smiley.efi
Command Error Status: Access Denied
```

Interestingly, running `EnrollDefaultKeys.efi` will also fail, since it's also unsigned.


# Challenge 1: Signing Binaries
In order to run `display_smiley.efi` we have to sign it, but to do so we have to know the private key.

Oh no! The private key file is leaked somewhere inside `Stage2SecureBoot`! Can you find it?
Once you do, head over to `Level1SignApp` which runs `Level1SignApp/MountedDrive/display_smiley.efi`, and try to sign it (`sbsign` might be helpful!).

Then run `run_level1.sh` again and see if the signed version of `display_smiley.efi` runs despite secure boot.
If it does, you're done!

Note, you can always run `setup.sh` again to reset SecureBoot, and you'll have to run `EnrollDefaultKeys.efi --no-default` again to reenable it.

# Challenge 2: Vulnerable Grub
This challenge is based on a real-life GRUB vulnerability, dubbed [BootHole](https://eclypsium.com/blog/theres-a-hole-in-the-boot/).
After enabling secure boot using `EnrollDefaultKeys.efi`, head over to `Level2Grub` and execute `./run_grub.sh`.
GRUB will run and since there's nothing to boot, exit to the boot manager.

There's some trickery you can do by modifying `MountedDrive/EFI/BOOT/grub.cfg`.
Can you cause a crash?
