package sq;

public class Main {
	public static void main(final String[] args) {
		Behaelter behalter = new Queue(4);

		behalter.insert(0);
		behalter.insert(1);
		behalter.insert(2);

		System.out.println(behalter.hasNext() + " = " + behalter.getNext());
		System.out.println(behalter.hasNext() + " = " + behalter.getNext());
		System.out.println(behalter.hasNext() + " = " + behalter.getNext());
		System.out.println(behalter.hasNext());

		behalter.remove();
		behalter.remove();
		behalter.remove();

		behalter.insert(10);
		behalter.insert(20);
		behalter.insert(30);
		behalter.insert(40);

		System.out.println(behalter.hasNext() + " = " + behalter.getNext());
		System.out.println(behalter.hasNext() + " = " + behalter.getNext());
		System.out.println(behalter.hasNext() + " = " + behalter.getNext());
		System.out.println(behalter.hasNext() + " = " + behalter.getNext());
		System.out.println(behalter.hasNext());
	}
}
