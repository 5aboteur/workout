/*
 * oblivion.c - A simple character device driver with R/W capabilities.
 */

#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/uaccess.h>

#include "oblivion.h"

#define DEVICE_NAME "oblivion"

static int major;
static int minor = 0;

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = device_open,
	.release = device_release,
	.read = device_read,
	.write = device_write
};

// entry & exit funcs

static int __init
kmodule_start(void)
{
	printk(KERN_INFO "Initialize 'oblivion' driver\n");

	major = register_chrdev(0, DEVICE_NAME, &fops);
	if (major < 0) {
		printk(KERN_ALERT "Registering device failed with %d\n", major);
		return major;
	}

	printk(KERN_INFO " ~> Device name: %s\n", DEVICE_NAME);
	printk(KERN_INFO " ~> Major number: %d\n", major);
	printk(KERN_INFO " ~> Minor number: %d\n", minor);

	return 0;
}

static void __exit
kmodule_end(void)
{
	unregister_chrdev(major, DEVICE_NAME);
	printk(KERN_INFO "Module successfully unloaded\n");
}

/* ---------------------------------------------------------------------- */

#define MSGSIZ 256

static char kbuf[MSGSIZ] =
	"'TES IV: Oblivion' is the greatest game of our century!\n";

// R/W handling

static int
device_open(struct inode *inod, struct file *filp)
{
	printk(KERN_INFO " >>> in\n");
	return 0;
}

static int
device_release(struct inode *inod, struct file *filp)
{
	printk(KERN_INFO " <<< out\n");
	return 0;
}

static ssize_t
device_read(struct file *filp, char __user *ubuf, size_t count, loff_t *offp)
{
	ssize_t rbytes, ret;
	size_t kbuf_len;

	// nothing to do
	if (count == 0 || *offp != 0)
		return 0;

	if (ubuf == NULL) {
		printk(KERN_ALERT " 'ubuf' is NULL\n");
		return -EBADMSG;
	}

	kbuf_len = strlen(kbuf);
	rbytes = (kbuf_len < count) ? kbuf_len : count;

	ret = copy_to_user(ubuf, kbuf, rbytes);
	if (ret > 0) {
		printk(KERN_ALERT " failed to copy data to userspace\n");
		return -EFAULT;
	}

	*offp = rbytes;

	printk(KERN_INFO " %zu bytes read;\n returned message from <%s>: %s\n",
		rbytes, DEVICE_NAME, kbuf);

	return rbytes;
}

static ssize_t
device_write(struct file *filp, const char __user *ubuf, size_t count, loff_t *offp)
{
	ssize_t wbytes, ret;

	// nothing to do
	if (count == 0 || *offp != 0)
		return 0;

	if (ubuf == NULL) {
		printk(KERN_ALERT " 'ubuf' is NULL\n");
		return -EBADMSG;
	}

	wbytes = (MSGSIZ < count) ? MSGSIZ : count;

	ret = copy_from_user(kbuf, ubuf, wbytes);
	if (ret > 0) {
		printk(KERN_ALERT " failed to copy data from userspace\n");
		return -EFAULT;
	}

	// make sure that string actually ends
	kbuf[((wbytes == MSGSIZ) ? wbytes - 1 : wbytes)] = '\0';

	printk(KERN_INFO " %zu bytes written;\n returned message from <%s>: %s\n",
		wbytes, DEVICE_NAME, kbuf);

	return wbytes;
}

/* ---------------------------------------------------------------------- */

module_init(kmodule_start);
module_exit(kmodule_end);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("5aboteur");
