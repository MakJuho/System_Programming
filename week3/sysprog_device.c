#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>


static char *buffer = NULL;
static int sum = 0;

// device 연다
int sysprog_device_open(struct inode *inode, struct file *filp){
	printk(KERN_ALERT "sysprog_device open function called\n");
	return 0;
}

int sysprog_device_release(struct inode *inode, struct file *filp){
	printk(KERN_ALERT "sysprog_device release function called\n");
	return 0;
}

ssize_t sysprog_device_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos){
	int tmp;
	printk(KERN_ALERT "sysprog_device write function called\n");
	copy_from_user(buffer, buf, 1024);
	printk(KERN_ALERT "s_write_buffer:%s\n",buffer);
	kstrtouint(buffer,10,&tmp);
	
	sum = sum + tmp;
	printk(KERN_ALERT "write_sum:%d\n", sum);
	// sum 값 구하기
	//tmp = kstrtol(buffer,&ptr ,10);
	//sum = sum+buffer;
	// modified contents.
	
	//sum = sum + kstrtol(buf);
	

	return count;

}

ssize_t sysprog_device_read(struct file *filp, char *buf, size_t count, loff_t *f_pos){
	printk(KERN_ALERT "sysprog_device read function called\n");
	// buffer에 sum 대입
	//strcpy(buffer,itoa(sum));
	printk(KERN_ALERT "read_sum:%d\n", sum);
	sprintf(buffer, "%d", sum);
	copy_to_user(buf, buffer, 1024);
	return count;
}

static struct file_operations sys_fops ={
	.owner = THIS_MODULE,
	.read = sysprog_device_read,
	.write = sysprog_device_write,
	.open = sysprog_device_open,
	.release = sysprog_device_release
};

int __init sysprog_device_init(void){
	if(register_chrdev(240, "sysprog_device", &sys_fops) < 0)
		printk(KERN_ALERT "[sysprog] driver init failed\n");
	else
		printk(KERN_ALERT "[sysprog] driver init successful\n");

	buffer = (char*)kmalloc(1024, GFP_KERNEL);
	if(buffer != NULL)
		memset(buffer, 0, 1024);

	return 0;

}

void __exit sysprog_device_exit(void){
	unregister_chrdev(240, "sysprog_device");
	printk(KERN_ALERT "[sysprog] driver cleanup\n");
	kfree(buffer);
}



// 파라미터에 function pointer가 들어간다.
// init은 code가 시작하는 주소
module_init(sysprog_device_init);
// exit
module_exit(sysprog_device_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Juho Woo");
MODULE_DESCRIPTION("This is the hello world example for device driver in system programming lecture");



