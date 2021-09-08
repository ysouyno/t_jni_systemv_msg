# t_jni_systemv_msg

## `java`测试代码

``` java
package jni;

public class tmain {
	{
		System.load("/home/ysouyno/mygits/t_jni_systemv_msg/libjni_tmain.so");
	}
	public native void no_args_return();

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		new tmain().no_args_return();
		try {
			Thread.sleep(10000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
```

## 说明

似乎`System V`的`msg`不能满足要求，我需要可以传递动态长度的数据，而服务器端`msgrcv`的第三个参数是个固定值，因为手册上写到：

> The argument msgsz specifies the size in bytes of mtext. The received message shall be truncated to msgsz bytes if it is larger than msgsz and (msgflg & MSG_NOERROR) is non-zero.

测试代码来自我的“[关于第四十六章的练习（一）](https://github.com/ysouyno/study_notes_the_linux_programming_interface/tree/dev#%E5%85%B3%E4%BA%8E%E7%AC%AC%E5%9B%9B%E5%8D%81%E5%85%AD%E7%AB%A0%E7%9A%84%E7%BB%83%E4%B9%A0%E4%B8%80)”，权限回忆了，另还练了下如何写`Makefile`。

``` shellsession
[ysouyno@arch t_jni_systemv_msg]$ ./svmsg_server
seq_num: 5
^C
[ysouyno@arch t_jni_systemv_msg]$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages
0x1aaaaaa1 2          ysouyno    620        0            0

[ysouyno@arch t_jni_systemv_msg]$ ipcrm -Q 0x1aaaaaa1
[ysouyno@arch t_jni_systemv_msg]$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages

[ysouyno@arch t_jni_systemv_msg]$
```
