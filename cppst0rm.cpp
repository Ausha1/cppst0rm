#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int usage() {
    cout << "Usage:\n\n";
    cout << "{} = Required\n[] = Not Required\n() = One or the other\n\n";
    cout << "./cppst0rm {-i} {ipsw} {-t} {shsh2 blob} (-r, -b) [-rb] {-d} {board config} [-id] [identifier] [--kpp] [--legacy] [--skip-baseband]\n\n";
    cout << "Example: ./cppst0rm -i ipsw.ipsw -t blob.shsh2 -r -d n69ap --kpp\n\n";
    cout << "-i    path to ipsw\n";
    cout << "-t    path to shsh2 blob\n";
    cout << "-r    restore mode\n";
    cout << "-b    boot teathered (Use this every time to boot)\n";
    cout << "-d    specify board config\n";
    cout << "-id    specify iPhone identifier (ex. iPhone8,4)\n";
    cout << "--kpp    Use this argument if your phone has kpp (A9 and down)\n";
    cout << "--legacy    Use this if you are restoring or booting iOS 11 or below\n";
    cout << "--skip-baseband    Skip Baseband\n";
    cout << "\n-----EXTRA-----\n";
    cout << "\n-rb    Remove the boot folder for the device you are booting\n";
    return 0;

}

