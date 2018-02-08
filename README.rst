http2-push-nginx-module
=======================

.. image:: https://travis-ci.org/ghedo/http2-push-nginx-module.png
  :target: https://travis-ci.org/ghedo/http2-push-nginx-module

**DEPRECATED** NGINX upstream now supports [HTTP/2 server push](http://hg.nginx.org/nginx/rev/641306096f5b)

http2-push-nginx-module_ is an *experimental* and *extremely unstable* NGINX
module that implements HTTP/2 server push.

The module can be used by either specifying what resources to push statically
in the NGINX config file (see static_ example) or by leveraging OpenResty and
Lua's FFI support (see openresty_ example).

.. _http2-push-nginx-module: https://ghedo.github.io/http2-push-nginx-module
.. _static: https://github.com/ghedo/http2-push-nginx-module/tree/master/examples/static
.. _openresty: https://github.com/ghedo/http2-push-nginx-module/tree/master/examples/openresty

Configuration
-------------

http2_server_push
~~~~~~~~~~~~~~~~~

**syntax:** *http2_server_push on | off*

**default:** *http2_server_push off*

**context:** *http, server*

Specifies whether to enable HTTP/2 server push.

http2_push_path
~~~~~~~~~~~~~~~

**syntax:** *http2_push_path <url>*

**context:** *http, server, location*

Specifies a resource that should be pushed.

http2_max_pushed_streams
~~~~~~~~~~~~~~~~~~~~~~~~

**syntax:** *http2_max_pushed_streams <number>*

**default:** *http2_max_pushed_streams 100*

**context:** *http, server*

Specifies the maximum number of resources that will be pushed on a connection.

Building
--------

http2-push-nginx-module is distributed as source code. Build with:

.. code-block:: bash

   # download and unpack NGINX sources
   $ wget 'http://nginx.org/download/nginx-1.12.2.tar.gz'
   $ tar -xzvf nginx-1.12.2.tar.gz
   $ cd nginx-1.12.2/

   # apply required patch to NGINX
   $ patch -p01 < /path/to/http2-push-nginx-module/patches/nginx_1.12.2_http2_server_push.patch

   # configure and build NGINX
   $ ./configure --prefix=/opt/nginx \
         --with-http_ssl_module \
         --with-http_v2_module \
         --add-module=/path/to/http2-push-nginx-module
   $ make

TODO
----

* Honour MAX_CONCURRENT_STREAMS setting from clients
* Write tests (basic, 304 response, CONTINUATION, ...)
* Write example to parse Link headers (in Lua)

Copyright
---------

Copyright (C) 2017 Alessandro Ghedini <alessandro@ghedini.me>

See COPYING_ for the license.

.. _COPYING: https://github.com/ghedo/http2-push-nginx-module/tree/master/COPYING
