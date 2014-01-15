package itsec.a42;

public class Hash {
	private final static int	BITSIZE		= 64;
	private final static int	BYTESIZE	= BITSIZE / 8;

	public static byte[] getHashBytes(String text) {
		text = padding(text);

		byte[] bytes = text.getBytes();

		byte[] result = new byte[BYTESIZE];
		for (int i = 0; i < BYTESIZE; i++) {
			result[i] = xorByteBlocks(bytes, i);
		}

		// System.out.println(getHexString(result));
		return result;
	}

	public static String getHashString(String text) {
		return new String(getHashBytes(text));
	}

	public static String getHexString(byte[] result) {
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < result.length; i++) {
			String hex = Integer.toHexString(result[i] & 0xFF);
			if (hex.length() == 1)
				sb.append("0");

			sb.append(hex).append(":");
		}
		return sb.substring(0, sb.length() - 1);
	}

	private static byte xorByteBlocks(byte[] bytes, int blockMod) {
		byte result = 0;
		for (int i = blockMod; i < bytes.length; i += BYTESIZE) {
			byte current = bytes[i];
			result ^= current;
		}

		return result;
	}

	private static String padding(String text) {
		int length = text.length();
		int mod = length % BYTESIZE;

		if (mod != 0) {
			int charToAdd = BYTESIZE - mod;
			StringBuffer buf = new StringBuffer();
			for (int i = 0; i < charToAdd; i++)
				buf.append(" ");

			text += buf.toString();
		}
		return text;
	}
}
