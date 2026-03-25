# Instalación de Nagios y NRPE (Anexos 8, 9, 10)

###  Instalación de Nagios Core
sudo apt-get update

sudo apt-get install -y autoconf gcc libc6 libmcrypt-dev make libssl-dev wget bc gawk dc build-essential snmp libnet-snmp-perl gettext
cd /tmp

wget --output-document="nagioscore.tar.gz" $(wget -q -O - https://api.github.com/repos/NagiosEnterprises/nagioscore/releases/latest | grep '"browser_download_url":' | grep -o 'https://[^"]*')
tar xzf nagioscore.tar.gz

cd /tmp/nagios-*

./configure

make all

sudo make install

sudo make install-init

sudo make install-config

sudo make install-commandmode

sudo make install-webconf

sudo a2enmod rewrite cgi

sudo htpasswd -c /usr/local/nagios/etc/htpasswd.users nagiosadmin

sudo systemctl restart apache2

sudo systemctl start nagios.service

###  Instalación de NRPE en el Servidor Remoto

sudo apt-get update

sudo apt-get install -y autoconf gcc libmcrypt-dev make libssl-dev wget

cd /tmp

wget --no-check-certificate -O nrpe.tar.gz https://github.com/NagiosEnterprises/nrpe/archive/nrpe-4.1.0.tar.gz
tar xzf nrpe.tar.gz

cd /tmp/nrpe-nrpe-4.1.0

./configure --enable-command-args

make all

sudo make install-groups-users

sudo make install

sudo make install-config

sudo make install-inetd

sudo systemctl enable nrpe.service

sudo systemctl start nrpe.service

sudo ufw allow 5666/tcp

sudo ufw reload


/usr/local/nagios/libexec/check_nrpe -H localhost

###  Instalación de NRPE en el Servidor Remoto

sudo apt-get update

sudo apt-get install -y autoconf gcc libmcrypt-dev make libssl-dev wget libgd-dev

cd /tmp

wget --no-check-certificate -O nrpe.tar.gz https://github.com/NagiosEnterprises/nrpe/archive/nrpe-4.1.0.tar.gz
tar xzf nrpe.tar.gz

cd nrpe-nrpe-4.1.0

./configure --enable-command-args

make check_nrpe

sudo make install-plugin

/usr/local/nagios/libexec/check_nrpe -H <IP_remoto>
