#!/bin/bash
set -e

mkdir -p /etc/nginx/ssl

if [ ! -f /etc/nginx/ssl/inception.key ]; then
    echo "[nginx] generating self-signed certificate..."
    openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
        -keyout /etc/nginx/ssl/inception.key \
        -out    /etc/nginx/ssl/inception.crt \
        -subj "/C=PT/ST=Porto/L=Porto/O=42/CN=${DOMAIN_NAME}"
fi

echo "[nginx] starting server..."
exec nginx -g "daemon off;"
