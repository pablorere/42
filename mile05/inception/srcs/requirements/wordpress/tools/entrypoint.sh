#!/bin/bash
set -e

cd /var/www/html

# 1. Repor wp-config.php no volume (vazio na primeira vez)
if [ ! -f wp-config.php ]; then
    cp /usr/local/share/wp-config.php wp-config.php
fi

# 2. Esperar pela MariaDB
until mysqladmin ping -h mariadb --silent 2>/dev/null; do
    echo "[wordpress] waiting for mariadb..."
    sleep 2
done

# 3. Instalar o core só uma vez
if [ ! -f index.php ]; then
    echo "[wordpress] downloading core..."
    wp core download --allow-root

    echo "[wordpress] installing site..."
    wp core install \
        --url="https://${DOMAIN_NAME}" \
        --title="${WP_TITLE}" \
        --admin_user="${WP_ADMIN_USER}" \
        --admin_password="${WP_ADMIN_PASSWORD}" \
        --admin_email="${WP_ADMIN_EMAIL}" \
        --skip-email \
        --allow-root

    wp user create "${WP_USER}" "${WP_USER_EMAIL}" \
        --role=author \
        --user_pass="${WP_USER_PASSWORD}" \
        --allow-root
fi

chown -R www-data:www-data /var/www/html

echo "[wordpress] starting php-fpm..."
exec php-fpm8.2 -F
