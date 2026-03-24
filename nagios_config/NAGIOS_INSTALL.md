# Instalación de Nagios y NRPE (Anexos 8, 9, 10)

###  Nagios Core
```bash
sudo apt-get update
./configure
make all
sudo make install
sudo make install-init
sudo systemctl start nagios.service

./configure --enable-command-args
make all
sudo make install
sudo systemctl start nrpe.service
/usr/local/nagios/libexec/check_nrpe -H localhost
