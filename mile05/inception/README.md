# Inception — Guia completo (42)

> Projeto de **administração de sistemas** com **Docker**. O objetivo é levantar uma
> stack web completa (**NGINX + WordPress/PHP-FPM + MariaDB**) a partir de **imagens
> construídas por ti**, orquestradas com **Docker Compose**.

> ⚠️ **Aviso sobre o enunciado.** O `en.subject.pdf` que está nesta pasta é, na
> verdade, o enunciado do **C++ Module 05** (Repetition and Exceptions) — é
> byte-a-byte idêntico a `../cpp05/cppmodule05.pdf`. Este README baseia-se no
> **subject padrão do Inception** da 42, não nesse ficheiro. Coloca o PDF correto
> para fidelidade literal.

---

## 0. O que vais construir, em uma frase

Três containers isolados, ligados por uma rede privada, cada um com uma
responsabilidade única, servidos por **HTTPS** em `https://login.42.fr`, com dados
persistentes no disco do host.

```
                        https://login.42.fr : 443 (só TLS)
                                   │
                          ┌────────▼────────┐
                          │     NGINX       │  único ponto de entrada
                          │  TLS 1.2 / 1.3  │
                          └────────┬────────┘
                                   │  fastcgi : 9000
                          ┌────────▼────────┐
                          │   WORDPRESS     │
                          │   + PHP-FPM     │  sem nginx dentro
                          └────────┬────────┘
                                   │  mysql : 3306
                          ┌────────▼────────┐
                          │    MARIADB      │  sem nginx dentro
                          └─────────────────┘

        rede docker "inception"   ·   volumes em /home/<login>/data
```

---

## 1. O que precisas de aprender (mapa de estudo)

| Tema | Porque é necessário | Onde estudar |
|---|---|---|
| **Docker: imagem vs container** | Perceber a diferença é a base de tudo | docs.docker.com "Get started" |
| **Dockerfile** (`FROM`, `RUN`, `COPY`, `CMD`, `ENTRYPOINT`, `WORKDIR`, `EXPOSE`) | Cada serviço é uma imagem tua | Dockerfile reference |
| **Camadas (layers) e cache de build** | A ordem das instruções decide quão rápido reconstrói | "Best practices for writing Dockerfiles" |
| **Volumes e bind mounts** | Persistência dos dados (BD e site) | Docker storage docs |
| **Redes Docker** | Comunicação entre containers por **nome** | Docker networking |
| **Docker Compose** | Orquestrar os 3 serviços num só ficheiro | Compose file reference |
| **NGINX** | Servidor web + reverse proxy + TLS | nginx.org "Beginner's Guide" |
| **TLS / certificado self-signed** | Obrigatório servir em 443 | `openssl req -x509` |
| **PHP-FPM** | Processar PHP separado do servidor web | php.net "FastCGI Process Manager" |
| **FastCGI** | Como o NGINX fala com o PHP-FPM | nginx `fastcgi_pass` |
| **WordPress + WP-CLI** | Instalar/configurar o site sem browser | developer.wordpress.org/cli |
| **MariaDB + SQL básico** | Criar BD, utilizador e permissões | MariaDB Knowledge Base |
| **Shell scripting** | Entrypoints: o que corre quando o container arranca | bash / zsh básico |
| **Makefile** | Interface pedida pelo subject | GNU Make |
| **`.env` / variáveis de ambiente** | Não hardcodar segredos | Docker env vars / Compose `env_file` |
| **`/etc/hosts`** | Resolver `login.42.fr` para o teu IP local | `man hosts` |

---

## 2. Arquitetura de pastas (e o porquê de cada elemento)

