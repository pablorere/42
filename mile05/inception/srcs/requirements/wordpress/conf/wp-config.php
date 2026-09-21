<?php
define('DB_NAME',     getenv('MYSQL_DATABASE'));
define('DB_USER',     getenv('MYSQL_USER'));
define('DB_PASSWORD', getenv('MYSQL_PASSWORD'));
define('DB_HOST',     'mariadb:3306');
define('DB_CHARSET',  'utf8');
define('DB_COLLATE',  '');

define('WP_HOME',    'https://' . getenv('DOMAIN_NAME'));
define('WP_SITEURL', 'https://' . getenv('DOMAIN_NAME'));

define('AUTH_KEY',         'JuQP4lUN>md{aWBa!SaZ0fC=l$!|5c-J-}o/$,^h|=OmOw>+mRbiGdl94HVtH[0F');
define('SECURE_AUTH_KEY',  'yrR:Q}hcFMU+54}e>]4k%KEC6z$p[@e!0#ChHnd,y-2LAa(fNojSJ8i5UC*ta|=a');
define('LOGGED_IN_KEY',    'fG]r/A,A3UEkU8]kb7CACS5c9PJSH^WDUDnuRYM0Y)gJDNZ,WZV|&dwvE#T%A)/D');
define('NONCE_KEY',        'CB8k9m:>%zC8_t]tK?sx7J3y[!+wN6Qnf|YhR&^pN0pXV81IR1Vo|<dA7FEff1#D');
define('AUTH_SALT',        'W^:X%,3iJtYqJa$<D3b2A)qs)([B2Zu(vbWv6L9S{/b5}Ea6zhkU50trSW{{lGnH');
define('SECURE_AUTH_SALT', 'elsOmkur2qIh05I+y=$Pk:vz#KKr<O>_V4bSDE.mFVo/I-r3Qw&I!begwMYbnHlO');
define('LOGGED_IN_SALT',   'QgnA@.j^cz|;:xe4LDkZjGvFSfHqcLX.?j+_PNwM@E,7nnpt%*{}?ZN74tQ|ltbi');
define('NONCE_SALT',       'TH6upd7vv|WOnsKXQE<<MSi]28*9S=ln)}VbEj!=nX,is)6lMF1[rKG>dSA1J.E}');

$table_prefix = 'wp_';
if (!defined('ABSPATH')) define('ABSPATH', __DIR__ . '/');
require_once ABSPATH . 'wp-settings.php';
