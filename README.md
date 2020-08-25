# serc_template_application
This is a Project, to be used as a template application for the [serc](https://github.com/RohanVDvivedi/serc.git) framework

### For setup before first run :
 * you must install [serc](https://github.com/RohanVDvivedi/serc.git) *and its dependencies*.

### For setting up the https server :
 * checkout main source file at src/main.c
 * use appropriate https server run line
 * add ssl certificates (you may use `make ssl_cert` for building self signed certificates)

### For managing your application :

 * #### to update routing 
   * `make routes`
   * this will create a source file "distributer.c" in your src folder, you need to compile it with your application and serc
   * the above point is already taken care of by `make all`, read makefile and read serc source for more information.

 * #### to built self signed ssl certificates and private/public keys (if you want to use https)
   * `make ssl_cert`

 * #### to clean all binaries (this will also delete the distributer.c source)
   * `make clean`

 * #### to build your application
   * `make all`

 * #### to run your application
   * `sudo ./bin/app.out`
