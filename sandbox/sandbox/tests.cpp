#include <iostream>
#include <cassert>
#include "vector.h"
#include "unique_ptr.h"

namespace Tests {

void VectorTests()
{
    Core::Vector<int> vector = { 3, 5, 6 };
    assert(!vector.Empty());
    assert(vector.Size() == 3);
    assert(vector.Capacity() == 3);
    assert(vector.Front() == 3);
    assert(vector.Back() == 6);

    vector.PushBack(18);
    assert(vector.Size() == 4);
    assert(vector.Capacity() == 7);
    assert(vector.Back() == 18);

    vector.PopBack();
    assert(vector.Size() == 3);
    assert(vector.Capacity() == 7);
    assert(vector.Back() == 6);

    vector.ShrinkToFit();
    assert(vector.Capacity() == vector.Size());
    assert(!vector.Empty());

    auto data = vector.Data();
    assert(data[0] == 3);

    assert(vector.At(1) == 5);

    bool correctExeption = false;
    try {
        assert(vector.At(vector.Size()));
    } catch (std::out_of_range&) {
        correctExeption = true;
    } catch (...) {
        correctExeption = false;
    }
    assert(correctExeption);

    auto iterator = vector.Begin();
    assert(*iterator == 3);
    assert(*(++iterator) == 5);
    assert(*(--iterator) == 3);

    iterator = vector.End();
    assert(*(--iterator) == vector.Back());
    iterator--;
    assert(*iterator == 5);
    iterator = vector.Begin();
    assert(*(iterator + 2) == 6);
    iterator += 2;
    assert(*iterator == 6);

    assert(vector[0] == vector.Front());
    assert(vector[vector.Size() - 1] == vector.Back());

    vector.Resize(1);
    assert(vector.Size() == 1);
    assert(vector.Capacity() == 3);

    vector.Clear();
    assert(vector.Empty());
    assert(vector.Size() == 0);

    vector.Reserve(3);
    assert(vector.Capacity() == 3);
    assert(vector.Empty());

    vector.PushBack(18);
    assert(vector.Back() == 18);
    assert(vector.Size() == 1);

    Core::Vector<int> moveVector = std::move(vector);
    assert(vector.Empty());
    assert(vector.Capacity() == 0);
    assert(vector.Data() == nullptr);
    assert(!moveVector.Empty());
    assert(moveVector.Back() == 18);
    assert(moveVector.Data()[0] == 18);

    vector = std::move(moveVector);
    assert(!vector.Empty());
    assert(vector.Back() == 18);
    assert(vector.Data()[0] == 18);
    assert(moveVector.Empty());
    assert(moveVector.Capacity() == 0);
    assert(moveVector.Data() == nullptr);
}

void UniquePtrTests()
{
    Core::unique_ptr<int> p1(new int(2));
    Core::unique_ptr<int> p2(nullptr);
    Core::unique_ptr<int> p3;
    assert(std::is_constructible<Core::unique_ptr<int>>::value);
    assert(!std::is_copy_constructible<Core::unique_ptr<int>>::value);
    assert(*p1.get() == 2);
    p1.reset(new int(1));
    assert(*p1.get() == 1);
    p1.release();
    assert(p1.get() == nullptr);
}

}