int dependencies() {
    ifstream check_Downloads_folder;
    check_Downloads_folder.open("./Downloads");
    if(!check_Downloads_folder) {
        cout << "{!} Downloads folder missing! Creating a new one...\n";
        system("mkdir ./Downloads");
    }
    
    ifstream check_Dependencies_folder;
    check_Dependencies_folder.open("./Dependencies");
    if(!check_Dependencies_folder) {
        cout << "{!} Dependencies folder missing! Creating a new one...\n";
        system("mkdir ./Dependencies");
    }

    ifstream check_for_homebrew;
    check_for_homebrew.open("/usr/local/bin/brew");
    if(!check_for_homebrew) {
        cout << "{!} Homebrew was not found on your system! I will install it now...\n";
        system("/bin/bash -c '$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)'");
        check_for_homebrew.open("/usr/local/bin/brew");
        if(!check_for_homebrew) {
            cout << "{!} Homebrew didn't install for some reason. Please install it manually then re-run this program.\n";
            return 0;
        }

    }
    cout << "{!} Homebrew ready!\n";

    string keypress;
    cout << "{!} Downloading required dependencies...\n";
    ifstream check_git;
    check_git.open("/usr/bin/git");
    if(!check_git) {
        cout << "Git not found! Installing it now...\n";
        system("brew install git");
    }
    cout << "{!} git ready!\n";

    ifstream check_irecovery;
    check_irecovery.open("/usr/local/bin/irecovery");
    if(!check_irecovery) {
        cout << "libirecovery not found! Installing it now...\n";
        system("brew install libirecovery");
    }
    cout << "{!} libirecovery ready!\n";

    ifstream predownloaded_futurerestore;
    predownloaded_futurerestore.open("./Dependencies/futurerestore");
    if(!predownloaded_futurerestore) {
        cout << "{!} Manual download required! I will open your web browser to a precompiled futurerestore binary. Place the downloaded binary in the Dependencies folder. Type anything and press enter to continue: ";
        cin >> keypress;
        system("open https://github.com/futurerestore/futurerestore/actions");
        while(true){
            cout << "{!} Place the downloaded binary in the 'Dependencies' folder in your cppst0rm folder. Type anything and press enter once done: ";
            cin >> keypress;
            bool futurerestore;
            ifstream check_futurerestore;
            check_futurerestore.open("./Dependencies/futurerestore");
            if(!check_futurerestore) {
                cout << "\n{!} The futurerestore binary was not found in the Dependencies folder! Make sure the naming is correct and that it's actually there.\n";
            } else {
                break;
            }
        }
    }
    cout << "{!} futurerestore ready!\n";
    
    ifstream predownloadloaded_iBoot64Patcher;
    predownloadloaded_iBoot64Patcher.open("./Dependencies/iBoot64Patcher");
    if(!predownloadloaded_iBoot64Patcher) {
        cout << "{!} Manual download required! Do the same thing you did for futurerestore. Type anything and press enter to continue: ";
        cin >> keypress;
        system("open https://github.com/Cryptiiiic/iBoot64Patcher/actions");
        while(true) {
            cout << "{!} Place the downloaded binary in the 'Dependencies' folder in your cppst0rm folder. Type anything and press enter once done: ";
            cin >> keypress;
            bool iBoot64Patcher;
            ifstream check_iBoot64Patcher;
            check_iBoot64Patcher.open("./Dependencies/iBoot64Patcher");
            if(!check_iBoot64Patcher) {
                cout << "\n{!} The iBoot64Patcher binary was not found in the Dependencies folder! Make sure the naming is correct and that it's actually there.\n";
            } else {
                break;
            }
        }
    }
    cout << "{!} iBoot64Patcher ready!\n";

    ifstream predownloaded_Kernel64Patcher;
    predownloaded_Kernel64Patcher.open("./Dependencies/Kernel64Patcher");
    if(!predownloaded_Kernel64Patcher) {
        cout << "{!} Downloading and compiling Kernel64Patcher from GitHub (fork)...\n";
        system("git clone https://github.com/iSuns9/Kernel64Patcher.git ./Downloads/Kernel64Patcher");
        cout << "Kernel64Patcher successfully downloaded!\n";
        cout << "Building...\n";
        system("gcc ./Downloads/Kernel64Patcher/Kernel64Patcher.c -o Kernel64Patcher");
        cout << "Building done!\n";
        cout << "Moving to correct location...\n";
        //Remove downloaded git repository so that there is no confusion with the system on where to move Kernel64Patcher
        system("rm -rf ./Dependencies/Kernel64Patcher/");
        //Now we can move the binary without it going back into the downloaded git repository folder
        system("mv Kernel64Patcher ./Dependencies/Kernel64Patcher");
    }
    cout << "{!} Kernel64Patcher ready!\n";

    ifstream predownloaded_img4tool;
    predownloaded_img4tool.open("./Dependencies/img4tool");
    if(!predownloaded_img4tool) {
        //Clean downloads if buildroot is already there for a fresh one
        ifstream cleanbuildroot;
        cleanbuildroot.open("./Downloads/buildroot_macos-latest");
        if(cleanbuildroot) {
            system("rm -rf ./Downloads/buildroot_macos-latest");
        }
        cout << "{!} Manual download required! Download the latest 'buildroot_macos-latest.' Type anything and press enter: ";
        cin >> keypress;
        system("open https://github.com/tihmstar/img4tool/releases");
        cout << "{!} Place the buildroot folder in the 'Downloads' folder. Type anything and press enter to continue: ";
        cin >> keypress;
        bool img4tool;
        ifstream check_img4tool;
        check_img4tool.open("./Downloads/img4tool");
        while(true) {
            bool img4tool;
            ifstream check_img4tool;
            check_img4tool.open("./Downloads/buildroot_macos-latest");
            if(!check_img4tool) {
                cout << "\n\n{!} The buildroot folder was not found in the 'Downloads' folder! Make sure the naming is correct and that it's actually there.\nPress any key and press enter once moved: ";
                cin >> keypress;
            } else {
                break;
            }
        }
        cout << "{!} Installing img4tool...\n";

        //Take care of bin
        system("chmod +x ./Downloads/buildroot_macos-latest/usr/local/bin/img4tool");
        system("mv ./Downloads/buildroot_macos-latest/usr/local/bin/img4tool ./Dependencies");

        //Take care of include
        system("mv ./Downloads/buildroot_macos-latest/usr/local/include/img4tool /usr/local/include");

        //Take care of lib
        system("mv ./Downloads/buildroot_macos-latest/usr/local/lib/libimg4tool.a /usr/local/lib && mv ./Downloads/buildroot_macos-latest/usr/local/lib/libimg4tool.la /usr/local/lib && mv ./Downloads/buildroot_macos-latest/usr/local/lib/pkgconfig /usr/local/lib");
    }
    cout << "{!} img4tool ready!\n";
    
    ifstream predownloaded_img4;
    predownloaded_img4.open("./Dependencies/img4");
    if(!predownloaded_img4) {
        ifstream check_img4;
        check_img4.open("./Downloads/img4lib");
        if(check_img4) {
            system("rm -rf ./Downloads/img4lib");
        }
        system("git clone https://github.com/xerub/img4lib.git ./Downloads/img4lib");
        cout << "Changing directories for make...\n";
        system("cd ./Downloads/img4lib");
        cout << "Making img4...\n";
        system("cd ./Downloads/img4lib && make COMMONCRYPTO=1");
        cout << "img4 built successfully!\n";
        cout << "Moving img4...\n";
        system("mv ./Downloads/img4lib/img4 ./Dependencies");
        cout << "Done!\n";
    }
    cout << "{!} img4 ready!\n";

    ifstream predownloaded_ldid;
    predownloaded_ldid.open("./Dependencies/ldid_macos_x86_64");
    if(!predownloaded_ldid) {
        cout << "{!} Manual download required! Type anything and press enter to continue: ";
        cin >> keypress;
        system("open https://github.com/ProcursusTeam/ldid/releases");
        while(true) {
            cout << "{!} Place the downloaded binary in the 'Dependencies' folder in your cppst0rm folder. Type anything and press enter once done: ";
            cin >> keypress;
            bool ldid;
            ifstream check_ldid;
            check_ldid.open("./Dependencies/ldid_macos_x86_64");
            if(!check_ldid) {
                cout << "\n{!} The ldid binary was not found in the Dependencies folder! Make sure the naming is correct and that it's actually there.\n{!} Did you download the arm version on accident?\n";
            } else {
                break;
            }
        }
    }
    cout << "{!} ldid ready!\n";

    ifstream predownloaded_restored_external64_patcher;
    predownloaded_restored_external64_patcher.open("./Dependencies/restored_external64_patcher");
    if(!predownloaded_restored_external64_patcher) {
        ifstream check_restored_external64_patcher;
        check_restored_external64_patcher.open("./Downloads/restored_external64_patcher");
        if(check_restored_external64_patcher) {
            system("rm -rf ./Downloads/restored_external64_patcher");
        }
        cout << "{!} Downloading restored_external64_patcher from github...\n";
        system("git clone https://github.com/iSuns9/restored_external64patcher.git ./Downloads/restored_external64_patcher");
        cout << "Building...\n";
        system("cd ./Downloads/restored_external64_patcher && make");
        cout << "Moving binary...\n";
        system("mv ./Downloads/restored_external64_patcher/restored_external64_patcher ./Dependencies");
    }
    cout << "{!} restored_external64_patcher ready!\n";

    ifstream predownloaded_asr64_patcher;
    predownloaded_asr64_patcher.open("./Dependencies/asr64_patcher");
    if(!predownloaded_asr64_patcher) {
        ifstream check_asr64_patcher;
        check_asr64_patcher.open("./Downloads/asr64_patcher");
        if(check_asr64_patcher) {
            system("rm -rf ./Downloads/asr64_patcher");
        }
        cout << "{!} Downloading asr64_patcher from github...\n";
        system("git clone https://github.com/exploit3dguy/asr64_patcher.git ./Downloads/asr64_patcher");
        cout << "Building...\n";
        system("cd ./Downloads/asr64_patcher && make");
        cout << "Moving binary...\n";
        system("mv ./Downloads/asr64_patcher/asr64_patcher ./Dependencies");
    }
    cout << "{!} asr64_patcher ready!\n";

    ifstream check_python3;
    check_python3.open("/usr/local/bin/python3");
    if(!check_python3) {
        cout << "Installing python3/pip3...\n";
        system("brew install python3");
        cout << "Installing pyimg4...\n";
        system("pip3 install pyimg4");
    }
    cout << "{!} pyimg4 ready!\n";

    ifstream check_gaster;
    check_gaster.open("./Dependencies/gaster");
    if(!check_gaster) {
        ifstream check_git_gaster;
        check_git_gaster.open("./Downloads/gaster-Cryptic-image-fix");
        if(check_git_gaster) {
            system("rm -rf ./Downloads/gaster-Cryptic-image-fix");
        }
        cout << "{!} Downloading gaster...\n";
        system("git clone https://github.com/Cryptiiiic/gaster.git ./Downloads/gaster-Cryptic-image-fix");
        cout << "{!} Building...\n";
        system("cd ./Downloads/gaster-Cryptic-image-fix && make");
        cout << "Moving binary...\n";
        system("mv ./Downloads/gaster-Cryptic-image-fix/gaster ./Dependencies");
    }
    cout << "{!} gaster ready!\n";

    cout << "Installing python3 dependencies...\n";
    system("pip3 install requests");
    cout << "Python dependencies ready!\n";

    cout << "{!} Running chmod just in case...\n";
    system("chmod +x ./Dependencies/futurerestore && chmod +x ./Dependencies/iBoot64Patcher && chmod +x ./Dependencies/img4 && chmod +x ./Dependencies/img4tool && chmod +x ./Dependencies/Kernel64Patcher && chmod +x  ./Dependencies/ldid_macos_x86_64 && chmod +x ./Dependencies/restored_external64_patcher && chmod +x ./Dependencies/asr64_patcher && chmod +x ./Dependencies/gaster");
    cout << "{!} You're good to go!\n";
    return 0;
}

