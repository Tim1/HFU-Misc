package itsec.a42;

public class Main {
	static String	k	= "00000000";
	static String	x	= "12345678";

	public static void main(final String[] args) {
		// Bob's original hash
		String m = Hash.getHashString(k + x);

		// Oscar
		String x1 = "xxxx";
		String x0 = x + x1;
		String m0 = Hash.getHashString(m + x1);

		// Alice test
		String m1 = Hash.getHashString(k + x0);

		System.out.println("M  - " + Hash.getHexString(m.getBytes()));
		System.out.println("M0 - " + Hash.getHexString(m0.getBytes()));
		System.out.println("M1 - " + Hash.getHexString(m1.getBytes()));
	}
}
