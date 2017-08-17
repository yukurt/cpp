#include <boost/type_index.hpp>
#include <iostream>
#include <vector>

class Widget
{
public:
    Widget(int x): a(x) {}

private:
    int a;
};

std::vector<Widget> createVec() // factory function
{
    std::vector<Widget> tmp;

    for (int i = 0; i < 10; ++i)
    {
        tmp.push_back(Widget(i));
    }

    return tmp;
}

template<typename T>
void f(const T& param)
{
    using std::cout;
    using boost::typeindex::type_id_with_cvr;

    // show T
    cout << "T = "
        << type_id_with_cvr<T>().pretty_name()
        << '\n';

    // show param's type
    cout << "param = "
        << type_id_with_cvr<decltype(param)>().pretty_name()
        << '\n';
}

int main()
{
    const auto vw = createVec(); // init vw w/factory return

    if (!vw.empty()) {
        f(&vw[0]); // call f
    }

    return 0;
}
