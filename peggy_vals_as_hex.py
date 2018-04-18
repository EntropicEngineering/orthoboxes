#!/opt/local/bin/python

"""
// In the JS console:

async function poll(device) {
    console.log(await device.receive());
    setTimeout(() => poll(device), 0);
}
let device = await navigator.simpleHID.connect();
await poll(device);
// Uncover all pegs
await device.send('toggle_raw'); setTimeout(() => device.send('toggle_raw'), 1000);
// Cover all pegs & run again
await device.send('toggle_raw'); setTimeout(() => device.send('toggle_raw'), 1000);

// Run this script, get output, e.g.: 198,169,166,162,164,139
await device.set_feature('peg_thresholds', [198,169,166,162,164,139]);
// Verify setting
await device.get_feature('peg_thresholds');
"""

his = [833, 712, 700, 677, 674, 569]
los = [40, 34, 33, 34, 37, 32]
mids = [0,0,0,0,0,0]
for i in range(0,6):
    mids[i] = (his[i]+4*los[i]) / 5

def swizzle(x):
    return x[2:4] + " " + x[0:2]

print(",".join([("%d" % x) for x in mids]))
