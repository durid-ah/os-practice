cmd_/home/durid/projects/os-practice/01_kernel_module/Module.symvers := sed 's/\.ko$$/\.o/' /home/durid/projects/os-practice/01_kernel_module/modules.order | scripts/mod/modpost -m -a  -o /home/durid/projects/os-practice/01_kernel_module/Module.symvers -e -i Module.symvers   -T -