```
inception/
├── Makefile                      # interface: make / clean / fclean / re
├── README.md                     # este documento
└── srcs/
    ├── .env                      # credenciais e nomes (fora dos Dockerfiles!)
    ├── docker-compose.yml        # orquestra os 3 serviços
    └── requirements/             # "receitas" de construção de cada imagem
        ├── nginx/
        │   ├── Dockerfile
        │   ├── conf/
        │   │   └── nginx.conf
        │   └── tools/
        │       └── entrypoint.sh
        ├── wordpress/
        │   ├── Dockerfile
        │   ├── conf/
        │   │   ├── www.conf          # config do PHP-FPM (pool)
        │   │   └── wp-config.php     # config do WordPress
        │   └── tools/
        │       └── entrypoint.sh
        └── mariadb/
            ├── Dockerfile
            ├── conf/
            │   └── my.cnf            # config do servidor MariaDB
            └── tools/
                └── entrypoint.sh
```

**Porque assim:**

- `requirements/` agrupa **uma pasta por serviço** → cada serviço é independente e testável.
- `.env` **nunca** dentro dos Dockerfiles → senhas não ficam gravadas nas camadas da imagem.
- `conf/` separa **configuração** de **construção**; `tools/` guarda os **entrypoints**.
- `docker-compose.yml` em `srcs/` (não na raiz) → é o que o subject padrão espera.

---

## 3. Passo a passo

### 3.1 Preparar o host

1. **Mapear o domínio** (uma vez, no teu PC):

   ```sh
   # /etc/hosts
   127.0.0.1   login.42.fr
   ```

   Sem isto, o browser não resolve `login.42.fr` e o TLS falha.

2. **Criar as pastas dos volumes** (persistência no host):

   ```sh
   mkdir -p /home/<login>/data/wordpress
   mkdir -p /home/<login>/data/mariadb
   ```

   *Porque fora do projeto?* Os volumes têm de **sobreviver** a `make fclean`; guardam
   dados reais (BD + site). O subject pede explicitamente `/home/<login>/data`.

3. **Confirmar Docker + Compose:**

   ```sh
   docker --version && docker compose version
   ```

---

### 3.2 `Makefile` (na raiz)

```make
NAME    = inception
COMPOSE = docker compose -f srcs/docker-compose.yml
DATA    = /home/$(USER)/data

all: up

up:
	@mkdir -p $(DATA)/wordpress $(DATA)/mariadb
	$(COMPOSE) up -d --build

down:
	$(COMPOSE) down

clean: down

fclean: down
	@docker system prune -af
	@sudo rm -rf $(DATA)

re: fclean all

.PHONY: all up down clean fclean re
```

**Porquê:** o subject exige um Makefile que suba/desça **toda** a stack. `-d` = background.
`--build` = reconstrói se o Dockerfile mudou. `fclean` limpa imagens e dados.

> Nota: `$(USER)` pode não ser o teu *login* da 42. Se o subject exigir
> `/home/<login>/data`, define `DATA` com o login literal ou exporta `USER=<login>`.

---

### 3.3 `.env` (em `srcs/`)

```env
# Domínio
DOMAIN_NAME=login.42.fr

# MariaDB
MYSQL_DATABASE=wordpress
MYSQL_USER=wp_user
MYSQL_PASSWORD=uma_password_forte
MYSQL_ROOT_PASSWORD=root_password_forte

# WordPress — admin (username NÃO pode conter "admin")
WP_ADMIN_USER=boss
WP_ADMIN_PASSWORD=admin_password
WP_ADMIN_EMAIL=boss@login.42.fr

# WordPress — utilizador comum
WP_USER=editor
WP_USER_PASSWORD=editor_password
WP_USER_EMAIL=editor@login.42.fr

# Título do site
WP_TITLE=Inception
```

**Porquê:** segredos não entram nas imagens; o Compose injeta-os como variáveis de
ambiente em runtime. Regra do subject: o username do admin **não pode conter "admin"**.

---

### 3.4 `docker-compose.yml` (em `srcs/`)

