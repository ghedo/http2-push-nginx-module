http2-push-nginx-module
=======================

.. image:: https://travis-ci.org/ghedo/http2-push-nginx-module.png
  :target: https://travis-ci.org/ghedo/http2-push-nginx-module

http2-push-nginx-module_ is an *experimental* and *extremely unstable* NGINX
module that implements HTTP/2 server push.

.. _http2-push-nginx-module: https://ghedo.github.io/http2-push-nginx-module

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

Building
--------

http2-push-nginx-module is distributed as source code. Build with:

.. code-block:: bash

   # download and unpack NGINX sources
   $ wget 'http://nginx.org/download/nginx-1.11.2.tar.gz'
   $ tar -xzvf nginx-1.11.2.tar.gz
   $ cd nginx-1.11.2/

   # apply required patch to NGINX
   $ patch -p01 < /path/to/http2-push-nginx-module/patches/nginx_1.11.12_http2_server_push.patch

   # configure and build NGINX
   $ ./configure --prefix=/opt/nginx \
         --with-http_ssl_module \
         --with-http_v2_module \
         --add-module=/path/to/http2-push-nginx-module
   $ make

TODO
----

* Honour MAX_CONCURRENT_STREAMS setting from clients
* Clean-up (e.g. do we really need the request context?)
* Write tests (basic, 304 response, CONTINUATION, ...)
* Write example to parse Link headers (in Lua)

Copyright
---------

Copyright (C) 2017 Alessandro Ghedini <alessandro@ghedini.me>

See COPYING_ for the license.

.. _COPYING: https://github.com/ghedo/http2-push-nginx-module/tree/master/COPYING
