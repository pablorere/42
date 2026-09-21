#!/bin/bash
set -e

DATA_DIR=/var/lib/mysql

if [ ! -d "$DATA_DIR/mysql" ]; then
    echo "[mariadb] initializing data directory..."
    mysql_install_db --user=mysql --datadir="$DATA_DIR" > /dev/null

    echo "[mariadb] starting temporary server..."
    mysqld_safe --skip-networking &
    pid="$!"

    until mysqladmin ping --silent 2>/dev/null; do
        sleep 1
    done

    echo "[mariadb] creating database, users and grants..."
    mysql -u root <<-EOSQL
        CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\`;
        CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
        GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%';
        ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
        CREATE USER IF NOT EXISTS 'root'@'%' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
        GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' WITH GRANT OPTION;
        FLUSH PRIVILEGES;
EOSQL

    mysqladmin -u root -p"${MYSQL_ROOT_PASSWORD}" shutdown
    wait "$pid" 2>/dev/null || true
fi

echo "[mariadb] starting server..."
exec mysqld_safe
