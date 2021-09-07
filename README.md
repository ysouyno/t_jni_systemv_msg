# t_jni_systemv_msg

## `java` code

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
