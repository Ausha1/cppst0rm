# cppst0rm
A more automated and mainstream version of Mineek's Sunst0rm (https://github.com/mineek/sunst0rm)

## Note to all users who encounter any issues: DO NOT open any issues in futurerestore. Weather that be on Discord, or GitHub, this program does not use futurerestore incorrectly, and issues with futurerestore are unlikely. Instead, get support in [cppst0rm's Discord server](https://discord.gg/gUwb4Apw).

## Since this program is so automated, I fealt not the need of a guide, but if any help is needed, please refer to cppst0rm's Discord server for further help if the usage guide doesn't make sense to you.

## Things to Undrstand
- This utility uses a checkm8 exploit to downgrade your device *tethered*. This means that every time your iPhone turns off, weather that be shut down, restarting, battery dying, or whatever, you have to use this program to turn it back on.
- On A10 - A11 devices, crucial functionality like the Home Button, Audio, Micraphone, and Vibration DO NOT work at the moment.
- On iPhone X, the touch screen does not work after downgrading, but the iPhone 8 and iPhone 8 Plus are fine.
- You should NOT do this to your main device. The downgrade is not exactly stable since there will be some issues. For example, on the iPhone SE 1st generation (iPhone8,4), the Compass, Dication/Siri, and flashlight have some issue related to them. In my case, Siri, Dictation, and the Compass did NOT work at all, while the flashlight's only issue was a delay from pressing the button in control center.

## Requirements
- An INTEL mac, M1 Macs are NOT supported yet.
- A compatible iPhone
- Basic knowledge of the mac terminal

## Build cppst0rm
- To get the cppst0rm executable, open a Terminal window, cd into your cppst0rm directory, and type ```make```

## Usage
| Option          | Description                                                               |
|-----------------|---------------------------------------------------------------------------|
|`-i`             |path to ipsw.                                                              |
|`-t`             |path to shsh2 blob                                                         |
|`-r`             |restore mode                                                               |
|`-b`             |boot tethered (use this every time to boot)                                |
|`-d`             |specify board config (Ex. `n69ap`)                                         |
|`-id`            |specify iPhone identifier (Ex. `iPhone8,4)                                 |
|`--kpp`          |Use this argument if the iDevice you are handling has an `A9 chip or lower`|
|`--legacy`       |Use this argument if you are restoring or booting `iOS 11 or below`        |
|`--skip-baseband`|Skip the baseband while restoring through futurerestore                    |
|`-rb`            |Remove the boot folder for your device and create a fresh one              |

### To Restore
```./cppst0rm -i [path to ipsw] -t [path to blob] -r -d [boardconfig]```
- Use `--kpp` if your iDevice has an A9 chip or lower, otherwise leave it out
- You can find your boardconfig (here)[ipsw.me]. Just click on your category, find your device, and hit the `Device Information` tab.
- Since the process of patching files from the ipsw requires specifying if kpp is required, make sure you really need `--kpp` or not

## To Boot
```./cppst0rm -i [path to ipsw] -t [path to blob] -b -d [boardconfig] -id [identifier]```
- Use `--kpp` if you did while restoring or if your device has kpp

## Credits
[M1n1Exploit](https://github.com/Mini-Exploit) - Some code from ra1nstorm

[Arna13](https://github.com/Arna13) - Writing an easy to understand [guide](https://github.com/Arna13/sunst0rm-guide)

[swayea](https://github.com/swayea) - Logo's

[Sunst0rm](https://github.com/mineek/sunst0rm) - The backbone for this repository