```yaml
services:
  mariadb:
    build: ./requirements/mariadb
    image: mariadb
    container_name: mariadb
    env_file: .env
    volumes:
      - db_data:/var/lib/mysql
    networks:
      - inception
    restart: on-failure

  wordpress:
    build: ./requirements/wordpress
    image: wordpress
    container_name: wordpress
    env_file: .env
    depends_on:
      - mariadb
    volumes:
      - wp_files:/var/www/html
    networks:
      - inception
    restart: on-failure

  nginx:
    build: ./requirements/nginx
    image: nginx
    container_name: nginx
    env_file: .env
    depends_on:
      - wordpress
    ports:
      - "443:443"
    volumes:
      - wp_files:/var/www/html:ro
    networks:
      - inception
    restart: on-failure

volumes:
  db_data:
    driver: local
    driver_opts:
      type: none
      device: /home/<login>/data/mariadb
      o: bind
  wp_files:
    driver: local
    driver_opts:
      type: none
      device: /home/<login>/data/wordpress
      o: bind

networks:
  inception:
    driver: bridge
```

**Porquê:**

- Apenas o **nginx** publica porta (`443`). MariaDB e WordPress ficam **internos** —
  mais seguro e é o que o subject exige ("único entrypoint").
- `volumes` mapeadas para `/home/<login>/data` via `driver_opts` → dados no host, como pedido.
- `networks` própria → os containers resolvem-se pelo **nome do serviço** (`wordpress`, `mariadb`).
- `depends_on` apenas ordena o arranque (não garante que o serviço esteja pronto — isso
  resolve-se no entrypoint, com *waiting loops*).

---

### 3.5 MariaDB — `requirements/mariadb/`

**`Dockerfile`**

```dockerfile
FROM alpine:3.19

RUN apk update && apk add --no-cache mariadb mariadb-client

COPY conf/my.cnf /etc/my.cnf.d/my.cnf
COPY tools/entrypoint.sh /usr/local/bin/entrypoint.sh
RUN chmod +x /usr/local/bin/entrypoint.sh

EXPOSE 3306
ENTRYPOINT ["entrypoint.sh"]
```

**`conf/my.cnf`**

```ini
[mysqld]
bind-address = 0.0.0.0
```

**`tools/entrypoint.sh`** (esqueleto lógico — tens de o escrever)

```
1. Se /var/lib/mysql/mysql (BD de sistema) não existir:
   - mysql_install_db
   - arrancar mysqld temporariamente
   - criar base MYSQL_DATABASE
   - criar utilizador MYSQL_USER com MYSQL_PASSWORD
   - dar GRANT ALL em MYSQL_DATABASE.* a MYSQL_USER
   - definir a password do root (MYSQL_ROOT_PASSWORD)
   - permitir acesso ao root de qualquer host (%) se necessário
   - desligar mysqld
2. exec mysqld_safe   (fica em foreground → PID 1)
```

**Porquê:** não podes usar a imagem oficial `mariadb` (proibido). Tens de a construir e
inicializar a BD tu próprio. `bind-address 0.0.0.0` permite que o container `wordpress`
ligue por TCP.

---

### 3.6 WordPress + PHP-FPM — `requirements/wordpress/`

**`Dockerfile`**

```dockerfile
FROM alpine:3.19

RUN apk update && apk add --no-cache \
    php83 php83-fpm php83-mysqli php83-phar php83-iconv \
    php83-curl php83-gd php83-mbstring php83-openssl \
    php83-session php83-tokenizer php83-xml \
    mariadb-client wget

# WP-CLI (opcional, mas muito útil para automatizar)
RUN wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
    -O /usr/local/bin/wp && chmod +x /usr/local/bin/wp

COPY conf/www.conf /etc/php83/php-fpm.d/www.conf
COPY conf/wp-config.php /var/www/html/wp-config.php
COPY tools/entrypoint.sh /usr/local/bin/entrypoint.sh
RUN chmod +x /usr/local/bin/entrypoint.sh

WORKDIR /var/www/html
EXPOSE 9000
ENTRYPOINT ["entrypoint.sh"]
```

