import <iostream>;

export module Module;

export{
	void MyFunc();
	void f2();
}

export namespace TestNampespace {
	// ....
}

export class Test
{
public:
	std::string f();
private:
	int var1 {0};
	std::string var2 {""};
};