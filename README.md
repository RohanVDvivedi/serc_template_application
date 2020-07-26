# serc_template_application
This is a Project, to be used as a template application for the [serc](https://github.com/RohanVDvivedi/serc.git) framework

All you need to do is :

### For first run :

* **set up necessary configurations in .serc_config folder**
* **set up necessary routing logic in .serc_config folder**
* **set up necessary application logic in src and inc folders**
* git clone https://github.com/RohanVDvivedi/serc.git
* cd serc
* sudo make install

### For https server :

* checkout main source file at src/main.c
* use appropriate https server run line
* add ssl certificates (you may use `make ssl_cert` for building self signed certificates)

### For subsequent run :

* #### to update routing 
  * `make routes`
  * this will create a source file "distributer.c" in your src folder, you need to compile it with your application and serc
  * the above point is already taken care of by `make all`, read makefile and read serc source for more information.

* #### to built self signed ssl certificates and private/public keys (if you want to use https)
  * `make ssl_cert`

* #### to clean all binaries (including serc binaries)
  * `make clean`

* #### to build your application
  * `make all`