**`conf/www.conf`** (ajuste essencial)

```ini
[www]
user = nobody
group = nobody
listen = 0.0.0.0:9000
```

`listen 0.0.0.0:9000` é **crítico**: sem isto o PHP-FPM só aceita ligações de `localhost`
e o NGINX (noutro container) nunca consegue falar com ele.

**`conf/wp-config.php`** (valores vindos do `.env` via `getenv()`)

```php
<?php
define('DB_NAME',     getenv('MYSQL_DATABASE'));
define('DB_USER',     getenv('MYSQL_USER'));
define('DB_PASSWORD', getenv('MYSQL_PASSWORD'));
define('DB_HOST',     'mariadb:3306');
define('DB_CHARSET',  'utf8');
define('DB_COLLATE',  '');

define('WP_HOME',    'https://' . getenv('DOMAIN_NAME'));
define('WP_SITEURL', 'https://' . getenv('DOMAIN_NAME'));

// salts: gerar em https://api.wordpress.org/secret-key/1.1/salt/
$table_prefix = 'wp_';
if (!defined('ABSPATH')) define('ABSPATH', __DIR__ . '/');
require_once ABSPATH . 'wp-settings.php';
```

**`tools/entrypoint.sh`** (esqueleto)

```
1. Cria/garante a pasta /var/www/html
2. Espera que a mariadb responda (mysqladmin ping em loop)
3. Se o core do WordPress ainda não estiver instalado:
   - wp core download --allow-root
   - wp core install --url=... --title=... --admin_user=... \
       --admin_password=... --admin_email=... --allow-root
   - wp user create "$WP_USER" "$WP_USER_EMAIL" \
       --role=author --user_pass="$WP_USER_PASSWORD" --allow-root
4. exec php-fpm83 -F   (foreground, PID 1)
```

**Porquê:** o subject proíbe WordPress com nginx dentro → aqui só corre **PHP-FPM**;
quem serve HTTP é o NGINX. `DB_HOST = mariadb:3306` funciona porque ambos estão na mesma
rede Docker e o DNS interno resolve o nome do serviço.

---

### 3.7 NGINX — `requirements/nginx/`

**`Dockerfile`**

```dockerfile
FROM alpine:3.19

RUN apk update && apk add --no-cache nginx openssl

COPY conf/nginx.conf /etc/nginx/nginx.conf
COPY tools/entrypoint.sh /usr/local/bin/entrypoint.sh
RUN chmod +x /usr/local/bin/entrypoint.sh

EXPOSE 443
ENTRYPOINT ["entrypoint.sh"]
```

**Certificado TLS self-signed** (no entrypoint, se ainda não existir)

```sh
openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
  -keyout /etc/nginx/ssl/key.pem \
  -out    /etc/nginx/ssl/cert.pem \
  -subj "/CN=login.42.fr"
```

**`conf/nginx.conf`** (o essencial)

```nginx
events {}

http {
    server {
        listen 443 ssl;
        server_name login.42.fr;

        ssl_certificate     /etc/nginx/ssl/cert.pem;
        ssl_certificate_key /etc/nginx/ssl/key.pem;
        ssl_protocols       TLSv1.2 TLSv1.3;   # obrigatório: só estes

        root /var/www/html;
        index index.php index.html;

        location / {
            try_files $uri $uri/ /index.php?$args;
        }

        location ~ \.php$ {
            fastcgi_pass wordpress:9000;       # nome do serviço + porta
            fastcgi_index index.php;
            include fastcgi_params;
            fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
        }
    }
}
```

**Porquê:**

- `ssl_protocols TLSv1.2 TLSv1.3` → exigência explícita do subject.
- `fastcgi_pass wordpress:9000` → o NGINX entrega o PHP ao PHP-FPM do outro container.
- `nginx -g "daemon off;"` no entrypoint → o processo tem de ficar em foreground para o
  container não morrer.