int restore(string ipsw, string blob, string boardUpper, bool kpp, bool legacy, bool skipbb) {
    //Make the board lowercase for compatibility reasons
    string board;
    locale loc;
    for(string::size_type i = 0; i < boardUpper.length(); ++i) {
        board.push_back(tolower(boardUpper[i],loc));
    }

    //So that errors aren't caused, deleting the work folder if it exists is necessary
    ifstream workfolder;
    workfolder.open("./work");
    if(workfolder) {
        system("rm -rf ./work");
    }
    system("mkdir ./work");

    //Extract the contents of the ipsw to the work directory
    cout << "{!} Unzipping contents of the ipsw...\n";
    string unzip_cmd("unzip " + ipsw + " -d ./work");
    const char *unzip = unzip_cmd.c_str();
    system(unzip);

    //Made the ramdisk directory
    system("mkdir ./work/ramdisk");

    //Use a tweaked version of sunst0rm's (Origional utilities can be found here: https://github.com/mineek/sunst0rm) api and manifest to get required names and info about the device's ipsw
    system("mkdir ./work/port");
    string port("cd ./Utilities && python3 port.py -mode RESTORE -board " + board);
    const char *port_cmd = port.c_str();
    system(port_cmd);

    //Store the contents of the text files generated by the python scripts in a variable that can be used later
    ifstream ramdisk_name;
    ramdisk_name.open("./work/port/restoreramdisk_name.txt");
    stringstream ramdisk_buffer;
    ramdisk_buffer << ramdisk_name.rdbuf();
    string ramdisk = ramdisk_buffer.str();
    if(ramdisk == "") {
        cout << "\n{!} Error: BoardConfig was not recognized!\n";
        return 0;
    }

    ifstream kernelcache_name;
    kernelcache_name.open("./work/port/kernelcache_name.txt");
    stringstream kernelcache_buffer;
    kernelcache_buffer << kernelcache_name.rdbuf();
    string kernelcache = kernelcache_buffer.str();

    //Extract the restore ramdisk with img4
    cout << "{!} Extracting ramdisk using img4\n";
    string extract_ramdisk("./Dependencies/img4 -i ./work/" + ramdisk + " -o ./work/ramdisk.dmg");
    const char *extract_ramdisk_cmd = extract_ramdisk.c_str();
    system(extract_ramdisk_cmd);

    //Mount the ramdisk
    cout << "{!} Mounting the ramdisk\n";
    system("hdiutil attach ./work/ramdisk.dmg -mountpoint ./work/ramdisk");

    //Patch the ASR in the ramdisk
    cout << "{!} Patching ASR in the ramdisk\n";
    system("./Dependencies/asr64_patcher ./work/ramdisk/usr/sbin/asr ./work/patched_asr");

    //Resign it
    cout << "{!} Resigning ASR\n";
    system("./Dependencies/ldid_macos_x86_64 -e ./work/ramdisk/usr/sbin/asr > ./work/ents.plist && ./Dependencies/ldid_macos_x86_64 -S./work/ents.plist ./work/patched_asr");

    //Copy restored_external to work on it
    cout << "{!} Moving restored_external to work directory\n";
    system("cp ./work/ramdisk/usr/local/bin/restored_external ./work");

    if(!legacy) {
        //Patch it
        cout << "{!} Patching restored_external\n";
        system("./Dependencies/restored_external64_patcher ./work/restored_external ./work/restored_external_patched");

        //Extract the entitlements from restored_external
        cout << "{!} Extracting restored_external ents\n";
        system("./Dependencies/ldid_macos_x86_64 -e ./work/restored_external > ./work/restored_external_ents.plist");

        //Resign restored_external_patched
        cout << "{!} Resigning restored_external_patched\n";
        system("./Dependencies/ldid_macos_x86_64 -S./work/restored_external_ents.plist ./work/restored_external_patched");

        //Chmod new restored_external_patched
        cout << "{!} Running chmod on new restored_external_patched\n";
        system("chmod -R 755 ./work/restored_external_patched");


    } else {
        cout << "{!} Legacy mode, skipping restored_external\n";
    }

    //Remove the old asr and restored_external from the ramdisk
    cout << "{!} Cleaning ramdisk of old files\n";
    system("rm ./work/ramdisk/usr/sbin/asr && rm ./work/ramdisk/usr/local/bin/restored_external");

    //Chmod ASR
    cout << "{!} Running chmod on the new asr\n";
    system("chmod -R 755 ./work/patched_asr");

    //Copy the patched files back
    cout << "{!} Repopulating ramdisk with patched asr and ramdisk\n";
    system("cp -a ./work/restored_external_patched ./work/ramdisk/usr/local/bin/restored_external && cp -a ./work/patched_asr ./work/ramdisk/usr/sbin/asr");

    //Detach the ramdisk
    cout << "{!} Detaching the ramdisk\n";
    system("hdiutil detach ./work/ramdisk");

    //Rebuild the ramdisk
    cout << "{!} Rebuilding the ramdisk\n";
    system("pyimg4 im4p create -i ./work/ramdisk.dmg -o ./work/ramdisk.im4p -f rdsk");

    //Extract the kernel
    cout << "{!} Extracting the kernel\n";
    if(kpp) {
        string extract_kernelcache_kpp("pyimg4 im4p extract -i ./work/" + kernelcache + " -o ./work/kcache.raw --extra ./work/kpp.bin");
        const char *extract_kernelcache_kpp_cmd = extract_kernelcache_kpp.c_str();
        system(extract_kernelcache_kpp_cmd);
    } else {
        string extract_kernelcache("pyimg4 im4p extract -i ./work/" + kernelcache + " -o ./work/kcache.raw");
        const char *extract_kernelcache_cmd = extract_kernelcache.c_str();
        system(extract_kernelcache_cmd);
    }

    //Patch the kernel
    cout << "{!} Patching the kernel\n";
    system("./Dependencies/Kernel64Patcher ./work/kcache.raw ./work/krnl.patched -f -a");

    //Rebuild the kernel
    cout << "{!} Rebuilding the kernel\n";
    if(kpp) {
        system("pyimg4 im4p create -i ./work/krnl.patched -o ./work/krnl.im4p --extra ./work/kpp.bin -f rkrn --lzss");
    } else {
        system("pyimg4 im4p create -i ./work/krnl.patched -o ./work/krnl.im4p -f rkrn --lzss");
    }

    //Pwn the user's iDevice with gaster
    cout << "{!} Pwning with gaster\n";
    system("./Dependencies/gaster pwn");

    string readytorestore;
    cout << "\nAre you ready to restore your iDevice? (y/n): ";
    cin >> readytorestore;

    if(readytorestore == "n" || readytorestore == "N") {
        cout << "{!} Cleaning\n";
        system("rm -rf ./work");
        cout << "{!} Cleaning done!\n\nThanks for using cppst0rm! <3\n";
        return 0;
    }

    cout << "{!} Restoring device\n";
    if(skipbb) {
        string futurerestore_skipbb("cd ./work && ../Dependencies/futurerestore -t " + blob + " --use-pwndfu --skip-blob --rdsk ../work/ramdisk.im4p --rkrn ../work/krnl.im4p --latest-sep --skip-baseband " + ipsw);
        const char *futurerestore_skipbb_cmd = futurerestore_skipbb.c_str();
        system(futurerestore_skipbb_cmd);
    } else {
        string futurerestore("cd ./work && ../Dependencies/futurerestore -t " + blob + " --use-pwndfu --skip-blob --rdsk ../work/ramdisk.im4p --rkrn ../work/krnl.im4p --latest-sep --latest-baseband " + ipsw);
        const char *futurerestore_cmd = futurerestore.c_str();
        system(futurerestore_cmd);
    }

    cout << "{!} Done!\n";
    cout << "{!} Cleaning\n";
    system("rm -rf ./work");
    cout << "{!} Cleaning done!\n\nThanks for using cppst0rm! <3\n";
    return 0;
}

