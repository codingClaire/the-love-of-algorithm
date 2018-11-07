template<class E>
class SequenceList
{
protected:
	int count;
	int maxSize;
	E* elems;

	bool Full();
	void Init(int size);

public:
	SequenceList(int size = DEFAULT_SIZE);
	virtual ~SequenceList();
	int Length() const;
	bool Empty() const;
	void Clear();
	void Traverse(void(*Visit)(E &));
	StatusCode GetElem(int position, E &e) const;
	StatusCode SetElem(int position, E &e) const;
	StatusCode Delete(int position, E &e);
	StatusCode Insert(int position, const E &e);
	SequenceList(const SequenceList<E> &copy);
	SequenceList<E> &operator=(const SequenceList<E> &copy);
};