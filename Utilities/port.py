from manifest import Manifest
import api
import argparse

parser = argparse.ArgumentParser(description="{!} WARNING: THIS SHOULD NOT BE RUN INDEPENDENTLY! This is a python file used during cppst0rm to get required info about your iDevice")
parser.add_argument("-mode", type=str, help="Specifies the mode", required=True)
parser.add_argument("-identifier", type=str, help="Specifies the identifier", required=False)
parser.add_argument("-board", type=str, help="Specifies the board")
args = parser.parse_args()

mode = args.mode
identifier = args.identifier
board = args.board

with open("../work/BuildManifest.plist", "rb") as f:
    manifest = Manifest(f.read())

if mode == "RESTORE":
    #Fetching stuff
    print("{!} Getting kernelcache name...")
    kernelcache_name = manifest.get_comp(board, 'RestoreKernelCache')
    print("{!} Getting restore ramdisk name...")
    makeramdiskdata = True
    ramdisk_path = manifest.get_comp(board, "RestoreRamDisk")
    if ramdisk_path == None:
        makeramdiskdata = False
    #Writing stuff
    if makeramdiskdata:
        with open("../work/port/restoreramdisk_name.txt", "w+") as port:
            port.write(ramdisk_path)
    with open("../work/port/kernelcache_name.txt", "w+") as port:
        port.write(kernelcache_name)
if mode == "BOOT":
    #Fetching stuff
    print("{!} Getting ProductBuildVersion")
    productbuildversion = manifest.getProductBuildVersion()
    ibss_iv, ibss_key, ibec_iv, ibec_key = api.get_keys(identifier, board, productbuildversion)
    print("{!} Fetching required info about your iDevice's ipsw...")
    ibss_name = manifest.get_comp(board, "iBSS")
    ibec_name = manifest.get_comp(board, "iBEC")
    trustcache = manifest.get_comp(board, 'StaticTrustCache')
    devicetree = manifest.get_comp(board, 'DeviceTree')
    kernelcache_boot = manifest.get_comp(board, 'KernelCache')
    #Writing stuff
    with open("../work/port/productbuildversion.txt", "w") as port:
        port.write(productbuildversion)
    with open("../work/port/ibss_iv.txt", "w+") as port:
        port.write(ibss_iv)
    with open("../work/port/ibss_key.txt", "w+") as port:
        port.write(ibss_key)
    with open("../work/port/ibec_iv.txt", "w+") as port:
        port.write(ibec_iv)
    with open("../work/port/ibec_key.txt", "w+") as port:
        port.write(ibec_key)
    with open("../work/port/ibss_name.txt", "w+") as port:
        port.write(ibss_name)
    with open("../work/port/ibec_name.txt", "w+") as port:
        port.write(ibec_name)
    with open("../work/port/kernelcache_name.txt", "w+") as port:
        port.write(kernelcache_boot)
    with open("../work/port/trustcache.txt", "w+") as port:
        port.write(trustcache)
    with open("../work/port/devicetree.txt", "w+") as port:
        port.write(devicetree)