int boot(string ipsw, string blob, bool rb, string boardUpper, string identifier, bool kpp, bool legacy) {
    //chmod the boot script to eliminate minimize issues
    cout << "{!} Running chmod on boot.sh\n";
    system("chmod +x ./Utilities/boot.sh");

    //Make the board lowercase for compatibility reasons
    string board;
    locale loc;
    for(string::size_type i = 0; i < boardUpper.length(); ++i) {
        board.push_back(tolower(boardUpper[i],loc));
    }

    //Remove work folder if it exists
    ifstream workfolder;
    workfolder.open("./work");
    if(workfolder) {
        system("rm -rf ./work");
    }

    //If boot folder doesn't exist, create one.
    ifstream bootfolder;
    bootfolder.open("./boot");
    if(!bootfolder) {
        system("mkdir ./boot");
    }

    //If the user requested to delete their boot folder, do it now
    if(rb) {
        cout << "{!} User specefied to delete the boot folder for their device: (Board: " << board << "), (Identifier: " << identifier << ")\n";
        string rm_bootfolder("rm -rf ./boot/" + board);
        const char *rm_bootfolder_cmd = rm_bootfolder.c_str();
        system(rm_bootfolder_cmd);
    }

    //Check if the boot folder contains the user's board so that there is no time wasted making new files
    ifstream existing_bootfolder;
    existing_bootfolder.open("./boot/" + board);
    if(!existing_bootfolder) {
        //Ask the user if they want to try to make the custom boot logo
        string input_makebootlogo;
        cout << "\nDo you want to try to make a boot logo for your device? (y/n): ";
        cin >> input_makebootlogo;
        bool makebootlogo;

        if(input_makebootlogo == "y" || input_makebootlogo == "Y") {
            makebootlogo = true;
        } else if(input_makebootlogo == "n" || input_makebootlogo == "N") {
            makebootlogo = false;
        } else {
            cout << "{!} Error: Please only answer with 'y' or 'n'\n";
            return 0;
        }

        //Make a work folder
        system("mkdir ./work");

        //Make a new folder inside of boot with the name of the user's board config for later use
        string new_bootfolder("mkdir ./boot/" + board);
        const char *new_bootfolder_cmd = new_bootfolder.c_str();
        system(new_bootfolder_cmd);

        //Extract the contents of the ipsw to the work directory
        cout << "{!} Unzipping contents of the ipsw\n";
        string unzip_cmd("unzip " + ipsw + " -d ./work");
        const char *unzip = unzip_cmd.c_str();
        system(unzip);

        //Use a tweaked version of sunst0rm's (Origional utilities can be found here: https://github.com/mineek/sunst0rm) api and manifest to get required names and info about the device's ipsw
        system("mkdir ./work/port");
        string port("cd ./Utilities && python3 port.py -mode BOOT -identifier " + identifier + " -board " + board);
        const char *port_cmd = port.c_str();
        system(port_cmd);

        //Store the contents of the text files generated by the python scripts in a variable that can be used later
        //Devicetree
        ifstream read_devicetree;
        read_devicetree.open("./work/port/devicetree.txt");
        stringstream read_devicetree_buffer;
        read_devicetree_buffer << read_devicetree.rdbuf();
        string devicetree = read_devicetree_buffer.str();

        //ibec_iv
        ifstream read_ibec_iv;
        read_ibec_iv.open("./work/port/ibec_iv.txt");
        stringstream read_ibec_iv_buffer;
        read_ibec_iv_buffer << read_ibec_iv.rdbuf();
        string ibec_iv = read_ibec_iv_buffer.str();

        //ibec_key
        ifstream read_ibec_key;
        read_ibec_key.open("./work/port/ibec_key.txt");
        stringstream read_ibec_key_buffer;
        read_ibec_key_buffer << read_ibec_key.rdbuf();
        string ibec_key = read_ibec_key_buffer.str();

        //ibec_name
        ifstream read_ibec_name;
        read_ibec_name.open("./work/port/ibec_name.txt");
        stringstream read_ibec_name_buffer;
        read_ibec_name_buffer << read_ibec_name.rdbuf();
        string ibec = read_ibec_name_buffer.str();

        //ibss_iv
        ifstream read_ibss_iv;
        read_ibss_iv.open("./work/port/ibss_iv.txt");
        stringstream read_ibss_iv_buffer;
        read_ibss_iv_buffer << read_ibss_iv.rdbuf();
        string ibss_iv = read_ibss_iv_buffer.str();

        //ibss_key
        ifstream read_ibss_key;
        read_ibss_key.open("./work/port/ibss_key.txt");
        stringstream read_ibss_key_buffer;
        read_ibss_key_buffer << read_ibss_key.rdbuf();
        string ibss_key = read_ibss_key_buffer.str();

        //ibss_name
        ifstream read_ibss_name;
        read_ibss_name.open("./work/port/ibss_name.txt");
        stringstream read_ibss_name_buffer;
        read_ibss_name_buffer << read_ibss_name.rdbuf();
        string ibss = read_ibss_name_buffer.str();

        //trustcache
        ifstream read_trustcache;
        read_trustcache.open("./work/port/trustcache.txt");
        stringstream read_trustcache_buffer;
        read_trustcache_buffer << read_trustcache.rdbuf();
        string trustcache = read_trustcache_buffer.str();

        //kernelcache
        ifstream read_kernelcache;
        read_kernelcache.open("./work/port/kernelcache_name.txt");
        stringstream read_kernelcache_buffer;
        read_kernelcache_buffer << read_kernelcache.rdbuf();
        string kernelcache = read_kernelcache_buffer.str();


        //decrypt ibss
        cout << "{!} Decrypting iBSS\n";
        string decrypt_ibss("./Dependencies/img4 -i ./work/" + ibss + " -o ./work/ibss.dmg -k " + ibss_iv + ibss_key);
        const char *decrypt_ibss_cmd = decrypt_ibss.c_str();
        system(decrypt_ibss_cmd);

        //decrypt ibec
        cout << "{!} Decrypting iBEC\n";
        string decrypt_ibec("./Dependencies/img4 -i ./work/" + ibec + " -o ./work/ibec.dmg -k " + ibec_iv + ibec_key);
        const char *decrypt_ibec_cmd = decrypt_ibec.c_str();
        system(decrypt_ibec_cmd);

        //patch ibss
        cout << "{!} Patching iBSS\n";
        string patch_ibss("./Dependencies/iBoot64Patcher ./work/ibss.dmg ./work/ibss.patched");
        const char *patch_ibss_cmd = patch_ibss.c_str();
        system(patch_ibss_cmd);

        //patch ibec
        cout << "{!} Patching iBEC\n";
        string patch_ibec("./Dependencies/iBoot64Patcher ./work/ibec.dmg ./work/ibec.patched -b '-v'");
        const char *patch_ibec_cmd = patch_ibec.c_str();
        system(patch_ibec_cmd);

        //convert blob into im4m
        cout << "{!} Converting blob into IM4M\n";
        string convert_blob("./Dependencies/img4tool -e -s " + blob + " -m ./work/IM4M");
        const char *convert_blob_cmd = convert_blob.c_str();
        system(convert_blob_cmd);

        //convert ibss into img4
        cout << "{!} Converting iBSS to IMG4\n";
        system("./Dependencies/img4 -i ./work/ibss.patched -o ./work/ibss.img4 -M ./work/IM4M -A -T ibss");

        //convert ibec into img4
        cout << "{!} Converting iBEC to IMG4\n";
        system("./Dependencies/img4 -i ./work/ibec.patched -o ./work/ibec.img4 -M ./work/IM4M -A -T ibec");

        //sign the devicetree
        cout << "{!} Signing DeviceTree\n";
        string sign_devicetree("./Dependencies/img4 -i ./work/" + devicetree + " -o ./work/devicetree.img4 -M ./work/IM4M -T rdtr");
        const char *sign_devicetree_cmd = sign_devicetree.c_str();
        system(sign_devicetree_cmd);

        //sign the trustcache
        cout << "{!} Signing TrustCache\n";
        if(!legacy) {
            string sign_trustcache("./Dependencies/img4 -i ./work/" + trustcache + " -o ./work/trustcache.img4 -M ./work/IM4M -T rtsc");
            const char *sign_trustcache_cmd = sign_trustcache.c_str();
            system(sign_trustcache_cmd);
        }

        //extract the kernel
        cout << "{!} Extracting kernel\n";
        if(kpp) {
            string extract_kernel_kpp("pyimg4 im4p extract -i ./work/" + kernelcache + " -o ./work/kcache.raw --extra ./work/kpp.bin");
            const char *extract_kernel_kpp_cmd = extract_kernel_kpp.c_str();
            system(extract_kernel_kpp_cmd);
        } else {
            string extract_kernel("pyimg4 im4p extract -i ./work/" + kernelcache + " -o ./work/kcache.raw");
            const char *extract_kernel_cmd = extract_kernel.c_str();
            system(extract_kernel_cmd);
        }

        //patch the kernel
        cout << "{!} Patching kernel\n";
        system("./Dependencies/Kernel64Patcher ./work/kcache.raw ./work/krnlboot.patched -f");

        //convert the kernel
        cout << "{!} Converting kernel\n";
        if(kpp) {
            system("pyimg4 im4p create -i ./work/krnlboot.patched -o ./work/krnlboot.im4p --extra ./work/kpp.bin -f rkrn --lzss");
        } else {
            system("pyimg4 im4p create -i ./work/krnlboot.patched -o ./work/krnlboot.im4p -f rkrn --lzss");
        }

        //sign the kernel
        cout << "{!} Signing kernel\n";
        system("pyimg4 img4 create -p ./work/krnlboot.im4p -o ./work/krnlboot.img4 -m ./work/IM4M");

        //Make the boot logo for the specific device based on the user's choice
        if(makebootlogo) {
            cout << "{!} Making bootlogo\n";
            string make_bootlogo("./Dependencies/img4tool -c ./work/bootlogo.img4 -p ./bootlogos/" + board + "bootlogo.im4p -s " + blob);
            const char *make_bootlogo_cmd = make_bootlogo.c_str();
            system(make_bootlogo_cmd);
        }

        cout << "{!} Copying files to the boot directory\n";
        
        //copy ibss
        string copy_ibss("cp ./work/ibss.img4 ./boot/" + board);
        const char *copy_ibss_cmd = copy_ibss.c_str();
        system(copy_ibss_cmd);

        //copy ibec
        string copy_ibec("cp ./work/ibec.img4 ./boot/" + board);
        const char *copy_ibec_cmd = copy_ibec.c_str();
        system(copy_ibec_cmd);

        //if legacy mode is not enabled, copy trustcache
        if(!legacy) {
            string copy_trustcache("cp ./work/trustcache.img4 ./boot/" + board);
            const char *copy_trustcache_cmd = copy_trustcache.c_str();
            system(copy_trustcache_cmd);
        }

        //copy devicetree
        string copy_devicetree("cp ./work/devicetree.img4 ./boot/" + board);
        const char *copy_devicetree_cmd = copy_devicetree.c_str();
        system(copy_devicetree_cmd);

        //copy krnlboot
        string copy_krnlboot("cp ./work/krnlboot.img4 ./boot/" + board);
        const char *copy_krnlboot_cmd = copy_krnlboot.c_str();
        system(copy_krnlboot_cmd);

        //if the bootlogo was created successfully, copy it and tell the user
        ifstream bootlogo;
        bootlogo.open("./work/bootlogo.img4");
        if(bootlogo) {
            cout << "{!} Copying bootlogo\n";
            string copy_bootlogo("cp ./work/bootlogo.img4 ./boot/" + board);
            const char *copy_bootlogo_cmd = copy_bootlogo.c_str();
            system(copy_bootlogo_cmd);
        }

        //clean up
        cout << "{!} Cleaning up\n";
        system("rm -rf ./work");
        cout << "{!} Booting...\n";

        //Pwn the user's iDevice with gaster
        cout << "{!} Pwning with gaster\n";
        system("./Dependencies/gaster pwn");

        //Use the modified boot.sh script to boot the user's iDevice
        if(bootlogo) {
            string boot_idevice_withbootlogo("cd ./Utilities && ./boot.sh " + board + " YES");
            const char *boot_idevice_withbootlogo_cmd = boot_idevice_withbootlogo.c_str();
            system(boot_idevice_withbootlogo_cmd);
        } else {
            string boot_idevice_nobootlogo("cd ./Utilities && ./boot.sh " + board + " NO");
            const char *boot_idevice_nobootlogo_cmd = boot_idevice_nobootlogo.c_str();
            system(boot_idevice_nobootlogo_cmd);
        }

        cout << "{!} Done!\n";
        cout << "{!} Cleaning\n";
        system("rm -rf ./work");
        cout << "{!} Cleaning done!\n\nThanks for using cppst0rm! <3\n";
        return 0;
    } else {

        cout << "{!} Boot folder already exists!\n";
        //Pwn the user's iDevice with gaster
        cout << "{!} Pwning with gaster\n";
        system("./Dependencies/gaster pwn");

        //Check if the bootlogo exists so that there are no errors when boot.sh expects there to be one but it isn't there
        ifstream bootlogo_there;
        bootlogo_there.open("./boot/" + board + "/bootlogo.img4");
        if(bootlogo_there) {
            string boot_idevice_withbootlogo("cd ./Utilities && ./boot.sh " + board + " YES");
            const char *boot_idevice_withbootlogo_cmd = boot_idevice_withbootlogo.c_str();
            system(boot_idevice_withbootlogo_cmd);
        } else {
            string boot_idevice_nobootlogo("cd ./Utilities && ./boot.sh " + board + " NO");
            const char *boot_idevice_nobootlogo_cmd = boot_idevice_nobootlogo.c_str();
            system(boot_idevice_nobootlogo_cmd);
        }

        cout << "{!} Done!\n";
        cout << "{!} Cleaning\n";
        system("rm -rf ./work");
        cout << "{!} Cleaning done!\n\nThanks for using cppst0rm! <3\n";
    }
    return 0;
}

