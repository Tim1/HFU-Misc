package sq;

public class Stack implements Behaelter {
	private Integer[]	elem;
	private int			anz	= 0;

	public Stack() {
		this(10);
	}

	public Stack(final int dim) {
		elem = new Integer[dim];
	}


	@Override
	public boolean insert(final Integer insert) {
		if (isFull())
			return false;

		elem[anz++] = insert;
		return true;
	}

	@Override
	public boolean remove() {
		if (isEmpty())
			return false;

		elem[--anz] = null;
		return true;
	}

	@Override
	public boolean isFull() {
		return anz == elem.length;
	}

	@Override
	public boolean isEmpty() {
		return anz == 0;
	}

	@Override
	public Integer getFirst() {
		return elem[0];
	}

	@Override
	public boolean hasNext() {
		return anz - 1 >= 0;
	}

	@Override
	public Integer getNext() {
		return elem[--anz];
	}

}
