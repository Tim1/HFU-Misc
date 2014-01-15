package itsec.a42;

import java.security.MessageDigest;

public class Main {
	static String k = "00000000000000000000";
	static String x = "12345678901234567890";

	public static void main(final String[] args) throws Exception {
		MessageDigest md = MessageDigest.getInstance("SHA-1");

		// Bob's original hash
		String m = Hash.getHashString(k + x);
		byte[] sm = md.digest(m.getBytes());

		// Oscar
		String x1 = "xxxx";
		String x0 = x + x1;
		String m0 = Hash.getHashString(m + x1);
		byte[] sm0 = md.digest((m + x1).getBytes());

		// Alice test
		String m1 = Hash.getHashString(k + x0);
		byte[] sm1 = md.digest((k + x0).getBytes());

		System.out.println("M  - " + Hash.getHexString(m.getBytes()));
		System.out.println("M0 - " + Hash.getHexString(m0.getBytes()));
		System.out.println("M1 - " + Hash.getHexString(m1.getBytes()));
		
		System.out.println("SM - " + Hash.getHexString(sm));
		System.out.println("SM0- " + Hash.getHexString(sm0));
		System.out.println("SM1- " + Hash.getHexString(sm1));
	}
}
