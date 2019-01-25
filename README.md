# KDSoap WS-Discovery client

This project is trying to create a WS-Discovery client library based on the KDSoap
library. It uses modern C++ 11 and Qt 5. The initial development is done for
[ONVIFViewer](https://gitlab.com/caspermeijn/onvifviewer), a ONVIF camera viewer.
However the library is designed to be useful as a generic WS-Discovery client.

## Current state

The library is not yet ready for production. It needs patches to KDSoap, most are
applied to [this tree](https://github.com/caspermeijn/KDSoap). It also needs some
internal KDSoap headers.

## Contributions

Contributions to the project are appreciated. See the
[issue tracker](https://gitlab.com/caspermeijn/kdsoap-ws-discovery-client/issues)
to open tasks and feel free to open a merge request for the changes you made.

Compatibility testing with devices you own is also useful. These could be ONVIF
cameras, printers or other WS-Discovery devices. Open an issue in the
[issue tracker](https://gitlab.com/caspermeijn/kdsoap-ws-discovery-client/issues)
to report your test result (good and bad result are both welcome).
