#include <iostream>
#include <cassert>
#include "vector.h"
#include "tests.h"
#include "shared_ptr.h"

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

void SharedPtrTests()
{
    //Core::Vector<int> vector = { 3, 5, 6 };
    Core::shared_ptr<int> num; 
    assert(num.get() == nullptr);
    assert(num.use_count() == 0);

    Core::shared_ptr<int> num2 = num;
    assert(num2.use_count() == 0);
    assert(num.use_count() == 0);

    Core::shared_ptr<int> num3(new int(5));
    assert(*num3.get() == 5);
    assert(num3.use_count() == 1);

    Core::shared_ptr<int> num4 = num3;
    assert(*num4.get() == 5);
    assert(num4.use_count() == 2);

    //num = num3;

    //std::shared_ptr<int> sharedReference(new int(5));
    //std::cout << *sharedReference.get() << std::endl;
    ////std::cout << sharedReference.use_count() << std::endl;
    //std::shared_ptr<int> sharedReference2;
    //sharedReference2 = sharedReference;
    //std::cout << *sharedReference2.get() << std::endl;
}

}