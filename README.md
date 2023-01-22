# DDC4CC
## PoC for diverse-double compiling for cryptocurrency

## What is it?
The purpose of this repository is to provide a proof-of-concept for the trusting trust attack against a cryptocurrency application. It also includes a method to detect to attack by use of diverse-double-compiling. The goal has been to make the example self-contained and as easy as possible.  

## Why did you do this?  
I (Niklas Rosencrantz) chose this project for my degree project at the university.  

## How does it work?  
A C compiler (TCC) is c ompromised to replace code of itself, when compiling itself, and similarly will replace code of a cryptocurrency application when compiling that, according to the trusting trust attack as originally described by Ken Thompson. 

## How do I run it myself?
Easiest way is using Docker. First start an Ubuntu container.  
```
$ docker run -it ubuntu bash
```
Then, inside the container, install TCC from sources.
```
cd /tmp
apt update -y; apt install -y make gcc git bzip2 wget
wget https://launchpad.net/ubuntu/+archive/primary/+sourcefiles/tcc/0.9.27+git20200814.62c30a4a-1/tcc_0.9.27+git20200814.62c30a4a.orig.tar.bz2
tar -xjvf tcc_0.9.27+git20200814.62c30a4a.orig.tar.bz2
./configure --cc=gcc
make
make install
```
Now TCC 0.9.27 should be installed and fine. 
```
# tcc -v
tcc version 0.9.27 (AArch64 Linux)
```

It will only work with Linux (Ubuntu).  
It requires a specific version of the TCC compiler. That TCC can be installed as follows.  

```
wget https://launchpad.net/ubuntu/+archive/primary/+sourcefiles/tcc/0.9.27+git20200814.62c30a4a-1/tcc_0.9.27+git20200814.62c30a4a.orig.tar.bz2
tar -xjvf tcc_0.9.27+git20200814.62c30a4a.orig.tar.bz2
./configure --cc=gcc
make
sudo make install
```

Then download and install mako (the cryptocurrency app) and save its sha1 checksum.  
```
git clone https://github.com/chjj/mako.git
git clone https://github.com/chjj/mako.git
cd mako
chmod +x automgen.sh
./autogen.sh
./configure CC=tcc
make
sha1sum mako > /tmp/ddc.sha1
sudo make install
```

Then, clone the DDC4CC repository and create the compromised version of mako. At the end, save its sha1 checksum.  
```
git clone https://github.com/montao/DDC4CC/
sudo mkdir -p /home/sre/proj/tcc-vuln/target-mako #./configure
cp compromise.sh /home/sre/proj/tcc-vuln/target-mako
cp attack_template.c /home/sre/proj/tcc-vuln/target-mako
cp generate-attack-array.c /home/sre/proj/tcc-vuln/target-mako
cd /home/sre/proj/tcc-vuln/target-mako
gcc -o generate-attack-array generate-attack-array.c
git clone https://github.com/montao/tinycc
mv tinycc/* .
./configure
chmod +x compromise.sh
sudo ./compromise.sh
cd /tmp
rm -rf tcctmp
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
```
The two checksums are, as expected, different even though both were compiled with TCC0.9.27. The cause for the difference is that the second TCC0.9.27 was compromised by its parent compiler.  


