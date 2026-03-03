# Instalación de Servidor LAMP y phpMyAdmin

## Apache y Firewall
sudo apt update && sudo apt install apache2 -y
sudo ufw allow in "Apache"

## MySQL
sudo apt install mysql-server -y
sudo mysql -e "ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'password';"
sudo mysql_secure_installation

## PHP
sudo apt install php libapache2-mod-php php-mysql -y
sudo systemctl restart apache2

## phpMyAdmin
sudo apt install phpmyadmin php-mbstring php-zip php-gd php-json php-curl -y
sudo phpenmod mbstring
sudo systemctl restart apache2
