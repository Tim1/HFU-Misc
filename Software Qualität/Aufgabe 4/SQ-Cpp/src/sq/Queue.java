package sq;

public class Queue implements Behaelter {
	private Integer[]	elem;
	private int			posInsert	= 0;
	private int			posRemove	= 0;
	private int			anz			= 0;

	private int			pos			= 0;
	private boolean		first		= true;


	public Queue(final int dim) {
		elem = new Integer[dim];
	}

	public Queue() {
		this(10);
	}

	@Override
	public boolean insert(final Integer insert) {
		if (isFull())
			return false;

		elem[posInsert] = insert;
		anz++;
		posInsert = (posInsert + 1) % elem.length;
		pos = posRemove;
		first = true;

		return true;
	}

	@Override
	public boolean remove() {
		if (isEmpty())
			return false;

		elem[posRemove] = null;
		anz--;
		posRemove = (posRemove + 1) % elem.length;
		pos = posRemove;
		first = true;

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
		return elem[posRemove];
	}

	@Override
	public boolean hasNext() {
		return (pos != posInsert || first) && elem[pos] != null;
	}

	@Override
	public Integer getNext() {
		Integer result = elem[pos];

		pos = (pos + 1) % elem.length;
		first = false;

		return result;
	}

}
