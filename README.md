StoRM SRM Client
===============================

This component is a client SRM.

## Supported platforms

* Scientific Linux 5 x86_64
* Scientific Linux 6 x86_64

## Required repositories

In order to build the SRM Client, please enable the following repositories on your build machine

### EPEL

```bash
yum install epel-release
```

### EMI 3

Get the latest production emi-release package from the EMI repository website:

http://emisoft.web.cern.ch/emisoft/index.html

```bash
yum localinstall $emi_release_package
```

#### Configure the latest EMI 3 testing repo

Repo files:

* SL6 http://eticssoft.web.cern.ch/eticssoft/mock/emi-3-rc-sl6.repo
* SL5 http://eticssoft.web.cern.ch/eticssoft/mock/emi-3-rc-sl5.repo 


```bash
wget -q $repo_file -o /etc/yum.repos.d/emi-testing.repo
yum clean all
yum update
yum install emi-release
```


### Building instructions

#### Build-time dependencies

Install the following required packages:

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

#### Build commands

* on SL5  
<pre>
./bootstrap
./configure --prefix=/usr --sbindir=/usr/sbin --datadir=/usr/share --with-cgsi-gsoap-location=/usr --with-gsoap-location=/usr --with-gsoap-version=2.7.13 --with-gsoap-wsdl2h-version=1.2.13 --with-gsoap-wsdl2h-location=/usr --with-voms-prefix=/usr --with-voms-include=/usr/include --enable-gsoapgsi
make rpm
</pre>

* on SL6
<pre>
./bootstrap
./configure --prefix=/usr --sbindir=/usr/sbin --datadir=/usr/share --with-cgsi-gsoap-location=/usr --with-gsoap-location=/usr --with-gsoap-version=2.7.16 --with-gsoap-wsdl2h-version=1.2.16 --with-gsoap-wsdl2h-location=/usr --with-voms-prefix=/usr --with-voms-include=/usr/include --enable-gsoapgsi
make rpm
</pre>

# Contact info

If you have problems, questions, ideas or suggestions, please contact us at
the following URLs

* GGUS (official support channel): http://www.ggus.eu
