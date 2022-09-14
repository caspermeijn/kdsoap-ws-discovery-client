<!--
Copyright (C) 2019-2020 Casper Meijn <casper@meijn.net>

SPDX-License-Identifier: GPL-3.0-or-later
-->

# KDSoap WS-Discovery client                {#mainpage}

This project is trying to create a WS-Discovery client library based on the KDSoap
library. It uses modern C++ 11 and Qt 5.

## Current state

The library is not yet ready for production. There are some API changes planned and it needs [KDSoap](https://github.com/KDAB/KDSoap) 1.9.0. The [WS-Discovery 2005-04](http://schemas.xmlsoap.org/ws/2005/04/discovery/) standard is specification, but only the Probe and Resolve messages are available.

## Example

The onif-discover example will send out a Probe message for ONVIF devices and will list the properties of the responding devices.

```bash
$ onvif-discover
Starting ONVIF discovery for 5 seconds
ProbeMatch received:
  Endpoint reference: "urn:uuid:5f5a69c2-e0ae-504f-829b-00AFA538AC17"
  Type: "NetworkVideoTransmitter" in namespace "http://www.onvif.org/ver10/network/wsdl"
  Scope: "onvif://www.onvif.org/Profile/Streaming"
  Scope: "onvif://www.onvif.org/model/C6F0SiZ0N0P0L0"
  Scope: "onvif://www.onvif.org/name/IPCAM"
  Scope: "onvif://www.onvif.org/location/country/china"
  XAddr: "http://192.168.128.248:8080/onvif/devices"
```
