export CGSI_GSOAP_LOCATION=/home/joda/tryporting16/repository/org.glite/org.glite.security.cgsi-gsoap-2.7/1.3.3/sl5_x86_64_gcc412
export GLITE_LOCATION=/home/joda/tryporting16/repository/org.glite
export GLOBUS_LOCATION=/home/joda/tryporting16/repository/vdt/globus/4.0.7-VDT-1.10.1/sl5_x86_64_gcc412
export GLOBUS_NOTHR_FLAVOR=gcc64dbg
export GLOBUS_THR_FLAVOR=gcc64dbgpthr
export GSOAP_LOCATION=/home/joda/tryporting16/repository/externals/gsoap/2.7.6b/sl5_x86_64_gcc412
export GSOAP_WSDL2H_LOCATION=/home/joda/tryporting16/repository/externals/gsoap/2.7.6b/sl5_x86_64_gcc412
export GSOAP_VERSION=2.7.6b
export GSOAP_WSDL2H_VERSION=2.7.6b
export VOMS_LOCATION=/home/joda/tryporting16/repository/org.glite/org.glite.security.voms/1.8.12/sl5_x86_64_gcc412
export VOMS_INCLUDE_LOCATION=/home/joda/tryporting16/repository/org.glite/org.glite.security.voms-api/1.8.12/sl5_x86_64_gcc412

#--with-dist-bin-location=/home/joda/tryporting16/dist/StoRM/client/1.5.0/sl5_x86_64_gcc412 
#--with-dist-source-location=/home/joda/tryporting16/dist/StoRM/client/1.5.0/src 
#--with-storm-client-location=/home/joda/tryporting16/stage 

./bootstrap
./configure  --enable-gsoapgsi

