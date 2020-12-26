/*
 * Copyright (c) 2017, GlobalLogic Ukraine LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by the GlobalLogic.
 * 4. Neither the name of the GlobalLogic nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY GLOBALLOGIC UKRAINE LLC ``AS IS`` AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL GLOBALLOGIC UKRAINE LLC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>

#include <linux/types.h>

#include <linux/ktime.h>
#include <linux/slab.h>

struct head_list {
  struct head_list *next;
  ktime_t time;
};

MODULE_AUTHOR("Serhii Popovych <serhii.popovych@globallogic.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

static struct head_list *head;

static int number = 1;
module_param(number,uint,S_IRUGO);
MODULE_PARM_DESC(number, "The amount of number to print hello world");

static int __init initter(void)
{
  uint i;

  struct head_list *key1, *key2;

  head = kmalloc(sizeof(struct head_list *), GFP_KERNEL);

  key1 = head;

  if(number == 0) {
    printk(KERN_WARNING "The parameter is 0");
  }else if(number >=5 && number <= 10) {
    printk(KERN_WARNING "The parameter is between 5 and 10");
  } 
  BUG_ON(number > 10);

  for(i = 0; i < number; i++){
    key1->next = kmalloc(sizeof(struct head_list), GFP_KERNEL);
    key1->time = ktime_get();
    if (i == 7){
		  key1 = NULL;
	  }
    pr_info("Hello World!");
    key2 = key1;
    key1 = key1->next;
  }

  if (number != 0) {
    kfree(key2->next);
    key2->next = NULL;
  }

  return 0;
}

static void __exit exitter(void)
{
  struct head_list *key;

  while (head != NULL && number != 0) {
    key = head;
    pr_info("Time: %lld", key->time);
    head = key->next;
    kfree(key);
  }
  pr_info("");
}
module_init(initter);
module_exit(exitter);
