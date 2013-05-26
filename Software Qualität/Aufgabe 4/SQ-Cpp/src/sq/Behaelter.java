package sq;
public interface Behaelter {
	public boolean insert(Integer insert);

	public boolean remove();

	public boolean isFull();

	public boolean isEmpty();

	public Integer getFirst();

	public boolean hasNext();

	public Integer getNext();
}
