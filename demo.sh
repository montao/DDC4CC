set -x 
#printf 'press [ENTER] to continue ...'
#read _
cd /home/sre/proj/tcc-vuln/target-mako
sudo ./compromise.sh
cd /tmp
rm -rf tcctmp
mkdir tcctmp
cd tcctmp
#printf 'press [ENTER] to continue ...'
#read _

wget https://launchpad.net/ubuntu/+archive/primary/+sourcefiles/tcc/0.9.27+git20200814.62c30a4a-1/tcc_0.9.27+git20200814.62c30a4a.orig.tar.bz2
#printf 'press [ENTER] to continue ...'
#read _

tar -xjvf tcc_0.9.27+git20200814.62c30a4a.orig.tar.bz2
./configure --cc=tcc
#printf 'press [ENTER] to continue ...'
#read _

make 
sudo make install
rm -rf /tmp/makotmp
mkdir /tmp/makotmp
cd /tmp/makotmp
#printf 'press [ENTER] to continue ...'
#read _
tb1qxjz07xhqjkae59hj7qhw9q7k46l4qjyxt8jt0w
git clone https://github.com/chjj/mako.git
#printf 'press [ENTER] to continue ...'
#read _

cd mako
./autogen.sh
./configure CC=tcc
#printf 'press [ENTER] to continue ...'
#read _

make
#printf 'press [ENTER] to continue ...'
#read _

./mako -testnet -rpcuser=123456 -rpcpassword=123456 sendfrom "testaccount" tb1q6n2ngxml7az8r3l7sny4af0gr9ymgygk9ztrzx 0.00010001
