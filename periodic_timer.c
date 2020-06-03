/* kernel module to create a periodic timer */
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_INFO */
#include <linux/init.h> /* Needed for the macros */
#include <linux/timer.h>
 
int g_time_interval = 10000;
struct timer_list g_timer;
 
void _TimerHandler(unsigned long data)
{
    /*Restarting the timer...*/
    mod_timer( &g_timer, jiffies + msecs_to_jiffies(g_time_interval));
 
    printk(KERN_INFO "Timer Handler called.\n");
}
 
static int __init my_init(void)
{
    printk(KERN_INFO "My module inserted into kernel!!!.\n");
 
    /*Starting the timer.*/
    setup_timer(&g_timer, _TimerHandler, 0);
    mod_timer( &g_timer, jiffies + msecs_to_jiffies(g_time_interval));
 
    return 0;
}
 
static void __exit my_exit(void)
{
    del_timer(&g_timer);
    printk(KERN_INFO "My module exited from kernel!!!\n");
}
 
module_init(my_init);
module_exit(my_exit);


void printll(node *head, int k) {
    if (!head)
        return;
    if (k==0) {
        printf("%d", head->val);
        printll(head->next, k);
    } else {
        printll(head->next, k-1);
        printf("%d", head->val);
    }
 }   


void findfpair(node *root, int s, vector<int> &r) {
    if (!root)
        return;
    findfpair(root->left, s, r);
    umap[root->val] = 1;
    if (umap.count([s-root->val]) > 0) {
        r.push_back(root->val);
        r.push_back(s-root->val);
    }
    findfpair(root->right, s, r);

}

vector<int> findpair(node *root, int s) {
    vector<int> p;
    findfpair(root, s, r);
    return p; 
}

