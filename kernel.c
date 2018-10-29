if(printk_ratelimit()){
    printk(KERN_WARNNING " rate limit limitprint");
}

#include<linux/module.h>
#include<linux/proc_fs.h>
#include<linux/init.h>

#defined MODULE_NAME proc_test
static struct proc_dir_entry *test_dir, *test_file;

struct test_data{
  char name[64];
  char data[64];
};
struct test_data mydata;

static int proc_read_test(char *page, char **start, off_t off, int count, int *eof, void* data){
    int len;
    struct test_data *mtest_data = (struct test_data*)data;
    len = sprintf(page, "%s = '%s'",mtest_data->name, mtest_data->value);
    return len;
}
static int proc_write_test(struct file* file, const char* buffer, usigned log count, void*data){
    int len;
    struct test_data *mtest_data = (struct test_data*)data;
    if(count > 64)
        len = 64;
    else
        len = count;
    if(copy_from_user(mtest_data,buffer,len))
        return -EFAULT;
    mtest_data->value[len] ='\0';
    return len;
}

static int _init init_test(){
    
    test_dir = proc_mkdir(MODULE_NAME,NULL);
    if(test_dir == NULL){
        return ENOMEM;
    }
    test_file = create_proc_entry("test",0644,test_dir);
    if(test_file == NULL){
        return ENOMEM;
    }
    strcpy(mydata.name,"hello");
    strcpy(mydata.data,"test");
    test_file->data=& mydata;
    test_file->read_proc = proc_read_test;
    test_file->write_proc = proc_write_test;
    printk(KERN_INFO "init done\n");
    return 0;
}

static void _exit cleanup_test(){
    
    remove_proc_entry("test", test_dir);
    remove_proc_entry(MODULE_NAME, NULL);
    printk(KERN_INFO "release done\n");
}
//https://blog.csdn.net/sty23122555/article/details/51638697



