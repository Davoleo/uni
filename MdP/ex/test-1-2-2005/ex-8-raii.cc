void lock(const char*);
void unlock(const char*);
void do_the_job();

class Lock {
private:
	const char* res_name;
public:
	Lock(const char* res_name): res_name(res_name) {
		lock(res_name);
	}

	Lock(const Lock& other) = delete;
	Lock& operator=(const Lock& other) = delete;


	~Lock() noexcept {
		unlock(this->res_name);
	}
};

int main() {
	Lock lock1("lock1");
	Lock lock2("lock2");
	do_the_job();
	return 0;
}