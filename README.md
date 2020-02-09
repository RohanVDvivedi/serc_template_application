# serc_template_application
This is a Project, to be used as a template application for the serc framework

All you need to do is :

### For first run :

mkdir .serc_framework
cd .serc_framework
git clone https://github.com/RohanVDvivedi/serc.git
cd ..
make routes clean all

### For subsequent run :

* #### to update serc framework
  * make update_serc

* #### to update routing 
  * make routes

* #### to clean all binaries (including serc binaries)
  * make clean

* #### to build application
  * make all
