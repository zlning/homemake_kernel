#include<linux/init.h>
#include<linux/module.h>

MODULE_LICENSE(" BSD/GPL");

static int hello_init(void){
    
    printk(KERN_ALERT"hello world\n");
    printk(KERN_INFO "The process is \"%s\" (pid %i)\n", current->comm, current->pid);
    return 0;
    
}
static void hello_exit(void){
    
    printk(KERN_ALERT"Goodbye, cruel World!\n");
}
module_init(hello_init);
module_exit(hello_exit);