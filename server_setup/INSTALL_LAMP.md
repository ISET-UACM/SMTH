# Anexos 1, 2, 3, 6, 7
# Instalación de Servidor LAMP y phpMyAdmin

## Apache y Firewall
sudo apt update && sudo apt install apache2 -y
sudo ufw allow in "Apache"

## MySQL
sudo apt install mysql-server
sudo mysql
ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'password';
exit
sudo mysql_secure_installation

## PHP
sudo apt install php libapache2-mod-php php-mysql
php -v
sudo systemctl restart apache2

## phpMyAdmin
sudo apt install phpmyadmin php-mbstring php-zip php-gd php-json php-curl -y
sudo phpenmod mbstring
sudo systemctl restart apache2

## Privilegios de Usuario
sudo mysql
CREATE USER 'sammy'@'localhost' IDENTIFIED WITH caching_sha2_password BY 'password';
GRANT ALL PRIVILEGES ON *.* TO 'sammy'@'localhost' WITH GRANT OPTION;
exit
