class char_vec
{
	public:
		class generic_exception {};
		static char_vec *new_char_vec(int s);
		char &operator[](int i) { return element[i]; }
	
	private:
		int sz;
		char element[1];
}

static char_vec *char_vec::new_char_vec(int s)
{
	if (s < 0)
		throw generic_exception{};
	char *vec = new char[s];
	
}