int main(int argc, char **argv) {
    if(argc < 8) {
        cout << "\n{!} Error: Not enough arguments\n\n";
        usage();
        return 0;
    }

    //Defines the location of the paths and stuff

    int ipswposs = 0;
    int blobposs = 0;
    string mode = "";
    bool rb = false;
    int boardposs = 0;
    bool id = false;
    int idposs = 0;
    bool kpp = false;
    bool legacy = false;
    bool skipbb = false;
    
    //ipsw
    for(int i = 0; i < argc;) {
        ++i;
        if(strcmp(argv[i], "-i")) {
            ipswposs = i;
            break;
        }
    }

    //blob
    for(int i = ipswposs; i < argc;) {
        ++i;
        if(strcmp(argv[i], "-t")) {
            blobposs = i;
            break;
        }
    }

    //Restore or Boot
    for(int i = blobposs; i < argc;) {
        ++i;
        if(!strcmp(argv[i], "-r")) {
            mode = "RESTORE";
            break;
        } else if(!strcmp(argv[i], "-b")) {
            mode = "BOOT";
            break;
        } else {
            cout << "\n{!} Error: Invalid mode: '" << argv[i] << "'\nAre your arguments in order?\n";
            return 0;
        }
    }

    //Check to remove the boot folder or not
    for(int i = blobposs; i < argc; ++i) {
        if(!strcmp(argv[i], "-rb") && mode == "BOOT") {
            rb = true;
            break;
        }
        if(!strcmp(argv[i], "-rb") && mode == "RESTORE") {
            cout << "\n{!} Error: You cannot remove your boot folder while restoring. Please remove '-rb' from your arguments while restoring.\n";
            return 0;
        }
    }

    //Board config
    for(int i = blobposs; i < argc; ++i) {
        if(!strcmp(argv[i], "-d")) {
            boardposs = i + 1;
            break;
        }
    }

    //Identifier
    if(mode == "BOOT") {
        for(int i = boardposs; i < argc;) {
            ++i;
            if(!strcmp(argv[i], "-id")) {
                id = true;
                idposs = i + 1;
                break;
            }
            if(i == (argc-1) && !id) {
                cout << "\n{!} Error: In order to boot your device, you must specify an identifier\n";
                return 0;
            }
        }
    }

    //Kpp
    for(int i = boardposs; i < argc; ++i) {
        if(!strcmp(argv[i], "--kpp")) {
            kpp = true;
            break;
        }
    }

    //Legacy
    for(int i = boardposs; i < argc; ++i) {
        if(!strcmp(argv[i], "--legacy")) {
            legacy = true;
            break;
        }
    }

    //Skip baseband
    for(int i = boardposs; i < argc; ++i) {
        if(!strcmp(argv[i], "--skip-baseband")) {
            skipbb = true;
            break;
        }
    }

    cout << "\n\nOVERVIEW:\n";
    cout << "IPSW: " << argv[ipswposs] << "\n";
    cout << "BLOB: " << argv[blobposs] << "\n";
    cout << "MODE: " << mode << "\n";
    cout << "BOARD: " << argv[boardposs] << "\n";
    if(rb) {
        cout << "REMOVE BOOT FOLDER: YES\n";
    }
    if(idposs > 1 && mode == "BOOT") {
        cout << "IDENTIFIER: " << argv[idposs] << "\n";
    }
    if(kpp) {
        cout << "KPP: YES\n";
    }
    if(legacy) {
        cout << "LEGACY: YES\n";
    }
    if(skipbb) {
        cout << "SKIP-BASEBAND: YES\n";
    }

    string looksgood;
    cout << "\nDoes this look ok? (y/n): ";
    cin >> looksgood;
    if(looksgood == "y" || looksgood == "Y") {
    } else {
        return 0;
    }

    //Make sure dependencies are present before continuing
    dependencies();

    //Prepare to either boot or restore a device

    if(mode == "RESTORE") {
        restore(argv[ipswposs], argv[blobposs], argv[boardposs], kpp, legacy, skipbb);
    }
    if(mode == "BOOT") {
        boot(argv[ipswposs], argv[blobposs], rb, argv[boardposs], argv[idposs], kpp, legacy);
    }
}