---

## 4. Construir, subir e testar

```sh
make            # constrói e sobe
docker ps       # 3 containers: nginx, wordpress, mariadb
docker logs nginx
docker logs wordpress
docker logs mariadb
```

Testes de aceitação:

```sh
curl -k https://login.42.fr          # deve devolver o HTML do WordPress
curl -kI https://login.42.fr         # 200 OK
# testar que TLS 1.0/1.1 são recusados:
openssl s_client -connect login.42.fr:443 -tls1_1   # deve falhar
```

Checklist mental:

- [ ] `https://login.42.fr` abre o WordPress instalado
- [ ] apenas o nginx tem porta publicada
- [ ] `docker volume` aponta para `/home/<login>/data`
- [ ] `make fclean` remove tudo sem deixar lixo
- [ ] passwords só existem no `.env` (nunca nos Dockerfiles)
- [ ] nenhuma imagem oficial (`nginx` / `wordpress` / `mariadb`) é usada diretamente
- [ ] nenhuma tag `latest`

---

## 5. Parte bónus (se quiseres ir mais longe)

| Serviço | Função | O que aprendes |
|---|---|---|
| **Redis** | cache de objetos do WordPress | cache em memória, plugin WP |
| **FTP (vsftpd/pure-ftpd)** | acesso aos ficheiros do site | partilhar o volume com outro container |
| **Static website** | site não-PHP (ex.: currículo) | servir conteúdo estático separado |
| **Adminer** | interface web para a BD | ferramentas de gestão de BD |
| **Portainer** | gestão dos containers | observabilidade |

Cada bónus precisa de **justificação**; não basta existir.

---

## 6. Armadilhas comuns (aponta isto)

1. **PHP-FPM a ouvir em `127.0.0.1`** → o NGINX não o alcança. Usa `0.0.0.0:9000`.
2. **`depends_on` não espera** o serviço estar pronto → faz *wait loop* no entrypoint.
3. **Volumes vazios** → o build pode sobrescrever `/var/www/html`. Instala o core
   **em runtime**, não no Dockerfile.
4. **Permissões** no volume partilhado (nginx lê, wordpress escreve) → acerta `chown`/`chmod`.
5. **Certificado** no caminho errado ou `server_name` sem bater com o domínio.
6. **`docker-compose` (v1) vs `docker compose` (v2)** → usa o v2.
7. **Segredos no Dockerfile** → reprovado.
8. **`latest`** em qualquer `FROM`/`image` → reprovado.
9. **`bind-address` ignorado no Debian**: `/etc/mysql/conf.d/` é lido **antes** de
   `/etc/mysql/mariadb.conf.d/50-server.cnf` (que fixa `127.0.0.1`). Copia o `my.cnf`
   para `/etc/mysql/mariadb.conf.d/99-inception.cnf` para ganhar.
10. **`/var/lib/mysql` pré-inicializado na imagem**: o `apt install mariadb-server`
    deixa o datadir criado no build; num volume novo o *guard* de init salta. Limpa-o
    no Dockerfile (`rm -rf /var/lib/mysql && install -d -o mysql -g mysql /var/lib/mysql`).
11. **Datadir antigo/incompatível no host**: se `/home/<login>/data/mariadb` já tiver
    conteúdo (ex.: de uma tentativa com Alpine), o init também salta. Limpa-o antes de subir.

---

## 7. Resumo do "porquê" (o discurso da defesa)

- **NGINX único entrypoint + TLS**: isola o mundo externo; só um ponto de exposição.
- **PHP-FPM separado do NGINX**: cada container faz uma coisa (responsabilidade única).
- **MariaDB isolada**: a BD nunca é exposta à internet.
- **Volumes no host**: os dados vivem fora do ciclo de vida dos containers.
- **`.env`**: configuração e segredos separados das imagens.
- **Imagens construídas por ti**: compreender a stack em vez de a consumir.
