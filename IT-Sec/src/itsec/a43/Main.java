package itsec.a43;

import itsec.a42.Hash;

import java.security.MessageDigest;

public class Main {
	public static void main(String[] args) throws Exception {
		MessageDigest md = MessageDigest.getInstance("SHA-1");

		byte[] digest = md.digest("".getBytes());
		// convert the byte to hex format method 2
		String hexString = Hash.getHexString(digest);
		System.out.println("Hex format : " + hexString.toString());
	}
}
