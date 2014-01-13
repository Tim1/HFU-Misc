package itsec;

public class Hash {
	private final static int	BITSIZE		= 128;
	private final static int	BYTESIZE	= BITSIZE / 8;

	public static byte[] hash(String text) {
		text = padding(text);

		byte[] bytes = text.getBytes();

		byte[] result = new byte[BYTESIZE];
		for (int i = 0; i < BYTESIZE; i++) {
			result[i] = xorByteBlocks(bytes, i);
		}

		print(result);
		return result;
	}

	private static void print(byte[] result) {
		for (int i = 0; i < BYTESIZE; i++) {
			String hex = Integer.toHexString(result[i]);
			if (hex.length() == 1)
				hex = "0" + hex;

			System.out.print(hex + " ");
		}
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
