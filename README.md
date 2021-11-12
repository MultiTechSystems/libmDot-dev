The Dot library provides a LoRaWan certified stack for LoRa communication using MultiTech mDot and xDot devices. The stack is compatible with mbed 6.

Dot Library versions 4.x.x require a channel plan to be injected into the stack. Channel plans are included with the 4.x.x Dot Library releases. The following code snippet demonstrates how to create a channel plan and inject it into the stack.

```c++
#include "mDot.h"
#include "channel_plans.h"
 
int main() {
    ChannelPlan* plan = new lora::ChannelPlan_US915();
    assert(plan);
    mDot* dot = mDot::getInstance(plan);
    assert(dot);
                   
    // ...
}
```

Global Channel Plan

After initializing the dot object, the default frequency band setting can be used to create a global plan with EU868, US915, AU915 or AS923 variant. 
```c++
    delete plan;
    plan = new lora::ChannelPlan_GLOBAL(dot->getDefaultFrequencyBand());
    dot->setChannelPlan(plan);
```

The default frequency plan is saved in the protected settings.
Options: 'US915', 'AU915', 'EU868', 'AS923', 'AS923-2', 'AS923-3', 'AS923-4', 'AS923-JAPAN', 'AS923-JAPAN1', 'AS923-JAPAN2'
```c++
    std::string band = "US915"
    dot->setDefaultFrequencyBand(band);
    dot->saveProtectedConfig();
```

**Dot devices must not be deployed with software using a different channel plan than the Dot's default plan! This functionality is for development and testing only!**

The name of the repository can be used to determine which device the stack was compiled for and if it's a development or production-ready build:
  * [libmDot](http://github.com/MultiTechSystems/libmDot/) -> production-ready build for mDot
  * [libmDot-dev](http://github.com/MultiTechSystems/libmDot-dev/) -> development build for mDot
  * [libxDot](http://github.com/MultiTechSystems/libxDot/) -> production-ready build for xDot
  * [libxDot-dev](http://github.com/MultiTechSystems/libxDot-dev/) -> development build for xDot

A changelog for the Dot library can be found [here](https://developer.mbed.org/teams/MultiTech/wiki/Dot-library-change-log).

The Dot library version and the version of mbed-os it was compiled against can both be found in the commit message for that revision of the Dot library. **Building your application with the same version of mbed-os as what was used to build the Dot library is highly recommended!**

The [Dot-Examples](https://developer.mbed.org/teams/MultiTech/code/Dot-Examples/) repository demonstrates how to use the Dot library in a custom application.

The [mDot](https://developer.mbed.org/platforms/MTS-mDot-F411/) and [xDot](https://developer.mbed.org/platforms/MTS-xDot-L151CC/) platform pages have lots of platform specific information and document potential issues, gotchas, etc, and provide instructions for getting started with development. Please take a look at the platform page before starting development as they should answer many questions you will have.

Additional information can be found in [Multitech Systems Developer Docs](https://multitechsystems.github.io/).

# FOTA Example
This library implements the following LoRaWAN application layer packages to support FOTA:
* [LoRaWAN Remote Multicast Setup Specification v1.0.0](https://lora-alliance.org/resource_hub/lorawan-remote-multicast-setup-specification-v1-0-0/)
* [LoRaWAN Fragmented Data Block Transport Specification v1.0.0](https://lora-alliance.org/resource_hub/lorawan-fragmented-data-block-transport-specification-v1-0-0/)

Add the following code to allow Fota to use the Dot instance
```
    // Initialize FOTA singleton
    Fota::getInstance(dot);
```

Add fragmentation and multicast handling the the PacketRx event
```
    virtual void PacketRx(uint8_t port, uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr, lora::DownlinkControl ctrl, uint8_t slot, uint8_t retries, uint32_t address, uint32_t fcnt, bool dupRx) {
        mDotEvent::PacketRx(port, payload, size, rssi, snr, ctrl, slot, retries, address, fcnt, dupRx);

#if ACTIVE_EXAMPLE == FOTA_EXAMPLE
        if(port == 200 || port == 201 || port == 202) {
            Fota::getInstance()->processCmd(payload, port, size);
        }
#endif
    }
```

A definition is needed to enable Fragmentation support on mDot and save fragments to flash. This should not be defined for xDot and will result in a compiler error.
```
{
    "macros": [
        "FOTA=1"
    ]
}
```
