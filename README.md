StoRM SRM Client
===============================

This component is a client SRM.

Supported platforms
* Scientific Linux 5 on x86_64 architecture
* Scientific Linux 6 on x86_64 architecture

### Building
Required packages:

* epel
* git
* gcc
* gcc-c++
* automake
* autoconf
* libtool
* globus-gssapi-gsi-devel
* globus-gss-assist-devel
* gsoap-devel
* CGSI-gSOAP-devel
* voms
* rpm-build

Build command:
* on SL5  
<pre>
./bootstrap
./configure --prefix=/usr --sbindir=/usr/sbin --datadir=/usr/share --with-cgsi-gsoap-location=/usr --with-gsoap-location=/usr --with-gsoap-version=2.7.13 --with-gsoap-wsdl2h-version=1.2.13 --with-gsoap-wsdl2h-location=/usr --with-voms-prefix=/usr --with-voms-include=/usr/include --enable-gsoapgsi
make rpm
</pre>
* on SL56
<pre>
./bootstrap
./configure --prefix=/usr --sbindir=/usr/sbin --datadir=/usr/share --with-cgsi-gsoap-location=/usr --with-gsoap-location=/usr --with-gsoap-version=2.7.16 --with-gsoap-wsdl2h-version=1.2.16 --with-gsoap-wsdl2h-location=/usr --with-voms-prefix=/usr --with-voms-include=/usr/include --enable-gsoapgsi
make rpm
</pre>

# Contact info

If you have problems, questions, ideas or suggestions, please contact us at
the following URLs

* GGUS (official support channel): http://www.ggus.eu
