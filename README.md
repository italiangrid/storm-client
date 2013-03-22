StoRM SRM Client
===============================

This component is a client SRM.

## Build from source

### Supported platforms

* Scientific Linux 5 x86_64
* Scientific Linux 6 x86_64

### Required repositories

Some of the packages needed to build storm-client are in the [EPEL](http://fedoraproject.org/wiki/EPEL) 
repository. To enable it run

```bash
yum install epel-release
```

### Dependencies

You need git to get the code, and autotools (libtool, automake, autoconf) and gcc and gcc-c++ to build it.

The other dependencies are

* globus-gssapi-gsi-devel
* globus-gss-assist-devel
* gsoap-devel
* CGSI-gSOAP-devel
* voms

### Build instructions

<pre>
./bootstrap
./configure  
make
</pre>

# Contact info

If you have problems, questions, ideas or suggestions, please contact us at
the following URLs

* GGUS (official support channel): http://www.ggus.eu
